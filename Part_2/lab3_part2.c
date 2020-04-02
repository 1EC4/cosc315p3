#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>

#define filepath "lab3_part2_input.txt"
#define int32size sizeof(__int32_t)
#define charsize sizeof(char)
#define FS_SUCCESS 0
#define FS_GENERIC_ERROR 1
#define FS_SPACE_ERROR 2
#define FS_ARG_ERROR 3

// Structure for inodes
struct inode {
    char name[9]; // 8 bytes + 1 null terminator byte
    __int32_t size;
    __int32_t blockPointers[8];
    __int32_t used;
};

// Structure for blocks.
// Structure is used to improve readibility.
struct block {
    char data[1024];
};

// Declare helper functions
int streq(char* s1, char* s2);
int myFileSystem(char* diskName);
int saveFileSystem(char* diskName);
int create_file(char name[8], int size);
int delete_file(char name[8]);
int list_files(void);
int read_file(char name[8], int blockNum, char buf[1024]);
int write_file(char name[8], int blockNum, char buf[1024]);

// Super Block Information
char fBlock[128]; // Free Block List
struct inode inodes[16]; // List of inodes
// Remaining 127 blocks
struct block blocks[128];
// Name of filesystem
char disk[20];

// Main function
int main(int argc, char *argv[]) {
    srand(time(0));
    // Open input file
    FILE *fp;
    fp = fopen(filepath, "r");
    char buff[20];
    fgets(buff, 20, fp);
    // Extract disk name from buffer
    // ie: strips chracters like \n, \r, etc
    for (int i = 0; i < 20; i++){
        /* Valid ASCII Characters in disk name:
           48-57:  0-9
           65-90:  A-Z
           97-122: a-z
        */
        int chr = (int)buff[i];
        if ((
                chr > 47 && chr < 58
            ) || (
                chr > 64 && chr < 91
            ) || (
                chr > 96 && chr < 123
            ))
        {
            disk[i] = chr;
        } else {
            disk[i] = 0;
            break;
        }
    }

    printf("File System:\t%s\n", disk);
    
    if (myFileSystem(disk) == EXIT_FAILURE){
        printf("Something went wrong while loading the filesystem. Please ensure the disk is properly formatted.\n");
        return EXIT_FAILURE;
    } else {
        printf("Successfully loaded filesystem.\n");
    }

    printf("----------------------------------\n");

    // Read remaining lines of input file
    while(fgets(buff, 20, fp) != NULL) {

        // Tokenize string using " " space as delimiter
        char *command = strtok(buff, " ");          // First token
        char* file_name;                            // Second token (initialized in switch statement)
        int size_block;                             // Third token (initialized in switch statement)
        char buffer[1024];
        for (int i = 0; i < 1024; i++){
            int j = rand() % 64;
            if (j == 0){
                buffer[i] = 10;
            } else if (j == 1){
                buffer[i] = 32;
            } else if (j >= 2 && j <= 11){
                buffer[i] = j + 46;
            } else if (j >= 12 && j <= 37){
                buffer[i] = j + 53;
            } else {
                buffer[i] = j + 59;
            }
        }

        // Choose action based on first character (command) from input
        int fs_response;
        switch (*command) {
            case 'C': // DOne
                file_name = strtok(NULL, " ");        // Second token
                size_block = atoi(strtok(NULL, " "));   // Third token
                printf("Creating %s (%d) - ", file_name, size_block);
                fs_response = create_file(file_name, size_block);
                break;
            case 'D': // Done
                file_name = strtok(NULL, " ");        // Second token
                char actual_fn[8];
                for (int i = 0; i < 9; i++){
                    /* Valid ASCII Characters in file name:
                    46    : .
                    48-57:  0-9
                    65-90:  A-Z
                    97-122: a-z
                    */
                    int chr = (int)file_name[i];
                    if (chr == 46 || (
                            chr > 47 && chr < 58
                        ) || (
                            chr > 64 && chr < 91
                        ) || (
                            chr > 96 && chr < 123
                        ))
                    {
                        actual_fn[i] = chr;
                    } else {
                        actual_fn[i] = 0;
                        break;
                    }
                }
                printf("Deleting %s - ", actual_fn);
                fs_response = delete_file(actual_fn);
                break;
            case 'L':  // Done
                printf("Listing files\n");
                fs_response = list_files();
                break;
            case 'R':
                file_name = strtok(NULL, " ");        // Second token
                size_block = atoi(strtok(NULL, " "));   // Third token
                printf("Reading %s (%d) - ", file_name, size_block);
                fs_response = read_file(file_name, size_block, buffer);
                break;
            case 'W':
                file_name = strtok(NULL, " ");        // Second token
                size_block = atoi(strtok(NULL, " "));   // Third token
                printf("Writing %s (%d) - ", file_name, size_block);
                fs_response = write_file(file_name, size_block, buffer);
                break;
            default:
                fs_response = FS_GENERIC_ERROR;
                break;
        }

        switch(fs_response){
            case FS_SUCCESS:
                printf("Success\n");
                break;
            case FS_GENERIC_ERROR:
                printf("Something went wrong\n");
                break;
            case FS_SPACE_ERROR:
                printf("Not enough space on the disk\n");
                break;
            case FS_ARG_ERROR:
                printf("Invalid arguments\n");
                break;
        }

        printf("----------START BUFFER----------------\n\n\n%s\n\n------------END BUFFER----------------\n", buffer);
    }

    // Close input file
    fclose(fp);

    return EXIT_SUCCESS;
}

// Returns true if and only if s1 == s2
int streq(char* s1, char* s2){
    if ( sizeof(s1) != sizeof(s2))
        return 0;

    for(int i = 0; i < sizeof(s1); i++){
        if (s1[i] != s2[i]){
            return 0;
        }
    }
    return 1;
}


// Open the file with name diskName
int myFileSystem(char* diskName) {

    // Reference integer for disk file
    int disk;
    // Buffer array for reading from disk file
    char buffer[1024];

    // Open disk file
    disk = open(diskName, O_RDONLY);
    if (disk == -1){ // Runs if there is an error when opening the disk file
        return EXIT_FAILURE;
    }

    // Variable to keep track of bit position in buffer array
    int bit_pos = 0;
    // Read Block 0 (Superblock)
    read(disk, buffer, 1024);
    // Copy the first 128 bytes into the free block list array
    memcpy(fBlock, &buffer[bit_pos], 128 * charsize);
    bit_pos += 128 * charsize;
    // Copy data from buffer into the 16 inodes
    for (int i = 0; i < 16; i++){
        // Copy the name from the buffer array
        memcpy(inodes[i].name, &buffer[bit_pos], 8 * charsize);
        bit_pos += 8 * charsize;
        // And append a null byte to the end
        inodes[i].name[8] = 0;

        // Buffer variable for 32-bit integers
        char cpBuf[int32size];
        // Copy size information into integer buffer
        memcpy(cpBuf, &buffer[bit_pos], int32size);
        // Convert integer buffer into 32-bit integer and store result in inode size variable
        sscanf(cpBuf, "%d", &inodes[i].size);
        bit_pos += int32size;

        // For each block pointer
        for(int j = 0; j < 8; j++){
            // Copy block pointer information into integer buffer
            memcpy(cpBuf, &buffer[bit_pos], int32size);
            // Convert integer buffer into 32-bit integer and store result in block pointer array
            sscanf(cpBuf, "%d", &inodes[i].blockPointers[j]);
            bit_pos += int32size;
        }

        // Copy used information into integer buffer
        memcpy(cpBuf, &buffer[bit_pos], int32size);
        // Convert integer buffer into 32-bit integer and store result in inode used variable
        sscanf(cpBuf, "%d", &inodes[i].used);
        bit_pos += int32size;
    }

    // Read the remaining 127 blocks
    for(int i = 0; i < 127; i++){
        // Read 1 KB of data from disk
        read(disk, buffer, 1024);
        // Copy data from buffer into the corresponding block
        memcpy(blocks[i].data, &buffer[0], 1024 * charsize);
    }

    // Close disk
    close(disk);

    return EXIT_SUCCESS;
}

int saveFileSystem(char* diskName){
    /*
    int32_t x=someValue;
    char *ptr = (char*)&x;
    char *msg = new char[5];
    for(int i=0;i<4;++i, ++ptr)
        msg[i] = *ptr;
    */


    int file = open(diskName, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    if (write(file, fBlock, 128) < 0)
        return FS_GENERIC_ERROR;

    for (int i = 0; i < 16; i++){
        char fname[8];
        memcpy(fname, &inodes[i].name[0], 8);
        if (write(file, fname, 8) < 0)
            return FS_GENERIC_ERROR;
        
        char *ptr = (char*)&inodes[i].size;
        char size[int32size];
        for (int i = 0; i < int32size; i++, ptr++){
            size[i] = *ptr;
        }

        if (write(file, size, int32size) < 0)
            return FS_GENERIC_ERROR;

        for (int j = 0; j < 8; j++){
            ptr = (char*)&inodes[i].blockPointers[j];
            char bPointer[int32size];
            for (int i = 0; i < int32size; i++, ptr++){
                bPointer[i] = *ptr;
            }
            if (write(file, bPointer, int32size) < 0)
                return FS_GENERIC_ERROR;
        }

        ptr = (char*)&inodes[i].used;
        char used[int32size];
        for (int i = 0; i < int32size; i++, ptr++){
            used[i] = *ptr;
        }

        if (write(file, used, int32size) < 0)
            return FS_GENERIC_ERROR;
    }

    char emptyBuffer[128];
    for (int i = 0; i < 128; i++){
        emptyBuffer[i] = 0;
    }

    if (write(file, emptyBuffer, 128) < 0)
        return FS_GENERIC_ERROR;

    for (int i = 1; i < 128; i++){
        if (write(file, blocks[i].data, 1024) < 0)
            return FS_GENERIC_ERROR;
    }

    close(file);

    return FS_SUCCESS;
}


// Create a file with the specified name and size (number of blocks).
// Assume the file size is specified at file creation time and the file does not grow or shrink from this point on.
int create_file(char name[8], int size) {
    // Step 1: Look for a free inode by searching the collection of objects representing inodes within the super block object.

    if (size < 0 && size > 8){
        return FS_ARG_ERROR;
    }

    int inode = -1;
    for (int i = 0; i < 16; i++){
        if (inodes[i].used == 0){
            inode = i;
            break;
        }
    }

    if (inode == -1){
        return FS_SPACE_ERROR;
    }

    for (int i = 0; i < 16; i++){
        if (inodes[i].used == 1
        && streq(inodes[i].name, name) == 1){
            return FS_ARG_ERROR;
        }
    }

    // Step 2: Look for a number of free blocks equal to the size variable passed to this method. If not enough free blocks exist, then return an error.

    int begin_block = -1;
    for(int i = 0; i < 128; i++){
        int sufficient_space = 1;
        for(int j = 0; j < size; j++){
            if (fBlock[i + j] == 1){
                i = i + j;
                sufficient_space = 0;
                break;
            }
        }
        if (sufficient_space == 1){
            begin_block = i;
            break;
        }
    }

    if (begin_block == -1){
        return FS_SPACE_ERROR;
    }

    // Step 3: Now we know we have an inode and free blocks necessary to create the file. So mark the inode and blocks as used and update the rest of the information in the inode.

    memcpy(inodes[inode].name, &name[0], 8);
    inodes[inode].name[8] = 0;
    inodes[inode].used = 1;
    inodes[inode].size = size;
    for(int i = 0; i < size; i++){
        fBlock[begin_block + i] = 1;
        inodes[inode].blockPointers[i] = begin_block + 1;
    }

    // TODO Step 4: Write the entire super block back to disk. An easy way to do this is to seek to the beginning of the disk and write the 1KB memory chunk.

    if (saveFileSystem(disk) != FS_SUCCESS){
        return FS_GENERIC_ERROR;
    }

    // If no free inode exists, then return an error. Also make sure that no other file in use with the same name exists.
    return FS_SUCCESS;
}


// Delete the file with the specified name.
int delete_file(char name[8]) {
    // Step 1: Look for an inode that is in use with given name by searching the collection of objects representing inodes within the super block object.
    int inode = -1;
    for (int i = 0; i < 16; i++){
        if (streq(inodes[i].name, name) == 1){
            inode = i;
            break;
        }
    }
    // Step 2: Free blocks of the file being deleted by the object representing the free block list in the super block object.

    for(int i = 0; i < inodes[inode].size; i++){
        fBlock[inodes[inode].blockPointers[i]] = 0;
    }

    // Step 3: Mark inode as free.

    inodes[inode].used = 0;

    // Step 4: Write the entire super block back to disk.

    if (saveFileSystem(disk) != FS_SUCCESS){
        return FS_GENERIC_ERROR;
    }

    // If it does not exist, then return an error.
    return FS_SUCCESS;
}


// List the names of all files in the file system and their sizes.
int list_files(void) { 
    // Step 1: Print the name and size fields of all used inodes.

    printf("%s\n", disk);
    for(int i = 0; i < 16; i++){
        if (inodes[i].used == 1){
            printf("\t%s\t\t%dKB\n", inodes[i].name, inodes[i].size);
        }
    }
    printf("\n");
    return FS_SUCCESS;
}


// Read the specified block from this file into the specified buffer. blockNum can range from 0 to 7.
int read_file(char name[8], int blockNum, char buf[1024]) {
    // Step 1: Locate the inode for this file as in Step 1 of delete.

    int inode = -1;
    for (int i = 0; i < 16; i++){
        if (streq(inodes[i].name, name) == 1){
            inode = i;
            break;
        }
    }

    // Step 2: Seek to blockPointers[blockNum] and read the block from disk to buf.
    
    memcpy(buf, &blocks[inodes[inode].blockPointers[blockNum]].data[0], 1024);

    // Return an error if and when appropriate. For instance, make sure BlockNum does not exceed size-1.
    return FS_SUCCESS;
}


// Write the data in the buffer to the specified block in the specified file. 
int write_file(char name[8], int blockNum, char buf[1024]) {
    // Step 1: Locate the inode for this file as in Step 1 of delete.

    int inode = -1;
    for (int i = 0; i < 16; i++){
        if (streq(inodes[i].name, name) == 1){
            inode = i;
            break;
        }
    }

    // Step 2: Seek to blockPointers[blockNum] and write buf to disk.

    memcpy(blocks[inodes[inode].blockPointers[blockNum]].data, &buf[0], 1024);
    if (saveFileSystem(disk) != FS_SUCCESS){
        return FS_GENERIC_ERROR;
    }

    // Return an error if and when appropriate.
    return FS_SUCCESS;
}
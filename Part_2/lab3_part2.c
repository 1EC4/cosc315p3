#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

#define filepath "lab3_part2_input.txt"
#define disk_name "disk0"
#define int32size sizeof(__int32_t)
#define charsize sizeof(char)

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
int myFileSystem(char* diskName);
int create_file(char name[8], int size);
int delete_file(char name[8]);
int list_files(void);
int read_file(char name[8], int blockNum, char buf[1024]);
int write_file(char name[8], int blockNum, char buf[1024]);

// Super Block Information
char fBlock[128]; // Free Block List
struct inode inodes[16]; // List of inodes
// Remaining 127 blocks
struct block blocks[127];

// Main function
int main(int argc, char *argv[]) {
    
    myFileSystem(disk_name); // Load filesystem

    return EXIT_SUCCESS;

    // Open input file
    FILE *fp;
    fp = fopen(filepath, "r");
    char buff[20];

    fgets(buff, 20, fp);
    printf("File System:\t%s", buff);
    printf("----------------------\n");

    // Read remaining lines of input file
    while(fgets(buff, 20, fp) != NULL) {

        // Tokenize string using " " space as delimiter
        char *command = strtok(buff, " ");          // First token
        char *file_name = strtok(NULL, " ");        // Second token
        int size_block = atoi(strtok(NULL, " "));   // Third token
        char *buffer[1024];

        // Choose action based on first character (command) from input
        switch (*command) {
            case 'C':
                printf("Creating %s (%d)\n", file_name, size_block);
                create_file(file_name, size_block);
                break;
            case 'D':
                printf("Deleting %s", file_name);
                delete_file(file_name);
                break;
            case 'L':
                printf("Listing files\n");
                list_files();
                break;
            case 'R':
                printf("Reading %s (%d)\n", file_name, size_block);
                read_file(file_name, size_block, buffer);
                break;
            case 'W':
                printf("Writing %s (%d)\n", file_name, size_block);
                write_file(file_name, size_block, buffer);
                break;
            default:
                printf("Invalid Command\n");
                break;
        }
    }

    // Close input file
    fclose(fp);

    return EXIT_SUCCESS;
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
        printf("Could not open %s.\n", diskName);
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


// Create a file with the specified name and size (number of blocks).
// Assume the file size is specified at file creation time and the file does not grow or shrink from this point on.
int create_file(char name[8], int size) {
    // Step 1: Look for a free inode by searching the collection of objects representing inodes within the super block object.

    // Step 2: Look for a number of free blocks equal to the size variable passed to this method. If not enough free blocks exist, then return an error.

    // Step 3: Now we know we have an inode and free blocks necessary to create the file. So mark the inode and blocks as used and update the rest of the information in the inode.

    // Step 4: Write the entire super block back to disk. An easy way to do this is to seek to the beginning of the disk and write the 1KB memory chunk.



    // If no free inode exists, then return an error. Also make sure that no other file in use with the same name exists.
    return EXIT_SUCCESS;
}


// Delete the file with the specified name.
int delete_file(char name[8]) {
    // Step 1: Look for an inode that is in use with given name by searching the collection of objects representing inodes within the super block object.

    // Step 2: Free blocks of the file being deleted by the object representing the free block list in the super block object.

    // Step 3: Mark inode as free.

    // Step 4: Write the entire super block back to disk.



    // If it does not exist, then return an error.
    return EXIT_SUCCESS;
}


// List the names of all files in the file system and their sizes.
int list_files(void) { 
    // Step 1: Print the name and size fields of all used inodes.



    return EXIT_SUCCESS;
}


// Read the specified block from this file into the specified buffer. blockNum can range from 0 to 7.
int read_file(char name[8], int blockNum, char buf[1024]) {
    // Step 1: Locate the inode for this file as in Step 1 of delete.

    // Step 2: Seek to blockPointers[blockNum] and read the block from disk to buf.
    


    // Return an error if and when appropriate. For instance, make sure BlockNum does not exceed size-1.
    return EXIT_SUCCESS;
}


// Write the data in the buffer to the specified block in the specified file. 
int write_file(char name[8], int blockNum, char buf[1024]) {
    // Step 1: Locate the inode for this file as in Step 1 of delete.

    // Step 2: Seek to blockPointers[blockNum] and write buf to disk.



    // Return an error if and when appropriate.
    return EXIT_SUCCESS;
}
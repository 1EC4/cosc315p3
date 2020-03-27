#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define filepath "lab3_part2_input.txt"

// Declare helper functions
int myFileSystem(char* diskName);
int create_file(char name[8], int size);
int delete_file(char name[8]);
int list_files(void);
int read_file(char name[8], int blockNum, char buf[1024]);
int write_file(char name[8], int blockNum, char buf[1024]);

// Main function
int main(int argc, char *argv[]) {
    // Open input file
    FILE *fp;
    fp = fopen(filepath, "r");
    char buff[20];

    fgets(buff, 20, fp);
    printf("File System:\t%s", buff);
    printf("----------------------\n");

    // Read remaining lines of input file
    while(fgets(buff, 20, fp) != NULL) {

        // Declare variables
        char *command;
        char *file_name;
        int file_size;
        int block_num;
        char *buffer[1024];

        // Choose action based on first character (command) from input
        command = strtok(buff, " ");
        switch (*command) {
            case 'C':
                file_name = strtok(NULL, " ");
                file_size = atoi(strtok(NULL, " "));
                printf("Creating %s (%d)\n", file_name, file_size);
                create_file(file_name, file_size);
                break;
            case 'D':
                file_name = strtok(NULL, " ");
                printf("Deleting %s", file_name);
                delete_file(file_name);
                break;
            case 'L':
                printf("Listing files\n");
                list_files();
                break;
            case 'R':
                file_name = strtok(NULL, " ");
                block_num = atoi(strtok(NULL, " "));
                printf("Reading %s (%d)\n", file_name, block_num);
                read_file(file_name, block_num, buffer);
                break;
            case 'W':
                file_name = strtok(NULL, " ");
                block_num = atoi(strtok(NULL, " "));
                printf("Writing %s (%d)\n", file_name, block_num);
                write_file(file_name, block_num, buffer);
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
    // Read the first 1KB and parse it to structs/objecs representing the super block.
    // An easy way to work with the 1KB memory chunk is to move a pointer to aposition where a struct/object begins.
    // You can use the sizeof operator to help cleanly determine the position.
    // Next, cast the pointer to a pointer of the struct/object type.
    // Be sure to close the file in a destructor or otherwise before the process exits.


    
    return EXIT_SUCCESS;
}

// Create a file with this name and this size high level pseudo code for creating a new file
int create_file(char name[8], int size) {
    // Step 1: Look for a free inode by searching the collection of objects representing inodes within the super block object.

    // Step 2: Look for a number of free blocks equal to the size variable passed to this method. If not enough free blocks exist, then return an error.

    // Step 3: Now we know we have an inode and free blocks necessary to create the file. So mark the inode and blocks as used and update the rest of the information in the inode.

    // Step 4: Write the entire super block back to disk. An easy way to do this is to seek to the beginning of the disk and write the 1KB memory chunk.



    // If no free inode exists, then return an error. Also make sure that no other file in use with the same name exists.
    return EXIT_SUCCESS;
}

// Delete the file with this name
int delete_file(char name[8]) {
    // Step 1: Look for an inode that is in use with given name by searching the collection of objects representing inodes within the super block object.

    // Step 2: Free blocks of the file being deleted by the object representing the free block list in the super block object.

    // Step 3: Mark inode as free.

    // Step 4: Write the entire super block back to disk.



    // If it does not exist, then return an error.
    return EXIT_SUCCESS;
}


// List names of all files on disk
int list_files(void) { 
    // Step 1: Print the name and size fields of all used inodes.



    return EXIT_SUCCESS;
}


// Read this block from this file
int read_file(char name[8], int blockNum, char buf[1024]) {
    // Step 1: Locate the inode for this file as in Step 1 of delete.

    // Step 2: Seek to blockPointers[blockNum] and read the block from disk to buf.
    


    // Return an error if and when appropriate. For instance, make sure BlockNum does not exceed size-1.
    return EXIT_SUCCESS;
}


// Write this block to this file
int write_file(char name[8], int blockNum, char buf[1024]) {
    // Step 1: Locate the inode for this file as in Step 1 of delete.

    // Step 2: Seek to blockPointers[blockNum] and write buf to disk.



    // Return an error if and when appropriate.
    return EXIT_SUCCESS;
}
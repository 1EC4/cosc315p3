#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define filepath "lab3_part1_input.txt"
unsigned int virtualAddress;

int main(int argc, char *argv[]) {
    // Open input file
    FILE *fp;
    fp = fopen(filepath, "r");
    char buff[10];

    // Read first line of input file (n)
    fgets(buff, 10, fp);
    int n = atoi(buff);
    printf("n = %d\n", n);

    // Read second line of input file (m)
    fgets(buff, 10, fp);
    int m = atoi(buff);
    printf("m = %d\n", m);

    // Calculate limit
    int limit = ( 1 << n ) - 1;
    
    // Read remaining lines of input file (v1, v2, v3, ...)
    while(fgets(buff, 10, fp) != NULL) {
        // Determine virtual address
        virtualAddress = atoi(buff);

        // Calculate page number using bit-wise operation (n / 2^n)
        int page = virtualAddress >> n;

        // Calculate offset using bit-wise operation (m % 2^n)
        int offset = virtualAddress & limit;
        // Print virtual address, page number, and offset
        printf("virtual address %d is in page number %d and offset %d\n", virtualAddress, page, offset);
    }

    // Close input file
    fclose(fp);

    return EXIT_SUCCESS; 
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define filepath "lab3_part2_input.txt"
unsigned int virtualAddress;

int main(int argc, char *argv[]) {
    // Open input file
    FILE *fp;
    fp = fopen(filepath, "r");
    char buff[20];
    
    // Read remaining lines of input file
    while(fgets(buff, 20, fp) != NULL) {

        // Print line to console
        printf("%s", buff);
    }

    // Close input file
    fclose(fp);

    return EXIT_SUCCESS;
}

# COSC 315: Operating Systems - Project 3

### Table of Contents
- [Description](#description)
- [Core Features](#core-features)
- [Design Choices](#design-choices)
- [Build Instructions](#build-instructions)
- [Sample Output](#sample-output)
- [Contributors](#contributors)

## Description
This project involves two components. The first component uses an input file where we recieve 'n' number of bits that represent the offset, 'm' number of bits for the page number, and then a series of virtual addresses. Using this information, we converted these addresses such that their location is represented by a page number p that offsets by d instructions.  

The second component mimics how a simple UNIX-like file system operates. We used provided code to build the filesystem; our task was to make a program that could read a series of instructions from a text file that do specific operations to that filesystem. The first line tells us the name of the filesystem and every line afterwards represents a given instruction. Each token in an instruction is delimited by " ", there are at most 3 tokens per line. The first token is the command to be done. If the command calls for additional arguments to function properly, the second token is the string representing file name and the third token is an integer that represents either the size (in blocks) or which block in the file where the operation should occur.

## Core Features

**Part 1: Memory Management**
- [x] Takes a sequence of virtual addresses to extract the page number and offset for each address.
- [x] Reads an input file containing the number of bits for page and offset, followed by a list of virtual addresses.
- [x] Calculates the page and offset numbers using bit-wise operations.
- [x] Prints out the virtual address that is read, along with the calculated page and offset numbers.

**Part 2: File Systems**
- [x] Opens a pre-formatted virtual file system.
- [x] Reads an input file containing and tokenizes each line into 1 - 3 tokens.
- [x] Evaluates the first token and jump to the appropriate command.
- [x] Processes the command on the file system and prints actions to the terminal.
- [x] Writes to the file system to ensure persistence.

## Design Choices
  1. We chose to solve the first component on paper outlining how the offset and page would be calculated, then implemented the program in C.
  2. In order to avoid using division or modulus operators, we used shift left `<<` and shift right `>>` operators.
  3. To improve clarity, we separated the project into separate directories, each with their own makefiles.
  4. We also used C to program the second component for a lower-level implementation that C++ would offer.
  5. We kept all of the second components file system functions in one file as there is a small amount of them. This allowed us to keep the project simple without an abundance of C files accompanied by its own header files.   
  
## Build instructions

  1. Clone the project to a local repository:   `git clone https://github.com/1EC4/cosc315p3.git`
  
**Part 1: Memory Management**

  2. Navigate to the Java directory: `cd "cosc315p2/Part_1"`
  3. Build the program: `make`
  4. Run the program: `./program`
  
**Part 2: File Systems**

  2. Navigate to the Java directory: `cd "cosc315p2/Part_2"`
  3. Build the program: `make`
  4. Run the program:`./program`

## Sample Output

**Part 1: Memory Management**

Check out [this example file](Part_1/sample_output.txt) for sample output.

**Part 2: File Systems**

Check out [this example file](Part_2/sample_output.txt) for sample output.


## Contributors
- **Anthony Boyko**
  1. Fixed a logical error for the offset in part one and changed how limit was calculated
  2. Paired programming with Nick for Part 2 `delete`, `list`, `read` and `write` 
  3. Fixed erros involving segmentation faults along function not actually doing anything in saving of filesystem
  4. Updated Readme

- **Nick Rieske**
  1. Wrote `MyFileSystem` to load a filesystem from a disk file
  2. Wrote initial version of `SaveFileSystem`
  3. Programmed `delete`, `list`, `read`, and `write` functions with Anthony
  4. Programmed `create` function
  5. Wrote `makefile`'s for parts 1 and 2

- **Jonathan Gresl**
  1. Programmed `lab3_part1.c` to open the input file and read through each line
  2. Used the formulas from the team meeting to calculate and print the page and offset with bit-wise operations
  3. Programmed `lab3_part2.c` to open the input file, and tokenize the input lines
  4. Built a switch statement to look at the first token and determine which command should be run
  5. Framed out the file system functions to be called in the switch statement with the appropriate arguments
  6. Paired debugging with Anthony to determine source of a segmentation fault

[Back to The Top](#cosc-315-operating-systems---project-3)

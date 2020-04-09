# COSC 315: Operating Systems - Project 3

### Table of Contents
- [Description](#description)
- [Core Features](#core-features)
- [Design Choices](#design-choices)
- [Build Instructions](#build-instructions)
- [Sample Output](#sample-output)
- [Contributors](#contributors)
- [Programming Experience](#programming-experience)

## Description
This project involves two components. The first component uses an input file where we recieve 'n' number of bits that represent the offset, 'm' number of bits for the page number, and then a series of virtual addresses. Using this information, we converted these addresses such that their location is represented by a page number p that offsets by d instructions.  

The second component mimics how a simple UNIX-like file system operates. We used provided code to build the filesystem; our task was to make a program that could read a series of instructions from a text file that do specific operations to that filesystem. The first line tells us the name of the filesystem and every line afterwards represents a given instruction. Each token in an instruction is delimited by " ", there are at most 3 tokens per line. The first token is the command to be done. If the command calls for additional arguments to function properly, the second token is the string representing file name and the third token is an integer that represents either the size (in blocks) or location (by block) in the file where an operation should occur.

## Core Features
**Request scheduling using threads and synchronization:**
- [x] 1
- [x] 2
- [x] 3
- [x] 4
- [x] 5
- [x] 6
- [x] 7

## Design Choices
  1. We chose to solve the first part on paper first for how the offset and page would be calculated then afterwards implemented it in c
  2. Because the project is two distinct parts we decided to separate them with their own makefiles and folders for clarity sake.
  3. We keep all of part 2s functions in one file due to there only needing to be a handful. This meant there was a need to give each task its own header file along with a c file to accompany it. 
    
  
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
Check out [this example file](sample_output.txt) for sample output.

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
  1. 
  2. 
  3. 
  4. 
  5. 

## Programming Experience

Not sure if we need this

[Back to The Top](#cosc-315-operating-systems---project-3)

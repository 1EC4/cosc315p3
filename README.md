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

This project involves two components. The first component has take a input file where we recieve n number of bits that represent the offset, m number of bits for the page number and then a series of virtual addresses. Using this information we had to convert these addresses such that there location was represented by a page number p that offset by d instructions.  

In the second part our task was to mimic how a simple UNIX-like file system operates We were given code that will make the filesystem. While our task was to make a program that could read a series of instruction from a text file that do specific operations to that filesystem. The first line would tell us the name of the filesystem and every line afterwards is telling us a given instruction. Each token in an instruction is split by " ", there are at most 3 tokens per line. The first is the command to be done. While the second if there is a file name and the 3rd will either be a integer representing the size or where in a file an operation occurs.

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
  
**Part 1:**

  2. Navigate to the Java directory: `cd "cosc315p2/Part_1"`
  3. Build the program: `make`
  4. Run the program: ./lab3_part1
  
**Part 2:**

  2. Navigate to the Java directory: `cd "cosc315p2/Part_2"`
  3. Build the program: `make`
  4. Run the program: ./lab3_part2

## Sample Output
Check out [this example file](sample_output.txt) for sample output.

## Contributors
- **Anthony Boyko**
  - 1 fixed a logical error for the offset in part one and changed how limit was calculated
  - 2 Paired programming with nick for Part 2 delete, list, read and write 
  - 3 fixed erros involving segmentation faults along function not actually doing anything in saving of filesystem
  - 4 Updated Readme
  - 5

- **Nick Rieske**
  - 1
  - 2
  - 3
  - 4
  - 5

- **Jonathan Gresl**
  - 1
  - 2
  - 3
  - 4
  - 5

## Programming Experience

Not sure if we need this

[Back to The Top](#cosc-315-operating-systems---project-3)

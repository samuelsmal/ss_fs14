# 1-Process creation and management to C++
## Systems Software, UZH, FS14

## Requirements

* clang++/g++, with C++11 supported
* make (for building)

## Compiling:

    $ make prepare # will create the bin and obj directories
    $ make         # will compile and link the sources

In order to compile the program you need `clang++` and a `C++11` library.

## Running:

    $ make run

Will run the proramm with the provided samples.

## Cleaning:

    $ make clean

Will remove the objective-files and the temporary files.

    $ make remove

Will in addition to `make clean` will remove the binary.

## Programm overview

The main class is `Upcat` (`src/upcat.h`), it does the heavy lifting.
The `main` function (`src/main.cpp`) is the starting point, constructs a new
`Upcat` object on the stack, and calls `Upcat.createAndRunProcesses()`, which is
the entry point for the process creation and management
(see `Upcat.childProcess()` and `Upcat.parentProcess()`).

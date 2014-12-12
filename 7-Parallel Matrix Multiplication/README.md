# 7 - Parallel Matrix Multiplication
## Systems Software, UZH, FS14

## Requirements

* clang++/g++, with C++11 supported
* make (for building)

## Compiling:

    $ make prepare # will create the bin and obj directories
    $ make         # will compile and link the sources

In order to compile the program you need `clang++` and a `C++11` library.
If you want to use `g++` instead of `clang++` you have to change the `CXX` variable in the makefile.

## Running:

    $ make run

Will run the proramm with following arguments:
<number of cooks of first type> <number of cooks of second type> <sleeping time min (nanoseconds)> <sleeping time max (nanoseconds)> <number of spoons> <number of pans> <number of lids> = 10 12 100 1000 5 3 20

## Cleaning:

    $ make clean

Will remove the objective-files and the temporary files.

    $ make remove

Will in addition to `make clean` will remove the binary.

## Program overview

Follow the trail from `main.cpp`...

### Deadlocks

No usage of mutexes.

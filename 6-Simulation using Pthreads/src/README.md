# 6-Simulating the Activity of a Restaurant Kitchen using Posix Threads
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

Will run the proramm with following arguments:
<number of cooks1>, <number of cooks2>, <sleeping time min (nanoseconds)>, <sleeping time max (nanoseconds)>, <number of spoons>, <number of pans>, <number of lids> = 10, 12, 100, 1000, 5, 3, 20

## Cleaning:

    $ make clean

Will remove the objective-files and the temporary files.

    $ make remove

Will in addition to `make clean` will remove the binary.

## Program overview

Follow the trail from `main.cpp`.

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
<number of cooks of first type> <number of cooks of second type> <sleeping time min (nanoseconds)> <sleeping time max (nanoseconds)> <number of spoons> <number of pans> <number of lids> = 10 12 100 1000 5 3 20

## Cleaning:

    $ make clean

Will remove the objective-files and the temporary files.

    $ make remove

Will in addition to `make clean` will remove the binary.

## Program overview

Follow the trail from `main.cpp`...

### Deadlocks

We use three mutexes: Two for the logging (one for the live feedback, one for the end result), one for the tools.
They are never in a nested locked status, thus a deadlock cannot result.

After the quit message (`q + ⏎`) the simulation will shut down gracefully,
meaning that the last meals are cooked, and the cooks take their rest.

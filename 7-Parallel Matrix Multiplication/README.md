# 7 - Parallel Matrix Multiplication
## Systems Software, UZH, FS14

## Requirements

* clang++/g++, with C++11 supported
* make (for building)

## Compiling:

    $ make prepare # will create the bin and obj directories
    $ make         # will compile and link the sources

In order to compile the program you need `gg++`, a `C++11` library and `openMP`
and `pthreads` working on your machine. Bear in mind that `clang++` as of now
doesn't support `openMP` out of the box.

## Running:

    $ make run

Will run it with the provided sample data (located in `./sample_data`). The
program will save the result there.

## Cleaning:

    $ make clean

Will remove the objective-files and the temporary files.

    $ make remove

Will in addition to `make clean` will remove the binary.

## Program details

Since the openMP and the serial version require different code than the pthread
version, we made several implementations. Both are roughly the same, the ideas
are all functions calls are the same. Pthread's version needs some additional
casting and memory loading though, but this is due to pthread's structure.
OpenMP might do something like this under the hood.

### Deadlocks

No usage of mutexes. Values are either writen once or never, data is immutable.


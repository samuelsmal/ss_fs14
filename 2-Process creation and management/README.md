# 1-Process creation and management to C++
## Systems Software, UZH, FS14

The program is again pretty straight foreward.

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
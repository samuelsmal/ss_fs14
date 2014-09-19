# 1-Introduction to C++
## Systems Software, UZH, FS14

The program is pretty straight foreward: Sorting is done via an inline operator.

## Compiling:

    $ make prepare # will create the bin and obj directories
    $ make         # will compile and link the sources

In order to compile the program you need `clang++` and a `C++11` library.

## Running:

    $ make run

Will write the sorted database to a file.

    $ make run_unix_style

Will write the sorted database to the standard console.
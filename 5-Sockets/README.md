# Information

I used the advice from **Advanced Programming in the UNIX Environment** by **W.
R. Stevens** for the handling of the client and server.

Note that the program is written completely in C, using `clang`. Which builds by
default in GNU C11 mode.

# How to run

1. Open n terminals.
2. 1. In the first write: `./bin/sensor`
   2. In rest write: `./bin/host`
3. Terminate the sensor (and the program) by hitting `CTRL-C` in the sensor terminal.

# How to compile

`make` is enough.
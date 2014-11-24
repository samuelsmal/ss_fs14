# Information

I used the advice from **Advanced Programming in the UNIX Environment** by **W.
R. Stevens** for the handling of the client and server.

Note that the program is written completely in C, using `clang`. Which builds by
default in `GNU C11` mode.

# How to run

1. Open n terminals.
2.
   1. In the first write: `./bin/sensor <socket address>`.
   1. In rest write: `./bin/host <socket address> <auth token>`.
      The `auth token` can be any three letter combination. But only `TMP` will grant you access.
3. Terminate the sensor (and the program) by hitting `CTRL-C` in the sensor terminal.

If you get an error, saying the address is already in use, make sure to delete the socket file.

# How to compile

`make` is enough.

# Notes on decisions

Since package loss is not toleratable the only choice is use of connection-oriented
sockets.

Additional the setting of the homework specified usage of UNIX domain sockets. Which seems to a rather weird choice. Why would I want to access a sensor on the same machine? The example presented in the lecture would hint at a internet domain socket.

Since both stream and datagram UNIX domain services are reliable.

Since the processes are unrelated one cannot use `socketpair`.

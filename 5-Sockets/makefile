# Requires the following project directory structure:
#  /bin
#  /obj
#  /src

# Use 'make remove' to clean up the hole project
CXX        = clang++
CFLAGS     = -std=c++11 -Weverything -Wall -Wextra -Wpointer-arith -Wcast-qual \
             -Wno-missing-braces -Wempty-body -Wno-error=uninitialized \
             -Wno-error=deprecated-declarations -Wno-c++98-compat \
             -pedantic-errors -pedantic \
             -Os


LINKER     = clang++ -o
LFLAGS     =

all: sensor host

sensor: src/sensor.cpp
	@$(CXX) $(CFLAGS) $< -o bin/sensor
	@echo "Compiled sensor successfully!"

host: src/host.cpp
	@$(CXX) $(CFLAGS) $< -o bin/host
	@echo "Compiled host successfully!"

clean:
	rm -f bin/sensor bin/host

# Requires the following project directory structure:
#  /bin
#  /obj
#  /src

# Use 'make remove' to clean up the hole project

# Name of target file
TARGET     = pat_matching

CXX        = g++
CFLAGS     = -std=c++11 -Wall -Wextra -Wpointer-arith -Wcast-qual \
             -Wno-missing-braces -Wempty-body -Wno-error=uninitialized \
             -Wno-error=deprecated-declarations -Wno-c++98-compat \
             -pedantic-errors -pedantic \
             -Os -fopenmp


LINKER     = g++ -o
LFLAGS     = -fopenmp

SRCDIR     = src
OBJDIR     = obj
BINDIR     = bin

SOURCES   := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES  := $(wildcard $(SRCDIR)/*.h)
OBJECTS   := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

RM         = rm -f

$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $@ $(LFLAGS) $(OBJECTS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(CXX) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONEY: prepare
prepare:
	mkdir -p bin
	mkdir -p obj

.PHONEY: clean
clean:
	@$(RM) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONEY: remove
remove: clean
	@$(RM) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"


.PHONEY: run
run:
	./bin/$(TARGET) test_sequence.txt test_patterns.txt 4 2
	./bin/$(TARGET) test_sequence.txt test_patterns.txt 3 1
	./bin/$(TARGET) test_sequence.txt test_patterns.txt 4 0

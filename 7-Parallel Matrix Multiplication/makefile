# Requires the following project directory structure:
#  /bin
#  /obj
#  /src

# Use 'make remove' to clean up the hole project

# Name of target file
TARGET     = matr_mult

CXX        = g++
CFLAGS     = -std=c++11 -Wall -Wextra -Wpointer-arith -Wcast-qual \
             -Wno-missing-braces -Wempty-body -Wno-error=uninitialized \
             -Wno-error=deprecated-declarations\
             -pedantic-errors -pedantic \
             -Os -fopenmp -pthread


LINKER     = g++ -o
LFLAGS     = -fopenmp -pthread

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
	./bin/$(TARGET) sample_data/left_matrix.txt sample_data/right_matrix.txt 0 2 sample_data/output.txt
	./bin/$(TARGET) sample_data/left_matrix.txt sample_data/right_matrix.txt 1 4 sample_data/output.txt
	./bin/$(TARGET) sample_data/left_matrix.txt sample_data/right_matrix.txt 2 4 sample_data/output.txt

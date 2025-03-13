# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -pthread

# Target executable name
TARGET = ipc

# Source files
SRC = ipc.cpp

# Mark targets as phony to avoid issues
.PHONY: all clean run

# Default target (runs when you type 'make')
all: $(TARGET)

# Compile the program
$(TARGET): $(SRC)
	$(CXX) -o $(TARGET) $(SRC) $(CXXFLAGS)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean compiled files
clean:
	rm -f $(TARGET)

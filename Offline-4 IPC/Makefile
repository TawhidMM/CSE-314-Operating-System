# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -pthread

# Target executable name
TARGET = ipc

# Source files
SRC = ipc.cpp

# Build target
all: $(TARGET)

# Compile the program
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean the compiled files
clean:
	rm -f $(TARGET)

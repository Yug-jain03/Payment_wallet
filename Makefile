# Compiler
CXX = g++
# Compiler flags
CXXFLAGS = -std=c++11 -Wall

# Source files
SRCS = main.cpp User.cpp Wallet.cpp Report.cpp Transaction.cpp
# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
EXEC = main

# Default rule to build the executable
all: $(EXEC)

# Rule to link the executable
$(EXEC): $(OBJS)
    $(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)

# Rule to compile source files into object files
%.o: %.cpp
    $(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean up generated files
clean:
    rm -f $(OBJS) $(EXEC).exe
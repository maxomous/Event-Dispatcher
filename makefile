# see: https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html

TARGET = EventDispatcher
DIRS = 
LIBS =

# add to libs for debugging gdb -v -da -Q
CXX = g++

# -g   for debugging
# -Wall -Werror   to show all errors
CXXFLAGS= -std=c++17 -g -Wall -Werror -Wextra

# this ensures that if there is a file called default, all or clean, it will still be compiled
.PHONY: default all clean

default: $(TARGET)
all: default

# substitute '.cpp' with '.o' in any *.cpp 
OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp $(addsuffix /*.cpp, $(DIRS))))

# build the executable
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
# if make is interupted, dont delete any object file
.PRECIOUS: $(TARGET) $(OBJECTS)

# build the objects
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -Wall $(LDLIBS) -o $@ 

clean:
	-rm -f *.o $(addsuffix /*.o, $(DIRS))
	-rm -f $(TARGET)

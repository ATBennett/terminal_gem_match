
# The compiler
CC = g++ -std=c++14

#Compiler flags
CFLAGS = -g

#Linker flags
LFLAGS = -lncurses

#The build target executable
TARGET = terminal_gem_match

#Builds the lists of files to be compiled
SOURCES 	:= 	$(wildcard src/*.cpp)
INCLUDES 	:= 	$(wildcard include/*.h) #not used
OBJECTS		:= 	$(SOURCES:src/%.cpp=obj/%.o)

bin/$(TARGET): $(OBJECTS)
	@ mkdir -p bin
	$(CC) $^ -o $@ $(LFLAGS)

$(OBJECTS): obj/%.o : src/%.cpp
	@ mkdir -p obj
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean cleanest

clean:
	rm obj/*.o

cleanest: clean
	rm bin/$(TARGET)
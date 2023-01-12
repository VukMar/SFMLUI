# Specify the target file and the source files
TARGET = libV-UI.a
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(patsubst src/%.cpp,obj/%.o,$(SOURCES))
DEPS = $(patsubst src/%.cpp,obj/%.d,$(SOURCES))

# Specify the compiler and flags
CC = g++
CFLAGS = -Wall -O2 -Iinclude -MMD
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Default target
all: $(TARGET)

# Rule to build the target
$(TARGET): $(OBJECTS)
	ar rcs $@ $^

# Rule to build the object files
obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) $(LIBS) -c -o $@ $<

# Rule to include dependencies
-include $(DEPS)

# Rule to clean up the project
clean:
	del *.a obj\*.o obj\*.d

# Rule to rebuild the project from scratch
rebuild: clean all

# Phony targets
.PHONY: all clean rebuild


OUTPUTDIR = build
OBJDIR = $(OUTPUTDIR)/objects
PROJECTNAME = se
SRCDIR = src
SRC = $(wildcard src/*.cpp)
OBJ = $(patsubst src/%.cpp, $(OUTPUTDIR)/objects/%.o, $(SRC))
CC = g++

INCLUDE_DIRS = -Iinclude -Iheaders

CFLAGS =

DEBUG_FLAGS = -DDEBUG

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE_DIRS)

library: $(OBJ)
	ar rcs $(OUTPUTDIR)/lib$(PROJECTNAME).a $(OBJ)

debug: CFLAGS += $(DEBUG_FLAGS)
debug: library
OUTPUTDIR = build
PROJECTNAME = app
SRC = $(wildcard src/*.cpp)
CC = g++

INCLUDE_DIRS = -Iinclude -Iheaders
LIB_DIR = -Llib
LIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

DEBUG_FLAGS = -DDEBUG

CFLAGS =

debug: CFLAGS += $(DEBUG_FLAGS)
debug: program

program:
	$(CC) $(CFLAGS) $(SRC) -o $(OUTPUTDIR)/$(PROJECTNAME) $(INCLUDE_DIRS) $(LIB_DIR) $(LIBS)


OUTPUTDIR = build
OBJDIR = $(OUTPUTDIR)/objects
PROJECTNAME = engine
SRCDIR = src
SRC = $(wildcard src/*.cpp)
OBJ = $(patsubst src/%.cpp, $(OUTPUTDIR)/objects/%.o, $(SRC))
CC = g++

INCLUDE_DIRS = -Iinclude -Iheaders
LIB_DIR = -Llib
LIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

CFLAGS = 

DEBUG_FLAGS = -DDEBUG

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE_DIRS)

library: $(OBJ)
	ar rcs $(OUTPUTDIR)/lib$(PROJECTNAME).a $(OBJ)

program: library
	$(CC) -DDEBUG driver/main.cpp -o $(OUTPUTDIR)/$(PROJECTNAME) $(INCLUDE_DIRS) -L$(OUTPUTDIR) $(LIB_DIR) $(LIBS) -l$(PROJECTNAME)
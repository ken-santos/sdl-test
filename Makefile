OBJS = main.cpp

OBJ_NAME = main

# The compiler this program use
CC = g++

# COMPILER FRAGS
# -w suppresses all warnings
CC_FLAGS = -w

# Specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image

all : $(OBJS)
	$(CC) $(OBJS) $(CC_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
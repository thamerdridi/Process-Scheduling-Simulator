CC = gcc
CFLAGS = -Wall -g

# Name of your final executable
TARGET = main

# Source files
SRC = main.c

# Object files
OBJ = $(SRC:.c=.o)

all: $(TARGET) permissions

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Set permissions for the executable, header files, and file1.txt
permissions:
	chmod 744 $(TARGET) *.h file1.txt

clean:
	rm -f $(TARGET) $(OBJ)

.PHONY: clean permissions


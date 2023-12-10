CC = gcc
CFLAGS = -Wall -g


TARGET = main


SRC = main.c


OBJ = $(SRC:.c=.o)

all: $(TARGET) permissions

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

permissions:
	chmod 744 $(TARGET) *.h file1.txt

clean:
	rm -f $(TARGET) $(OBJ)

.PHONY: clean permissions


CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pedantic
LDFLAGS = -lm


SRC = main.c tabela_hash.c
OBJ = $(SRC:.c=.o)
TARGET = tabela_hash


.PHONY: all clean


all: $(TARGET)


$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS)


%.o: %.c tabela_hash.h
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJ) $(TARGET)







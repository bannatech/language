SRC_DIR = src
INC_DIR = inc

CC      = gcc
CFLAGS  = -Wall -I$(INC_DIR)

DEPS    = $(INC_DIR)/fh.h

OBJ     = $(SRC_DIR)/main.o \
          $(SRC_DIR)/fh.o

OUT     = main

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm $(SRC_DIR)/*.o
	rm $(OUT)

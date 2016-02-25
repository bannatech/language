SRC_DIR = ../../../src
INC_DIR = ../../../inc

CC      = gcc
CFLAGS  = -std=c99 -Wall -I$(INC_DIR)

DEPS    = i$(INC_DIR)/helper.h \
                      var.h    \
                      ht.h

OBJ     = test.o             \
          $(SRC_DIR)/var.o   \
          $(SRC_DIR)/ht.o

OUT     = test

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm *.o
	rm $(OUT)

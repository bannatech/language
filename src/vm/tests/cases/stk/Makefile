SRC_DIR = ../../../src
INC_DIR = ../../../inc

CC      = gcc
CFLAGS  = -std=c99 -Wall -I$(INC_DIR)

DEPS    = i$(INC_DIR)/helper.h \
                      ns.h     \
                      object.h \
                      stk.h    \
                      var.h    \

OBJ     = test.o            \
          $(SRC_DIR)/stk.o  \
          $(SRC_DIR)/object.o \
          $(SRC_DIR)/ns.o   \
          $(SRC_DIR)/var.o

OUT     = test

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm *.o
	rm $(OUT)

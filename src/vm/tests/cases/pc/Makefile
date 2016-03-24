SRC_DIR = ../../../src
INC_DIR = ../../../inc

CC      = gcc
CFLAGS  = -std=c99 -Wall -I$(INC_DIR)

DEPS    = i$(INC_DIR)/is_mdata.h \
                      helper.h   \
                      fh.h       \
                      is.h       \
                      bc.h       \
                      var.h      \
                      pc.h

OBJ     = test.o          \
          $(SRC_DIR)/fh.o \
          $(SRC_DIR)/is.o \
          $(SRC_DIR)/bc.o \
          $(SRC_DIR)/var.o\
          $(SRC_DIR)/pc.o

OUT     = test

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm *.o
	rm $(OUT)

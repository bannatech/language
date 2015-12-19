SRC_DIR = src
INC_DIR = inc

CC      = gcc
CFLAGS  = -std=c99 -Wall -I$(INC_DIR)

DEPS    = $(INC_DIR)/is_mdata.h \
                     helper.h   \
                     fh.h       \
                     bc.h       \
                     is.h       \
                     types.h    \
                     stk.h      \
                     ht.h       \
                     ns.h

OBJ     = $(SRC_DIR)/main.o \
          $(SRC_DIR)/fh.o   \
          $(SRC_DIR)/bc.o   \
          $(SRC_DIR)/is.o   \
          $(SRC_DIR)/types.o\
          $(SRC_DIR)/stk.o  \
          $(SRC_DIR)/ht.o   \
          $(SRC_DIR)/ns.o

OUT     = main

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm $(SRC_DIR)/*.o
	rm $(OUT)

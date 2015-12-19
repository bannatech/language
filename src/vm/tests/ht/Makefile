SRC_DIR = ../../src
INC_DIR = ../../inc

CC      = gcc
CFLAGS  = -std=c99 -Wall -I$(INC_DIR)

DEPS    = i$(INC_DIR)/helper.h \
                      types.h  \
                      ht.h

OBJ     = test.o             \
          $(SRC_DIR)/types.o \
          $(SRC_DIR)/ht.o

OUT     = test

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm *.o
	rm $(SRC_DIR)/*.o
	rm $(OUT)

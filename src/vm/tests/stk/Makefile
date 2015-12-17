SRC_DIR = ../../src
INC_DIR = ../../inc

CC      = gcc
CFLAGS  = -std=c99 -Wall -I$(INC_DIR)

DEPS    = i$(INC_DIR)/stk.h   \
                      types.h \

OBJ     = test.o            \
          $(SRC_DIR)/stk.o  \
          $(SRC_DIR)/types.o

OUT     = test

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm *.o
	rm $(SRC_DIR)/*.o
	rm $(OUT)

SRC_DIR = src
INC_DIR = inc

CC      = gcc
CFLAGS  = -std=c99 -Wall -Wconversion -I$(INC_DIR)

DEPS    = $(INC_DIR)/is_mdata.h \
                     helper.h   \
                     fh.h       \
                     bc.h       \
                     is.h       \
                     var.h      \
                     var_ops.h  \
                     stk.h      \
                     ns.h       \
                     pc.h       \
                     rt.h       \
                     ins_def.h  \
                     proc.h

OBJ     = $(SRC_DIR)/main.o     \
          $(SRC_DIR)/fh.o       \
          $(SRC_DIR)/is.o       \
          $(SRC_DIR)/bc.o       \
          $(SRC_DIR)/var.o      \
          $(SRC_DIR)/var_ops.o  \
          $(SRC_DIR)/stk.o      \
          $(SRC_DIR)/ns.o       \
          $(SRC_DIR)/rt.o       \
          $(SRC_DIR)/ins_def.o  \
          $(SRC_DIR)/pc.o       \
          $(SRC_DIR)/proc.o

OUT     = toi

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm $(SRC_DIR)/*.o
	rm $(OUT)

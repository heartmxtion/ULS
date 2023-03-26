CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

OBJDIR = obj
SRCDIR = src
LIB_DIR = libmx
LIB_NAME = $(LIB_DIR)/libmx.a
LIB = $(LIB_NAME)
ULS = uls

SRC = $(SRCDIR)/*.c
OBJS = $(OBJDIR)/*.o

all: $(LIB) $(ULS)

$(ULS):
	mkdir $(OBJDIR)
	$(CC) $(CFLAGS) -c $(SRC)
	mv *.o $(OBJDIR)
	$(CC) -o $(ULS) $(OBJS) -L$(LIB_DIR) $(LIB_NAME)

$(LIB):
	make -sC $(LIB_DIR)

clean:
	rm -f $(OBJS)
	rm -df $(OBJDIR)

uninstall:
	make -sC $(LIB_DIR) $@
	make clean
	rm -f $(ULS)

reinstall:
	make uninstall
	make all

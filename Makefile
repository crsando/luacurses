LUA_INCLUDE = /usr/include/lua5.3

SRC_DIR = src
OBJ_DIR = obj

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:*.c=*.o)

CPPFLAGS += -I$(LUA_INCLUDE)

CFLAGS += -fPIC -Wall -Wextra
CFLAGS += -ggdb -O0

LFLAGS += -llua5.3 -lcurses

all: obj/libcurses.so obj/libcurses.a

obj/libcurses.so: $(OBJ)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LFLAGS) -shared -o $@ $^

obj/libcurses.a: $(OBJ)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $<

clean:
	$(RM) -rf $(OBJ_DIR)/*

.PHONY: all clean

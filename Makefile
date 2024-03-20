LUA_INCLUDE = /usr/local/include/luajit-2.1

SRC_DIR = src
OBJ_DIR = obj

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CPPFLAGS += -I$(LUA_INCLUDE)

CFLAGS += -fPIC -Wall -Wextra
# CFLAGS += -ggdb -O0

LFLAGS += -lluajit-5.1 -lncurses

all: dirs obj/ccurses.so

dirs:
	mkdir -p obj/

obj/ccurses.so: $(OBJ)
	$(CC) $(CPPFLAGS) $(CFLAGS) -shared -o $@ $^ $(LFLAGS) 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@ $(LFLAGS)

clean:
	$(RM) -rf $(OBJ_DIR)/*

.PHONY: all clean dirs install

install:
	cp obj/ccurses.so /usr/local/lib/lua/5.1/
	cp src/curses.lua /usr/local/share/lua/5.1/
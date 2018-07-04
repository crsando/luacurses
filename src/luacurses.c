/**
 * @file luacurses.c
 * @author William Blount
 * @date 6/15/2018
 * @brief a simple lua wrapper for ncurses
 */

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#include <assert.h>
#include <curses.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1024

typedef struct {
    WINDOW *window;
    bool    colors;
} _screen_ctx_t;

typedef struct {
    short id;
} _color_pair_ctx_t;

static const char *colorNames[] = {
    "COLOR_BLACK",
    "COLOR_RED",
    "COLOR_GREEN",
    "COLOR_YELLOW",
    "COLOR_BLUE",
    "COLOR_MAGENTA",
    "COLOR_CYAN",
    "COLOR_WHITE",
    NULL
};

static const int colorValues[] = {
    COLOR_BLACK,
    COLOR_RED,
    COLOR_GREEN,
    COLOR_YELLOW,
    COLOR_BLUE,
    COLOR_MAGENTA,
    COLOR_CYAN,
    COLOR_WHITE,
    NULL
};

int l_screen_init(lua_State *L) {
    _screen_ctx_t *ctx;

    ctx = lua_newuserdata(L, sizeof(*ctx));
    ctx->window = initscr();
    ctx->colors = has_colors();

    if(ctx->colors) {
        start_color();
    }

    return 1;
}

int l_screen_read(lua_State *L) {
    _screen_ctx_t *ctx;
    int n;
    bool blocking;

    assert(lua_isuserdata(L, 1));
    ctx = lua_touserdata(L, 1);
    n = luaL_checkinteger(L, 2);
    blocking = lua_toboolean(L, 3);

    nodelay(ctx->window, !blocking);

    char buf[n];
    for(int i = 0; i < n; i++) {
        int ch = wgetch(ctx->window);
        if(ch < 0) {
            buf[n] = 0;
            break;
        }
        buf[n] = (char) ch;
    }
    lua_pushstring(L, buf);

    return 1;
}

int l_screen_readline(lua_State *L) {
    _screen_ctx_t *ctx;
    bool blocking;
    char *buf;

    assert(lua_isuserdata(L, 1));
    ctx = lua_touserdata(L, 1);
    blocking = lua_toboolean(L, 2);

    nodelay(ctx->window, !blocking);
    buf = (char *) calloc(MAX_LINE_LENGTH, sizeof(*buf));
    wgetstr(ctx->window, buf);

    lua_pushstring(L, buf);

    return 1;
}

int l_screen_iscolor(lua_State *L) {
    _screen_ctx_t *ctx;

    assert(lua_isuserdata(L, 1));
    ctx = lua_touserdata(L, 1);

    lua_pushboolean(L, ctx->colors);

    return 1;
}

int l_screen_getsize(lua_State *L) {
    _screen_ctx_t *ctx;
    int x;
    int y;

    assert(lua_isuserdata(L, 1));
    ctx = lua_touserdata(L, 1);

    getmaxyx(ctx->window, y, x);

    lua_pushinteger(L, x);
    lua_pushinteger(L, y);

    return 2;
}

int l_screen_getcursor(lua_State *L) {
    _screen_ctx_t *ctx;
    int x;
    int y;

    assert(lua_isuserdata(L, 1));
    ctx = lua_touserdata(L, 1);

    getyx(ctx->window, y, x);

    lua_pushinteger(L, x);
    lua_pushinteger(L, y);

    return 2;
}

int l_screen_setcursor(lua_State *L) {
    _screen_ctx_t *ctx;
    int x;
    int y;

    assert(lua_isuserdata(L, 1));
    ctx = lua_touserdata(L, 1);
    x = luaL_checkinteger(L, 2);
    y = luaL_checkinteger(L, 3);

    wmove(ctx->window, y, x);

    return 0;
}

int l_screen_write(lua_State *L) {
    _screen_ctx_t *screen;
    const char *str;
    _color_pair_ctx_t *color_pair;

    assert(lua_isuserdata(L, 1));
    screen = lua_touserdata(L, 1);
    str = luaL_checkstring(L, 2);
    color_pair = lua_touserdata(L, 3);

    wattron(screen->window, COLOR_PAIR(color_pair->id));
    waddstr(screen->window, str);
    wattroff(screen->window, COLOR_PAIR(color_pair->id));

    return 0;
}

int l_screen_clear(lua_State *L) {
    _screen_ctx_t *ctx;

    assert(lua_isuserdata(L, 1));
    ctx = lua_touserdata(L, 1);

    wclear(ctx->window);

    return 0;
}

int l_screen_refresh(lua_State *L) {
    _screen_ctx_t *ctx;

    assert(lua_isuserdata(L, 1));
    ctx = lua_touserdata(L, 1);

    wrefresh(ctx->window);

    return 0;
}

int l_screen_destroy(lua_State *L) {
    endwin();

    return 0;
}

int l_color_pair_init(lua_State *L) {
    _color_pair_ctx_t *ctx;
    short fg;
    short bg;

    ctx = lua_newuserdata(L, sizeof(*ctx));
    ctx->id = (short) luaL_checkinteger(L, 1);
    fg = (short) luaL_checkinteger(L, 2);
    bg = (short) luaL_checkinteger(L, 3);

    init_pair(ctx->id, fg, bg);

    return 1;
}

// TODO: Add methods that allow configuring echo and other such properties of
// the screen.
static const struct luaL_Reg c_curses[] = {
    {"screen_init",         l_screen_init},
    {"screen_read",         l_screen_read},
    {"screen_readline",     l_screen_readline},
    {"screen_iscolor",      l_screen_iscolor},
    {"screen_getsize",      l_screen_getsize},
    {"screen_getcursor",    l_screen_getcursor},
    {"screen_setcursor",    l_screen_setcursor},
    {"screen_write",        l_screen_write},
    {"screen_clear",        l_screen_clear},
    {"screen_refresh",      l_screen_refresh},
    {"screen_destroy",      l_screen_destroy},
    {"color_pair_init",     l_color_pair_init},
    {NULL, NULL}
};

int luaopen_c_curses(lua_State *L) {
    // Load the functions.
    luaL_newlib(L, c_curses);

    // Load the color constants.
    for(int i = 0; colorNames[i] != NULL; i++) {
        lua_pushstring(L, colorNames[i]);
        lua_pushinteger(L, colorValues[i]);
        lua_settable(L, -3);
    }

    return 1;
}

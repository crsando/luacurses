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

typedef struct {
    WINDOW *window;
    bool    colors;
} _screen_ctx_t;

int pair = 1;

static const int colors[] = {
    COLOR_BLACK,
    COLOR_RED,
    COLOR_GREEN,
    COLOR_YELLOW,
    COLOR_BLUE,
    COLOR_MAGENTA,
    COLOR_CYAN,
    COLOR_WHITE
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

    assert(lua_isuserdata(L, 1));
    ctx = lua_touserdata(L, 1);
    blocking = lua_toboolean(L, 2);

    nodelay(ctx->window, !blocking);

    char buf[256];
    for(int i = 0; i < 256; i++) {
        int ch = wgetch(ctx->window);
        if(ch < 0 || ch == '\n') {
            buf[n] = 0;
            break;
        }
        buf[n] = (char) ch;
    }
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
    _screen_ctx_t *ctx;
    const char *str;
    int fg;
    int bg;

    assert(lua_isuserdata(L, 1));
    ctx = lua_touserdata(L, 1);
    str = luaL_checkstring(L, 2);
    fg = luaL_checkinteger(L, 3);
    bg = luaL_checkinteger(L, 4);

    init_pair(pair, colors[fg], colors[bg]);
    wattron(ctx->window, COLOR_PAIR(pair));
    waddstr(ctx->window, str);
    wattroff(ctx->window, COLOR_PAIR(pair));
    pair++;

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
    {NULL, NULL}
};

int luaopen_c_curses(lua_State *L) {
    luaL_newlib(L, c_curses);
    return 1;
}

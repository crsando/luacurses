----------------------------------------------
--! @file curses.lua
--! @author William Blount
--! @date 6/18/2018
--! @brief object oriented wrapper for curses.
----------------------------------------------

c_curses = require("c_curses")

local Screen = {}
Screen.__index = Screen

setmetatable(Screen, {
    __call = function(cls, ...)
        local self = setmetatable({}, cls)
        self:init(...)
        return self
    end,
})

function Screen:init()
    self.ctx = c_curses.screen_init();
end

function Screen:read(n, blocking)
    if blocking == nil then blocking = true end
    return c_curses.screen_read(self.ctx, n, blocking)
end

function Screen:readline(blocking)
    if blocking == nil then blocking = true end
    return c_curses.screen_readline(self.ctx, blocking)
end

function Screen:iscolor()
    return c_curses.screen_iscolor(self.ctx)
end

function Screen:getsize()
    return c_curses.screen_getsize(self.ctx)
end

function Screen:getcursor()
    return c_curses.screen_getcursor(self.ctx)
end

function Screen:setcursor(x, y)
    c_curses.screen_setcursor(self.ctx, x, y)
end

function Screen:write(string, fg, bg)
    fg = fg or 7 -- TODO: Get rid of hard coded values here.
    bg = bg or 0
    c_curses.screen_write(self.ctx, string, fg, bg)
end

function Screen:clear()
    c_curses.screen_clear(self.ctx)
end

function Screen:refresh()
    c_curses.screen_refresh(self.ctx)
end

function Screen:destroy()
    c_curses.screen_destroy()
end

----------------------------------------------

-- TODO: Move the color defs from lua to C.
local colors = {
    BLACK =     0,
    RED =       1,
    GREEN =     2,
    YELLOW =    3,
    BLUE =      4,
    MAGENTA =   5,
    CYAN =      6,
    WHITE =     7
}

----------------------------------------------

local curses = {
    Screen = Screen,
    colors = colors
}

return curses

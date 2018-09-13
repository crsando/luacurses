----------------------------------------------
--! @file curses.lua
--! @author William Blount
--! @date 6/18/2018
--! @brief object oriented wrapper for curses.
----------------------------------------------

c_curses = require("c_curses")

--------------------------------------------------------------------------------

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
    self.ctx = c_curses.init();
end

function Screen:read(n, blocking)
    if blocking == nil then blocking = true end
    return c_curses.read(self.ctx, n, blocking)
end

function Screen:readline(blocking)
    if blocking == nil then blocking = true end
    return c_curses.readline(self.ctx, blocking)
end

function Screen:iscolor()
    return c_curses.iscolor(self.ctx)
end

function Screen:getsize()
    return c_curses.getsize(self.ctx)
end

function Screen:getcursor()
    return c_curses.getcursor(self.ctx)
end

function Screen:setcursor(x, y)
    c_curses.setcursor(self.ctx, x, y)
end

function Screen:write(string, fg, bg)
    c_curses.write(self.ctx, string, fg, bg)
end

function Screen:clear()
    c_curses.clear(self.ctx)
end

function Screen:refresh()
    c_curses.refresh(self.ctx)
end

function Screen:destroy()
    c_curses.destroy()
end

--------------------------------------------------------------------------------

local curses = {
    Screen = Screen
}

return curses

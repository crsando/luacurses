-------------------------------------------
--! @file test.lua
--! @author William Blount
--! @date 6/19/2018
--! @brief simple test script for luacurses
-------------------------------------------

curses = require("curses")

local function do_test()
    local screen = curses.Screen()
    local cp1 = curses.ColorPair(1, 0, 7)
    local cp2 = curses.ColorPair(2, 1, 7)
    screen:setcursor(1, 1)
    screen:write("Hello, World!", cp1)
    screen:setcursor(2, 2)
    screen:write("Name: ", cp1)
    screen:refresh()
    local name = screen:readline()
    screen:setcursor(3,3)
    screen:write(name, cp2)
    screen:refresh()
    screen:destroy()
end

do_test()

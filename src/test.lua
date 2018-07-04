-------------------------------------------
--! @file test.lua
--! @author William Blount
--! @date 6/19/2018
--! @brief simple test script for luacurses
-------------------------------------------

curses = require("curses")

local function do_test()
    local screen = curses.Screen()
    screen:setcursor(1, 1)
    screen:write("Hello, World!", curses.ColorPair(curses.COLOR_RED, curses.COLOR_BLACK))
    screen.setcursor(2, 2)
    screen:write("Name: ")
    screen:refresh()
    local name = screen:readline()
    screen:setcursor(3,3)
    screen:write(name, curses.ColorPair(curses.COLOR_RED, curses.COLOR_BLACK))
    screen:refresh()
    screen:destroy()
end

do_test()

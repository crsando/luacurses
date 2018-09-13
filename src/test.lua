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
    screen:write("Hello, World!", 0, 7)
    screen:setcursor(2, 2)
    screen:write("Name: ", 0, 7)
    screen:refresh()
    local name = screen:readline()
    screen:setcursor(3,3)
    screen:write(name, 0, 7)
    screen:refresh()
    screen:destroy()
end

do_test()

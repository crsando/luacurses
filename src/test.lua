-------------------------------------------
--! @file test.lua
--! @author William Blount
--! @date 6/19/2018
--! @brief simple test script for luacurses
-------------------------------------------

curses = require("curses")
local colors = curses.colors

-- for k, v in pairs(curses.colors) do 
--     print(k, v)
-- end

local function do_test()
    local screen = curses.Screen()
    screen:setcursor(1, 1)
    screen:write("Hello, World!", colors.WHITE, colors.CYAN)
    screen:setcursor(2, 2)
    screen:write("Name: ", colors.BLACK, colors.GREEN)
    screen:refresh()
    local name = screen:readline()
    screen:setcursor(3,3)
    screen:write(name, 0, 7)
    screen:refresh()
    screen:destroy()
end

do_test()

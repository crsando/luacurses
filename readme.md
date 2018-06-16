# luacurses

A simple Lua wrapper for (n)curses. Attempts to expose an API which is more Lua-esque than just the base (n)curses one.

## Getting Started

These instructions will get you a copy of luacurses up and running on your local machine for development and testing purposes.

### Prerequisites

In order to build luacurses you will need the following:
- A C compiler (GCC is recommended)
- Make
- Lua 3.5.2 (or later) and the associated headers
- (N)curses and the associated headers

### Building

Simply clone or download the repository and run `make linux` from the `src/` directory.

### Installing

Copy `luacurses.so` and put it in the same directory as your Lua executable (or with your other libraries).

## Features

Luacurses only exposes a small subset of the (n)curses API. This is because 1) it would be more work to do so and 2) the additional benefit of supporting the entire API is quite small as the (n)curses API contains a large number of redundant and obsolete methods (for compatibility reasons).

That being said, luacurses is a feature-rich and capable (n)curses wrapper and exposes the following methods:

#TODO: Do this!

## Built With

[GCC](https://gcc.gnu.org/) - C compiler.  
[Lua 3.5.4](https://www.lua.org/) - Lua language.  
[Ncurses](https://www.gnu.org/software/ncurses/) - The flavor of curses used in testing this wrapper (although any curses library should work).  

## Contributing

Simply fork the repository, make your changes, and make a pull request.

## License

This project is licensed under the MIT License - see [license.md](license.md) for details.

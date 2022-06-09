# 42-fillit
by ikarjala and staskine @ Hive Helsinki

This is a school project for the coding school Hive Helsinki.
The goal of the program is to parse an input file containing ASCII representations of tetriminos (tetris blocks)
and arrange them to fit inside the smallest possible square.

# Implementation
Our project uses a recursive solver with 64-bit values to represent tetriminos as well as chunks of the grid;
each 0 or 1 representing free or occupied space in a given position.
This allows us to more effectively both check (via bitwise operations) whether there is room for a tetrimino in a given position on the grid,
as well as place it down on the map or remove it.

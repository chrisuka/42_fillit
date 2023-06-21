# Fillit
by [ikarjala](https://github.com/qriskap) and [staskine](https://github.com/staskine) @ [Hive Helsinki](https://www.hive.fi/en/)

This is a school project for the coding school Hive Helsinki.
The goal of the program is to parse an input file containing ASCII representations of tetriminos (tetris blocks)
and arrange them to fit inside the smallest possible square.

The version tagged [old](https://github.com/ickarjala/42-fillit/tree/old) is the first version of the program to pass evaluations.

## Installation
For a normal build just go into the root folder and type
``make all`` or ``make install``.
For a debug build use ``make debug``. This adds debug symbols and fsanitize to the binary.
For more info see the Makefile.

## Usage
```
$> ./fillit <tetrimino_file>
```
where *tetrimino_file* is of format:
* at least 1 4x4 grid depicting a single tetrimino
* blocks represented by \#, empty spaces by \.
* exactly 4 blocks per shape
* every block is connected
* must be one of the classic known tetris shapes
* multiple tetriminos separated with 1 linebreak, no extra linebreak after last shape
* no more than 26 tetriminos

See the example files in `eval_tests`.

## Implementation
Our project uses a recursive solver with 64-bit values to represent tetriminos as well as chunks of the grid;
each 0 or 1 representing free or occupied space in a given position.
* the map is an array of 16-bit values each representing one 16-wide row in the grid
* each tetrimino has a 64-bit code representing how it covers a 4-row area in a map
* as we iterate the x and y, we can cast one row in the map to a chunk of 4 rows and overlay the tetrimino code over it.

This allows us to more effectively both check (via bitwise operations) whether there is room for a tetrimino in a given position on the grid,
as well as place it down on the map or remove it.
```
we represent the teriminos as 64 bits, which map in memory the same way as 4 rows in the map
.#..             0010 <
.#..             0010
##..   becomes   0011 -> 0x0322 (ULL) -> 0x0000000300020002ULL
....             0000

```
(extra zeroes are an empty area of the row because a tetrimino only needs 4 bits per row)

We do not rotate the tetriminos as they would be considered different shapes.
We print the tetriminos on the map as alphabet corresponding to the order in the file.

Example :
```
$> cat -e eval_tests/nom.fillit
#...$
#...$
#...$
#...$
$
####$
....$
....$
....$
$
.#..$
##..$
.#..$
....$
$> ./fillit eval_tests/nom.fillit
ABBBB
A.C..
ACC..
A.C..
.....
$>
```
As the example shows, when there are multiple ways to fit the tetris into an equal-sized square area,
we prefer setting the tetris earlier in the queue closer to the top-left, origin of the map.
order of importance: tetrimino index > y > x

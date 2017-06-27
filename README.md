# Sudoku Solver

[Sudoku](https://en.wikipedia.org/wiki/Sudoku) Solver.

This solver supports solving 4x4 boards, with 2x2 regions, and 9x9 boards, with 3x3 regions. For simplicity, no other board types are supported.

## Motivation

Wanted to work on a small side project to get better at programming in C++.

## Usage

```bash
$ solver < examples/9x9sudoku_1.txt
```

The initial state of the Sudoku board is read from `stdin`. It expects a 2D grid of numbers in a square where blank spots are represented by `.`. For examples, see the `examples` directory. Whitespace is ignored when reading in the initial board.

### Installation

```bash
$ mkdir build && cd build
$ cmake .. && make solver
```

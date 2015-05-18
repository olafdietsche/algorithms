// -*- mode: c++ -*-
#ifndef __eight_queens_h_included__
#define __eight_queens_h_included__

// Copyright (c) 2015 Olaf Dietsche

/* usage:
    board b(8);
    if (eight_queens(b))
        b.print(std::cout);
*/

#include <iostream>
#include <vector>

class board {
public:
	board(int size);

	int size() const { return board_size; }

	bool valid(int row, int col) const;
	void set(int row, int col) { a[row][col] = true; }
	void clear(int row, int col) { a[row][col] = false; }

	void print(std::ostream &f) const;

private:
	bool row_empty(int row) const;
	bool column_empty(int col) const;
	bool diagonals_empty(int row, int col) const;

	int board_size;
	std::vector<std::vector<bool> > a;
};

bool eight_queens(board &b, int row = 0);

#endif

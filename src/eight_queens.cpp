#include "eight_queens.h"

board::board(int size)
	: board_size(size),
	  a(board_size, std::vector<bool>(board_size, false))
{
}

bool board::valid(int row, int col) const
{
	return row_empty(row) && column_empty(col) && diagonals_empty(row, col);
}

bool board::row_empty(int row) const
{
	for (int col = 0; col < board_size; ++col) {
		if (a[row][col])
			return false;
	}

	return true;
}

bool board::column_empty(int col) const
{
	for (int row = 0; row < board_size; ++row) {
		if (a[row][col])
			return false;
	}

	return true;
}


bool board::diagonals_empty(int row, int col) const
{
	int r, c;

	// check first diagonal
	if (row < col) {
		r = 0;
		c = col - row;
	} else {
		r = row - col;
		c = 0;
	}

	for (; r < board_size && c < board_size; ++r, ++c) {
		if (a[r][c])
			return false;
	}

	// check second diagonal
	if (row < board_size - col) {
		r = 0;
		c = col + row;
	} else {
		r = row - (board_size - col - 1);
		c = board_size - 1;
	}

	for (; r < board_size && c >= 0; ++r, --c) {
		if (a[r][c])
			return false;
	}

	return true;
}

void board::print(std::ostream &f) const
{
	f << '+';
	for (int col = 0; col < board_size; ++col)
		f << '-';

	f << "+\n";

	for (int row = 0; row < board_size; ++row) {
		f << '|';
		for (int col = 0; col < board_size; ++col)
			f << (a[row][col] ? '*' : ' ');

		f << "|\n";
	}

	f << '+';
	for (int col = 0; col < board_size; ++col)
		f << '-';

	f << "+\n";

	for (int row = 0; row < board_size; ++row) {
		for (int col = 0; col < board_size; ++col)
			if (a[row][col])
				f << '(' << row << ',' << col << ")\n";
	}
}

bool eight_queens(board &b, int row)
{
	for (int col = 0; col < b.size(); ++col) {
		if (b.valid(row, col)) {
			b.set(row, col);
			if (row == b.size() - 1 || eight_queens(b, row + 1))
				return true;

			b.clear(row, col);
		}
	}

	return false;
}

#include <iostream>

#define N 81		// sudoku size
#define A 9			// row/col size
#define B 3			// box size

void row_col_fix(int*, bool, int);

void sort_sudoku(int*);

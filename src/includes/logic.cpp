#include <iostream>
#include "utils.h"

#define N 81
#define A 9
#define B 3

//TODO:
// candidate operations
//			find all possible candidates using the three basic rules of sudoku
// row/col/boxSolver
//			if number can be placed in only one field of row/col/box it will be placed there
// row/col/boxMatchSolver
//			if number of candidates, their value and the amount of fields are all equal no other
//			candidates are relevant
// mutually exclusive region solver
//			explained on the website

void find_candidates(int* sudoku)
{
		int candidates[N][10] = {0};		// 10 because one extra integer serves as candidate counter

		for (int i = 0; i < N; i++)
				if (sudoku[i] == 0)
						for (int j = 1; j <= A; j++)
								if (row_col_is_valid(sudoku, 0, i, j) && row_col_is_valid(sudoku, 1, i, j) && box_is_valid(sudoku, i, j))
								{
										candidates[i][candidates[i][A]] = j;
										candidates[i][A]++;
								}

		print_candidates(candidates);
}

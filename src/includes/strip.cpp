#include <iostream>
#include "utils.h"
#include "logic.h"

#define N 81
#define A 9
#define B 3

void strip_sudoku(int* sudoku)
{
		int indices[N] = {0};
		int help = 0;

		fill_array(indices, N);
		shuffle_array(indices, N);

		for (int i = 0; i < 30; i++)
		{
				sudoku[indices[i]] = 0;
				/*
				help = sudoku[indices[i]];
				sudoku[indices[i]] = 0;
				if (!can_solve(sudoku, ))
						sudoku[indices[i]] = help;
						*/
		}
		find_candidates(sudoku);
}

/*
bool can_solve(int* sudoku)
{
		find_candidates(sudoku);


}
*/


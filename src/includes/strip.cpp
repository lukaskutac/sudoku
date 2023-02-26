#include <iostream>
#include "utils.h"
#include "logic.h"

#define N 81
#define A 9
#define B 3

// TODO:
// [ ] isntead of randomly shuffling array choose a number that has the least possibilities for filling
//			- when i remove the first number the next number can't be in the same row/col/box as the first 
//			one and so on

void strip_sudoku(int* sudoku)
{
		int indices[N] = {0};
		int help = 0;

		fill_array(indices, N);
		shuffle_array(indices, N); // don't do that 

		for (int i = 0; i < 30; i++)		// maybe there's some logic to removing the numbers (so far it's random)
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


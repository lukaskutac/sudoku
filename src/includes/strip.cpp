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
// [ ] don't pick already removed indices

bool can_solve(int* sudoku)
{
		int candidates[N][10] = {0};		// 10 because one extra integer serves as candidate counter

		solve_sudoku(sudoku, candidates);

		return puzzle_is_solved(candidates);
}

void strip_sudoku(int* sudoku)
{
		int indices[N] = {0};
		int forbidden[N] = {0};
		int help;
		int ri;					// random index
		int fc = 0;			// forbidden counter
		int index;
		int offset;

		fill_array(indices, N);			// initial filling of the indices array

		for (int i = 0; i < N; i++)
		{
				if (i % A == 0 && i != 0)		// every 9th cycle
				{
						printf("filling array\n");
						fill_array(indices, N);			// reset available indices (otherwise we wouldn't have any)
						printf("placing forbidden\n");
						place_forbidden(indices, forbidden, fc);		// place forbidden indices (already removed numbers)
				}

				// improve picking nubmers so that i don't pick already removed numbers
				ri = pick_random(indices);		// pick a random available index 
				printf(", i: %d\n", i);
				help = sudoku[ri];
				sudoku[ri] = 0;

				if (!can_solve(sudoku))
				{
						sudoku[ri] = help;
						continue;
				}

				forbidden[fc] = ri;			// already picked indices (we don't want to pick them again)
				fc++;
				printf("fc: %d\n", fc);

				for (int x = 0; x < B; x++)
						for (int j = 0; j < A; j++)
						{
								index = (x == 0) ? (ri / A * A) : ((x == 1) ? ri % A : (ri / 27 * 27 + ri % A / B * B));
								offset = (x == 0) ? j : ((x == 1) ? (j * A) : (j % B + j / B * A));

								indices[index + offset] = N;
						}
		}
}

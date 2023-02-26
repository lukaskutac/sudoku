#include <iostream>
#include "utils.h"

#define N 81
#define A 9
#define B 3

//TODO:
// [x] candidate operations
//			find all possible candidates using the three basic rules of sudoku
// [ ] row/col/boxSolver
//			if number can be placed in only one field of row/col/box it will be placed there
// [ ] row/col/boxMatchSolver
//			if number of candidates, their value and the amount of fields are all equal no other
//			candidates are relevant
// [ ] mutually exclusive region solver
//			explained on the website

void single_solver(int candidates[][10])
{
		// if there's a number that only fits one field in row/col/box remove all other candidates from this field (i think)
		// and remove this candidate from all fields in the row/col/box it is unique to
		// TODO:
		// [ ] add a cycle for changing modes so that the code isn't repeated so much (kinda like utils::sudoku_is_valid)
		// [ ] determine the wheter number is unique using the registered method
		// also it doesn't work, it only does something with the first col for some reason + it's not even correct
		
		bool checked[A] = {false};
		//bool registered[A];
		bool unique;
		int index;

		for (int i = 0; i < A; i++)
		{
				//reset(registered, A);
				index = i * A;

				for (int j = 0; j < A; j++)
				{
						for (int k = 0; k < candidates[index + j][A]; k++)
						{
								unique = true;

								if (!checked[candidates[index + j][k] - 1])
										checked[candidates[index + j][k] - 1] = true;
								else
										continue;

								for (int l = index; l < index + A; l++)
								{
										if (l == index + j)
												continue;

										for (int m = 0; m < candidates[l][A]; m++)
												if (candidates[l][m] == candidates[index + j][k])
														unique = false;
								}

								if (unique)
										remove_candidates(candidates, 0, index, candidates[index][k]);
						}
				}
		}
}

void basic_candidates(int* sudoku, int candidates[][10], int* given)
{
		// finds all numbers that could be placed in a certain field that follow the basic sudoku rules 
		// (number appears only once in every row/col/box)
		
		int gc = 0;			// given counter

		for (int i = 0; i < N; i++)
		{
				if (sudoku[i] == 0)	// maybe set candidates to sudoku[i] in different color for better readability
						for (int j = 1; j <= A; j++)
						{
								if (!box_is_valid(sudoku, i, j))
										continue;
								else if (row_col_is_valid(sudoku, 0, i, j) && row_col_is_valid(sudoku, 1, i, j))
								{
										candidates[i][candidates[i][A]] = j;
										candidates[i][A]++;
								}
						}
				else
				{
						candidates[i][0] = sudoku[i];
						given[gc] = i;
						gc++;
				}
		}
}

void find_candidates(int* sudoku)
{
		int candidates[N][10] = {0};		// 10 because one extra integer serves as candidate counter
	  int given[N] = {0};							// numbers that are given by sudoku

		basic_candidates(sudoku, candidates, given);
		print_candidates(candidates, given);
		single_solver(candidates);
		print_candidates(candidates, given);
}



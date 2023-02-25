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

				for (int j = 0; j < candidates[index][A]; j++)
				{
						unique = true;

						if (!checked[candidates[index][j] - 1])
								checked[candidates[index][j] - 1] = true;
						else
								continue;

						for (int k = i * A; k < A; k++)
						{
								if (k == index)
										continue;

								for (int l = 0; l < candidates[k][A]; l++)
										if (candidates[k][j] == candidates[index][j])
												unique = false;
						}

						if (unique)
								remove_candidates(candidates, index, candidates[index][j]);

						index++;
				}
		}
}

void basic_candidates(int* sudoku, int candidates[][10])
{
		// finds all numbers that could be placed in a certain field that follow the basic sudoku rules 
		// (number appears only once in every row/col/box)
		

		for (int i = 0; i < N; i++)
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
}

void find_candidates(int* sudoku)
{
		int candidates[N][10] = {0};		// 10 because one extra integer serves as candidate counter
																		//
		basic_candidates(sudoku, candidates);
		print_candidates(candidates);
		single_solver(candidates);
		print_candidates(candidates);
}



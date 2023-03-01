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
		// [ ] determine the whether number is unique using the registered method
		// [ ] it works but not completely, when it finished it should mark green all single fields and remove this candidate
		//			from all other fields (idea: lower the candidates[index][A] every time you remove candidate and shift them so 
		//			that they're next to each other with no spaces and if the value of candidates[index][A] == 1 recursively call
		//			remove_candidates, good luck, hope it works)
		
		bool checked[A];
		//bool registered[A];
		bool unique;
		int index;
		int offset;			// offset for going through all fields of row/col/box
		int checking_offset;		// offset for going through all fields needed for comaprison

		for (int x = 0; x < B; x++)			// switching modes
				for (int i = 0; i < A; i++)			// switching row/col/box 
				{
						reset(checked, A);

						for (int j = 0; j < A; j++)			// switching fields within row/col/box
						{
								// index formula depends on whether we want to check row/col/box
								index = (x == 0) ? (i * A) : ((x == 1) ? i : (i / B * 27 + i % B * B));
								offset = (x == 0) ? j : ((x == 1) ? (j * A) : (j % B + j / B * A));

								if (candidates[index + offset][A] == 1)
								{
										remove_candidates(candidates, index + offset, candidates[index + offset][0]);
										continue;
								}

								for (int k = 0; k < candidates[index + offset][A]; k++)	// going through candidates within field
								{
										unique = true;

										if (candidates[index + offset][k] == 0)			// this candidate was previously removed
												continue;

										if (!checked[candidates[index + offset][k] - 1])		// make sure we check every number once at most
												checked[candidates[index + offset][k] - 1] = true;
										else
												continue;

										for (int l = 0; l < A; l++)			// going through fields in the same row/col/box to compare them
										{
												checking_offset = (x == 0) ? l : ((x == 1) ? (l * A) : (l % B + l / B * A));

												if (index + checking_offset == index + offset)
														continue;

												for (int m = 0; m < candidates[index + checking_offset][A]; m++)			// going through candidates of all fields in the same row
														if (candidates[index + checking_offset][m] == candidates[index + offset][k])
														{
																unique = false;
																break;
														}

												if (!unique)
														break;
										}

										if (unique)
										{
												remove_candidates(candidates, index + offset, candidates[index + offset][k]);
												break;
										}
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
				if (sudoku[i] == 0)			// if number was removed
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
		printf("basic: \n");
		print_candidates(candidates, given);
		single_solver(candidates);
		printf("single solve: \n");
		print_candidates(candidates, given);
}



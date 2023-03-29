#include <iostream>
#include "utils.h"

#define N 81
#define A 9
#define B 3

void single_solver(int candidates[][10])
{
		bool checked[A];
		bool unique;
		int index;
		int offset;							// offset for going through all fields of row/col/box
		int checking_offset;		// offset for going through all fields needed for comaprison

		for (int x = 0; x < B; x++)			// switching modes
				for (int i = 0; i < A; i++)			// switching row/col/box depending on mode
				{
						reset(checked, A);

						// index and offset formula depends on whether we want to check row/col/box
						index = (x == 0) ? (i * A) : ((x == 1) ? i : (i / B * 27 + i % B * B));

						for (int j = 0; j < A; j++)			// switching fields within row/col/box
						{
								offset = (x == 0) ? j : ((x == 1) ? (j * A) : (j % B + j / B * A));

								if (candidates[index + offset][A] == 1)
								{
										remove_candidates(candidates, index + offset, candidates[index + offset][0]);
										continue;
								}

								for (int k = 0; k < candidates[index + offset][A]; k++)	// going through candidates within field
								{
										unique = true;

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

void reset_possible_sets(int arr[][5])
{
		for (int i = 0; i < A; i++)
				for (int j = 0; j < 5; j++)
						arr[i][j] = 0;
}

void basic_candidates(int* sudoku, int candidates[][10], int* given)
{
		// finds all numbers that could be placed in a certain field that follow the basic sudoku rules 
		// (number appears only once in every row/col/box)
		
		int gc = 0;			// given counter

		for (int i = 0; i < N; i++)
		{
				if (sudoku[i] == 0)			// if field is blank
						for (int j = 1; j <= A; j++)		// checking numbers 1 - 9
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
						candidates[i][A] = 1;
						given[gc] = i;
						gc++;
				}
		}
}

void solve_sudoku(int* sudoku, int candidates[][10])
{
	  int given[N] = {0};			// numbers that are given by sudoku

		basic_candidates(sudoku, candidates, given);
		single_solver(candidates);
}



#include <iostream>
#include "utils.h"

#define N 81
#define A 9
#define B 3

//TODO:
// [x] basic candidates
//			find all possible candidates using the three basic rules of sudoku
// [x] single solver
//			if number can be placed in only one field of row/col/box it will be placed there
// [ ] hidden candidates
//			explained lower
// [ ] intersecting candidates
//			explained online

void single_solver(int candidates[][10])
{
		// if there's a number that only fits one field in row/col/box remove all other candidates from this field (i think)
		// and remove this candidate from all fields in the row/col/box it is unique to
		// TODO:
		// [x] add a cycle for changing modes so that the code isn't repeated so much (kinda like utils::sudoku_is_valid)
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
				for (int i = 0; i < A; i++)			// switching row/col/box depending on mode
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

// skip given cells
// each cell must have atlest one common candidate (unless its a twin, then it has to have 2 
// all the time)
// take a cell, consider its candidates, if some of those are the same as another cell continue
// else skip this cell, then do cell counter++, the amount of common candidates cannost be lower 
// then counter 
//
// difficulty levels:
// 1. [ ] easy - solvable by reducing number of candidates to one
// 2. [ ] medium - solvable by finding hidden/naked twins, triples and quads
// 3. [ ] hard - solvable by using everything above + by removing intersecting candidates
//							from certain fields


void reset_possible_sets(int arr[][5])
{
		for (int i = 0; i < A; i++)
				for (int j = 0; j < 5; j++)
						arr[i][j] = 0;
}

void hidden_candidates(int candidates[][10], int* given) // remove given from pars (i just need it for dev stuff)
{
		// looks for sets* of candidates hidden in a cluster of candidates (and also naked candidates*)
		// *sets - either pairs, triples or quads
		// *naked candidates - when the amount of fields is eaqual to amount of distinct candidates in 
		// those fields

		int possible_sets[A][5];
		int num;
		int index, offset, last_index;
		bool is_a_set;

		for (int x = 0; x < B; x++)
				for (int i = 0; i < A; i++)
				{
						reset_possible_sets(possible_sets);

						for (int j = 0; j < A; j++)
						{
								index = (x == 0) ? (i * A) : ((x == 1) ? i : (i / B * 27 + i % B * B));
								offset = (x == 0) ? j : ((x == 1) ? (j * A) : (j % B + j / B * A));
								last_index = candidates[index + offset][A];

								for (int k = 0; k < last_index; k++)
								{
										num = candidates[index + offset][k];		// puts candidate into a variable

										possible_sets[num - 1][possible_sets[num - 1][4]] = (index + offset);

										if (possible_sets[num - 1][4] < 3)
												possible_sets[num - 1][4]++;
										else
										{
												possible_sets[num - 1][4] = A;
												break;
										}
								}
						}

						for (int j = 0; j < 8; j++)
						{
								if (possible_sets[j][4] == A)
										continue;

								for (int k = j + 1; k < A; k++)
								{
										if (possible_sets[k][4] == A)
												continue;

										is_a_set = true;

										if (possible_sets[j][4] == possible_sets[k][4])
										{
												for (int l = 0; l < possible_sets[j][4]; l++)
												{
														if (possible_sets[j][l] != possible_sets[k][l])
														{
																is_a_set = false;
																break;
														}
												}

												if (is_a_set)
												{
														printf("unit id: %d, mode: %d is a set of %d numbers: ", i, x, possible_sets[j][4]);
														for (int z = 0; z < possible_sets[j][4]; z++)
																printf("%d, ", candidates[possible_sets[j][z]][z]);
														printf("\n");
														print_candidates(candidates, given);
												}
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
	  int given[N] = {0};							// numbers that are given by sudoku

		basic_candidates(sudoku, candidates, given);
		//printf("basic: \n");
		//print_candidates(candidates, given);
		single_solver(candidates);
		hidden_candidates(candidates, given);
//		print_candidates(candidates, given);
}



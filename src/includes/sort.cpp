#include <iostream>
#include "utils.h"

#define N 81		// sudoku size
#define A 9			// row/col size
#define B 3			// box size

bool row_col_fix(int* sudoku, bool mode, int index)	// later make it a bool func. so i know if it was succesful or suckful
{
		// searches box for a number that is possibly missing in row or column (based on mode)

		// if (index % B == 2) -> skip (neni treba kontrolovat, asi)
		// optimize: don't check the whole box, just the possible indeces (under or right to the index)
		bool tried_prev = false;

try_prev:
		int first_index = ((index % A) / B) * B + (index / 27) * 27;		// first index of first row inside of box cotaining index (the parameter)
		int last_index = first_index + 27;															// first index of first row outside of box cotaining index (the parameter)

		for (int i = first_index; i < last_index; i += A)		// index of the beginning of a row
				for (int j = 0; j < B; j++)											// index of the beginning + column offset
						if (is_available(index, i + j, mode))
								if (row_col_is_valid(sudoku, mode, index, sudoku[i + j]))
								{
										std::swap(sudoku[index], sudoku[i + j]);
										return true;
								}

		if (!tried_prev)
		{
				index = previous_instance(sudoku, index, mode, 0);
				tried_prev = true;
				goto try_prev;
		}

		return false;
}

/*
bool try_swap(int* sudoku, bool mode, int index)
{
		// forces to switch the repeating number with the adjacent number so then a different number 
		// is being repeated, then it forces to switch this number with the number adjacent to it and 
		// it just repeats that until the row/col is sorted
		
		int swap_index = index;
		int offset = mode ? 1 : A;
		int counter;
		bool looped;
		bool next_available = mode ? ((index % A) % B == 0) : ((index / A) % B == 0);
		bool tried_next = false;		// tried next row or column
		bool swaped_ROC = false;			// swap Row Or Column
		
try_again:
		counter = 0;
		looped = false;

		printf("before: \n");
		print(sudoku);

		while (true)
		{
				if (swap_index == index && counter != 0) // if we come over the base index 2 times the algorithm is stuck in a loop
				{
						if (looped)
								break;
						else
								looped = true;
				}

				printf("%d. swapped %d and %d at %d\n", counter, sudoku[swap_index], sudoku[swap_index + offset], swap_index);
				std::swap(sudoku[swap_index], sudoku[swap_index + offset]);
				swap_index = previous_instance(sudoku, swap_index, mode, sudoku[swap_index]);
				if (swap_index < 0)
				{
						printf("success!\n after: \n");
						print(sudoku);
						return true;
				}

				counter++;
		}

		if (next_available)
		{
				if (!tried_next)
				{
						offset *= 2;
						tried_next = true;
						swap_index = index;
						goto try_again;
				}
				else if (!swaped_ROC)
				{
						int first_index = mode ? index % A : (index / A) * A;
						int last_index = mode ? first_index + 72 : first_index + 8;
						int incrementor = mode ? A : 1;
						bool swap_set = false;

						printf("swapping %s %d and %d\n", mode ? "cols" : "rows", first_index, first_index + offset);
						for (int i = first_index; i <= last_index; i += incrementor)
						{
								std::swap(sudoku[i], sudoku[i + offset]);
								if (!swap_set && !row_col_is_valid(sudoku, mode, i, 0))
								{
										swap_index = i;
										swap_set = true;
								}
						}
						
						if (!swap_set)
								return false;

						// change offset
						swaped_ROC = true;
						//offset *= 2;
						goto try_again;
				}
		}

		printf("try_swap failed at index: %d\n", index);
		printf("after: \n");
		print(sudoku);

		return false;
}
*/

bool try_swap(int* sudoku, bool mode, int index)
{
		// forces to switch the repeating number with the adjacent number so then a different number 
		// is being repeated, then it forces to switch this number with the number adjacent to it and 
		// it just repeats that until the row/col is sorted
		
		int offset = mode ? 1 : A;
		bool next_available = mode ? ((index % A) % B == 0) : ((index / A) % B == 0);
		bool tried_next = false;
		
try_next:
		int swap_index = index;
		int counter = 0;
		bool looped = false;

		printf("before: \n");
		print(sudoku);

		while (true)
		{
				if (swap_index == index && counter != 0) // if we come over the base index 2 times the algorithm is stuck in a loop
				{
						if (looped)
								break;
						else
								looped = true;	// the algorithm is stuck in a loop
				}

				printf("%d. swapped %d and %d at %d\n", counter, sudoku[swap_index], sudoku[swap_index + offset], swap_index);
				std::swap(sudoku[swap_index], sudoku[swap_index + offset]);
				swap_index = previous_instance(sudoku, swap_index, mode, sudoku[swap_index]);
				if (swap_index < 0)
				{
						printf("success!\n after: \n");
						print(sudoku);
						return true;
				}

				counter++;
		}

		if (!tried_next && next_available)
		{
				printf("trying_next\n");
				offset *= 2;
				tried_next = true;
				goto try_next;
		}
		else
				printf("failed next\n");

		printf("try_swap failed at index: %d\n", index);
		printf("after: \n");
		print(sudoku);

		return false;
}

void sort_sudoku(int* sudoku)
{
		int first_index;
		int last_index;
		int incrementor;

		for (int i = 0; i < N; i += 10)
		{
				if (i % 30 == 20)
						continue;

				for (int j = 0; j < 2; j++)
				{
						first_index = (j == 0) ? (i / A) * A : i % A;
						last_index = (j == 0) ?  A * (i / A) + 8 : (i % A) + 72;
						incrementor = (j == 0) ? 1 : A;

						for (int k = first_index; k <= last_index; k += incrementor)
								if (!row_col_is_valid(sudoku, j, k, 0))
										printf("fuck segmentation %d\n", k);

										/*
										if (!row_col_fix(sudoku, j, k))
												printf("fuck segmentation\n");
												//try_swap(sudoku, j , k);
												*/
				}
		}
}

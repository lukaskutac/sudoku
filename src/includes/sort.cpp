#include <iostream>
#include "utils.h"

#define N 81		// sudoku size
#define A 9			// row/col size
#define B 3			// box size

bool row_col_fix(int* sudoku, bool mode, int index)	
{
		// searches box for a number that is possibly missing in row or column (based on mode)

		bool tried_prev = false;

try_prev:

		int first_index = ((index % A) / B) * B + (index / 27) * 27;
		int last_index = first_index + 27;

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

bool try_swap(int* sudoku, bool mode, int index, bool backtrack)
{
		// forces to switch the repeating number with the adjacent number so then a different number 
		// is being repeated, then it forces to switch this number's previous instance with the number 
		// adjacent to it and it just repeats that until the row/col is sorted
		
		int swap_index = index;
		int offset = backtrack ? (mode ? 2 : 18) : (mode ? 1 : A);
		int counter;
		bool looped;
		bool next_available = backtrack ? false : (mode ? ((index % A) % B == 0) : ((index / A) % B == 0));
		bool tried_next = false;				// tried next row or column
		bool swaped_ROC = false;				// swap Row Or Column
		
try_again:
		counter = 0;
		looped = false;

		while (true)
		{
				if (swap_index == index && counter != 0) // if we come over the base index 2 times the algorithm is stuck in a loop
				{
						if (looped)
								break;
						else
								looped = true;
				}

				std::swap(sudoku[swap_index], sudoku[swap_index + offset]);
				swap_index = previous_instance(sudoku, swap_index, mode, sudoku[swap_index]);
				if (swap_index < 0)
						return true;

				if (counter % 1000 == 0 && counter != 0)
						return false;

				counter++;
		}

		if (next_available)
				if (!tried_next)
				{
						offset = mode ? 2 : 18;
						tried_next = true;
						goto try_again;
				}

		return false;
}

void backtrack_sort(int* sudoku, int* parameters, int count)
{
		int index = 0;
		int first_index;
		int incrementor;
		int last_index;
		bool found_rep;

		for (int i = 0; i < count; i += 2)
		{
				first_index = parameters[i] ? (parameters[i + 1] % A) : ((parameters[i + 1] / A) * A);
				last_index = parameters[i] ? (first_index + 72) : (first_index + 8);
				incrementor = parameters[i] ? A : 1;
				found_rep = false;

				for (int j = first_index; j <= last_index; j += incrementor)
				{
						if (!row_col_is_valid(sudoku, parameters[i], j, 0))
						{
								found_rep = true;
								index = j;
								break;
						}
				}

				if (!found_rep)
						continue;

				if (!try_swap(sudoku, parameters[i], index, true))
						printf("backtrack failed\n");
		}
}

void sort_sudoku(int* sudoku)
{
		int first_index;
		int last_index;
		int incrementor;
		bool backtrack = false;
		int bc = 0;			// backtrack counter
		int parameters[18] = {0}; 

		for (int i = 0; i < N; i += 10)
		{
				if (i % 30 == 20)
						continue;

				for (int j = 0; j < 2; j++)
				{
						first_index = (j == 0) ? (i / A) * A : i % A;
						last_index = (j == 0) ?  first_index + 8 : first_index + 72;
						incrementor = (j == 0) ? 1 : A;

						for (int k = first_index; k <= last_index; k += incrementor)
								if (!row_col_is_valid(sudoku, j, k, 0))
										if (!row_col_fix(sudoku, j, k))
												if (!try_swap(sudoku, j , k, 0))
												{
														backtrack = true;
														parameters[bc] = j;
														parameters[bc + 1] = k;
														bc += 2;
												}
				}
		}

		if (backtrack)
				backtrack_sort(sudoku, parameters, bc);
}

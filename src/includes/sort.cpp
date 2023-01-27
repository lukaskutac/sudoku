#include <iostream>
#include "utils.h"

#define N 81		// sudoku size
#define A 9			// row/col size
#define B 3			// box size

bool row_col_fix(int* sudoku, bool mode, int index)
{
		// searches box for a number that is possibly missing in row or column (based on mode)

		// if (index % B == 2) -> skip (neni treba kontrolovat, asi)

		int first_index = ((index % A) / B) * B + (index / 27) * 27;		// first index of first row inside of box cotaining index (the parameter)
		int last_index = first_index + B * A;														// first index of first row outside of box cotaining index (the parameter)

		for (int i = first_index; i < last_index; i += A)		// index of the beginning of a row
				for (int j = 0; j < B; j++)											// index of the beggining + column offset
						if (is_available(i + j, mode))
								if (row_col_is_valid(sudoku, mode, index, sudoku[i + j]))
										std::swap(sudoku[index], sudoku[i + j]);

}

void sort_sudoku(int* sudoku, int index)
{
		int last_index;
		int incrementor;

		for (int i = 0; i < N; i += 10)
		{
				for (int j = 0; j < 2; j++)
				{
						last_index = (j == 0) ?  A * (i / A) + (A - 1) : (i % A) + (A - 1) * A;
						incrementor = (j == 0) ? 1 : A;

						for (int k = i; k < last_index; k += incrementor) // mozna nastavit k = 0 
								if (!row_col_is_valid(sudoku, j, k, 0))
										if (row_col_fix(sudoku, j, k))


				}

		}
}

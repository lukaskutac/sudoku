#include <iostream>
#include "utils.h"

#define N 81		// sudoku size
#define A 9			// row/col size
#define B 3			// box size

bool row_col_fix(int* sudoku, bool mode, int index)
{
		// searches box for a number that is possibly missing in row or column (based on mode)

		// ((index / 3) % 3)*3 -> sloupec boxu
		// ((index / 9) % 3)*3 -> radek boxu
		// 
		// if (index % B == 2) -> skip (neni treba kontrolovat, asi)

		int first_index = (mode) ? ((index + 1) / (A * B)) * (A * B) : ((index + A) / B) * B;
		int first_index = (index / A) * A + ((index % A) / B) * B;
		int last_index = first_index + (2 - (index / A) % B) * A; 

		for (int i = first_index; i <= last_index; i += incrementor)
				if (row_col_is_valid(sudoku, i, ))
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

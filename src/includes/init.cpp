#include <iostream>
#include "sort.h"
#include "utils.h"

#define N 81		// sudoku size
#define A 9			// row/col size
#define B 3			// box size

void init_box(int box[A])		
{														
		// initialize box array
		
		for (int i = 0; i < A; i++)
				box[i] = i + 1;
}

void init_sudoku(int sudoku[N])			
{
		// initialize sudoku array box by box
		
		int box[A] = {0};
		int index = 0;

		init_box(box);

		for (int i = 0; i < A; i++)
		{
				shuffle_box(box);

				for (int j = 0; j < A; j++)
				{
						index = (i / B) * (A * B) + (i % B) * B + (j / B) * A + j % B; // don't even ask
						sudoku[index] = box[j];
				}
		}
}

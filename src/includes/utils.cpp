#include <iostream>
#include <random>

#define N 81		// sudoku size
#define A 9			// row/col size
#define B 3			// box size

std::random_device rd;


void print(int* sudoku)		
{
		// formats the sudoku grid for better readability
		
		char line[] = " ------- ------- ------- \n";

		for (int i = 0; i < A; i++)
		{
				if (i % B == 0) printf("%s", line);

				for (int j = 0; j < A; j++)
				{
						if (j % B == 0) printf("| ");

						if (sudoku[i * A + j] != 0) printf("%d ", sudoku[i * A + j]);
						else printf(". ");
				}
				printf("|\n");
		}

		printf("%s", line);
}


void shuffle_box(int* box)		
{
		// shuffle initialized box array
		
		std::uniform_int_distribution<int> dist(0, 7);

		for (int i = 8; i > 0; i--)
				std::swap(box[i], box[dist(rd) % i]);
}

bool row_col_is_valid(int* sudoku, bool mode, int index, int num)		
{
		// validates row or column based on mode (mode == false -> check row, mode == true -> check column)
		// num is for checking a different value than sudoku[index] (checking possible numbers)

		int value = (num == 0) ? sudoku[index] : num;
		int decrementor = (mode) ? A : 1;
		int end = (mode) ? index % A : (index / A) * A;

		for (int i = index - decrementor; i >= end; i -= decrementor)
				if (sudoku[i] == value)
						return false;

		return true;
}

bool sudoku_is_valid(int* sudoku)
{
		// basiclly just repeatedly calls row_col_is_valid in both modes to check all rows and cols
		// pozn. vylepsit: pouzit bool array a pokud bude prvek zaznamenan nastavi se index o jeho hodnote na true,
		// pokud po cele iteraci bude nejaky prvek false -> return false jinak true
		 
		for (int i = 0; i < N; i++)
				if (!row_col_is_valid(sudoku, 0, i, 0))
						return false;

		for (int i = 0; i < N; i++)
				if (!row_col_is_valid(sudoku, 1, i, 0))
						return false;

		return true;
}

bool is_available(int index, bool mode)
{
		// returns true if an index is available to swap with (meaning the number behind it hasn't been sorted yet
		// or it has but it's adjacent to the duplicite number) otherwise returns false
		
		if (!mode)
				if ()


}

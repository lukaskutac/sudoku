#include <iostream>
#include <random>

#define N 81		// sudoku size
#define A 9			// row/col size
#define B 3			// box size

std::random_device rd;

void print(int* sudoku)		
{
		// formats the sudoku grid for better readability
		
		printf("\n");
		
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

		printf("%s\n", line);
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
		// checking of the num parameter doesn't work yet

		int value = (num == 0) ? sudoku[index] : num;
		int decrementor = mode ? A : 1;
		int first_index = (num == 0) ? (index - decrementor) : (mode ? (index % A) + (A - 1) * A : (index / A) * A + (A - 1));
		int last_index = mode ? index % A : (index / A) * A;

		for (int i = first_index; i >= last_index; i -= decrementor)
				if (i != index && sudoku[i] == value)
						return false;

		return true;
}

bool sudoku_is_valid(int* sudoku)
{
		// basiclly just repeatedly calls row_col_is_valid in both modes to check all rows and cols
		// pozn. vylepsit: pouzit bool array a pokud bude prvek zaznamenan nastavi se index o jeho hodnote na true,
		// pokud po cele iteraci bude nejaky prvek false -> return false jinak true
		 
		/*
		for (int i = 0; i < B; i++)
				if (!row_col_is_valid(sudoku, 0, i, 0))
						return false;

		for (int i = 0; i < B; i++)
				if (!row_col_is_valid(sudoku, 1, i, 0))
						return false;
						*/

		bool registered[A] = {false};

		for (int i = 0; i < B; i++)
				for (int j = i * A; j < i * A + A; j++)
						if (!registered[sudoku[i] - 1])
								registered[sudoku[i] - 1] = true;

		for (int i = 0; i < A; i++)
				if (!registered[i])
						return false;

		return true;
}

int previous_instance(int* sudoku, int index, bool mode, int num)
{
		// looks for previous instance of number behind index depending on mode
				
		int decrementor = mode ? A : 1;
		int first_index = (num == 0) ? (mode ? index - A : index - 1) : (mode ? index % A + 72 : (index / A) * A + 8 );
		int last_index = mode ? index % A : (index / A) * A;
		int value = (num == 0) ? sudoku[index] : num;

		/*
		 * bool swapped[A];

			 if (swapped[mode ? i / A : i % A])
			 return i;

			 */
		for (int i = first_index; i >= last_index; i -= decrementor)
				if (value == sudoku[i])
						return i;

		return -1;
}

bool is_available(int index, int candidate_index, bool mode)
{
		// returns true if candidate_index is available to swap with (meaning the number behind it hasn't been sorted yet
		// or it has but it's adjacent to the duplicite number) otherwise returns false

		if (index == candidate_index)
				return false;

		if (!mode)
		{
				if (index / A >= candidate_index / A)		// only number that's below index
						return false;
				if (index % A < index / A)							// number that's in the sorted part
				{
						if (index % A == candidate_index % A)		// number that's in the same column as index
								return true;
						else																		// number that's in the sorted part but different column than index
								return false;
				}
				if (index / A > candidate_index % A)		// number that's below or on the right side of index
						return false;
		}
		else
		{
				if (index % A >= candidate_index % A)		// only number that's on the right side of index
						return false;
				if (index / A <= index % A)							// number that's in the sorted part
				{
						if (index / A == candidate_index / A)		// number that's in the same row as index
								return true;
						else																		// number that's in the sorted part but different row than index
								return false;
				}
				if (index % A >= candidate_index / A)		// only number that's below index 
						return false;
		}

		return true;
}

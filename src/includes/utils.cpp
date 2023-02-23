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

/*
void shuffle_array(int* arr, int size)		
{
		// shuffle initialized box array
		
		std::uniform_int_distribution<int> dist(0, (size - 2));

		for (int i = (size - 1); i > 0; i--)
				std::swap(box[i], box[dist(rd) % i]);
}
*/

bool row_col_is_valid(int* sudoku, bool mode, int index, int num)		// rename to RoC_is_valid()	
{
		// validates row or column based on mode (mode == false -> check row, mode == true -> check column)
		// num is for checking a different value than sudoku[index] (checking possible numbers)
		// checking of the num parameter doesn't work yet

		if (index == 0)
				return true;

		int value = (num == 0) ? sudoku[index] : num;
		int incrementor = mode ? A : 1;
		int first_index = mode ? index % A : (index / A) * A;
		int last_index = (num == 0) ? ((index == 0) ? index : index - incrementor) : (mode ? first_index + 72 : first_index + 8);

		for (int i = first_index; i <= last_index; i += incrementor)
				if ((i != index || num != 0) && sudoku[i] == value)
						return false;

		return true;
}

void reset (bool* arr, int size)
{
		// sets all elements of given bool array to 0 (false)

		for (int i = 0; i < size; i++)
				arr[i] = 0;

		return;
}

bool sudoku_is_valid(int* sudoku)
{
		// basically just repeatedly calls row_col_is_valid in both modes to check all rows and cols
		// pozn. vylepsit: pouzit bool array a pokud bude prvek zaznamenan nastavi se index o jeho hodnote na true,
		// pokud po cele iteraci bude nejaky prvek false -> return false jinak true
		 
		bool registered_in_row[A];
		bool registered_in_col[A];
		bool registered_in_box[A];
		int box_index;

		// checking all rows
		for (int i = 0; i < N; i += A)
		{
				reset(registered_in_row, A);

				for (int j = 0; j < A; j++)
				{
						if (!registered_in_row[sudoku[i + j] - 1])
								registered_in_row[sudoku[i + j] - 1] = true;
						else 
						{
								printf("index: %d\n", i + j);
								return false;
						}
				}
		}

		// checking all columns
		for (int i = 0; i < A; i++)
		{
				reset(registered_in_col, A);

				for (int j = 0; j < N; j += A)
				{
						if (!registered_in_col[sudoku[i + j] - 1])
								registered_in_col[sudoku[i + j] - 1] = true;
						else 
						{
								printf("index: %d\n", i + j);
								return false;
						}
				}
		}

		// checking all boxes
		for (int i = 0; i < A; i++)
		{
				reset(registered_in_box, A);

				for (int j = 0; j < A; j++)
				{
						box_index = (i / B) * 27 + (i % B) * B + (j / B) * A + j % B;

						if (!registered_in_box[sudoku[box_index] - 1])
								registered_in_col[sudoku[box_index] - 1] = true;
						else 
						{
								printf("index: %d\n", box_index);
								return false;
						}
				}
		}

		return true;
}

int previous_instance(int* sudoku, int index, bool mode, int num)
{
		// looks for previous instance of number behind index depending on mode
				
		int incrementor = mode ? A : 1;
		int first_index = mode ? index % A : (index / A) * A;
		int last_index = (num == 0) ? (mode ? index - A : index - 1) : (mode ? first_index + 72 : first_index + 8 );
		int value = (num == 0) ? sudoku[index] : num;

		for (int i = first_index; i <= last_index; i += incrementor)
				if (value == sudoku[i] && index != i)
						return i;

		return -1;
}

void swap_ROC(int* sudoku, int f_ix, int l_ix, int inc, bool recursion)
{
		int offset = recursion ? ((inc == 1) ? 18 : 2) : ((inc == 1) ? A : 1);

		for (int i = f_ix; i <= l_ix; i += inc)
				std::swap(sudoku[i], sudoku[i + offset]);
}

bool is_available(int index, int candidate_index, bool mode)
{
		// returns true if candidate_index is available to swap with (meaning the number behind it hasn't been sorted yet
		// or it has but it's adjacent to the duplicite number) otherwise returns false

		if (index == candidate_index)
				return false;

		if (!mode)			// tells us if index is available for row
		{
				if (index / A >= candidate_index / A)		// only number that's below index
						return false;
				if (index % A < index / A)							// index is in the sorted part
				{
						if (index % A == candidate_index % A)		// number that's in the same column as index
								return true;
						else																		// number that's in the sorted part but different column than index
								return false;
				}
				if (index / A > candidate_index % A)		// number that's below or on the right side of index
						return false;
		}
		else		// tells us if index is available for column
		{
				if (index % A >= candidate_index % A)		// only number that's on the right side of index
						return false;
				if (index / A <= index % A)							// index is in the sorted part
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

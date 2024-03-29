#include <iostream>
#include <random>

#define N 81		// sudoku size
#define A 9			// row/col size
#define B 3			// box size

std::random_device rd;

void print_sudoku(int* sudoku, bool* given, int current)		
{
		// formats the sudoku grid for better readability
		
		printf("\n");
		
		char line[] = "\t      ------- ------- ------- \n";
		bool printing_current;

		for (int i = 0; i < A; i++)
		{
				printf("\33[0;37m");

				if (i % B == 0) 
						printf("%s", line);

				printf("\t     ");

				for (int j = 0; j < A; j++)
				{
						if (j % B == 0) 
								printf("| ");

						if ((i * A + j) == current)
						{
								printing_current = true;
								printf("\33[7;36m");
						}

						if (sudoku[i * A + j] != 0) 
						{
								if (!printing_current)
										if (given[i * A + j])
												printf("\33[1;31m");
										else
												printf("\33[0;33m");

								printf("%d", sudoku[i * A + j]);
						}
						else 
								printf(".");

						printing_current = false;
						printf("\33[0;37m ");
				}

				printf("|\n");
		}

		printf("%s\n", line);
}

void mark_given(int* sudoku, bool* given)
{
		for (int i = 0; i < N; i++)
				if (sudoku[i] != 0)
						given[i] = true;
}

int max_val(int arr[][10], int col)
{
		int max = arr[col][A];

		for (int i = col; i < N; i += A)
				if (arr[i][A] > max)
						max = arr[i][A]; 

		return max;
}

void print_candidates(int candidates[][10], int* given)
{
		// fromatted print of candidates array
		
		int column_width[A] = {0};
		int given_index = 0; 
		bool used_color;

		for (int i = 0; i < A; i++)
				column_width[i] = max_val(candidates, i);

		printf("\n");
		printf("\33[0;37m");
		
		for (int i = 0; i < N; i++)
		{
				if (i % A == 0)
				{
						for (int j = 0; j < A; j++)
						{
								printf("%s", j % B == 0 ? "++" : "+");

								for (int k = 0; k < (column_width[j] + 2); k++)
										printf("%c", i % 27 == 0 ? '=' : '-');
						}
						printf("++\n");

						printf("|| ");
				}

				for (int j = 0; j < column_width[i % A]; j++)
				{
						if (given[given_index] == i)
						{
								printf("\33[0;35m");
								used_color = true;
								given_index++;
						}
						else if (candidates[i][A] <= 1)
						{
								printf("\33[0;32m");
								used_color = true;
						}
						else
								printf("\33[0;31m");

						if (candidates[i][j] != 0)
						{
								printf("%d", candidates[i][j]);
								if (used_color)
								printf("\33[0;37m");
						}
						else
						{
								printf(" ");
								printf("\33[0;37m");
						}
				}

				if (i % A == 8)
						printf(" ||\n");
				else if (i % B == 2)
						printf(" || ");
				else
						printf(" | ");
		}

		for (int j = 0; j < A; j++)
		{
				printf("%s", j % B == 0 ? "++" : "+");

				for (int k = 0; k < (column_width[j] + 2); k++)
						printf("=");
		}
		printf("++\n");
}

bool puzzle_is_solved(int candidates[][10]) 
{
		// returns true if candidates in all fields have been reduced to exactly one

		for (int i = 0; i < N; i++)
				if (candidates[i][A] > 1)
						return false;

		return true;
}

int pick_random(int* indices, int* forbidden)
{
		// picks a random available index

		int available_indices[N] = {0};			// array of available indices we can remove
		int ac = 0;			// available index counter
		int random;
		int index;

		for (int i = 0; i < N; i++)
				if (indices[i] != N)	// only numbers that aren't related to any of the removed numbers and/or aren't removed themselves 
				{
						available_indices[ac] = indices[i];
						ac++;
				}

		if (ac == 0)		// in case no indices are available we make a list of indices of not yet removed numbers
		{
				int fc = 0;

				for (int i = 0; i < N; i++)
				{
						if (forbidden[fc] == i)
								fc++;
						else
						{
								available_indices[ac] = i;
								ac++;
						}
				}
		}

		std::uniform_int_distribution<int> dist(0, (ac - 1));

		random = dist(rd);

		return available_indices[random];
}

void flag_forbidden(int* indices, int* forbidden, int fc)
{
		for (int i = 0; i < fc; i++)
				indices[forbidden[i]] = N; 

		return;
}

bool has_next(int candidates[][10], int index, int candidate_index)
{
		if (candidates[index][A] > candidate_index)
				return true;

		return false;
}

void remove_candidates(int candidates[][10], int index, int unique_num)
{
		int field;
		int offset;
		int shift_count;

		if (candidates[index][A] != 1)
		{
				for (int i = 1; i < candidates[index][A]; i++)
						candidates[index][i] = 0;

				candidates[index][0] = unique_num;
				candidates[index][A] = 1;
		}

		for (int x = 0; x < B; x++)
				for (int i = 0; i < A; i++)
				{
						field = (x == 0) ? (index / A * A) : ((x == 1) ? (index % A) : (index / 27 * 27 + (index % A) / B * B));
						offset = (x == 0) ? i : ((x == 1) ? (i * A) : (i % B + i / B * A));

						if (index == (field + offset))
								continue;

						for (int k = 0; k < candidates[field + offset][A]; k++)
						{
								if (candidates[field + offset][A] == 1)
										continue;
								else if (candidates[index][0] == candidates[field + offset][k])
								{
										candidates[field + offset][k] = 0;

										shift_count = k;

										while (has_next(candidates, field + offset, shift_count))		// so that there isn't a blank space (0) between candidates
										{
												candidates[field + offset][shift_count] = candidates[field + offset][shift_count + 1];
												candidates[field + offset][shift_count + 1] = 0;
												shift_count++;
										}

										candidates[field + offset][A]--;

										// change condition so that its only true if im not gonna check it in the future in single sort
										// (it's behind index, to determine this i need to know mode)
										if (candidates[field + offset][A] == 1)	
										{
												remove_candidates(candidates, (field + offset), candidates[field + offset][0]);
										}
								}
						}
				}

		return;
}

void shuffle_array(int* arr, int size)
{
		// shuffle initialized box array
		
		std::uniform_int_distribution<int> dist(0, (size - 2));

		for (int i = (size - 1); i > 0; i--)
				std::swap(arr[i], arr[dist(rd) % i]);
}

void fill_array(int* arr, int size)
{
		// inserts unique values from 0 to 'size' into given array (size - 1 to be exact)

		for (int i = 0; i < size; i++)
				arr[i] = i;
}

bool row_col_is_valid(int* sudoku, bool mode, int index, int num)
{
		// validates row or column based on mode (mode == false -> check row, mode == true -> check column)
		// num is for checking a different value than sudoku[index] (checking possible numbers)

		if (index == 0 && num == 0)
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

bool box_is_valid(int* sudoku, int index, int num)
{
		// validates 3*3 box
		// num parameter is for checking different number than sudoku[index]
		
		int value = (num == 0) ? (sudoku[index]) : num;
		int box_id = (index / 27) * B + (index % A) / B;
		int first_index = (box_id / B) * 27 + (box_id % B) * B;
		int box_index;

		for (int i = 0; i < A; i++)
		{
				box_index = first_index + (i / B) * A + i % B;

				if (i != index && sudoku[box_index] == value)
						return false;
		}

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
		// i could've just used the row_col_is_valid and box_is_valid functions called repeatedly, but this
		// is a bit quicker and simpler and it is sufficient for what i need it to do
		 
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
								printf("Failed at index: %d\n", i + j);
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
								printf("Failed at index: %d\n", i + j);
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
								printf("Failed at index: %d\n", box_index);
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

void save_solution(int* sudoku, int* solution)
{
		for (int i = 0; i < N; i++)
				solution[i] = sudoku[i];
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

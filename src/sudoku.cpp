#include <iostream>
#include "includes/sort.h"
#include "includes/init.h"
#include "includes/utils.h"

#define N 81
#define A 9
#define B 3

int main()
{
    int sudoku[81] = {0};

		while (true)
		{
				init_sudoku(sudoku);
				print(sudoku);
				sort_sudoku(sudoku);
				print(sudoku);
				if (!sudoku_is_valid(sudoku))
						return 0;
		}

		// puzzle_sudoku(sudoku);
    

    return 0;
}

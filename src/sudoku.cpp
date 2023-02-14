#include <iostream>
#include "includes/sort.h"
#include "includes/init.h"
#include "includes/utils.h"

#define N 81
#define A 9
#define B 3

// TODO:
// try_swap nefunguje
// ujednotit poradi parametru (mode, index, ...)

int main()
{
    int sudoku[81] = {0};
		int counter = 0;

		while (true)
		{
				counter++;
				init_sudoku(sudoku);
				sort_sudoku(sudoku);

				if (counter % 10000 == 0)
						printf("counter: %d\n", counter);

				if (!sudoku_is_valid(sudoku))
				{
						print(sudoku);
						printf("counter: %d\n", counter);
						break;
				}
		}

		// puzzle_sudoku(sudoku);

    return 0;
}

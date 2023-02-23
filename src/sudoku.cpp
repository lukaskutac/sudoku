#include <iostream>
#include "includes/sort.h"
#include "includes/init.h"
#include "includes/utils.h"
#include "includes/strip.h"

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
		double time_taken;
		clock_t start = clock();
		clock_t end;

		while (true)
		{
				counter++;
				init_sudoku(sudoku);
				sort_sudoku(sudoku);
				//strip_sudoku(sudoku);

				if (counter % 100000 == 0)
				{
						end = clock();
						time_taken = double(end - start) / double(CLOCKS_PER_SEC);
						printf("counter %d, time taken: %f\n", counter, time_taken);
						start = clock();
				}

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

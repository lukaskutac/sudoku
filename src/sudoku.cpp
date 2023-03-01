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
    int sudoku[N] = {0};
		int solution[N] = {0};
		int counter = 0;
		double time_taken;
		clock_t start = clock();
		clock_t end;

		printf("\033[0;37m");

		init_sudoku(sudoku);
		sort_sudoku(sudoku);
		save_solution(sudoku, solution);
		strip_sudoku(sudoku);
		printf("solution:\n");
		print_sudoku(solution);
		printf("puzzle:\n");
		print_sudoku(sudoku);

		end = clock();
		time_taken = double(end - start) / double(CLOCKS_PER_SEC);
		printf("counter %d, time taken: %f\n", counter, time_taken);

		/*
		while (true)
		{
				counter++;
				init_sudoku(sudoku);
				sort_sudoku(sudoku);
				strip_sudoku(sudoku);

				if (counter % 100000 == 0)
				{
						end = clock();
						time_taken = double(end - start) / double(CLOCKS_PER_SEC);
						printf("counter %d, time taken: %f\n", counter, time_taken);
						start = clock();
				}

				if (!sudoku_is_valid(sudoku))
				{
						print_sudoku(sudoku);
						printf("counter: %d\n", counter);
						break;
				}
		}
		*/

    return 0;
}

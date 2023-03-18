#include <iostream>
#include "includes/sort.h"
#include "includes/init.h"
#include "includes/utils.h"
#include "includes/strip.h"

#define N 81
#define A 9
#define B 3

// TODO:
// [ ] ujednotit poradi parametru (mode, index, ...)

int main()
{
    int sudoku[N] = {0};
		int solution[N] = {0};
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

		printf("time: %f\n", time_taken);

    return 0;
}

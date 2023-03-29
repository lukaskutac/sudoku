#include <iostream>
#include "includes/sort.h"
#include "includes/init.h"
#include "includes/utils.h"
#include "includes/strip.h"
#include "includes/ui.h"

#define N 81
#define A 9
#define B 3

// don't include iostream in .h files

int main()
{
    int sudoku[N] = {0};
		int solution[N] = {0};
		bool play;

		printf("\033[0;37m");

		while (true)
		{
				play = menu();

				if (!play)
						return 0;
				else
				{
						init_sudoku(sudoku);
						sort_sudoku(sudoku);
						save_solution(sudoku, solution);
						strip_sudoku(sudoku);
				}

				play_game(sudoku, solution);
		}

    return 0;
}

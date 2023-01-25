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

		init_sudoku(sudoku);
		print(sudoku);

    return 0;
}

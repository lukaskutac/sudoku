#include <iostream>
#include <cstdlib>
#include <ctime>
#include <array>
#include "includes/generate.h"
#include "includes/init.h"

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
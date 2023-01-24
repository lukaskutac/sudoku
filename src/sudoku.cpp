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

    printf("Invalid row indices: \n");
    for (int i = 0; i < N; i++)
    {
        if (!row_col_is_valid(sudoku, 0, i, 0))
            printf("index: %d\n", i);
    }

    printf("Invalid col indices: \n");
    for (int i = 0; i < N; i++)
    {
        if (!row_col_is_valid(sudoku, 1, i, 0))
            printf("index: %d\n", i);
    }

		if (sudoku_is_valid(sudoku))
				printf("SuDoKu is valid! Yaaay\n");
		else
				printf("SuDoKu is invalid! Naaay\n");

    return 0;
}

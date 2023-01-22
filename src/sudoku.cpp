#include <iostream>
#include <cstdlib>
#include <ctime>
#include <array>
#include "includes/generate.h"

#define N 81
#define A 9
#define B 3

// -- MOTIVATION --
// Okay, I know how this is going to sound, but hear me out...
// I know I had some troubles in the past with staying motivated 
// enough to finish this but this time I will finish this program, 
// no more excuses.

int main()
{
    int sudoku[81] = {0};

		for (int i = 0; i < A; i++)
				for (int j = 0; j < A; j++)
						sudoku[i * A + j] = j;

		print(sudoku);

    return 0;
}

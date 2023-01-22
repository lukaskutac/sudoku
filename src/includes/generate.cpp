#include <iostream>
#include "solve.h"

#define N 81
#define A 9
#define B 3

void print(int sudoku[])
{
		// for terminal interface

		char line[] = " ------- ------- ------- \n";

		for (int i = 0; i < A; i++)
		{
				if (i % B == 0) printf("%s", line);

				for (int j = 0; j < A; j++)
				{
						if (j % B == 0) printf("| ");

						if (sudoku[i * A + j] != 0) printf("%d ", sudoku[i * A + j]);
						else printf(". ");
				}

				printf("|\n");
		}

		printf("%s", line);
}

void fill(int sudoku[])
{

		


}

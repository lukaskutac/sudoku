#include <iostream>
#include <random>
#include "utils.h"

#define N 81
#define A 9
#define B 3

std::random_device rd;

void print(int sudoku[])		// formats the sudoku grid for better readability
{
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

void shuffle_box(int box[A])		// shuffle initialized box array
{
		std::uniform_int_distribution<int> dist(0, 7);

		for (int i = 8; i > 0; i--)
				std::swap(box[i], box[dist(rd) % i]);
}

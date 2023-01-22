#include <iostream>
#include <random>
#include "generate.h"

#define N 81
#define A 9
#define B 3

std::random_device rd;

void init_box(int box[A])		// initialize box array
{														
		for (int i = 0; i < A; i++)
				box[i] = i + 1;
}

void shuffle_box(int box[A])		// shuffle initialized box array
{
		std::uniform_int_distribution<int> dist(0, 7);

		for (int i = 8; i > 0; i--)
				std::swap(box[i], box[dist(rd) % i]);
}

void init_sudoku(int sudoku[N])			// initialize sudoku array box by box
{
		int box[A] = {0};
		int index = 0;

		init_box(box);

		for (int i = 0; i < A; i++)
		{
				shuffle_box(box);

				for (int j = 0; j < A; j++)
				{

						index = i * A + (j % 3) * 3 + j / 3;
						sudoku[index] = box[j];
				}
		}
}

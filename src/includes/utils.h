#include <iostream>

#define N 81
#define A 9
#define B 3

void print(int*);

void shuffle_box(int*);

bool row_col_is_valid(int*, bool, int, int);

bool sudoku_is_valid(int*);

int available_box_index(int);

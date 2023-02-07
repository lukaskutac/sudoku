#include <iostream>

#define N 81
#define A 9
#define B 3

void print(int*);

void shuffle_box(int*);

bool row_col_is_valid(int*, bool, int, int);

void reset(bool*, int);

int previous_instance(int*, int, bool, int);

bool sudoku_is_valid(int*);

bool is_available(int, int, bool);

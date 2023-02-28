#include <iostream>

#define N 81
#define A 9
#define B 3

void print_sudoku(int*);

void print_candidates(int(*)[10], int*);

void remove_candidates(int(*)[10], int, int);

void shuffle_array(int*, int);

void fill_array(int*, int);

bool row_col_is_valid(int*, bool, int, int);

bool box_is_valid(int*, int, int);

void reset(bool*, int);

int previous_instance(int*, int, bool, int);

bool sudoku_is_valid(int*);

void swap_ROC(int*, int, int, int, bool);

bool is_available(int, int, bool);

#include <iostream>
#include <stdio.h>
#include <termios.h>
#include "utils.h"

#define N 81		// sudoku size
#define A 9			// row/col size
#define B 3			// box size

#define KEY_UP 65
#define KEY_DOWN 66
#define KEY_LEFT 68
#define KEY_RIGHT 67

static struct termios old, current;

// Initialize new terminal i/o settings
void initTermios(int echo) 
{
		tcgetattr(0, &old);					// grab old terminal i/o settings
		current = old;							// make new settings same as old settings
		current.c_lflag &= ~ICANON; // disable buffered i/o

		if (echo)
				current.c_lflag |= ECHO;		// set echo mode
		else
				current.c_lflag &= ~ECHO;		// set no echo mode

		tcsetattr(0, TCSANOW, &current);		// use these new terminal i/o settings now
}

// Restore old terminal i/o settings
void resetTermios(void) 
{
		tcsetattr(0, TCSANOW, &old);
}

// Read 1 character - echo defines echo mode
char getch_(int echo) 
{
		char ch;
		initTermios(echo);
		ch = getchar();
		resetTermios();
		return ch;
}

// Read 1 character without echo
char getch(void) 
{
		return getch_(0);
}

// Read 1 character with echo
char getche(void) 
{
		return getch_(1);
}

void title()
{
		system("clear");

		printf("\t ____        ____        _  __     \n"); 
		printf("\t/ ___| _   _|  _ \\  ___ | |/ /   _ \n"); 
		printf("\t\\___ \\| | | | | | |/ _ \\| ' / | | |\n");
		printf("\t ___) | |_| | |_| | (_) | . \\ |_| |\n");
		printf("\t|____/ \\__,_|____/ \\___/|_|\\_\\__,_|\n");
}

bool menu()
{
		char x = ' ';
		bool message;
		bool invalid_input = false;

		while (true)
		{
				title();
				printf("\n\t\t-- MAIN MENU --\n\n");
				printf("\t[1] PLAY\n");
				printf("\t[2] CONTROLS (how to play)\n");
				printf("\t[3] RULES\n");
				printf("\t[4] EXIT\n");

				if (invalid_input)
				{
						printf("\n\tNot a valid input. Please try again...\n");
						invalid_input = false;
				}

				switch (getch())
				{
						case '1':
								return true;
								break;
						case '2':
								title();
								printf("\n\t\t-- CONTROLS --\n\n");
								printf("\t- in main menu choose option 1 (PLAY) to start the game\n");
								printf("\t- use arrow keys (up/down/right/left) to move around the grid\n");
								printf("\t- press a number to enter it into the grid\n");
								printf("\t- press 'q' or 'Q' to stop playing\n");
								printf("\n\tPress any key to return to main menu...\n");
								x = getch();
								break;
						case '3':
								title();
								printf("\n\t\t-- RULES --\n\n");
								printf("\t- each row must contain the numbers from 1 to 9, without repetition\n");
								printf("\t- each column must contain the numbers from 1 to 9, without repetition\n");
								printf("\t- each box must contain the numbers from 1 to 9, without repetition\n");
								printf("\t- fill the whole grid to win\n");
								printf("\t- you are allowed to do maximum of 3 mistakes, then you lose\n");
								printf("\n\tPress any key to return to main menu...\n");
								x = getch();
								break;
						case '4':
								title();
								printf("\n\t\t-- EXIT --\n\n");
								printf("\tDo you really want to exit the application? (y/n): \n\n");

								message = false;

								while (true)
								{
										x = getch();
										if (x == 'y' || x == 'Y')
												return false;
										else if (x == 'n' || x == 'N')
												break;
										else if (!message)
										{
												printf("\tNot a valid input. Please try again...\n");
												message = true;
										}
								}

								message = false;
								break;
						default:
								invalid_input = true;
								break;
				}
		}
}

bool is_a_number(char x)
{
		// checking ASCII number codes
		for (int i = 49; i <= 57; i++)
				if (x == i)
						return true;

		return false;
}

bool is_blank(int* sudoku, int index)
{
		return !sudoku[index];
}

bool is_valid(int* solution, int index, int num)
{
		return (solution[index] == num) ? true : false;
}

void final_screen(int result)
{
		switch (result)
		{
				case 0:
						printf("\n\tGame ended.\n");
						break;
				case 1:
						printf("\n\tGame Over! You did too many mistakes.\n");
						break;
				case 2:
						printf("\n\tCongratulations! You won the game.\n");
						break;
				default:
						break;
		}

		printf("\n\tPress any key to return to main menu...\n");
		getch();
}

bool victory(int* sudoku)
{
		for (int i = 0; i < N; i++)
				if (sudoku[i] == 0)
						return false;

		return true;
}

void play_game(int* sudoku, int* solution)
{
		bool given[N] = {false};
		bool game_over = false;
		bool invalid_input = false;
		int invalid_message;
		int result;
		int current = 0;
		int mistakes = 0;
		int num;
		char x;

		mark_given(sudoku, given);

		while (true)
		{
				title();
				print_sudoku(sudoku, given, current);
				printf("\n\tMistakes: %d\n", mistakes);

				if (invalid_input)
				{
						switch (invalid_message)
						{
								case 0:
										printf("\n\tInvalid input, please try again...\n");
										break;
								case 1:
										printf("\n\tThis field is already solved, try a different one...\n");
										break;
								case 2:
										printf("\n\tNumber %c isn't the answer for this field...\n", x);
										break;
								default:
										break;
						}

						invalid_input = false;
				}

				if (game_over)
						break;

				// because in ASCII there isn't a single value for each arrow key but rather a sequence of keys
				// i have to use a sequence of switch statements to determine which arrow key was pressed
				x = getch();

				switch(x)
				{
						case 27:
								switch(getch())
								{
										case 91:
												switch(getch())
												{
														case KEY_UP:
																if (current / A != 0)
																		current -= A;
																break;
														case KEY_DOWN:
																if (current / A != 8)
																		current += A;
																break;
														case KEY_RIGHT:
																if (current % A != 8)
																		current++;
																break;
														case KEY_LEFT:
																if (current % A != 0)
																		current--;
																break;
												}
												break;
										default:
												printf("some key has been pressed!\n");
												break;
								}
								break;
						default:
								invalid_input = true;

								if (x == 'q' || x == 'Q')
								{
										result = 0;
										game_over = true;
										break;
								}

								if (!is_a_number(x))
								{
										invalid_message = 0;
								}
								else
								{
										num = (int(x) - 48);
										printf("%d", num);

										if (!is_blank(sudoku, current))
										{
												invalid_message = 1;
										}
										else if (!is_valid(solution, current, num))
										{
												invalid_message = 2;
												mistakes++;
										}
										else
										{
												invalid_input = false;
												sudoku[current] = num;
										}
								}

								break;
				}

				if (mistakes > 3)
				{
						result = 1;
						game_over = true;
				}
				else if (victory(sudoku))
				{
						result = 2;
						game_over = true;
				}
		}

		final_screen(result);
}

#include <iostream>
#include <stdio.h>
#include <termios.h>
#include "utils.h"

#define N 81		// sudoku size
#define A 9			// row/col size
#define B 3			// box size

static struct termios old, current;

// Initialize new terminal i/o settings
void initTermios(int echo) 
{
		tcgetattr(0, &old);					/* grab old terminal i/o settings */
		current = old;							/* make new settings same as old settings */
		current.c_lflag &= ~ICANON; /* disable buffered i/o */

		if (echo)
				current.c_lflag |= ECHO;		/* set echo mode */
		else
				current.c_lflag &= ~ECHO;		/* set no echo mode */

		tcsetattr(0, TCSANOW, &current);		/* use these new terminal i/o settings now */
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
								printf("\t- press escape to stop playing\n");
								printf("\n\tPress any key to return to main menu...\n");
								x = getch();
								break;
						case '3':
								title();
								printf("\n\t\t-- RULES --\n\n");
								printf("\t- each row must contain the numbers from 1 to 9, without repetition\n");
								printf("\t- each column must contain the numbers from 1 to 9, without repetition\n");
								printf("\t- each box must contain the numbers from 1 to 9, without repetition\n");
								printf("\t- guessing is not allowed :)\n");
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

void play_game(int* sudoku, int* solution)
{
		int given[N] = {0};

		title();

		mark_given(sudoku, given);

		while (!game_over)
		{
				print_sudoku(sudoku, given);
				getch();
		}
}

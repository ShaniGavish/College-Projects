// ID: <315775841>
// full name: < Shani Gavish>

//This program execute the "four in a row" game

#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

//Board
#define ROWS 6
#define COLS 7
char board[ROWS][COLS];

//Consts
#define PLAYER1_SIGN 'x'
#define PLAYER2_SIGN 'O'
#define PLAYER1_NUMBER 1
#define PLAYER2_NUMBER 2
#define NOT_EMPTY_CELL_FOUND -1 //This is sign for not empty cell found
#define NUM_WIN 4 //The sequence of characters to reach in order to win


//Player
struct player
{
	int player_number;
	char player_sign;
};
typedef struct player PLAYER;


/*********** Declarations ************/

/*This function initializes the game board by assigning each cell
with ' ' (resulting with an empty game board).*/
void initBoard();

/*This function gets players and initializes the players by assigning for 
each player a number and a sign.*/
void initPlayers(PLAYER* player1, PLAYER* player2);

/*This function executes a game for given players*/
void RunGame(PLAYER player1, PLAYER player2);

/*The function gets the current player, executes a round of the game and returns true if the game is won*/
bool Round(PLAYER* current_player);

/*This function asks the player choose coloumn and return his input*/
int GetPlayerInput();

/*This function gets a player input and return it is valid*/
int ValidatePlayerInput(int player_input);

/*This function gets a column number and returns the number in the line of next empty cell in the column*/
int NextEmptyCell(int col);

/*This function gets players and switches the current player*/
void SwitchTurn(PLAYER** current_player, PLAYER* player1, PLAYER* player2);

/*This function gets a row number, a column number and a sign,
and assigns the cell with the given sign.*/
void setCell(int row, int col, char sign);

/*This function gets a row number and a column number (a cell),
and returns the character in that cell (could be 'X', 'O' or ' ').*/
char getCell(int row, int col);

/*This function prints the game board*/
void PrintBoard();

/*This function gets a row number and print the row in the game board*/
void PrintRow(int row);

/*This function gets a sign , row and col of the last step and returns if there is a winning sequance aroud that point*/
bool IsWin(int row , int col , char sign);

/*This functions gets a sign , row/col (depending on which check it is) ,
check and return if there is a sequance with that sign which is long 
enough to win (as follows in a row / column / diagonal) */
bool CheckWinInRow(int row, char sign);
bool CheckWinInCol(int col, char sign);
bool CheckWinInRightDiagonal(int row, int col, char sign);
bool CheckInWinLeftDiagonal(int row, int col, char sign);

/*This fuction check and return if there is a tie */
bool IsTie();

/*This function clears the screen.*/
void clearScreen();


/*************** Main ****************/
//created players , initializes the game board and players and runs the game.
int main()
{
	PLAYER player1, player2;
	initBoard();
	initPlayers(&player1, &player2);
	RunGame(player1, player2);
}


/********** Implementations **********/
void initBoard()
{
	int i, j;
	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			setCell(i + 1, j + 1, ' ');
		}
	}
}

void initPlayers(PLAYER* player1 , PLAYER* player2)
{
	(*player1).player_number = PLAYER1_NUMBER;
	(*player1).player_sign = PLAYER1_SIGN;
	(*player2).player_number = PLAYER2_NUMBER ;
	(*player2).player_sign = PLAYER2_SIGN;
}

void RunGame(PLAYER player1, PLAYER player2)
{
	bool win_flag = 0;
	bool tie_flag;
	PLAYER* current_player = &player1;
	PrintBoard();
	while (!win_flag)
	{
		win_flag = Round(current_player);
		tie_flag = IsTie();
		if (win_flag)
		{
			printf("player number %d won! :)", (*current_player).player_number);
			break;
		}
		else if (tie_flag)
		{
			printf("That's a tie");
			break;
		}
		SwitchTurn(&current_player, &player1, &player2);
	}
}

bool Round(PLAYER* current_player)
{
	int player_input, row_input;
	printf("Player number %d:\n", (*current_player).player_number);
	player_input = GetPlayerInput();
	row_input = NextEmptyCell(player_input);
	setCell(row_input, player_input, (*current_player).player_sign);
	clearScreen();
	PrintBoard();
	return IsWin(row_input, player_input,(*current_player).player_sign);
}

int GetPlayerInput()
{
	int player_input, isValidInput = 0;
	
	while (!isValidInput)
	{
		printf("Please enter column input(a number between 1 - %d) : ", COLS);
		scanf("%d", &player_input);
		isValidInput = ValidatePlayerInput(player_input);
	}
	return player_input;
}

int ValidatePlayerInput(int player_input)
{
	if ((player_input > COLS) || (player_input < 1))
	{
		printf("The col you entered is not between 1-%d\n",COLS);
		return 0;
	}
	else if (NextEmptyCell(player_input) == NOT_EMPTY_CELL_FOUND)
	{
		printf("The col you entered is full.\n");
		return 0;
	}
	return 1;
}

int NextEmptyCell(int col)
{
	int i;
	for (i = ROWS; i > 0; i--)
	{
		if (getCell(i, col) == ' ')
		{
			return i;
		}
	}
	return NOT_EMPTY_CELL_FOUND;
}

void SwitchTurn(PLAYER** current_player, PLAYER* player1, PLAYER* player2)
{
	if (*current_player == player1)
	{
		(*current_player) = player2;
	}
	else
	{
		(*current_player) = player1;
	}
}

void setCell(int row, int col, char sign)
{
	board[row - 1][col - 1] = sign;
}

char getCell(int row, int col)
{
	return board[row - 1][col - 1];
}

void PrintBoard()
{
	int i;
	char c='A';

	//Print the first line of the game view (numbers 1-7)
	printf("    ");
	for (i = 0; i < COLS; i++)
	{
		printf("%d    ", i+1);
	}
	printf("\n");
	
	//Print the lines in the game board (before each line characters A-F)
	for (i = 0; i < ROWS; i++)
	{
		printf("%c   ", c + i);
		PrintRow(i);
		printf("\n");
	}
}

void PrintRow(int row)
{
	int i;
	for (i = 0; i < COLS; i++)
	{
		printf("%c    ", getCell(row+1, i+1));
	}
}

bool IsWin(int row, int col, char sign)
{
	return CheckWinInRow(row, sign) || CheckWinInCol(col, sign) || CheckWinInRightDiagonal(row, col, sign) || CheckInWinLeftDiagonal(row, col, sign);
}

bool CheckWinInRow(int row,  char sign)
{
	int i, count=0;
	for (i = 0; i < COLS; i++)
	{
		if (getCell(row, i + 1) == sign)
		{
			count++;
			if (count == NUM_WIN)
			{
				return 1;
			}
		}
		else
		{
			count = 0;
		}
	}
	return 0;
}

bool CheckWinInCol(int col, char sign)
{
	int i, count=0;
	for (i = 0; i < ROWS; i++)
	{
		if (getCell(i + 1, col) == sign)
		{
			count++;
			if (count == NUM_WIN)
			{
				return 1;
			}
		}
		else
		{
			count = 0;
		}
	}
	return 0;
}

bool CheckInWinLeftDiagonal(int row, int col, char sign)
{
	int i;
	int temprow = row;
	int tempcol = col;
	int count = 0;
	//find initial position in the left diagonal for checking the diagonal
	while (temprow > 0 && tempcol > 0)
	{
		tempcol--;
		temprow--;
	}
	for (i = 0; i<ROWS-temprow && i<COLS-tempcol; i++)
	{
		if (getCell(temprow + i + 1, tempcol + i + 1) == sign)
		{
			count++;
			if (count == NUM_WIN)
			{
				return 1;
			}
		}
		else
		{
			count = 0;
		}
	}
	return 0;
}

bool CheckWinInRightDiagonal(int row, int col, char sign)
{
	int i;
	int temprow = row;
	int tempcol = col;
	int count = 0;
	//find initial position in the right diagonal for checking the diagonal
	while (temprow <ROWS && tempcol > 1)
	{

		tempcol--;
		temprow++;
	}
	for (i = 0; i <=temprow && i < COLS-tempcol; i++)
	{
		if (getCell(temprow - i , tempcol + i) == sign)
		{
			count++;
			if (count == NUM_WIN)
			{
				return 1;
			}
		}
		else
		{
			count = 0;
		}
	}
	return 0;
}

bool IsTie()
{
	int i;
	bool is_tie = 1;
	for (i = 0; i < COLS; i++)
	{
		if (NextEmptyCell(i) != NOT_EMPTY_CELL_FOUND)
		{
			is_tie = is_tie * 0;;
		}
	}
	return is_tie;
}

void clearScreen()
{
	system("cls");
}



// ID: <315775841>
// full name: < Shani Gavish>

//This program execute "Snake" game

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

//Board
#define ROWS 25
#define COLS 75
char board[ROWS][COLS];

//point
typedef struct point {
	int x;
	int y;
}POINT;

//Snake
typedef struct snake {
	POINT* point;
	struct snake* next;
	struct snake* previous;
} SNAKE;


//Consts
#define GAME_BOARD_BORDER_CHAR '#'
#define GAME_BOARD_INNER__CHAR ' '
#define SNAKE_SIGN '@'
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
#define GROWTH_RATE 5
#define INITIAL_SPEED 1
#define INCREASE_SPEED 0.03
#define MAX_SPEED 0.9
#define GAME_OVER_STR "GAME OVER"

/*********** Declarations ************/

//This function initiales the game board and prints it
void initGame();
// Turn escape codes ON.
void init(void);
//This function initiales the game board
void initGameBoard();
//This function initiales the border game board
void initGameBoardBorder();
//This function initiales the inner game board
void initGameboardInner();
/*This function gets line , start point, end point and char 
and fills line accordingly to the char*/
void initGameBoardLine(int line,int start,int end,char c);
//This function prints the game board
void printGameBoard();

//This function initialises snake and returns its pointer
SNAKE* initSnake();
//Creates a new unit and returns pointer to it. 
SNAKE* InitUnit();
//This function creats new point and return its pointer
POINT* initPoint();

/*This function executes a game for given snake*/
void runGame(SNAKE** snake_head);
//This function gets pointer to snake and prints it on the game board
void printSnakeHead(SNAKE* snake);
/*This function gets pointer to the snake head , current direction ,grow counter
and current speed executes a step of the snake and returns if the game is over*/
bool step(SNAKE** snake_head,char* current_direction,int* grow_counter,float* current_speed);
/* Moves the cursor to position (x,y) on screen.
Parameters:
x: the row of the posiiton.
y: the column of the posiiton.*/
void gotoxy(int x, int y);
/*Delays the execution of the program.
Parameters:
secs: the length of the delay in seconds.*/
void sleep(float secs);
//This function gets new and current directions and updates the current direction 
void updateDirection(char new_direction, char* current_direction);
//This function gets user input , checks and returns if its valid
bool isValidUserInput(char direction);
//This functions gets grow counter and returns if to increase the snake  
bool isGrow(int grow_counter);
/*This function gets pointer to the snake head and direction and
increases the snake in 1 unit*/
void grow(SNAKE** snake_head, char* direction);
/*This function gets pointer to the snake head , and a direction and moves the snake
accordingly to the direction*/
void moveSnake(SNAKE** snake_head, char* direction);
//This function gets pointer to the snake head and returns the last unit of tha snake
SNAKE* getLastUnit(SNAKE* snake_head);
/*This function gets pointer to the snake head and a unit of the snake 
and disconnects the unit from the snake*/
void disconnectUnitFromSnake(SNAKE* snake_head, SNAKE* unit);
/*This function gets pointer to the snake head and pointer to the new snake head
and inserts the new snake head on the front of the sanke */
SNAKE* insertBefore(SNAKE* snake_head, SNAKE* new_snake_head);
//This function gets pointer to a snake unit and removes it from the board game 
void removeUnitFromBoard(SNAKE* unit);
/*This functions updates the point of the new head snake according to the old 
head snake point*/
void update_New_Snake_Head_Point(POINT* old_head_point, POINT* new_head_point, char direction);
/*This function gets pointer to the snake head ,
checks and returns if the game is over*/
bool isGameOver(SNAKE* snake_head);
/*This function gets pointer to the snake head ,
checks and returns if the snack clashes into the border*/
bool isBorderClash(SNAKE* snake_head);
/*This function gets pointer to the snake head ,
checks and returns if the snack clashes into its self*/
bool isSelfClash(SNAKE* snake_head);
//This function gets two pointers to points and return if its equals
bool IsSamePosition(POINT* point1, POINT* point2);
//This functions free the snake
void freeSnake(SNAKE* snake_head);
//This functions ends the game and prints an "end game" on the screen
void endGame();


/*************** Main ****************/
int main() 
{
	SNAKE* snake = initSnake();
	SNAKE** snake_head = &snake;
	initGame();
	runGame(snake_head);
	freeSnake(*snake_head);
	endGame();
}



/********** Implementations **********/

void initGame()
{
	init();
	initGameBoard();
	printGameBoard();
}

void init(void)
{
	system("cls");
}

void initGameBoard()
{
	initGameBoardBorder();
	initGameboardInner();
}

void initGameBoardBorder()
{
	int i;
	initGameBoardLine(0,0,COLS,GAME_BOARD_BORDER_CHAR);
	for (i = 1; i < (ROWS - 1); i++)
	{
		board[i][0] = GAME_BOARD_BORDER_CHAR;
		board[i][COLS - 1] = GAME_BOARD_BORDER_CHAR;
	}
	initGameBoardLine(ROWS-1, 0, COLS, GAME_BOARD_BORDER_CHAR);
}

void initGameboardInner()
{
	int i;
	for (i = 1; i < (ROWS - 1); i++)
	{
		initGameBoardLine(i,1,COLS-1,GAME_BOARD_INNER__CHAR);
	}
}

void initGameBoardLine(int line, int start, int end, char c)
{
	int i;
	for (i=start; i < end; i++)
	{
		board[line][i] = c;
	}
}

void printGameBoard()
{
	int i, j;
	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			printf("%c", board[i][j]);
		}
		printf("\n");
	}
}

SNAKE* initSnake()
{
	SNAKE* head = InitUnit();
	head->point->x = ROWS / 2 + 1;
	head->point->y = COLS / 2 + 1;
	return head;
}

SNAKE* InitUnit()
{
	SNAKE* new_unit = (struct SNAKE*)malloc(sizeof(SNAKE));
	if (new_unit)
	{
		new_unit->point = initPoint();
		new_unit->previous = NULL;
		new_unit->next = NULL;
	}
	return new_unit;
}

POINT* initPoint()
{
	POINT* point = (POINT*)malloc(sizeof(POINT));
	return point;
}

void printSnakeHead(SNAKE* snake)
{
	gotoxy(snake->point->x, snake->point->y);
	printf("%c",SNAKE_SIGN);
}

void runGame(SNAKE** snake_head)
{
	char current_direction = RIGHT; //initial direction
	int grow_counter = -1; 
	float current_speed = INITIAL_SPEED; //initial speed
	printSnakeHead(*snake_head);
	while (!step(snake_head, &current_direction, &grow_counter, &current_speed))
	{
		printSnakeHead(*snake_head);
		gotoxy(ROWS + 1, 0);
		sleep(current_speed);
	}
}

bool step(SNAKE** snake_head, char* current_direction, int* grow_counter, float* current_speed)
{
	char user_input;
	if (_kbhit())
	{
		user_input = _getch();
		updateDirection(user_input, current_direction);
	}
	if (isGrow(*grow_counter))
	{
		grow(snake_head, current_direction);
		*grow_counter = 0;
	}
	else
	{
		moveSnake(snake_head, current_direction);
		(*grow_counter)++;
		if(*current_speed<MAX_SPEED)
			(*current_speed) = *current_speed - INCREASE_SPEED;
	}
	return isGameOver(*snake_head);
}

void gotoxy(int x, int y)
{
	printf("\x1b[%d;%df", x, y);
}

void sleep(float secs)
{
	clock_t clocks_start = clock();
	while (clock() - clocks_start < secs * CLOCKS_PER_SEC);
}

void updateDirection(char new_direction, char* current_direction)
{
	if (isValidUserInput(new_direction))
		*current_direction = new_direction;
}

bool isValidUserInput(char direction)
{
	return (direction == RIGHT || direction == LEFT || direction == UP || direction == DOWN);
}

bool isGrow(int grow_counter)
{
	return (grow_counter == GROWTH_RATE);
}

void grow(SNAKE** snake_head, char* direction)
{
	SNAKE* new_unit = InitUnit();
	SNAKE* old_snake_head = *snake_head;
	*snake_head = insertBefore(old_snake_head, new_unit);
	update_New_Snake_Head_Point((old_snake_head)->point, (*snake_head)->point, *direction);
}

void moveSnake(SNAKE** snake_head, char* direction)
{
	SNAKE* last_unit = getLastUnit(*snake_head);
	SNAKE* old_snake_head = *snake_head;
	if (*snake_head != last_unit)
	{
		disconnectUnitFromSnake(old_snake_head, last_unit);
		*snake_head = insertBefore(old_snake_head, last_unit);
	}
	removeUnitFromBoard(last_unit);
	update_New_Snake_Head_Point((old_snake_head)->point, (*snake_head)->point, *direction);
}

SNAKE* getLastUnit(SNAKE* snake)
{
	while (snake->next)
		snake = snake->next;
	return snake;
}

void disconnectUnitFromSnake(SNAKE* snake, SNAKE* unit)
{
	if (snake != unit)
	{
		if (unit->next != NULL)
			unit->next->previous = unit->previous;
		if (unit->previous != NULL)
			unit->previous->next = unit->next;
	}
}

SNAKE* insertBefore(SNAKE* snake_head, SNAKE* new_snake_head)
{
	new_snake_head->next = snake_head;
	new_snake_head->previous = NULL;
	snake_head->previous = new_snake_head;
	return new_snake_head;
}

void removeUnitFromBoard(SNAKE* unit)
{
	gotoxy(unit->point->x, unit->point->y);
	printf(" ");
}

void update_New_Snake_Head_Point(POINT* old_head_point, POINT* new_head_point, char direction)
{
	switch (direction)
	{
	case LEFT:
		new_head_point->y = old_head_point->y - 1;
		new_head_point->x = old_head_point->x;
		break;
	case RIGHT:
		new_head_point->y = old_head_point->y + 1;
		new_head_point->x = old_head_point->x;
		break;
	case UP:
		new_head_point->y = old_head_point->y;
		new_head_point->x = old_head_point->x - 1;
		break;
	case DOWN:
		new_head_point->y = old_head_point->y;
		new_head_point->x = old_head_point->x + 1;
		break;
		// operator doesn't match any case constant a, d, w, s
	default:
		break;
	}
}

bool isGameOver(SNAKE* snake_head)
{
	return isBorderClash(snake_head) || isSelfClash(snake_head);
}

bool isBorderClash(SNAKE* snake_head)
{
	return (snake_head->point->x == 1 || snake_head->point->x == ROWS - 1 || snake_head->point->y == 1 || snake_head->point->y == COLS - 1);
}

bool isSelfClash(SNAKE* snake_head)
{
	POINT* snake_head_point = snake_head->point;
	snake_head = snake_head->next;
	while (snake_head)
	{
		if (IsSamePosition(snake_head_point, snake_head->point))
		{
			return true;
		}
		snake_head = snake_head->next;
	}
	return false;
}

bool IsSamePosition(POINT* point1, POINT* point2)
{
	return (point1->x == point2->x && point1->y == point2->y);
}

void freeSnake(SNAKE* snake_head)
{
	SNAKE* temp;
	while (snake_head)
	{
		temp = snake_head;
		snake_head = snake_head->next;
		free(temp->point);
		free(temp);
	}
}

void endGame()
{
	gotoxy(0, 0);
	printGameBoard();
	gotoxy(ROWS / 2 + 1, COLS / 2 - 3);
	printf(GAME_OVER_STR);
	gotoxy(ROWS + 1, 0);
}


// ************************************************************************************
// Name: Gabriela Schweers
// Date: 4/19/2022 - 5/19/2022
// Desc: A Tic-Tac-Toe game interface based on pre-provided function specifications.
// ************************************************************************************

// INCLUDES 
#pragma warning(disable:4996) // disables warning for scanf
#include <stdio.h> 
#include <conio.h>			  // for _getch()

// DEFINES 
#ifndef __TRUE_FALSE__ 
#define __TRUE_FALSE__ 
#define TRUE 1 
#define FALSE 0 
#endif						  // ROWS and COLS must be between 1 and 9 
#define ROWS 3
#define COLS 3
#define MARKONE 'X' 
#define MARKTWO 'O' 
#define BLANK ' ' 

#define CODE_OK 0
#define CODE_OOB 1
#define CODE_COLLISION 2 
#define CODE_SYMINVALID 3    // added "invalid symbol" error

#define IN_PROGRESS		1
#define X_WINS			2
#define O_WINS			3
#define TIE				4
#define ERROR			5
#define EPIC_FAIL		6

#define WIN_REQUIREMENT 3	// WIN_REQUIREMENT cannot be 0

// PROTOTYPES 
void InitializeBoard(char[ROWS][COLS]);
void DisplayBoard(char[ROWS][COLS]);
int PlayerMove(int, int, char[ROWS][COLS], char);
int VictoryCheck(char[ROWS][COLS], int);
void DisplayVictoryMessage(int);

// MAIN 
using namespace std;
int main() {
	// VARIABLE DECLARATION AND INITIALIZATION
	char board[ROWS][COLS];   // array to hold coordinates for tic-tac-toe board
	char absorbPhantom = ' '; // used to catch phantoms from user input

	int i = 0, j = 0;		  // for array and FOR loops
	int codeVal = -1;		  // used to catch return value from PlayerMove function
	int victoryChecker = -1;  // used to catch return value from VictoryCheck function 
	int row = 0;			  // used to hold row value inputted from user, sent to functions
	int col = 0;			  // used to hold column value inputted from user, sent to functions
	int whosTurn = 2;		  // used to determine who's turn it is (if whosTurn % 2 is... EVEN = player 1's turn, ODD = player 2's turn)

	// initialize the board before starting game...
	InitializeBoard(board);

	// welcoming message, outlining board dimensions, player 1 & 2 symbols, and win requirement to players
	printf("!! WELCOME TO TIC-TAC-TOE !!\n\n");
	printf("Player 1: 'X' ; Player 2: 'O'\n");
	printf("Current Board Dimensions: %d x %d.\n\n", ROWS, COLS);
	printf("In order to get a win, you must achieve %d marks placed consecutively in the following directions: \n", WIN_REQUIREMENT);
	printf("- Horizontally\n- Vertically\n- Diagonally UP\n- Diagonally DOWN\n\nGood luck! :)\n");
	printf("-------------------------------------------------------------------------------\n\n");

	// USER INPUT AND ERROR HANDLING
		while (victoryChecker == IN_PROGRESS || victoryChecker == -1) { // runs if start of game (victoryChecker = -1) OR VictoryCheck function returns IN_PROGRESS code
			if (whosTurn % 2 == 0) {
				printf("Player 1, please enter in a x-coordinate (row): ");
				scanf("%d%c", &row, &absorbPhantom);						// stores in row var

				printf("Player 1, please enter in a y-coordinate (column): ");
				scanf("%d%c", &col, &absorbPhantom);					    // stores in col var
				codeVal = PlayerMove(row, col, board, MARKONE);				// captures code returned by PlayerMove for error handling
			} else {
				printf("Player 2, please enter in a x-coordinate (row): ");
				scanf("%d%c", &row, &absorbPhantom);						// stores in row var

				printf("Player 2, please enter in a y-coordinate (column): ");
				scanf("%d%c", &col, &absorbPhantom);					    // stores in col var
				codeVal = PlayerMove(row, col, board, MARKTWO);				// captures code returned by PlayerMove for error handling
			}

			// ERROR HANDLING
			switch (codeVal) {
			case CODE_COLLISION:
				printf("\nThat space is already occupied. Please try again...\n");
				break;
			case CODE_OOB:
				printf("\nYou have entered a move that is outside of the board's range (%d x %d). Please try again...\n", ROWS, COLS);
				break;
			case CODE_SYMINVALID:
				printf("\nPLEASE ONLY CHOOSE FROM MARKONE 'X' OR MARKTWO 'O'\n");
				break;
			case CODE_OK:													// places move on the board ONLY in this instance
				printf("\nYou have successfully placed a mark on the board.\n");
				DisplayBoard(board);
				DisplayVictoryMessage(victoryChecker = VictoryCheck(board, WIN_REQUIREMENT));
				whosTurn++;													// increments whosTurn to switch between player 1's turn and player 2's turn
				break;
			default:
				break;
			}
			// whosTurn++;														
		}
		

	// EXIT TO OS
	printf("\nThanks for playing! :)\n");
	printf("Press any key to continue");									// cosmetics
	_getch();
	return 0;
}

// !! FUNCTION IMPLEMENTATIONS !!
 
// FUNCTION PURPOSE: initializes the board array with blank spaces
void InitializeBoard(char board[ROWS][COLS]) {
	// LOCAL VARS
	int i = 0, j = 0; // for array and FOR loops

	for (i = 0; i < ROWS; i++) {											// loops through and initializes board with blank spaces
		for (j = 0; j < COLS; j++) {
			board[i][j] = BLANK;
		}
	}
}

// FUNCTION PURPOSE: prints Tic Tac Toe board w/ moves from function defined below
void DisplayBoard(char board[ROWS][COLS]) {
	// LOCAL VARS
	int i = 0, j = 0, k = 0;												// for array and FOR loops
	char rowSep1 = '-';														// row separator symbol #1
	char rowSep2 = '+';														// row separator symbol #2

	// TABLE DISPLAY
	printf("*************TIC-TAC-TOE*************\n\n");					// board header
	printf(" ");

	for (i = 0; i < COLS; i++) {											// prints out # of columns on table
		printf("%2d", i + 1);
	}

	printf("\n\n");
	for (i = 0; i < ROWS; i++) {
		printf("%d ", i + 1);												// prints number of rows on side
		for (j = 0; j < (COLS); j++) {
			if (j != COLS - 1) {
				printf("%c|", board[i][j]);									// prints formatted array values w/ | cosmetic divider
			}
			else {
				printf("%c", board[i][j]);									// prints formatted array values without | cosmetic divider
			}
		}
		if (i != ROWS - 1) {												// PURELY COSMETIC IF-ELSE, avoids 2 extra spaces being printed at end of run...
			printf("\n  ");
			for (k = 0; k < (COLS - 1); k++) {
				printf("%c%c", rowSep1, rowSep2);							// prints -+ cosmetic divider
			}
			printf("-\n");
		}
		else {																// if last run...
			printf("\n");
			break;
		}
	}
}

// FUNCTION PURPOSE: places user moves on the board (does not print out anything, returns error/valid code(s))
int PlayerMove(int row, int col, char board[ROWS][COLS], char symbol) {
	if ((row > ROWS || col > COLS || row <= 0 || col <= 0)) {				// checks if that array spot is not blank (AKA taken)
		return CODE_OOB;
	}
	else if (board[row - 1][col - 1] != BLANK) {							// if row's value is larger then ROWS, same with COLS
		return CODE_COLLISION;
	}
	else if (symbol != MARKONE && symbol != MARKTWO) {						// if the symbol given is invalid (not 'X' or 'O')
		return CODE_SYMINVALID;
	}
	else {
		board[row - 1][col - 1] = symbol;									// if all is well....
		return CODE_OK;
	}
}

// FUNCTION PURPOSE: checks for a victory based on custom board size and custom win requirement (returns win/lose/tie/error codes)
int VictoryCheck(char checkMe[ROWS][COLS], int winRequirement) {
	// LOCAL VARS
	int blankSeen = FALSE;
	int XPresents = FALSE;
	int OPresents = FALSE;

	// checks for blank spots
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (checkMe[i][j] == BLANK)
				blankSeen = TRUE;
		}
	}

	// check to see if X or O present victory.
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			// scaning in a "vertical" direction...
			int count = 0;
			if (i <= ROWS - winRequirement) {
				for (int v = 0; v < winRequirement; v++) {
					if (checkMe[i][j] != BLANK && checkMe[i][j] == checkMe[i + v][j]) {
						count++;
					}
				}
				if (checkMe[i][j] == MARKONE && count == winRequirement)
					XPresents = TRUE;
				if (checkMe[i][j] == MARKTWO && count == winRequirement)
					OPresents = TRUE;
			}

			// scanning in a "horizontal" direction...
			count = 0;
			if (j <= COLS - winRequirement) {
				for (int h = 0; h < winRequirement; h++)
					if (checkMe[i][j] != BLANK && checkMe[i][j] == checkMe[i][j + h]) {
						count++;
					}
				if (checkMe[i][j] == MARKONE && count == winRequirement)
					XPresents = TRUE;
				if (checkMe[i][j] == MARKTWO && count == winRequirement)
					OPresents = TRUE;
			}

			// scanning in a "diagonal-up" direction...
			count = 0;
			if (i <= ROWS - 1 && j <= COLS - winRequirement) {
				for (int u = 0; u < winRequirement; u++)
					if (checkMe[i][j] != BLANK && checkMe[i][j] == checkMe[i - u][j + u]) {
						count++;
					}
				if (checkMe[i][j] == MARKONE && count == winRequirement)
					XPresents = TRUE;
				if (checkMe[i][j] == MARKTWO && count == winRequirement)
					OPresents = TRUE;
			}

			// scanning in a "diagonal-down" direction...
			count = 0;
			if (i <= ROWS - winRequirement && j <= COLS - winRequirement) {
				for (int d = 0; d < winRequirement; d++)
					if (checkMe[i][j] != BLANK && checkMe[i][j] == checkMe[i + d][j + d]) {
						count++;
					}
				if (checkMe[i][j] == MARKONE && count == winRequirement)
					XPresents = TRUE;
				if (checkMe[i][j] == MARKTWO && count == winRequirement)
					OPresents = TRUE;
			}
		}
	}
	// return codes used by DisplayVictoryMessage function defined below
	if (!blankSeen && !XPresents && !OPresents) 
		return TIE;
	if (XPresents && !OPresents)
		return X_WINS;
	if (OPresents && !XPresents)
		return O_WINS;
	if (XPresents && OPresents)
		return ERROR;
	return IN_PROGRESS;
}

// FUNCTION PURPOSE: returns messages to player based on code returned by VictoryCheck
void DisplayVictoryMessage(int victoryCode) {
	// displays the victory condition results...
	switch (victoryCode) {
	case IN_PROGRESS:
		printf("There is still no winner.\n");
		break;
	case X_WINS:
		printf("Player 1 has won the game.\n");
		break;
	case O_WINS:
		printf("Player 2 has won the game.\n");
		break;
	case TIE:
		printf("The game is a draw.\n");
		break;
	case ERROR:
		printf("Something bad happened... Player 1 and Player 2 have both won.\n");
		break;
	case EPIC_FAIL:
		printf("Something bad happened... VictoryCheck() has produced an impossible combination of return code indicators.\n");
		break;
	default:
		printf("DisplayVictoryMessage() was passed an invalid victoryCode.\n");
	}
}

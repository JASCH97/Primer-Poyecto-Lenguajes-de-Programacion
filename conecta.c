
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>



#define BOARD_ROWS 7
#define BOARD_COLS 7

 int  PLAYER = 1;
 int  COMPUTER = 2;
//int turns = 0;
int currentPlayer = 1;
bool gameOver = false;
const char *PIECES = "XO";
















void printBoard(char *board){
   int row, col;

   
   puts("\n    ****Connect Four****\n");
   for(row = 0; row < BOARD_ROWS; row++){
      for(col = 0; col < BOARD_COLS; col++){
         printf("| %c ",  board[BOARD_COLS * row + col]);
      }
      puts("|");
      puts("-----------------------------");

   }
    puts("  1   2   3   4   5   6   7\n");

}


int takeTurn(char *board, const char *PIECES){
   //int row, col = 3;
   int row, col = 0;
   
   printf("Eliga la columna en la que quiere jugar: ");
   while(1){ 
      if(1 != scanf("%d", &col) || col < 1 || col > 7 ){
         while(getchar() != '\n');
         puts("Number out of bounds! Try again.");
      } else { 
         break;
      }
   }
   col--;  

   for(row = BOARD_ROWS - 1; row >= 0; row--){
      if(board[BOARD_COLS * row + col] == ' '){
         board[BOARD_COLS * row + col] = *PIECES;
         return 1;
      }
   }
   return 0;

}

int takeTurn2(char *board, const char *equis){
   //int row, col = 3;
   int row, col = 0;
   
   printf("Eliga la columna en la que quiere jugar: ");
   while(1){ 
      if(1 != scanf("%d", &col) || col < 1 || col > 7 ){
         while(getchar() != '\n');
         puts("Number out of bounds! Try again.");
      } else { 
         break;
      }
   }
   col--;  

   for(row = BOARD_ROWS - 1; row >= 0; row--){
      if(board[BOARD_COLS * row + col] == ' '){
         board[BOARD_COLS * row + col] = *equis;
         return 1;
      }
      
   }
   return 0;

}


int checkWin(char *board){
    return (horizontalCheck(board) || verticalCheck(board) || diagonalCheck(board));

}
int checkFour(char *board, int a, int b, int c, int d){
    return (board[a] == board[b] && board[b] == board[c] && board[c] == board[d] && board[a] != ' ');

}
int horizontalCheck(char *board){
    int row, col, idx;
    const int WIDTH = 1;

    for(row = 0; row < BOARD_ROWS; row++){
       for(col = 0; col < BOARD_COLS - 3; col++){
          idx = BOARD_COLS * row + col;
          if(checkFour(board, idx, idx + WIDTH, idx + WIDTH * 2, idx + WIDTH * 3)){
             return 1;
          }
       }
    }
    return 0;

}
int verticalCheck(char *board){
    int row, col, idx;
    const int HEIGHT = 7;

    for(row = 0; row < BOARD_ROWS - 3; row++){
       for(col = 0; col < BOARD_COLS; col++){
          idx = BOARD_COLS * row + col;
          if(checkFour(board, idx, idx + HEIGHT, idx + HEIGHT * 2, idx + HEIGHT * 3)){
              return 1;
          }
       }
    }
    return 0;

}
int diagonalCheck(char *board){
   int row, col, idx, count = 0;
   const int DIAG_RGT = 6, DIAG_LFT = 8;

   for(row = 0; row < BOARD_ROWS - 3; row++){
      for(col = 0; col < BOARD_COLS; col++){
         idx = BOARD_COLS * row + col;
         if(count <= 3 && checkFour(board, idx, idx + DIAG_LFT, idx + DIAG_LFT * 2, idx + DIAG_LFT * 3) || count >= 3 && checkFour(board, idx, idx + DIAG_RGT, idx + DIAG_RGT * 2, idx + DIAG_RGT * 3)){
            return 1;
         }
         count++;
      }
      count = 0;
   }
   return 0;

}






int main() {


	int done = 0;
	const char *equis = "L";
	const char *PIECES = "XO";
	char board[BOARD_ROWS * BOARD_COLS];
	memset(board, ' ', BOARD_ROWS * BOARD_COLS);
	int turns = 0;

	printBoard(board); // print initial board
	while (!gameOver && !done) { // while no game over state


		if (turns == BOARD_COLS * BOARD_ROWS){
			gameOver = true;

		}
		if (currentPlayer == COMPUTER) { // AI move
			takeTurn(board, PIECES);

		}
		else if (currentPlayer == PLAYER) { // player move
			takeTurn(board, equis);
		}

		done = checkWin(board);
		
		currentPlayer = (currentPlayer == 1) ? 2 : 1; // switch player
		turns++; // iterate number of turns
		
		printBoard(board); // print board after successful move
	}

	printBoard(board);

	if (turns == BOARD_COLS * BOARD_ROWS) { // if draw condition
		printf("Empate\n");
		return 0;
	}
	else { // otherwise, someone won
		printf("ALguien gano\n");
		return 0;
	}





	return 0;
}



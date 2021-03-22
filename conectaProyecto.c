/*  --------------------------------------------------------
    Instituto Tecnologico de Costa Rica
    Escuela de Ingenieria en Computacion
    Sede Interuniversitaria de Alajuela
    Lenguajes de Programacion
    Semestre I 2021

    Prof. Samanta Ramijan 
    
    Estudiantes
    Tomas Acuna                     2018112856
    Joan Sanchez Chinchilla         2015123867  

    Primer proyecto: Programacion Imperativa                 
    --------------------------------------------------------

*/

//se importan las librerias necesarias
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


//se definen las variables constantes y globales
#define BOARD_ROWS 7
#define BOARD_COLS 7


int  PLAYER = 1;
int  COMPUTER = 2;
int currentPlayer = 1;
bool gameOver = false;
const char *circulo = "O";
const char *equis = "X";



//esta funcion imprime el tablero del juego y las fichas de colores
void printBoard(char *board){
   int row, col;                          //filas y columnas

   puts("\n    ****Connect Four****\n");
   for(row = 0; row < BOARD_ROWS; row++){
      for(col = 0; col < BOARD_COLS; col++){
         //printf("\033[0;31m",);
         printf("| ");
         if(board[BOARD_COLS * row + col] == 'X'){
            printf("\033[0;31m");                        //codigo para imprimir color rojo
            printf("%c ",  (board[BOARD_COLS * row + col]));
            printf("\033[0m");                           //codigo para imprimir normal nuevamente
         }  
         else{
            printf("\033[0;32m");                        //codigo para imprimir verde
            printf("%c ",  (board[BOARD_COLS * row + col]));
            printf("\033[0m");
         }
      }
      puts("|");
      puts("-----------------------------");

   }
    puts("  1   2   3   4   5   6   7\n");

}


//esta funcion realiza la jugada en base al turno del jugador actual
int takeTurn(char *board, const char *PIECES){
   
   int row, col = 0;
   if(PIECES == "X"){
      printf("Turno del Jugador 1, fichas 'X'\n");  
   }
   if(PIECES == "O"){
      printf("Turno del Jugador 2 (maquina), fichas 'O'\n");
   }
   printf("Elija la columna en la que quiere jugar: ");
   while(1){ 
      if(1 != scanf("%d", &col) || col < 1 || col > 7 ){
         while(getchar() != '\n');
         puts("Number out of bounds! Try again.");
      } else { 
         break;
      }
   }

   printf("%d",col);
   if(col == 1 && board[0] != ' '){
      printf("\n\nNo puede ingresar mas fichas en esta columna\n\n");
      takeTurn(board,PIECES);
   }
   if(col == 2 && board[1] != ' '){
      printf("No puede ingresar mas fichas en esta columna\n\n");
      takeTurn(board,PIECES);
   }
   if(col == 3 && board[2] != ' '){
      printf("\n\nNo puede ingresar mas fichas en esta columna\n\n");
      takeTurn(board,PIECES);
   }
   if(col == 4 && board[3] != ' '){
      printf("\n\nNo puede ingresar mas fichas en esta columna\n\n");
      takeTurn(board,PIECES);
   }
   if(col == 5 && board[4] != ' '){
      printf("\n\nNo puede ingresar mas fichas en esta columna\n\n");
      takeTurn(board,PIECES);
   }
   if(col == 6 && board[5] != ' '){
      printf("\n\nNo puede ingresar mas fichas en esta columna\n\n");
      takeTurn(board,PIECES);
   }
   if(col == 7 && board[6] != ' '){
      printf("\n\nNo puede ingresar mas fichas en esta columna\n\n");
      takeTurn(board,PIECES);
   }
   else{
      col--;  

      for(row = BOARD_ROWS - 1; row >= 0; row--){
         if(board[BOARD_COLS * row + col] == ' '){
            board[BOARD_COLS * row + col] = *PIECES;
            return 1;
         }
      }
   }
   return 0;

}

//***
int takeTurn2(char *board, const char *equis){  //no se esta utilizando esta funcion. Verificar.
   
   int row, col = 0;
   
   printf("Elija la columna en la que quiere jugar: ");
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


//Esta funcion valida si 4 fichas son iguales
int checkFour(char *board, int a, int b, int c, int d){
   return (board[a] == board[b] && board[b] == board[c] && board[c] == board[d] && board[a] != ' ');

}

//Esta funcion verifica si existen 4 fichas iguales en posicion horizontal
int horizontalCheck(char *board){
    int row, col, idx;
    const int WIDTH = 1;

    for(row = 0; row < BOARD_ROWS; row++){
       for(col = 0; col < BOARD_COLS - 3; col++){
          idx = BOARD_COLS * row + col;
          if(checkFour(board, idx, idx + WIDTH, idx + WIDTH * 2, idx + WIDTH * 3)){
             if(board[idx] == 88){ //88 es el valor ascii de X
                return 1;
             }
             else{
               return 2;
             }
          }
       }
    }
    return 0;

}

//Esta funcion verifica si existen 4 fichas iguales en posicion vertical
int verticalCheck(char *board){
    int row, col, idx;
    const int HEIGHT = 7;

    for(row = 0; row < BOARD_ROWS - 3; row++){
       for(col = 0; col < BOARD_COLS; col++){
          idx = BOARD_COLS * row + col;
          if(checkFour(board, idx, idx + HEIGHT, idx + HEIGHT * 2, idx + HEIGHT * 3)){
              if(board[idx] == 88){  //88 es el valor ascii de X
                return 1;
             }
             else{
               return 2;
             }
          }
       }
    }
    return 0;

}

//Esta funcion verifica si existen 4 fichas iguales en posicion diagonal
int diagonalCheck(char *board){
   int row, col, idx, count = 0;
   const int DIAG_RGT = 6, DIAG_LFT = 8;

   for(row = 0; row < BOARD_ROWS - 3; row++){
      for(col = 0; col < BOARD_COLS; col++){
         idx = BOARD_COLS * row + col;
         if(count <= 3 && checkFour(board, idx, idx + DIAG_LFT, idx + DIAG_LFT * 2, idx + DIAG_LFT * 3) || count >= 3 && checkFour(board, idx, idx + DIAG_RGT, idx + DIAG_RGT * 2, idx + DIAG_RGT * 3)){
            if(board[idx] == 88){  //88 es el valor ascii de X
                return 1;
             }
             else{
               return 2;
             }
         }
         count++;
      }
      count = 0;
   }
   return 0;

}

//Esta funcion verifica si existe un ganador o no
int checkWin(char *board){
    if(horizontalCheck(board) != 0){
       return horizontalCheck(board);
    }
    if(verticalCheck(board) != 0){
       return verticalCheck(board);
    }
    if(diagonalCheck(board) != 0){
       return diagonalCheck(board);
    }
    else{
       return 0;
    }

}

//Esta funcion devuelve un numero random entre 0 y 1
int randomTurn(){
   int i; 
   i = (rand() % 2);
   return i;

}


int main() {
   //se crean las variables de inicio necesarias
   srand(time(NULL));
   int r;
   r = randomTurn();
   int opcion;
   int done = 0;
   char board[BOARD_ROWS * BOARD_COLS];
   memset(board, ' ', BOARD_ROWS * BOARD_COLS);
   int turns = 0;


   printf("\nBienvenido al menu del Juego 'Connect Four'\n");
   printf("Seleccione una de las siguientes opciones y luego presione 'Enter'\n");
   printf("1.Iniciar Partida\n2.Salir\n\n--> ");
   scanf("%d",&opcion);

	switch(opcion){

      case 1: 
         printf("Elijiendo cual jugador empieza...\n");

         if(r == 0){
            printf("\nInicia el jugador 1, le corresponden las fichas 'X'\n");
            printf("Al jugador jugador 2 (maquina) le corresponden las fichas 'O'\n\n");

            printBoard(board); // printeando la board
            while (!gameOver && !done) { // mientras no se cumpla gameover y el done


               if (turns == 48){
                  gameOver = true;

               }
               if (currentPlayer == COMPUTER) { // AI jugada
                  takeTurn(board, circulo);

               }
               else if (currentPlayer == PLAYER) { // jugada del jugador
                  takeTurn(board, equis);
               }

               done = checkWin(board);
               
               currentPlayer = (currentPlayer == 1) ? 2 : 1; // switch player
               
               turns++; // aumentar los turnos
               printf("El turno actual es: %d",turns);
               
               printBoard(board); // printeando la board despues de una jugada
            }

            printBoard(board);

            if (turns == 49) { // condicion de empate
               printf("Empate\n");
               return 0;
            }
            else { // sino alguien gano
               if(done == 1){
                  printf("Ha ganado el jugador con las fichas X!\n");
                  return 0;
               }
               else{
                  printf("Ha ganado la maquina con las fichas O!\n");
                  return 0;
               }
               
               
            }
                     
         }
         else{
            currentPlayer = 2;
            printf("\nInicia el jugador 2(maquina), le corresponden las fichas 'O'\n");
            printf("Al jugador 1 le corresponden las fichas 'X'\n\n");

            printBoard(board); // printeando la board
            while (!gameOver && !done) { // mientras no se cumpla gameover y el done


               if (turns == 48){
                  gameOver = true;

               }
               if (currentPlayer == COMPUTER) { // AI jugada
                  takeTurn(board, circulo);

               }
               else if (currentPlayer == PLAYER) { // jugada del jugador
                  takeTurn(board, equis);
               }

               done = checkWin(board);
               
               currentPlayer = (currentPlayer == 1) ? 2 : 1; // switch player
               
               turns++; // aumentar los turnos
               
               printBoard(board); // printeando la board despues de una jugada
            }

            printBoard(board);

            if (turns == 49) { // condicion de empate
               printf("No quedan mas columnas por llenar! Es un Empate!\n");
               return 0;
            }
            else { // sino alguien gano
               if(done == 1){
                  printf("Ha ganado el jugador con las fichas X!\n");
                  return 0;
               }
               else{
                  printf("Ha ganado la maquina con las fichas O!\n");
                  return 0;
               }
               
               
            }
                     
         }
         
         break;


      case 2:
         break;


      default: printf("Opcion incorrecta,intente nuevamente.\n");

   }





	return 0;
}


#include <stdio.h>
#include <stdlib.h> //library for random function(srand)
#include <time.h>   //library for refreshing variables

/*prototypes*/
void newGame(char arr[]);
void clearBoard(int pos, char player, char arr[]);
void displaylBoard(int pos, char player, char arr[]);
int legalMove(int pos, char arr[]) ;
int gameWon(int pos, char arr[], char player);
void writeGame(char player, char arr[]);
void readGame(char arr[]);
void displayPrevGame(char arr[], char player, int i);
void Previous_Game(int i, char arr[], char player);
void playComputer(char arr[]);
void red();
void yellow();
void violet();
void reset();

/*main function*/
int main(void) {
  int entry, gametype, position;
	char array[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
  char arr[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
	char jnk;
	FILE *prevGame;
  /*originalBoard to be shown of the screen*/

  printf("\nWelcome to Tic-Tac-Toe\n\n");
  violet(); // call for color function
  printf("+---+---+---+\n");
  printf("| %c | %c | %c |\n", array[0], array[1], array[2]);
  reset(); // resetting the color to the original white
  red();   // call for red color function
  printf("+---+---+---+\n");
  printf("| %c | %c | %c |\n", array[3], array[4], array[5]);
  printf("+---+---+---+\n");
  reset();
  printf("| %c | %c | %c |\n", array[6], array[7], array[8]);
  printf("+---+---+---+\n");

  violet();
  printf("\nEnter:\n"
         "(%d)to start a new game,\n"
         "(%d)to load previous game,\n"
         "(%d)to play against your computer.\n",
         1, 2, 3);

  do { // check for whether the value is in the valid range.
	  scanf("%d", &entry);
	  scanf("%c", &jnk);
	  if (entry < 1 || entry > 3) {
		  printf("Invalid option, try again!\n");
	  }
	  
	  else if(entry == 1){
		  prevGame = fopen("TicTacToeSave.txt", "r");
		  if (prevGame == NULL){
			  printf("There isn't previous game, start a name game.\n");
			  newGame(arr);
		  }
		  
		  else{
			  printf("There is a saved game, would like to continue?\nEnter\n(1)To load game.\n(2)To start a name game.\n");
			  scanf("%d", &gametype);
			  scanf("%c", &jnk);
			  
			  if(gametype == 1){
				  readGame(arr);
			  }
		    
			  else if(gametype == 2){
				  printf("Player A --(X), Player B--(O)\n");
				  printf("+---+---+---+\t\t+---+---+---+\n");
				  printf("| 1 | 2 | 3 |\t\t| %c | %c | %c |\n", arr[0], arr[1], arr[2]);
				  printf("+---+---+---+\t\t+---+---+---+\n");
				  printf("| 4 | 5 | 6 |\t\t| %c | %c | %c |\n", arr[3], arr[4], arr[5]);
				  printf("+---+---+---+\t\t+---+---+---+\n");
				  printf("| 7 | 8 | 9 |\t\t| %c | %c | %c |\n", arr[6], arr[7], arr[8]);
				  printf("+---+---+---+\t\t+---+---+---+\n");
				  newGame(arr);
			  }
		  }
	  }
	  //options for selecting previous game
	  else if(entry == 2){
		  readGame(arr);
	  }
	  //options for playing against computer
	  else if(entry == 3){
		  playComputer(arr);
	  }
  } while (entry < 1 || entry > 3);
  

  return 0;
}



/*gametype func: new game/previous game/play against computer*/
void newGame(char arr[]) {
	int i, position, quit_save, win, emptySpace; // variable i for counter, position-stores user entry when asked
	char player, junk;
	
	for(i = 0; i < 9; i++) {         // counter upto 9 because board 9 spots
      if (i % 2 == 0) { // for odd numbers of i, player A plays
        player = 'A';
      }
      else if (i %2 != 0){ /// for even numbers of i, player A plays
        player = 'B';
      }
			
      do { // checks whether the user entered a value range 1-9
				printf("Player %c, enter position or 0 to quit:", player);
        scanf("%d", &position);
				scanf("%c", &junk);
        if (position < 0 || position > 9) {
          printf("Invalid Option. Try again!\n");
        }
        else if (position == 0) { // save game 
          i = 10;
          printf("Enter %d(yes) to save game or %d(no) to delete:", 1, 2);
          scanf("%d", &quit_save);
          if(quit_save == 1){
						writeGame(player, arr);
          }
        }
      } while (position < 0 || position > 9);

      emptySpace = legalMove(position, arr); // call for function to check whether the position chosen is occupied

      /*next step if the move is illegal*/
      if (emptySpace != 1) {
        printf("Invalid Option. Try again!\n");
        i -= 1; // the counter is set backwards so the loop is repeated
      }
      else {
        clearBoard(position, player, arr); // call for function for board if move is legal
      
				}
      win = gameWon(position, arr, player);
      if (win == 1) {
        printf("Player %c wins", player);
        i = 10;
      }
      else if (win == 2){
        printf("Game ends in a draw!");
        i = 10;
      }
		}
    
  }


/*prints clearboard that holds positions*/
void clearBoard(int pos, char player, char arr[]) {
red();

  displaylBoard(pos, player, arr);
  /*the arrays hold positions*/
  printf("\n Tic-Tac-Toe\n\n");
  reset();

  printf("Player A --(X), Player B--(O)\n");
  red();
  printf("+---+---+---+\t\t+---+---+---+\n");
  printf("| 1 | 2 | 3 |\t\t| %c | %c | %c |\n", arr[0], arr[1], arr[2]);
  printf("+---+---+---+\t\t+---+---+---+\n");
  printf("| 4 | 5 | 6 |\t\t| %c | %c | %c |\n", arr[3], arr[4], arr[5]);
  printf("+---+---+---+\t\t+---+---+---+\n");
  printf("| 7 | 8 | 9 |\t\t| %c | %c | %c |\n", arr[6], arr[7], arr[8]);
  printf("+---+---+---+\t\t+---+---+---+\n");

	
}

/*displayBoard func*/
void displaylBoard(int pos, char player, char arr[]) {
  char mark; // the mark is either X or O to denote moves of different players

  if (player == 'A') {
    mark = 'X';
  }
  else if (player == 'B') {
    mark = 'O';
  }

  arr[pos - 1] = mark; // depending on the if statement above, the empty is
                       // assigned a given mark.
}

/*legalmove func*/
int legalMove(int pos, char arr[]) {

  if (arr[pos - 1] == 'X' || arr[pos - 1] == 'O') {
    return 0; // the position is occupied, the return value resets i counter backwards by one value
  }
  return 1; // if the position is not occupied it return 0, and the i counter
 
}
/*gameWon func*/ // pass displayBoard
int gameWon(int pos, char arr[], char player){

  /*horizontal match along the different rows*/
  if (arr[0] == arr[1] && arr[1] == arr[2] && arr[0] != ' ') {
    return 1;
  }

  else if (arr[3] == arr[4] && arr[4] == arr[5] && arr[3] != ' ') {
    return 1;
  }

  else if (arr[6] == arr[7] && arr[7] == arr[8] && arr[6] != ' ') {
    return 1;
  }
  /*diagonal match along the two diagonals of the square*/
  else if (arr[0] == arr[4] && arr[4] == arr[8] && arr[0] != ' ') {
    return 1;
  }

  else if (arr[2] == arr[4] && arr[4] == arr[6] && arr[2] != ' ') {
    return 1;
  }

  /*vertical match along the vertical of the columns of the grid*/
  else if (arr[0] == arr[3] && arr[3] == arr[6] && arr[0] != ' ') {
    return 1;
  }

  else if (arr[1] == arr[4] && arr[4] == arr[7] && arr[1] != ' ') {
    return 1;
  }

  else if (arr[2] == arr[5] && arr[5] == arr[8] && arr[5] != ' ') {
    return 1;
  }
  /*if none-match and all the spaced are occupied*/
  else if (arr[0] != ' ' && arr[1] != ' ' && arr[2] != ' ' && arr[3] != ' ' &&
           arr[4] != ' ' && arr[5] != ' ' && arr[6] != ' ' && arr[7] != ' ' &&
           arr[8] != ' ') {
    return 2;
  }

  return 0; // if none of these options exists, returns -2 for the game to continue.
}

/*writeGame func */ // call only once in main func
void writeGame(char player, char arr[]){
  FILE *save_game;
  int counter = 0; // m is for the counter below

  save_game = fopen("TicTacToeSave.txt", "w");
  while (counter < 9) {
    fprintf(save_game, "%c,", arr[counter]); // writing the positions entered by the player
    counter++;
		}
  fclose(save_game);

  save_game = fopen("TicTacToeSave.txt", "a"); // appending the player at the end of 9 values in the array
  fprintf(save_game, "%c", player);
  fclose(save_game);
  
}

void readGame(char arr[]){
  FILE *previous_game;
  int i, m, position; // i is counter for the number of spaces available in the file. m is for the counter below.
	char player;
	
  i = 0;
  previous_game = fopen("TicTacToeSave.txt", "r");
  if (previous_game == NULL) { // check if the file contains any information.
    printf("There isn't saved game. Try a new game.");
    newGame(arr);
  }
  else {
    for (m = 0; m <= 9; m++) {
      if( m < 9){
      fscanf(previous_game, "%c,", &arr[m]); // scanning the content of the file and
        if (arr[m] == ' '){
         i++; //empty spaces
        }
      }
      else {
        fscanf(previous_game, "%c", &player);
      } 
    }
		
		displayPrevGame(arr, player, i);
    Previous_Game(i, arr, player);
  }
	fclose(previous_game);
}

void displayPrevGame(char arr[], char player, int i){
	printf("\n Tic-Tac-Toe\n\n");

  printf("Player A --(X), Player B--(O)\n");
  printf("+---+---+---+\t\t+---+---+---+\n");
  printf("| 1 | 2 | 3 |\t\t| %c | %c | %c |\n", arr[0], arr[1], arr[2]);
  printf("+---+---+---+\t\t+---+---+---+\n");
  printf("| 4 | 5 | 6 |\t\t| %c | %c | %c |\n", arr[3], arr[4], arr[5]);
  printf("+---+---+---+\t\t+---+---+---+\n");
  printf("| 7 | 8 | 9 |\t\t| %c | %c | %c |\n", arr[6], arr[7], arr[8]);
  printf("+---+---+---+\t\t+---+---+---+\n");

}
/*previous game func*/
void Previous_Game(int i, char arr[], char player) {
  int n, position, quit_save, win, emptySpace; // variable i for counter, position-stores user entry when asked
	char jnk;
	
  for(n = 0; n < i; n++) {         // counter upto 9 because board 9 spots
    if (n % 2 == 0) { // for odd numbers of i, player A plays
      player = 'A';
    }
    else if (n %2 != 0){ /// for even numbers of i, player A plays
       player = 'B';
    }
			
    do { // checks whether the user entered a value range 1-9
			printf("Player %c, enter position or 0 to quit:", player);
      scanf("%d", &position);
			scanf("%c", &jnk);
      if (position < 0 || position > 9) {
        printf("Invalid Option. Try again!\n");
      }
      else if (position == 0) { // save game 
        n = i;
        printf("Enter %d(yes) to save game or %d(no) to delete:", 1, 2);
        scanf("%d", &quit_save);
        if(quit_save == 1){
					writeGame(player, arr);
        }
      }
    } while (position < 0 || position > 9);

    emptySpace = legalMove(position, arr); // call for function to check whether the position chosen is occupied

      /*next step if the move is illegal*/
    if (emptySpace != 1) {
      printf("Invalid Option. Try again!\n");
      n -= 1; // the counter is set backwards so the loop is repeated
    }
    else {
      clearBoard(position, player, arr); // call for function for board if move is legal
    }
		
    win = gameWon(position, arr, player);
    if (win == 1) {
      printf("Player %c wins", player);
      n = i;
    }
    else if (win == 2){
      printf("Game ends in a draw!");
      n = i;
    }
	}
  
}


void playComputer(char arr[]) {
  int i, win, position, quit_save, emptySpace;
  char player, jnk;

  printf("You--(X), Computer--(O)\n");

  for (i = 0; i < 9; i++) { // counter upto 9 because board 9 spots
		if (i % 2 != 0) {
    	player = 'A';
		}
		else if (i % 2 == 0) { // computer starts the game to have a better chance of winning
			player = 'B';
		}

		if(player == 'A'){
      do { // checks whether the user entered a value range 1-9
				printf("Enter position or 0 to quit:");
        scanf("%d", &position);
				scanf("%c", &jnk);
        if (position < 0 || position > 9) {
          printf("Invalid Option. Try again!\n");
        }
        else if (position == 0) { // save game 
          i = 10;
          printf("Enter %d(yes) to save game or %d(no) to delete:", 1, 2);
          scanf("%d", &quit_save);
          if(quit_save == 1){
						writeGame(player, arr);
        	}
        }
      } while (position < 0 || position > 9);

 		}

		else if (player == 'B'){
      /*if the players intends to get a horizontal match on row 1*/
      if ((arr[0] == 'X' && arr[1] == 'X' && arr[2] == ' ') ||(arr[0] == 'O' && arr[1] == 'O' && arr[2] == ' ')) {
        position = 3;
      } 
			else if ((arr[0] == 'X' && arr[1] == ' ' && arr[2] == 'X') || (arr[0] == 'X' && arr[1] == ' ' && arr[2] == 'X')){
        position = 2;
      } else if ((arr[0] == ' ' && arr[1] == 'X' && arr[2] == 'X') || (arr[0] == ' ' && arr[1] == 'O' && arr[2] == 'O')) {
        position = 1;
      }
      /*if the players intends to get a horizontal match on row 2*/
      else if ((arr[3] == 'X' && arr[4] == 'X' && arr[5] == ' ') || (arr[3] == 'O' && arr[4] == 'O' && arr[5] == ' ')) {
        position = 6;
      } else if ((arr[3] == 'X' && arr[4] == ' ' && arr[5] == 'X') || (arr[3] == 'O' && arr[4] == ' ' && arr[5] == 'O')){
        position = 5;
				
      }		
			else if ((arr[3] == ' ' && arr[4] == 'X' && arr[5] == 'X') ||(arr[3] == ' ' && arr[4] == 'O' && arr[5] == 'O')){
        position = 4;
      }
      /*if the players intends to get a horizontal match on row 3*/
      else if ((arr[6] == 'X' && arr[7] == 'X' && arr[8] == ' ') || (arr[6] == 'O' && arr[7] == 'O' && arr[8] == ' ')){
        position = 9;
      } else if ((arr[6] == 'X' && arr[7] == ' ' && arr[8] == 'X') || (arr[6] == 'O' && arr[7] == ' ' && arr[8] == 'O')){
        position = 8;
      } else if ((arr[6] == ' ' && arr[7] == 'X' && arr[8] == 'X')|| (arr[6] == ' ' && arr[7] == 'O' && arr[8] == 'O')){
        position = 7;
      }

      /*if the players intends to get vertical match*/
      else if ((arr[0] == ' ' && arr[3] == 'X' && arr[6] == 'X') || (arr[0] == ' ' && arr[3] == 'O' && arr[6] == 'O')){
        position = 1;
      } 
			else if ((arr[0] == 'X' && arr[3] == 'X' && arr[6] == ' ') || (arr[0] == 'O' && arr[3] == 'O' && arr[6] == ' ')) {
        position = 7;

      } 
			else if ((arr[0] == 'X' && arr[3] == ' ' && arr[6] == 'X') || (arr[0] == 'O' && arr[3] == ' ' && arr[6] == 'O')) {
        position = 4;
      } 
			else if ((arr[1] == ' ' && arr[4] == 'X' && arr[7] == 'X') || (arr[1] == ' ' && arr[4] == 'O' && arr[7] == 'O')) {
        position = 2;
      } 
			else if ((arr[1] == 'X' && arr[4] == ' ' && arr[7] == 'X') || (arr[1] == 'O' && arr[4] == ' ' && arr[7] == 'O')) {
        position = 5;
      } 
			else if ((arr[1] == 'X' && arr[4] == 'X' && arr[7] == ' ')|| (arr[1] == 'O' && arr[4] == 'O' && arr[7] == ' ')) {
        position = 8;
      } else if ((arr[2] == ' ' && arr[5] == 'X' && arr[8] == 'X') || (arr[2] == ' ' && arr[5] == 'O' && arr[8] == 'O')) {
        position = 3;
      } else if ((arr[2] == 'X' && arr[5] == 'X' && arr[8] == ' ') || (arr[2] == 'O' && arr[5] == 'O' && arr[8] == ' ')){
        position = 9;
      } else if ((arr[2] == 'X' && arr[5] == ' ' && arr[8] == 'X') || (arr[2] == 'O' && arr[5] == ' ' && arr[8] == 'O')) {
        position = 6;
      }
      /*if the players intends to apply X along the diagonals*/
      else if ((arr[0] == 'X' && arr[4] == 'X' && arr[8] == ' ') || (arr[0] == 'O' && arr[4] == 'O' && arr[8] == ' ')) {
        position = 9;
      } else if ((arr[0] == ' ' && arr[4] == 'X' && arr[8] == 'X') || (arr[0] == ' ' && arr[4] == 'O' && arr[8] == 'O')) {
        position = 1;
      } else if ((arr[0] == 'X' && arr[4] == ' ' && arr[8] == 'X') || (arr[0] == 'O' && arr[4] == ' ' && arr[8] == 'O')) {
        position = 5;
      } 
			else if (arr[0] == 'X' || arr[8] == 'X' || arr[2] == 'X' || arr[6] == 'X') {
        position = 5;
			}
			else if ((arr[2] == 'X' && arr[4] == 'X' && arr[6] == ' ') || (arr[2] == 'O' && arr[4] == 'O' && arr[6] == ' ')) {
        position = 7;
      } else if ((arr[2] == 'X' && arr[4] == ' ' && arr[6] == 'X') || (arr[2] == 'O' && arr[4] == ' ' && arr[6] == 'O')) {
        position = 5;
      } else if ((arr[2] == ' ' && arr[4] == 'X' && arr[6] == 'X') || (arr[2] == ' ' && arr[4] == 'O' && arr[6] == 'O')){
        position = 3;
      }

      else if(arr[0] == ' ' || arr[1] == ' ' || arr[2] == ' ' || arr[3] == ' ' ||
           arr[4] == ' ' || arr[5] == ' ' || arr[6] == ' ' || arr[7] == ' ' ||
           arr[8] == ' '){ // if none of the scenarios above occur, generate a random number
        srand(time(NULL)); // this function refreshes the random number every second
        position = (rand() % (9 - 1 + 1)) + 1; // the format is (rand() %(upper_bound-lower_bound+1))+1. random numbers range 1-9
				//position = rand() % 10;
      }
		}
			 
			emptySpace = legalMove(position, arr); // call for function to check whether the position chosen is occupied

      /*next step if the move is illegal*/
      if (emptySpace != 1) {
				if (player == 'A'){
					printf("Invalid Option. Try again!\n");
        	i -= 1; // the counter is set backwards so the loop is repeated
     	 }
			  else if (player == 'B'){
					 i -= 1; // the counter is set backwards so the loop is repeated
				}
			}
      else {
        clearBoard(position, player, arr); // call for function for board if move is legal
      
				}
      win = gameWon(position, arr, player);
      if (win == 1) {
				i = 10;
				if(player == 'A'){
					printf("You won!\n");
				}
				else {
        printf("You LOST!\n");	
      	}
			}	
      else if (win == 2){
        printf("Game ends in a draw!");
        i = 10;
      }
    }

		
	}

/*color functions with their parameters*/
void red() { 
	printf("\033[1;31m"); }

void yellow() { // yellow
  printf("\033[1;33m");
}
void violet() { // violet
  printf("\033[1;33m");
}
void reset() { printf("\033[0m"); }

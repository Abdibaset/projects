#include <stdio.h>
#include <stdlib.h> //library for random function(srand)
#include <time.h>   //library for refreshing variables
#include <stdbool.h> 
#include <string.h>

int userinput(void);
bool legalMove(int pos, char pos_arr[]);
void writeGame(char player, char pos_arr[]);
int gameWon(int pos, char pos_arr[]);
void addMove(int pos, char player, char arr[]);
void clearBoard(char pos_arr[]);
void PlayGame(char pos_arr[], int numMoves);
void Previous_Game(char pos_arr[]);
void playAgainstComputer(char pos_arr[]);
void  red();
void yellow();
void violet();
void reset();


int main(void) {
    unsigned userEntry;
    char array[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    char pos_arr[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
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

    // accessing the user input
    printf("\nEnter:\n"
            "%d. Start a new game,\n%d. Load previous game,\n%d. Play against your computer.\n", 1, 2, 3);
    do{
        userEntry = userinput();
    } while (userEntry > 3 || userEntry < 1);

    printf("Success, the game has began ...\n");

    // calling the functions - PlayGame, Previous_Game, playAgainstComputer
    if(userEntry == 1){
        PlayGame(pos_arr, 0);
    } 
    else if(userEntry == 2){
        Previous_Game(pos_arr);
    }
    
    else if(userEntry == 3){
        playAgainstComputer(pos_arr);
    }
  
  exit(EXIT_SUCCESS);
}

/**
 * Function to get the user input
 * @return the user input as an integer
*/
int userinput(void){
   char input[256];
    if(fgets(input, sizeof input, stdin) == NULL){
        exit(EXIT_FAILURE);
    }
    int token = -1;

    if (sscanf(input, "%u", &token) != 1){
        printf("Input a number of desired range: ");
    }
    return token;
}

/**
 * Function to check if the move is legal
 * @param pos the position of the move
 * @param pos_arr the array of the positions and moves
 * @return true if the move is legal, false otherwise
 * 
*/
bool legalMove(int pos, char pos_arr[]) {

  if (pos_arr[pos - 1] == 'X' || pos_arr[pos - 1] == 'O') {
    return false; // the position is occupied, the return value resets i counter backwards by one value
  }
  return true; // if the position is not occupied it return 0, and the i counter
 
}

/**
 * Function to write the game to the file if the user wants to save the game
 * @param player the player who made the move
 * @param pos_arr the array of the positions and moves
 * 
*/
void writeGame(char player, char pos_arr[]){
  FILE *save_game;
  int counter = 0; // m is for the counter below

  save_game = fopen("GameHistory.txt", "w");
	
  while (counter < 9) {
    fprintf(save_game, "%c", pos_arr[counter]); // writing the positions entered by the player
    counter++;
  }
  fclose(save_game);
  
}

/**
 * Function to check if the game is won, drawn or lost
 * @param pos the position of the move
 * @param pos_arr the array of the positions and moves
 * @return 1 if the game is won, 2 if drawn, 0 otherwise
*/
int gameWon(int pos, char pos_arr[]){

  /*horizontal match along the different rows*/
  if (pos_arr[0] == pos_arr[1] && pos_arr[1] == pos_arr[2] && pos_arr[0] != ' ') {
    return 1;
  }
  else if (pos_arr[3] == pos_arr[4] && pos_arr[4] == pos_arr[5] && pos_arr[3] != ' ') {
    return 1;
  }
  else if (pos_arr[6] == pos_arr[7] && pos_arr[7] == pos_arr[8] && pos_arr[6] != ' ') {
    return 1;
  }
  /*diagonal match along the two diagonals of the square*/
  else if (pos_arr[0] == pos_arr[4] && pos_arr[4] == pos_arr[8] && pos_arr[0] != ' ') {
    return 1;
  }
  else if (pos_arr[2] == pos_arr[4] && pos_arr[4] == pos_arr[6] && pos_arr[2] != ' ') {
    return 1;
  }
  /*vertical match along the vertical of the columns of the grid*/
  else if (pos_arr[0] == pos_arr[3] && pos_arr[3] == pos_arr[6] && pos_arr[0] != ' ') {
    return 1;
  }
  else if (pos_arr[1] == pos_arr[4] && pos_arr[4] == pos_arr[7] && pos_arr[1] != ' ') {
    return 1;
  }
  else if (pos_arr[2] == pos_arr[5] && pos_arr[5] == pos_arr[8] && pos_arr[5] != ' ') {
    return 1;
  }
  /*if none-match and all the spaced are occupied*/
  else if (pos_arr[0] != ' ' && pos_arr[1] != ' ' && pos_arr[2] != ' ' && pos_arr[3] != ' ' &&
           pos_arr[4] != ' ' && pos_arr[5] != ' ' && pos_arr[6] != ' ' && pos_arr[7] != ' ' &&
           pos_arr[8] != ' ') {
    return 2;
  }

  return 0; // if none of these options exists, returns -2 for the game to continue.
}

/**
 * Function to add the move to the array of positions and moves
 * @param pos the position of the move
 * @param player the player who made the move
 * @param pos_arr the array of the positions and moves
 * 
*/
void addMove(int pos, char player, char pos_arr[]) {
  char mark; // the mark is either X or O to denote moves of different players

  if (player == 'A') { mark = 'X';}
  else { mark = 'O';}

  pos_arr[pos - 1] = mark; // depending on the if statement above, the empty is
                       // assigned a given mark.
}

/**
 * Function to display the current board
 * @param pos_arr the array of the positions and moves
 * 
*/
void displayBoard(char pos_arr[]) {
  red();

  /*the pos_arrays hold positions*/
  printf("\n Tic-Tac-Toe\n\n");
  reset();

  printf("Player A --(X), Player B--(O)\n");
  red();
  printf("+---+---+---+\t\t+---+---+---+\n");
  printf("| 1 | 2 | 3 |\t\t| %c | %c | %c |\n", pos_arr[0], pos_arr[1], pos_arr[2]);
  printf("+---+---+---+\t\t+---+---+---+\n");
  printf("| 4 | 5 | 6 |\t\t| %c | %c | %c |\n", pos_arr[3], pos_arr[4], pos_arr[5]);
  printf("+---+---+---+\t\t+---+---+---+\n");
  printf("| 7 | 8 | 9 |\t\t| %c | %c | %c |\n", pos_arr[6], pos_arr[7], pos_arr[8]);
  printf("+---+---+---+\t\t+---+---+---+\n");

	
}

/**
 * Function to play the game and display the board
 * @param pos_arr the array of the positions and moves
 * @param numMoves the number of moves made so far - if newgame, numMoves = 0
 * 
*/
void PlayGame(char pos_arr[], int numMoves) {
    int i, quit_save; // variable i for counter, position-stores user entry when asked
    char player;
    unsigned position;

    i = numMoves;
    while (i < 9) {         
        //WHOSE TURN - Player A - even, player B - odd 
        if (i % 2 == 0) { player = 'A';}
        else{ player = 'B';}
    
        // ask user to choose position 
        printf("\nEnter position or 0 to quit "); 	
        do { 
            printf("Player %c ->", player); 
            position = userinput();
            
        }while (position > 9 || position < 0); 

        if (position == 0) { // save game 
            printf("Enter %d(yes) to save game or %d(no) to delete:", 1, 2);
            scanf("%d", &quit_save);
            if(quit_save == 1){
                writeGame(player, pos_arr);
            }
            exit(EXIT_SUCCESS);
        }

        /*next step if the move is illegal*/
        if (legalMove(position, pos_arr)){ addMove(position, player, pos_arr);}
        else{
            printf("Invalid Option. Try again!\n");
            i -= 1;
        }

        
        displayBoard(pos_arr); // call for function for board if move is legal

        if (gameWon(position, pos_arr) == 1) {
            printf("Player %c wins", player);
            exit(EXIT_SUCCESS);
        }
            
        else if (gameWon(position, pos_arr) == 2){
            printf("Game ends in a draw!");
            exit(EXIT_SUCCESS);   
        }
        i++;
    }
}

/**
 * function to read the game history from the file if exists and calls the PlayGame function
 * @param pos_arr the array of the positions and moves
 * 
*/
void Previous_Game(char pos_arr[]){
  FILE *prevGame;
  char move;
  int pos = 0, numMoves = 0;
  //open and read file
  prevGame = fopen("GameHistory.txt", "r");

  if (prevGame == NULL){ 
    printf("There is no data to display\n");
    PlayGame(pos_arr, numMoves);
  }

  else{
    while((move = fgetc(prevGame)) != EOF){
      pos_arr[pos] = move;
      if (move != ' '){ numMoves++;}
      pos++;
    } 
    displayBoard(pos_arr);
    PlayGame(pos_arr,numMoves);
  }
}


//play against computer and can't win
/**
 * function to play against the computer and computer always wins
 * @param pos_arr the array of the positions and moves
 * 
*/
void playAgainstComputer(char pos_arr[]) {
  int position;
  char player;

  printf("Your Move --(X), Computer's Move --(O)\n");

  for (int i = 0; i < 9; i++) { // counter upto 9 because board 9 spots
	  if (i % 2 != 0) {
      player = 'A';
		  printf("\nEnter position or 0 to quit "); 	
      do { 
          printf("Player %c ->", player); 
          position = userinput();
          
      }while (position > 9 || position < 0); 

      if (position == 0) { // save game 
         printf("You lost!\n");
        exit(EXIT_SUCCESS);
      }

 	}

	else{
      player = 'B';
      /*if the players intends to get a horizontal match on row 1*/
      if ((pos_arr[0] == 'X' && pos_arr[1] == 'X' && pos_arr[2] == ' ') ||(pos_arr[0] == 'O' && pos_arr[1] == 'O' && pos_arr[2] == ' ')) {
        	position = 3;
      } 
		  else if ((pos_arr[0] == 'X' && pos_arr[1] == ' ' && pos_arr[2] == 'X') || (pos_arr[0] == 'X' && pos_arr[1] == ' ' && pos_arr[2] == 'X')){
        	position = 2;
      } else if ((pos_arr[0] == ' ' && pos_arr[1] == 'X' && pos_arr[2] == 'X') || (pos_arr[0] == ' ' && pos_arr[1] == 'O' && pos_arr[2] == 'O')) {
        	position = 1;
      }
      /*if the players intends to get a horizontal match on row 2*/
        else if ((pos_arr[3] == 'X' && pos_arr[4] == 'X' && pos_arr[5] == ' ') || (pos_arr[3] == 'O' && pos_arr[4] == 'O' && pos_arr[5] == ' ')) {
        position = 6;
      } else if ((pos_arr[3] == 'X' && pos_arr[4] == ' ' && pos_arr[5] == 'X') || (pos_arr[3] == 'O' && pos_arr[4] == ' ' && pos_arr[5] == 'O')){
        	position = 5;
				
      }		
		  else if ((pos_arr[3] == ' ' && pos_arr[4] == 'X' && pos_arr[5] == 'X') ||(pos_arr[3] == ' ' && pos_arr[4] == 'O' && pos_arr[5] == 'O')){
        	position = 4;
      }
      /*if the players intends to get a horizontal match on row 3*/
      else if ((pos_arr[6] == 'X' && pos_arr[7] == 'X' && pos_arr[8] == ' ') || (pos_arr[6] == 'O' && pos_arr[7] == 'O' && pos_arr[8] == ' ')){
      		position = 9;
      } else if ((pos_arr[6] == 'X' && pos_arr[7] == ' ' && pos_arr[8] == 'X') || (pos_arr[6] == 'O' && pos_arr[7] == ' ' && pos_arr[8] == 'O')){
        	position = 8;
      } else if ((pos_arr[6] == ' ' && pos_arr[7] == 'X' && pos_arr[8] == 'X')|| (pos_arr[6] == ' ' && pos_arr[7] == 'O' && pos_arr[8] == 'O')){
        	position = 7;
      }

      /*if the players intends to get vertical match*/
      else if ((pos_arr[0] == ' ' && pos_arr[3] == 'X' && pos_arr[6] == 'X') || (pos_arr[0] == ' ' && pos_arr[3] == 'O' && pos_arr[6] == 'O')){
        	position = 1;
      } 
	    else if ((pos_arr[0] == 'X' && pos_arr[3] == 'X' && pos_arr[6] == ' ') || (pos_arr[0] == 'O' && pos_arr[3] == 'O' && pos_arr[6] == ' ')) {
      		position = 7;

      } 
      else if ((pos_arr[0] == 'X' && pos_arr[3] == ' ' && pos_arr[6] == 'X') || (pos_arr[0] == 'O' && pos_arr[3] == ' ' && pos_arr[6] == 'O')) {
            position = 4;
        } 
      else if ((pos_arr[1] == ' ' && pos_arr[4] == 'X' && pos_arr[7] == 'X') || (pos_arr[1] == ' ' && pos_arr[4] == 'O' && pos_arr[7] == 'O')) {
            position = 2;
        } 
      else if ((pos_arr[1] == 'X' && pos_arr[4] == ' ' && pos_arr[7] == 'X') || (pos_arr[1] == 'O' && pos_arr[4] == ' ' && pos_arr[7] == 'O')) {
          position = 5;
        } 
      else if ((pos_arr[1] == 'X' && pos_arr[4] == 'X' && pos_arr[7] == ' ')|| (pos_arr[1] == 'O' && pos_arr[4] == 'O' && pos_arr[7] == ' ')) {
       		position = 8;
      } else if ((pos_arr[2] == ' ' && pos_arr[5] == 'X' && pos_arr[8] == 'X') || (pos_arr[2] == ' ' && pos_arr[5] == 'O' && pos_arr[8] == 'O')) {
        	position = 3;
      } else if ((pos_arr[2] == 'X' && pos_arr[5] == 'X' && pos_arr[8] == ' ') || (pos_arr[2] == 'O' && pos_arr[5] == 'O' && pos_arr[8] == ' ')){
        	position = 9;
      } else if ((pos_arr[2] == 'X' && pos_arr[5] == ' ' && pos_arr[8] == 'X') || (pos_arr[2] == 'O' && pos_arr[5] == ' ' && pos_arr[8] == 'O')) {
        	position = 6;
      }
      /*if the players intends to apply X along the diagonals*/
      else if ((pos_arr[0] == 'X' && pos_arr[4] == 'X' && pos_arr[8] == ' ') || (pos_arr[0] == 'O' && pos_arr[4] == 'O' && pos_arr[8] == ' ')) {
        	position = 9;
      } else if ((pos_arr[0] == ' ' && pos_arr[4] == 'X' && pos_arr[8] == 'X') || (pos_arr[0] == ' ' && pos_arr[4] == 'O' && pos_arr[8] == 'O')) {
        	position = 1;
      } else if ((pos_arr[0] == 'X' && pos_arr[4] == ' ' && pos_arr[8] == 'X') || (pos_arr[0] == 'O' && pos_arr[4] == ' ' && pos_arr[8] == 'O')) {
        	position = 5;
      } 
      else if (pos_arr[0] == 'X' || pos_arr[8] == 'X' || pos_arr[2] == 'X' || pos_arr[6] == 'X') {
            position = 5;
      }
      else if ((pos_arr[2] == 'X' && pos_arr[4] == 'X' && pos_arr[6] == ' ') || (pos_arr[2] == 'O' && pos_arr[4] == 'O' && pos_arr[6] == ' ')) {
        	position = 7;
      } else if ((pos_arr[2] == 'X' && pos_arr[4] == ' ' && pos_arr[6] == 'X') || (pos_arr[2] == 'O' && pos_arr[4] == ' ' && pos_arr[6] == 'O')) {
        	position = 5;
      } else if ((pos_arr[2] == ' ' && pos_arr[4] == 'X' && pos_arr[6] == 'X') || (pos_arr[2] == ' ' && pos_arr[4] == 'O' && pos_arr[6] == 'O')){
        	position = 3;
      }

      else { // if none of the scenarios above occur, generate a random number
       		srand(time(NULL)); // this function refreshes the random number every second
        	position = (rand()%9) + 1;
          //position = (rand() % (9 - 1 + 1)) + 1; // the format is (rand() %(upper_bound-lower_bound+1))+1. random numbers range 1-9
				//position = rand() % 10;
      }
	}
			 
	 /*next step if the move is illegal*/
    if (legalMove(position, pos_arr)){ 
      addMove(position, player, pos_arr);
      displayBoard(pos_arr); // call for function for board if move is legal
      }
    else{
      if(player == 'A') { printf("Invalid Option. Try again!\n");}
      i -= 1;
    }

          
   // displayBoard(pos_arr); // call for function for board if move is legal
      

    if (gameWon(position, pos_arr) == 1 && player == 'A') {
      printf("You won!\n");
      exit(EXIT_SUCCESS);
    }
    else if (gameWon(position, pos_arr) == 1 && player == 'B'){
      printf("You LOST!\n");	
      exit(EXIT_SUCCESS);
    }
    else if (gameWon(position, pos_arr)  == 2){
      printf("Game ends in a draw!");
      exit(EXIT_SUCCESS);
    }
    //exit(EXIT_SUCCESS);
  }
}


// accessory functions
void red() { printf("\033[1;31m"); }
void yellow() { printf("\033[1;33m");}
void violet() { printf("\033[1;33m");}
void reset() { printf("\033[0m"); }

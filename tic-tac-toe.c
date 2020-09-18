#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <ctype.h>

#define true 1
#define false 0
#define MaxMemory 100

int x,y, TotalMoves, grid_size, sequence_number, gridFull, PossibleMoves, win_decision;
char letter = 'X';
int successfulMove = 1;


//the maximum size of the grid
#define MaxGrid 10

struct Move
{
	//the symbol played by the player
	char player;
	//the coordinates of the move
	int x,y;
};

char grid[MaxGrid][MaxGrid];
/*
 * Checks if the given grid size is within the range; Returns true if the input is invalid, and false otherwise.
 */
int init_grid() {
    int i, j;
    if ( grid_size >= 3 && grid_size <= MaxGrid) // ifthe grid size is within the specified range
    {
        TotalMoves =0;
		for ( i= 0; i < grid_size; i++)
		    for (j= 0; j < grid_size; j++)
				 grid[i][j] = '.'; // intializing all grid values to "."
		return false;
	}
	else
		return true;
}



 //Checks if the player won
int player_won (char letter) {
 int diagonal = 0, SecondDiagonal= 0;
//to simplify the coming lines
 for (int n = 0; n < grid_size; n++) // a loop to check the vertical and horizontal lines for a winner
 {
   int vertical = 0, horizontal = 0;
	 for(int m = 0; m < grid_size; m++)
	 {
		 if ( grid[m][n] == letter) // to check if the letter exist in a vertical line
	 	    vertical += 1;

	 	 if ( grid[n][m] == letter) // to check if the letter exist in a horizontal line
			  horizontal += 1;

	 	 if (vertical == grid_size || horizontal == grid_size) // to check if the line fully have the same letter and therefore there is a winner (vertical or horizontal)
		   return true;
	 }
 }

  for ( int n=0; n < grid_size; n++) // a loop to check the diagonal line and second diagonal for  winner
  {

		if (grid[n][n] == letter) // to find if if there is a winner in diagonal
		   diagonal += 1;

		if (grid[grid_size-n-1][n] == letter) // to find if there is a winner diagonal
		   SecondDiagonal+= 1;

		if (diagonal == grid_size || SecondDiagonal == grid_size) // to see if the line is all with the same letter
       return true;
	}

return false;
}


 //Returns false if it encountered an error and true otherwise.
struct Move AllMoves[MaxMemory];
int make_move(int x, int y, char letter) {

 // to check if this point is not used before and is within the range
  if ((grid[x][y] == '.') && (x >=0 && x< grid_size) && (y>=0 &&y<grid_size))
  {
      // to count the numbers of moves once more move added
      TotalMoves++;

      // if not used we insert the letter of the player
      grid[x][y] = letter;
      
      // assigning values to the specific Move in the struct where TotalMove sis a counter for the moves
      AllMoves[TotalMoves].x = x;
	  AllMoves[TotalMoves].y = y;
	  AllMoves[TotalMoves].player = letter;
      
      return true;
	}
// if the point is not within the range we return false
  return false;
}

/* Returns the move performed at the "sequence_number"-th step during the current game, where the
 * first move is number 1 (not 0).
 *
 * If no such move exists (because sequence_number is not a valid move number in the
 * current game), the function returns an empty move.
 * An empty move is an object of struct Move that has both x and y set to -1.
 */
struct Move replay_move(int sequence_number) {

	//definig a struct for empty move and then assignig -1 to x and y in it
	struct Move emptyMove;
	emptyMove.x =-1;
	emptyMove.y =-1;
	
	// if it is not an empty move the struct for the sequence_number will be returned
	if (( TotalMoves >= sequence_number) && (sequence_number >= 1)) {return AllMoves[sequence_number];}
	else {return emptyMove;}
}

// This function asks the player for a gridsize then prints the  intial grid and the colmuns and rows numbers
void game_board(int grid_size) {
	printf("\n"); // to skip a line
	printf(" ");
	
	// printing grid values number in a row
	for (int x= 0; x < grid_size; x++){printf(" %i", x);}

	 // printing grid values number in colmuns
	for (int x= 0; x < grid_size;x++)
	{
		printf("\n");
		printf("%i ", x);

		// printing an intial grid
		for (int y=0; y< grid_size; y++){printf("%c ", grid[x][y]); }
	}
	printf("\n");
	printf("\n");
}

// to check the number of successful Moves
//int x, int y, char letter
void player () {
    int y = -1;
    int x = -1;

	// if moves counter is odd  then it's player 1 (X)
    if ( successfulMove%2 == 0 ){letter ='O'; }
	// if moves counter is even then it's player 2 (O)
	else {letter= 'X';}


	printf("\n\nPlayer %c, enter location (x,y): ", letter);
	scanf("%i,%i", &x, &y);

    //loops until a valid value is given
    while ((x == -1) || (y == -1)){
        //reset valyes to -1 again if both or any is not given
        x = -1;
        y = -1;
        printf("\n\nPlayer %c, enter location in this format x,y: ", letter);
        scanf("%i,%i", &x, &y);
        }

    int move = make_move( x, y, letter);
	if (move) {
		// countung the number of successful Moves
		successfulMove++;
		grid[x][y] = letter;

        printf("%i,%i", x, y);
	}

	// if the move was not successful it tells the player that they should have another input
	else
	{
        // prints an error message if point is already occupied.
        if(grid[x][y] != '.' && (x >=0 && x< grid_size) && (y>=0 &&y<grid_size))
        {
            printf("\n ******** Invalid choice: point is already occupied. Please try again. ********\n"); 
        }

        //prints an error message if chosen numbers are out of the range.
        else {printf("\n******** Invalid input: point is out of range. Please try again. ********\n"); }

        //recalls the function to ask for input
		player();
	}
 }

// this functio n replaies the played moves
void replayGame() { 
	int Answer, sequence_number=0;
	int MovesLeft = TotalMoves;

	// loops while the player chooses 1 to replay the sequence_number move
	printf("Do you want to replay the game moves, Yes=1, No=2 ?");
	scanf("%i", &Answer);
	while ( MovesLeft >0)
	{
		if (Answer == 1)
		{
			MovesLeft--;
			if (MovesLeft > 0) // if there are still moves it continues to ask
      {
				sequence_number++;
			  replay_move(sequence_number);
			  printf("Do you want to replay the next Move Yes==1, No=2?");
			}
		}
		if ( Answer == 2) // if the player chooses 2 the program stops
			exit(0);
		else
			printf("Input invalid choose yes=1 if you want to replay or 2 (No)"); // if choice is wrong it tells the player that it is wrong
		}
}


//the main function of your program, renamed to compile the tests.
int main() {

	//creating an instance of the struct.
	struct Move playerOne, playerTwo;
	PossibleMoves = grid_size*grid_size;

	printf("Hello, Here is the Tic-Tac-Toe Game!\n");
	printf("Please choose a grid size for the Game between 3 and 10 inclusive: "); // asking the user for grid size
	scanf("%i", &grid_size); // assinging the given the value to a variable for later use

	if (init_grid() == true) // if grid size is not within the range it asks for another input
	{
		printf("\nInvalid grid size: Please choose a grid size for the Game between 3 and 10 inclusive: "); // asking the user for grid size
		scanf("%i", &grid_size);
	}
    
    init_grid(); // calling the previously written function to use its values
    char status= 'a';

	while (status == 'a') // game c
	{
         // to start the game
		game_board(grid_size);
	
		player();
		// player_won(letter);
		// if (win_decision == true){status = 'b';}
		// else if (win_decision == false && successfulMove == PossibleMoves){status = 'c';}
		// else{status = 'a';}
	}

	// if (status == 'b')
	// {
	// 	printf("%c won the game\n", letter); // informing players of a win
	// }
	// if (status == 'c')
	// {
	// 	printf(" Game is over nobody won\n"); // if the grid is full and nobody won
	// }

	// if (status == 'b' || status == 'c'){
	// 	// replayGame();
	// }



 return 0;
 }

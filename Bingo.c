//Cole Wagner
//Bingo simulation

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PLAYER 3
#define ROW 5
#define COLUMN 5

void generateCard(int, int[3][5][5]);
void printCards(int[3][5][5]);
int isEqual(int, int);
int callNumber();
void playGame(int[3][5][5], int[75]);
int winCheck(int[3][5][5]);

int main() {

  srand(time(0));

  //array to store the numbers that get called
  int alreadyCalled[75] = {0};

  //3d array to store the BINGO cards for all 3 players
  int cards[PLAYER][ROW][COLUMN] = {
    {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}},

    {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}},

    {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}}
  };

//Generate 3 player's cards
  int i;
  for(i = 0; i < 3; i++) {
    generateCard(0, cards);
    generateCard(1, cards);
    generateCard(2, cards);
  }

//print out the cards
  printCards(cards);

  printf("\n\n");

//play the game
  playGame(cards, alreadyCalled);

  return 0;
}

//Function to randomly generate the player's BINGO cards
void generateCard(int num, int cards[3][5][5]) {

  int i;
  int j;
  int gen;
  for(i = 0; i < ROW; i++) {
    //The "used" array will check to make sure there are no repeats of numbers
    int used[5] = {0};
    for(j = 0; j < COLUMN; j++) {

      int b = 1;

      //while loop to keep regenerating each row until they are all unique numbers
      while(b) {

        //Generate the numbers in the right range acoording to their column
        if(i == 0) {
          gen = (rand() % (15 - 1 + 1)) + 1;
        } else if(i == 1) {
          gen = (rand() % (30 - 16 + 1)) + 16;
        } else if(i == 2) {
          gen = (rand() % (45 - 31 + 1)) + 31;
        } else if(i == 3) {
          gen = (rand() % (60 - 46 + 1)) + 46;
        } else if(i == 4) {
          gen = (rand() % (75 - 61 + 1)) + 61;
        }

        b = 0;

        //Check if any of the other numbers in the row is the same as the generated number
        int k;
        for(k = j; k >= 0; k--) {
          if(isEqual(used[k], gen) == 0) {
            //not the same
          } else {
            //If it is the same, keep the while loop going
            b = 1;
          }
        }

        cards[num][i][j] = gen;
        used[j] = gen;
      }
    }
  }

}

//Function to print out the bingo cards
void printCards(int cards[3][5][5]) {
  printf("\n");
  int i;
  int j;
  int h;
  //Triple nested for loop to print out all the rows and columns of each player's card
  for(i = 0; i < 3; i++) {
    printf("\n");
    printf("\nPlayer %d's Card", i + 1);
    for(j = 0; j < 5; j++)  {
      printf("\n");
      for(h = 0; h < 5; h++) {
          printf("%d  ", cards[i][j][h]);
      }
    }
  }
}

int isEqual(int a, int b) {
  if(a == b) {
    return 1;
  }
  return 0;
}

//Function to "call" bingo numbers. Returns the number
int callNumber(int alreadyCalled[75]) {

  int gen = (rand() % (75 - 1 + 1)) + 1;

//Check if the number has already been called
  if(isEqual(gen+1, alreadyCalled[gen+1])) {
    //If it has already been called, use recursion to call another number
    return callNumber(alreadyCalled);
  }

  alreadyCalled[gen+1] = gen+1;

  printf("\n%d was called",gen );
  return gen;
}

void playGame(int cards[3][5][5], int alreadyCalled[75]) {
  int called[3][5][5] = {
    {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}},

    {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}},

    {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}}
  };

//While loop to keep the game running until there is a winner.
//When there is a winner, winCheck will return the player number
  while(winCheck(cards) == 0) {
    int num = callNumber(alreadyCalled);

    int p;
    int i;
    int j;
    for(p = 0; p < 3; p++) {
      for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
          if(cards[p][i][j] == num) {
            cards[p][i][j] = -1;
          }
        }
      }
    }
  }

  printf("\n\nPlayer %d is the winner!\n", winCheck(cards));

}

//Function to check if the game is won, returns the player who won
int winCheck(int cards[3][5][5]) {

  int p;
  int i;
  int j;
  //Triple nested for loop to check every index of the cards
  for(p = 0; p < 3; p++) {
    for(i = 0; i < 5; i++) {
      for(j = 0; j < 5; j++) {

        //The following if statements check if there is a win via row or column
        if(cards[p][i][j] == -1) {
          if(!(cards[p][i][j] == -1)) {
            continue;
          } else {
            if((cards[p][i][0] == -1) && (cards[p][i][1] == -1) && (cards[p][i][2] == -1) && (cards[p][i][3] == -1) && (cards[p][i][4] == -1)) {
              return p + 1;
            } else if((cards[p][0][j] == -1) && (cards[p][1][j] == -1) && (cards[p][2][j] == -1) && (cards[p][3][j] == -1) && (cards[p][4][j] == -1)) {
              return p + 1;
              //The next two if statements will check for diagonal wins
            } else if((cards[p][0][0] == -1) && (cards[p][1][1] == -1) && (cards[p][2][2] == -1) && (cards[p][3][3] == -1) && (cards[p][4][4] == -1)) {
              return p + 1;
            } else if((cards[p][4][0] == -1) && (cards[p][3][1] == -1) && (cards[p][2][2] == -1) && (cards[p][1][3] == -1) && (cards[p][0][4] == -1)) {
              return p + 1;
            }
          }
        }
      }
    }
  }

  return 0;
}

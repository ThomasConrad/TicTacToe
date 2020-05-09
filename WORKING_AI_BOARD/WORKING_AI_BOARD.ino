bool tickx = false;
bool ticky = true;
bool tock = true;
bool ticks = false;
String pieces[] = { "X","-","O" };
String player[] = { "X", "O" };
int playerTurn = 1;
bool tick = true;

int x;
int y;
int x_;
int y_;

int initLayout[3][3] = {
  { 0,0,0 },
  { 0,0,0 },
  { 0,0,0 },
};





void arrayToArray(int a[3][3], int b[3][3]) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      a[i][j] = b[i][j];
    };
  };
}

class Board {
  int aiTeam;
  int zero = 9;
  int state[3][3];//byte arrays
  int desiredState[3][3];//byte arrays
  bool turn = true;
  String game;
  int turncount = 0;
  int ticker = 0;
  int Avg[3][3];
public:
  Board(int state_[3][3]) {
    arrayToArray(state, state_);
    arrayToArray(desiredState, state_);
  };
  /********SETTERS AND GETTERS*********/
  void setGame(String set) {
    game = set;
  }
  void setTeam(int set) {
    aiTeam = set;
  }

  String getGame() {
    return game;
  }
  void setTurn(bool set) {
    turn = set;
  }

  bool getTurn() {
    return turn;
  }
  /********FUNCTIONS********/
  void printArray() {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        Serial.print(state[i][j]);
        Serial.print(" ");
      };
      Serial.println();
    };
  };

  int getCount() {
    zero = 9;
    for (int i = 0; i < 3; i++) { //counts empty spaces on board
      for (int j = 0; j < 3; j++) {
        if (state[i][j] != 0) {
          zero--;
        }
      }
    }
    return zero;
  }

  void printBoard() {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        Serial.print(pieces[state[i][j] + 1]);
        Serial.print(" ");
      };
      Serial.println();
    };
  };
  void printDesiredBoard() {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        Serial.print(pieces[desiredState[i][j] + 1]);
        Serial.print(" ");
      };
      Serial.println();
    };
  };

  int wincheck() {
    int temp = 0;
    int winner = 0;
    //Vertical check
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        temp += state[j][i];

      }
      if (temp == 3) { winner = 1; }
      else if (temp == -3) { winner = -1; }

      temp = 0;
    }

    //Horisontal check
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        temp += state[i][j];
      }
      if (temp == 3) { winner = 1; }
      else if (temp == -3) { winner = -1; }
      temp = 0;
    }

    //Diagonal check 1
    int j = 0;
    for (int i = 0; i < 3; i++) {
      temp += state[i][j];
      j++;
    }
    if (temp == 3) { winner = 1; }
    else if (temp == -3) { winner = -1; }
    temp = 0;

    //Diagonal check 2
    j = 2;
    for (int i = 0; i < 3; i++) {
      temp += state[j][i];
      j--;
    }
    if (temp == 3) { winner = 1; }
    else if (temp == -3) { winner = -1; }
    temp = 0;


    return winner;
  }


  String findMove() {
    int count = 0;
    for (int i = 0; i < 3; i++) { //counts empty spaces on board
      for (int j = 0; j < 3; j++) {
        if (state[i][j] == 0) {
          count++;
        }
      }
    }
    if (count == 9) { //if board is empty, play middle
      state[1][1] = aiTeam;
      return "1,1";
    }
    if (count == 8) { //if one piece is played
      if (state[1][1] == 0) { //if middle is free, play there
        state[1][1] = aiTeam;
        return "1,1";
      }
      else { //else play a random corner
        int pick = millis() % 4;
        switch (pick) {
        case 0:
          state[0][0] = aiTeam;
          return "0,0";
          break;
        case 1:
          state[2][0] = aiTeam;
          return "2,0";
          break;
        case 2:
          state[0][2] = aiTeam;
          return "0,2";
          break;
        case 3:
          state[2][2] = aiTeam;
          return "2,2";
          break;
        }
      }
    }

    if (count == 3) { //if it has to move a piece
      for (int i = 0; i < 3; i++) { //First check to play winning moves, while moving a piece
        for (int j = 0; j < 3; j++) {
          if (state[i][j] == 0) {
            state[i][j] = aiTeam;
            if (wincheck() == aiTeam) {
              String moves = String(i) + "," + String(j);

              for (int i = 0; i < 3; i++) { //Check which piece can be moved:
                for (int j = 0; j < 3; j++) {
                  if (state[i][j] == aiTeam) {
                    state[i][j] = 0;
                    if (wincheck() == aiTeam) {
                      moves = String(i) + "," + String(j) + " moved to " + moves;
                      return moves;
                    }
                    else {
                      state[i][j] = aiTeam;
                    }
                  }
                }
              }


            }
            else {
              state[i][j] = 0;
            }
          }
        }
      }

      for (int i = 0; i < 3; i++) { //Second check to prevent losing moves
        for (int j = 0; j < 3; j++) {
          if (state[i][j] == 0) {
            state[i][j] = aiTeam*-1;
            if (wincheck() == aiTeam*-1) {
              state[i][j] = aiTeam;
              String moves = String(i) + "," + String(j);

              for (int i = 0; i < 3; i++) { //Check which piece can be moved:
                for (int j = 0; j < 3; j++) {
                  if (i == 1 && j == 1) {
                    continue;
                  }
                  else if (state[i][j] == aiTeam) {
                    state[i][j] = aiTeam*-1;
                    if (wincheck() != aiTeam*-1) {
                      state[i][j] = 0;
                      moves = String(i) + "," + String(j) + " moved to " + moves;
                      return moves;
                    }
                    else {
                      state[i][j] = aiTeam;
                    }
                  }
                }
              }


            }
            else {
              state[i][j] = 0;
            }
          }
        }
      }



      int I;
      int J;

      for (int i = 0; i < 3; i++) { //Deletes one brick, middle not included
        for (int j = 0; j < 3; j++) {
          if (state[i][j] == aiTeam) {
            if (i == 1 && j == 1) {
              continue;
            }
            state[i][j] = aiTeam*-1;
            if (wincheck() != aiTeam*-1) {
              state[i][j] = 0;
              I = i;
              J = j;
            }
            else {
              state[i][j] = aiTeam;
            }
          }
        }
      }
      int rand = random(0, 2);
      int counter = 0;
      for (int i = 0; i < 3; i++) { //Places one random, but not the same as the one which was moved
        for (int j = 0; j < 3; j++) {
          if (state[i][j] == 0) {
            if (i == I && j == J) {
              continue;
            }
            else if (counter == rand) {
              state[i][j] = aiTeam;
              return String(I) + "," + String(J) + " moved to" + String(i) + "," + String(j);
            }
            counter++;
          }
        }
      }
    }

    else { //if it doensn't have to move a piece

      for (int i = 0; i < 3; i++) { //First check to play winning moves
        for (int j = 0; j < 3; j++) {
          if (state[i][j] == 0) {
            state[i][j] = aiTeam;
            if (wincheck() == aiTeam) {
              String moves = String(i) + "," + String(j);
              return moves;
            }
            else {
              state[i][j] = 0;
            }
          }
        }
      }

      for (int i = 0; i < 3; i++) { //Second check to prevent losing moves
        for (int j = 0; j < 3; j++) {
          if (state[i][j] == 0) {
            state[i][j] = aiTeam*-1;
            if (wincheck() == aiTeam*-1) {
              state[i][j] = aiTeam;
              String moves = String(i) + "," + String(j);
              return moves;
            }
            else {
              state[i][j] = 0;
            }
          }
        }
      }

      int rand = millis() % count;
      int counter = 0;
      for (int i = 0; i < 3; i++) { //Places one random
        for (int j = 0; j < 3; j++) {
          if (state[i][j] == 0) {
            if (counter == rand) {
              state[i][j] = aiTeam;
              String moves = String(i) + "," + String(j);
              return moves;
            }
            counter++;
          }
        }
      }






    }
  }

  void append(int X, int Y, int data) {
    state[Y][X] = data;
  }

  void desiredAppend(int X, int Y, int data) {
    desiredState[Y][X] = data;
  }


  bool turncheck() {
    return turn;
  }

  

  bool check() {
    for (int i = 0; i < 1000; i++) {
      int readvalues[3][3] = { //Foerst laeser arduinoen de raa vaerdier for hall-sensorerne, og laver et arrayarray af dem, tilsvarende til spillepladen.
        { analogRead(A7), analogRead(A8), analogRead(A9) },
        { analogRead(A4), analogRead(A5), analogRead(A6) },
        { analogRead(A1), analogRead(A2), analogRead(A3) }
      };
      for (int i = 0; i < 3; i++) { //Denne funktion laegger den maalte vaerdi til et sumarray, der samler maalingerne.
        for (int j = 0; j < 3; j++) {
          Avg[i][j] += readvalues[i][j];
        };
      };
    }
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (Avg[i][j] / 1000 < 390) { //390 er sat til graensen hvor X maaler. Dette er fundet i testing
          desiredState[j][i] = -1;
          //board[i][j] = "X";
        }
        else if (Avg[i][j] / 1000 > 480) { //480 er sat til graensen hvor O maaler. Dette er fundet i testing
          desiredState[j][i] = 1;
          //board[i][j] = "O";
        }
        else {
          desiredState[j][i] = 0;
          //board[i][j] = "-"; //mellem disse to vaerdier er den tomme maaling
        }
      };
    };

    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        Avg[i][j] = 0;
      };
    };

    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (state[i][j] != desiredState[i][j]) {
          return false;
        }
      }
    }

    return true;
  }

  void update() {
    for (int i = 0; i < 1000; i++) {
      int readvalues[3][3] = { //Foerst laeser arduinoen de raa vaerdier for hall-sensorerne, og laver et arrayarray af dem, tilsvarende til spillepladen.
        { analogRead(A7), analogRead(A8), analogRead(A9) },
        { analogRead(A4), analogRead(A5), analogRead(A6) },
        { analogRead(A1), analogRead(A2), analogRead(A3) }
      };
      for (int i = 0; i < 3; i++) { //Denne funktion laegger den maalte vaerdi til et sumarray, der samler maalingerne.
        for (int j = 0; j < 3; j++) {
          Avg[i][j] += readvalues[i][j];
        };
      };
    }
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (Avg[i][j] / 1000 < 390) { //390 er sat til graensen hvor X maaler. Dette er fundet i testing
          desiredState[j][i] = -1;
          //board[i][j] = "X";
        }
        else if (Avg[i][j] / 1000 > 480) { //480 er sat til graensen hvor O maaler. Dette er fundet i testing
          desiredState[j][i] = 1;
          //board[i][j] = "O";
        }
        else {
          desiredState[j][i] = 0;
          //board[i][j] = "-"; //mellem disse to vaerdier er den tomme maaling
        }
      };
    };
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        Avg[i][j] = 0;
      };
    };

    arrayToArray(state, desiredState);
  }

};

Board TicTac(initLayout);

int hej = 1;

int n = 1;

String board[3][3] = {
  { "-", "-", "-" },
  { "-", "-", "-" },
  { "-", "-", "-" }
};
int Avg[3][3] = {
  { 0, 0, 0 },
  { 0, 0, 0 },
  { 0, 0, 0 }
};

int Randomgen;
int aiteam;
int play;
// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);
  pinMode(A8, INPUT);
  pinMode(A9, INPUT);
  Serial.begin(9600);
  randomSeed(analogRead(A11));
  Serial.println("Du laver et traek ved at holde brikken paa dens plads i tre sekunder.");
  delay(500);
  Randomgen = int(random(0, 10000));
  delay(200);
  play = int(random(0, 10000));

  if (play % 6 == 0) {
    TicTac.setTeam(-1);
    aiteam = -1;
  }
  else {
    TicTac.setTeam(1);
    aiteam = 1;
  }

  if (Randomgen % 2 == 0) {
    Serial.println("Spilleren starter. Du er " + String(pieces[aiteam*-1 + 1]) + ". ");
    TicTac.setTurn(true);
  }
  else {
    Serial.println("Computeren starter. Den er " + String(pieces[aiteam + 1]));

    TicTac.setTurn(false);

  }

}

// the loop function runs over and over again forever
void loop() {


  if (TicTac.getTurn() == true) {
    if (tick) { Serial.println("Lav dit traek: "); tick = !tick; }
    if (TicTac.check() == false) {
      delay(500);
      if (TicTac.check() == false) {
        delay(2000);
        if (TicTac.check() == false) {
          TicTac.update();
          TicTac.printBoard();
          TicTac.setTurn(false);
          tock = true;
        }
      }
    }
  }

  if (TicTac.getTurn() == false) {
    if (tock) { Serial.println("AI is playing: " + TicTac.findMove()); tock = !tock; TicTac.printBoard(); }

    if (TicTac.check() == true) {
      delay(500);
      if (TicTac.check() == true) {
        delay(2000);
        if (TicTac.check() == true) {
          TicTac.setTurn(true);
          tick = true;

        }
      }
    }
  }
  
  if (TicTac.wincheck() != 0) {
    Serial.println("Spiller " + pieces[TicTac.wincheck() + 1] + " har vundet. Spillet er forbi.");
    delay(60000);
  }
  


}

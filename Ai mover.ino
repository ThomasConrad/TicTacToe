bool tickx = false;
bool ticky = true;
bool tock = false;
bool ticks = false;
String pieces[] = { "X","-","O" };
int playerTurn = 1;

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
	int state[3][3];//byte arrays
	int desiredState[3][3];//byte arrays
	bool turn = true;
	String game;
	int turncount = 0;
	int ticker = 0;
public:
	Board(int state_[3][3]) {
		arrayToArray(state, state_);
		arrayToArray(desiredState, state_);
	};
	/********SETTERS AND GETTERS*********/
	void setGame(String set) {
		game = set;
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

	void append(int X, int Y, int data) {
		state[Y][X] = data;
	}

	void desiredAppend(int X, int Y, int data) {
		desiredState[Y][X] = data;
	}


	bool turncheck() {
		return turn;
	}

	void setPiece() {
		if (turncount > 5) {
			if (ticker == 0) {
				Serial.print("piece you want to move, X-coord: ");

				ticker++;
			}
			if (ticker == 1) {
				while (Serial.available()) {
					x_ = Serial.readString().toInt();
					Serial.println(x_);
					ticker++;
				}
			}
			if (ticker == 2) {
				Serial.print("piece you want to move, Y-coord: ");

				ticker++;
			}
			if (ticker == 3) {
				while (Serial.available()) {
					y_ = Serial.readString().toInt();
					Serial.println(y_);
					ticker++;
				}
				this->append(x_, y_, 0);
			}

		}


		if (ticker == 5) {
			Serial.print("X-coord: ");

			ticker++;
		}
		if (ticker == 6) {
			while (Serial.available()) {
				x = Serial.readString().toInt();
				Serial.println(x);
				ticky = false;
				ticks = true;
			}
		}

		if (ticker == 7) {
			Serial.print("Y-coord: ");

			ticker++;

		}
		if (ticker == 8) {
			while (Serial.available()) {
				y = Serial.readString().toInt();
				Serial.println(y);
				ticker++;
			}
		}
		if (ticker == 9) {
			this->append(x, y, playerTurn);
			Serial.println("Board: ");
			this->printBoard();
			tock = false;
			tickx = false;
			ticky = true;
			ticks = false;
			turn = true;
		}
	}

};

Board TicTac(initLayout);

int hej = 1;

int n = 1;
String board[3][3] ={
	{ "-", "-", "-" },
	{ "-", "-", "-" },
	{ "-", "-", "-" }
};
int Avg[3][3] ={
	{ 0, 0, 0 },
	{ 0, 0, 0 },
	{ 0, 0, 0 }
};

int Randomgen;

// the setup function runs once when you press reset or power the board
void setup() {
	// initialize digital pin 13 as an output.
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
	Randomgen = int(random(0,1000));
	if (Randomgen % 2 == 0) {
		Serial.println("Spilleren starter. Du er O. Lav dit traek:");
		TicTac.setTurn(true);
	}
	else {
		Serial.println("Computeren starter. Den er X. Venligst ryk til denne position:");
		TicTac.append(1, 1, -1);
		TicTac.printDesiredBoard();
		TicTac.setTurn(false);

	}



}

// the loop function runs over and over again forever
void loop() {
	/*
	int readvalues[3][3] =	{ //Foerst laeser arduinoen de raa vaerdier for hall-sensorerne, og laver et arrayarray af dem, tilsvarende til spillepladen.
		{ analogRead(A7), analogRead(A8), analogRead(A9) },
		{ analogRead(A4), analogRead(A5), analogRead(A6) },
		{ analogRead(A1), analogRead(A2), analogRead(A3) }


	};
	Denne funktion vil vise de raa vaerdier paa serial output
	for (int i = 0; i < 3; i++) {
	for (int j = 0; j < 3; j++) {
	Serial.print(readvalues[i][j]);
	Serial.print(" ");
	};
	Serial.println();

	};
	for (int i = 0; i < 3; i++) { //Denne funktion laegger den maalte vaerdi til et sumarray, der samler maalingerne.
		for (int j = 0; j < 3; j++) {
			Avg[i][j] += readvalues[i][j];
		};
	};
	n++;// En ilterator taeller antallet af gange som maalingerne er blevet summeret
	if (n >= 10000) { //Ved 10.000 gange udfoeres maalingen
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (Avg[i][j] / n < 390) { //390 er sat til graensen hvor X maaler. Dette er fundet i testing
					TicTac.append(i, j, -1);
					//board[i][j] = "X";
				}
				else if (Avg[i][j] / n > 480) { //480 er sat til graensen hvor O maaler. Dette er fundet i testing
					TicTac.append(i, j, 1);
					//board[i][j] = "O";
				}
				else {
					TicTac.append(i, j, 0);
					//board[i][j] = "-"; //mellem disse to vaerdier er den tomme maaling
				}
			};
		};
		n = 1;

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				Avg[i][j] = 0;
			};
		};
		//TicTac.printBoard();
	}
	*/


	if (TicTac.getTurn() == false) { //computeren venter paa at spilleren rykker til den rigtige stilling
		int timeout = millis();
		while (true)
		{
			//Tag 100000 maalinger fra sensorene
			for (int i = 0; i < 10000; i++) {
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
					if (Avg[i][j] / 10000 < 390) { //390 er sat til graensen hvor X maaler. Dette er fundet i testing
						TicTac.append(i, j, -1);
						//board[i][j] = "X";
					}
					else if (Avg[i][j] / 10000 > 480) { //480 er sat til graensen hvor O maaler. Dette er fundet i testing
						TicTac.append(i, j, 1);
						//board[i][j] = "O";
					}
					else {
						TicTac.append(i, j, 0);
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
				for (int j = 0; i < 3; i++) {

				}
			}
		}



	}


	if (TicTac.getTurn() == true) {

	}



}
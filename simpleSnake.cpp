#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y;		// Variables for head position
int fruitX, fruitY, score;	// Variables for fruit position and Score
int tailX[100], tailY[100];	// Keeps track of coordinates of tail in sequence
int nTail;					// Length of the tail
enum eDirection { STOP = 0 , LEFT , RIGHT , UP , DOWN};
eDirection dir;
void Setup() {
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}
void Draw() {
	system("cls");	// Clears the screen
	for (int i = 0; i < width+2; i++) {	// Top boarder of the map
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < height; i++) {	// Print the interior of the map
		for (int j = 0; j < width; j++) {
			if (j == 0) {
				cout << "#";	//  Print the left wall
			}
			if (i == y && j == x) {
				cout << "O";	// Instead of printing a empty space we print the head of the snake
			}
			else if (i == fruitY && j == fruitX) {
				cout << "F";	// Printing the fruit
			}
			else {

                bool print = false;
				for (int k = 0; k < nTail; k++) {


					if (tailX[k] == j && tailY[k] == i) {
						cout << "o";
						print = true;
					}
				}
					if (!print) {
						cout << " ";	// The remaining interior is empty
					}
			}
			if (j == width - 1) {
				cout << "#";	// Print the right wall
			}
		}
		cout << endl;
	}

	for (int i = 0; i < width+2; i++) {	// Bottom boarder of the map
		cout << "#";
	}
	cout << endl;
	cout << "Score: " << score << endl;
}
void Input() {
	if (_kbhit()) {			// Returns positive if any character on the keyboard is hit
		switch (_getch()) {
		// We switch it for w,a,s,d - controls for snake's direction
		case 'a':
			dir = LEFT;		// When a is pressed , we move left
			break;
		case 'd':
			dir = RIGHT;	// When d is pressed , we move right
			break;
		case 'w':
			dir = UP;		// When w is pressed , we move upwards
			break;
		case 's':
			dir = DOWN;		// When s is pressed , we move downwards
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}
void Logic() {
	int prevX = tailX[0];		// x coordinate of previous node being the tail
	int prevY = tailY[0];		// y coordinate of previous node being the tail
 	int prev2X, prev2Y;
	// To move the tail
	tailX[0] = x;
	tailY[0] = y;

	for (int i = 1; i < nTail; i++) {		// Since when we input ,our one of the nodes(head) turns by itself and we have to control the remaining nodes as the tail
		prev2X = tailX[i];
		prev2Y = tailY[i];

		tailX[i] = prevX;
		tailY[i] = prevY;

		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir) {
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UP:
			y--;		// Since the variable 'j' decreases in the loop
			break;
		case DOWN:
			y++;
			break;
		default:
			break;
	}
	if (x > width || x < 0 || y < 0 || y > height) {
		gameOver = true;
	}

	for(int i=0; i < nTail; i++){

        if(tailX[i] == x && tailY[i] == y){
            gameOver = true;
        }
	}

	if (x == fruitX && y == fruitY) {
		score = score + 10;		// After eating the fruit it should be relocated somewhere
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;				// When we eat the fruit , the tail increases
	}
}
int main() {
	Setup();
	while (!gameOver) {
		Draw();
		Input();
		Logic();
	}
	Sleep(10) ; // - Slows down the game a little bit
	return 0;
}

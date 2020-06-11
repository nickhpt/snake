
#include "stdafx.h"
#include <iostream>
#include <conio.h> //Console input output
#include <chrono> //for delay
#include <thread> // for delay
using namespace std;
bool gameOver;
const int width = 30;
const int height = 30;
int x, y, foodX, foodY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection{STOP = 0, LEFT,RIGHT,UP,DOWN};
eDirection dir;


void Setup() {
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	foodX = rand() % width-1; //zero to width - 2
	foodY = rand() % height-1; 
	score = 0;

}

void Draw() {
	system("cls"); //win cmd for clearing console

	for (int i = 0; i < width+2; i++) //top wall
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)

	{
		for (int j = 0; j < width + 2; j++)
		{
			if (j == 0)
				cout << "#"; // left wall

			if (i == y && j == x)
				cout << "O";
			else if (i == foodY && j == foodX)
				cout << "F";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{


					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " "; // else blank


				if (j == width - 1)
					cout << "#"; // right wall 
			}

			}
			cout << endl;

		}
	
	
	for (int i = 0; i < width+2; i++)
		cout << "#"; //bottom wall 
	cout << endl;
	cout << "Current score:" << score << endl;
	if (score >= 0 && score < 40)
		cout << "Reach 40!" << endl;
}
//Using conio.h for keyboard inputs
void Input() { 
	if (_kbhit())
	{
		switch (_getch()) 
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}

}

void Logic() 
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
	}

	switch (dir)
	{	
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	if (x > width || x < 0 || y > height || y < 0)
		gameOver = true;
	if (x == foodX && y == foodY)
		{
			
			score += 10;
			foodX = rand() % width -1; //zero to width - 2 
			foodY = rand() % height -1;
			nTail++;
		}
	

}


int main()
{
	Setup();
	while (!gameOver) {
		Draw();
		Input();
		Logic();
		std::this_thread::sleep_for(std::chrono::milliseconds(55));
	}
    return 0;
}


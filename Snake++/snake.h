#pragma once
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>
#include <Windows.h>
#include <conio.h>

#define width 20
#define height 10

// init vars
bool gameOver;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int tailLen;
enum eDir { STOP = 0, UP, LEFT, DOWN, RIGHT };
eDir dir;

std::string direction() {
	switch (dir) {
	case STOP:
		return "STOP";
		break;
	case UP:
		return "UP";
		break;
	case LEFT:
		return "LEFT";
		break;
	case DOWN:
		return "DOWN";
		break;
	case RIGHT:
		return "RIGHT";
		break;
	}
}

void setCol(int col) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), col);
}

void setup() {
	srand(time(0));
	gameOver = false;
	dir = STOP;
	x = width / 2; y = height / 2;
	fruitX = rand() % width; fruitY = rand() % height;
	::score = 0;
}

void draw() {
	system("cls"); // system("clear");
	for (int i = 0; i < width + 2; i++) std::cout << "\xB2";
	std::cout << "\n";

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0) std::cout << "\xDB";
			if (i == y && j == x) {
				setCol(2);
				std::cout << "O";
				setCol(7);
			}
			else if (i == fruitY && j == fruitX) {
				setCol(4);
				std::cout << "\xA2";
				setCol(7);
			}
			else {
				bool isTail = false;
				for (int k = 0; k < tailLen; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						setCol(2);
						std::cout << "o";
						setCol(7);
						isTail = true;
					}
				}
				if (!isTail) std::cout << " ";
			}
			if (j == width - 1) std::cout << "\xDB";
		}
		std::cout << "\n";
	}

	for (int i = 0; i < width + 2; i++) std::cout << "\xB2";
	std::cout << "\n";
	std::cout << "Score: " << score << "\n\n";
	std::cout << "X: " << x << " Y: " << y;
	std::cout << "\nFruit X: " << fruitX << " Fruit Y: " << fruitY;
	std::cout << "\nDirection: " << direction();
}

void input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'w':
			dir = UP;
			break;
		case 'a':
			dir = LEFT;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'x':
			std::exit(0);
			break;
		}
	}
}

void logic() {
	int prevX = tailX[0]; int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < tailLen; i++) {
		prev2X = tailX[i]; prev2Y = tailY[i];
		tailX[i] = prevX; tailY[i] = prevY;
		prevX = prev2X; prevY = prev2Y;
	}
	switch (dir) {
	case UP:
		y--;
		break;
	case LEFT:
		x--;
		break;
	case DOWN:
		y++;
		break;
	case RIGHT:
		x++;
		break;
	default:
		break;
	}

	// if (x > width || x < 0 || y > height || y < 0) gameOver = true;
	if (x >= width) x = 0; else if (x < 0) x = width - 1;
	if (y >= height) y = 0; else if (y < 0) y = height - 1;

	for (int i = 0; i < tailLen; i++) if (tailX[i] == x && tailY[i] == y) gameOver = true;

	if (x == fruitX && y == fruitY) {
		srand(time(0));
		score += 10;
		fruitX = rand() % width; fruitY = rand() % height;
		tailLen++;
	}
}
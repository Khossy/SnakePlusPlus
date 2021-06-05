#include <iostream>
#include <Windows.h> // #include <unistd.h>
#include "resource.h"
#include "snake.h"

int main() {
	SetConsoleTitleA("Snake++ (Developer Edition)");

	setup();
	while (!gameOver) {
		draw();
		input();
		logic();
		Sleep(60); // sleep(100);
	}
	return 0;
}
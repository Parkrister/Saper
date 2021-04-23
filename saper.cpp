// saper.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <Windows.h>

HANDLE nConsole = GetStdHandle(STD_OUTPUT_HANDLE);
COORD coord;

using std::cout;
using std::cin;

//color 1
#define grey 8
#define red 4
#define white 7
#define black 0

// color 2
#define blue 1
#define green 2
#define sh_blue 3
#define viol 5
#define orange 6
#define cyan 11
#define pink 12
#define dark_viol 12

// simbol
#define bomb_simbol 253
#define flag_simbol 63
#define clear_simbol 254
#define cell_simbol 219

// SETUP
#define bomb 160
const unsigned int m = 13;

unsigned short step = 0;

unsigned int mas[m][m];
unsigned int mark[m][m]; // mark for open()

unsigned short color = white;


int set_color(int c) {
	switch (c) {
	case 1:
		return white;
		break;
	case 2:
		return green;
		break;
	case 3:
		return sh_blue;
		break;
	case 4:
		return viol;
		break;
	case 5:
		return cyan;
		break;
	case 6:
		return pink;
		break;
	case 7:
		return dark_viol;
		break;
	case 8:
		return orange;
		break;
	}
}

// add_bomb v2.0
//void add_bomb(short x, short y) {
//	for (int i = -1; i <= 1; i++) {
//		for (int j = -1; j <= 1; j++) {
//			if ((x + i >= 0) && (x + i < m) && (y + i >= 0) && (y + i < m)) {
//				mas[x + i][y + j]++;
//			}
//		}
//	}
//}

/// add_bomb() v1.0
void add_bomb(short x, short y) {
	if ((x - 1 >= 0) && (x - 1 < m) && (y - 1 >= 0) && (y - 1 < m)) {
		mas[x - 1][y - 1]++;
	}
	if ((x >= 0) && (x < m) && (y - 1 >= 0) && (y - 1 < m)) {
		mas[x][y - 1]++;
	}
	if ((x + 1 >= 0) && (x + 1 < m) && (y - 1 >= 0) && (y - 1 < m)) {
		mas[x + 1][y - 1]++;
	}
	if ((x - 1 >= 0) && (x - 1 < m) && (y >= 0) && (y < m)) {
		mas[x - 1][y]++;
	}
	if ((x + 1 >= 0) && (x + 1 < m) && (y >= 0) && (y < m)) {
		mas[x + 1][y]++;
	}
	if ((x - 1 >= 0) && (x - 1 < m) && (y + 1 >= 0) && (y + 1 < m)) {
		mas[x - 1][y + 1]++;
	}
	if ((x >= 0) && (x < m) && (y + 1 >= 0) && (y + 1 < m)) {
		mas[x][y + 1]++;
	}
	if ((x + 1 >= 0) && (x + 1 < m) && (y + 1 >= 0) && (y + 1 < m)) {
		mas[x + 1][y + 1]++;
	}
	return;
}
///

///
bool open(short x, short y) {
	Sleep(10);

	if (mark[x][y] > 0) {
		step++;
	}
	mark[x][y] *= 0;

	coord = { m + 5, 2 };
	SetConsoleCursorPosition(nConsole, coord);
	printf("step == %d", step);

	coord = { y, x };
	SetConsoleCursorPosition(nConsole, coord);
	if (mas[x][y] > 8) {
		color = red;
		SetConsoleTextAttribute(nConsole, red);
		printf("%c", bomb_simbol);
		SetConsoleTextAttribute(nConsole, white);
		return false;
	}

	if (step >= (m * m - bomb)) {
		SetConsoleTextAttribute(nConsole, set_color(mas[x][y]));
		printf("%d", mas[x][y]);
		SetConsoleTextAttribute(nConsole, white);
		color = cyan;
		return false;
	}

	if (mas[x][y] == 0) {
		printf("%c", '.');

		//for (int i = -1; i <= 1; i++) {
		//	for (int j = -1; j <= 1; j++) {
		//		if (mark[y + i][x + i] > 0) {
		//			if ((y + i >= 0) && (y + i < m) && (x + i >= 0) && (x + i < m)) {
		//				open(y + i, x + i);
		//			}
		//		}
		//	}
		//}

		if ((mark[x - 1][y - 1] > 0) && ((x - 1 >= 0) && (x - 1 < m) && (y - 1 >= 0) && (y - 1 < m))) {
			open(x - 1, y - 1);
		}
		if ((mark[x][y - 1] > 0) && ((x >= 0) && (x < m) && (y - 1 >= 0) && (y - 1 < m))) {
			open(x, y - 1);
		}
		if ((mark[x + 1][y - 1] > 0) && ((x + 1 >= 0) && (x + 1 < m) && (y - 1 >= 0) && (y - 1 < m))) {
			open(x + 1, y - 1);
		}
		if ((mark[x - 1][y] > 0) && ((x - 1 >= 0) && (x - 1 < m) && (y >= 0) && (y < m))) {
			open(x - 1, y);
		}
		if ((mark[x + 1][y] > 0) && ((x + 1 >= 0) && (x + 1 < m) && (y >= 0) && (y < m))) {
			open(x + 1, y);
		}
		if ((mark[x - 1][y + 1] > 0) && ((x - 1 >= 0) && (x - 1 < m) && (y + 1 >= 0) && (y + 1 < m))) {
			open(x - 1, y + 1);
		}
		if ((mark[x][y + 1] > 0) && ((x >= 0) && (x < m) && (y + 1 >= 0) && (y + 1 < m))) {
			open(x, y + 1);
		}
		if ((mark[x + 1][y + 1] > 0) && ((x + 1 >= 0) && (x + 1 < m) && (y + 1 >= 0) && (y + 1 < m))) {
			open(x + 1, y + 1);
		}
		return true;
	}

	if (mas[x][y] < 9) {
		SetConsoleTextAttribute(nConsole, set_color(mas[x][y]));
		printf("%d", mas[x][y]);
		SetConsoleTextAttribute(nConsole, white);
		return true;
	}
}
///


int main() //////////// MAIN
{
	long ltime = time(0);
	int stime = (unsigned int)ltime / 2;
	srand(stime);
	short int x = 0, y = 0;
	short xb, yb;

	coord = { m + 5, 0 };
	SetConsoleCursorPosition(nConsole, coord);
	printf("need step == %i", (m * m - bomb));
	// fill mas[][]
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			mas[i][j] = 0;
		}
	}

	coord = { m + 5, 4 };
	SetConsoleCursorPosition(nConsole, coord);
	printf("| Enter x > %d for exit", m);
	coord = { m + 5, 5 };
	SetConsoleCursorPosition(nConsole, coord);
	printf("| Enter x = -1 for flag");

	// marks[][] for open()
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			mark[i][j] = 1;
		}
	}

	// fill cels
	coord = { 0, 0 };
	SetConsoleCursorPosition(nConsole, coord);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			SetConsoleTextAttribute(nConsole, white);
			printf("%c", cell_simbol);
		}
		putchar('\n');
	}
	SetConsoleTextAttribute(nConsole, white);

	// set bombs
	for (int i = 0; i < bomb; i++) {
		do {
			xb = rand() % m;
			yb = rand() % m;
		} while (mas[xb][yb] > 8);

		mas[xb][yb] = 9;
		add_bomb(xb, yb);
	}


	//// GAME
	do {
		SetConsoleTextAttribute(nConsole, white);
		coord = { m + 7, 11 };
		SetConsoleCursorPosition(nConsole, coord);
		printf("                               ");

		coord = { m + 7, 11 };
		SetConsoleCursorPosition(nConsole, coord);
		if (y < 0) { // flag
			printf("Set flag: ");
			do {
				cin >> x >> y;
			} while ((x < 0) && (y < 0));
			coord = { x, y };
			SetConsoleCursorPosition(nConsole, coord);
			SetConsoleTextAttribute(nConsole, grey);
			putchar(flag_simbol);
			SetConsoleTextAttribute(nConsole, white);
			y = 0;
			continue;
		}

		if (step == (m * m - bomb)) {
			color = cyan;
			break;
		}
		
		printf("Enter x, y: ");
		cin >> y;
		if (y < 0) {
			continue;
		}
		else {
			if (y > m) {
				break;
			}
		}
		cin >> x;
		if (!((x < m) && open(x, y) && (y < m))) {
			break;
		}
	} while (1);
	///

	coord = { m + 5, 7 };
	SetConsoleCursorPosition(nConsole, coord);
	puts("-------------------");
	if (color == cyan) {
		for (short i = 0; i < m; i++) {
			for (short j = 0; j < m; j++) {
				if (mas[i][j] > 8) {
					coord = { j, i };
					SetConsoleCursorPosition(nConsole, coord);
					SetConsoleTextAttribute(nConsole, color);
					printf("%c", bomb_simbol);
				}
			}
		}
		coord = { m + 5, 8 };
		SetConsoleCursorPosition(nConsole, coord);
		SetConsoleTextAttribute(nConsole, color);
		printf("\t     W I N ");
	}
	else {
		for (short i = 0; i < m; i++) {
			for (short j = 0; j < m; j++) {
				if (mas[i][j] > 8) {
					coord = { j, i };
					SetConsoleCursorPosition(nConsole, coord);
					SetConsoleTextAttribute(nConsole, color);
					printf("%c", bomb_simbol);
				}
			}
		}
		coord = { m + 5, 8 };
		SetConsoleCursorPosition(nConsole, coord);
		SetConsoleTextAttribute(nConsole, color);
		printf("      L O S E ");
	}
	SetConsoleTextAttribute(nConsole, white);
	coord = { m + 5, 9 };
	SetConsoleCursorPosition(nConsole, coord);
	puts("-------------------");

	coord = { 0, m + 1 };
	SetConsoleCursorPosition(nConsole, coord);

	return 0;
}
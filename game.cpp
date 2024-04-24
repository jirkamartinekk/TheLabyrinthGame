#define _CRT_SECURE_NO_WARNINGS 1
#include <string.h>
#include <iostream>
#include <conio.h>

#define MAX 8

int poziceX = 0;
int poziceY = 0;
int zivoty = 3;
char hraciPole [MAX][MAX];

void nactiHraciPole() {
	int sloupec, radek;
	for (radek = 0; radek < MAX; radek++)
		for (sloupec = 0; sloupec < MAX; sloupec++)
			hraciPole[radek][sloupec] = ' ';
	hraciPole[1][1] = '#';
	return;
}

void vypisSachovnici(void) {

	int sloupec;
	int radek;

	system("cls"); //systemovy prikaz clear screen

	printf("Pouzij klavesy W,A,S,D pro pohyb:");
	printf("\nStiskni klavesu Q pro ukonceni: ");
	printf("\n");
	printf("------------------------------");
	printf("\nZivoty: %d", zivoty);
	printf("\n");
	printf("------------------------------\n");

	for (radek = 0; radek < MAX; radek++) {
		for (sloupec = 0; sloupec < MAX; sloupec++) {
			printf("+-");
		}
		printf("+");
		printf("\n");
		for (sloupec = 0; sloupec < MAX; sloupec++) {

			if (sloupec == poziceX && radek == poziceY) {
				printf("|X");
			}
			else if (sloupec == (MAX - 1) && radek == (MAX - 1))
				printf("|#");
			else if ()
				printf("|%c", hraciPole[radek][sloupec]);
			else {
				printf("| ");
			}

		}
		printf("|\n");
	}
	for (sloupec = 0; sloupec < MAX; sloupec++) {
		printf("+-");
	}
	printf("+");

	printf("\n");

	return;
}


int main()
{
	char znak = 'f';

	nactiHraciPole();
	vypisSachovnici();

	do {
		if (_kbhit() != 0) {
			znak = _getch();
			if (znak == 224) znak = _getch();
			switch (znak) {
			case 75:
			case 'a': if (poziceX > 0) poziceX--;
						else zivoty--;
				break;
			case 77:
			case 'd': if (poziceX < (MAX - 1)) poziceX++;
						else zivoty--;
				break;
			case 72:
			case 'w': if (poziceY > 0) poziceY--;
						else zivoty--;
				break;
			case 80:
			case 's': if (poziceY < (MAX - 1))poziceY++;
						else zivoty--;
				break;
			}

			vypisSachovnici();
		}

	} while (znak != 'q' && !(poziceX == (MAX - 1) && (poziceY == MAX - 1)) && !zivoty == 0);
	if (poziceX == (MAX - 1) && (poziceY == MAX - 1)) printf("Gratuluji, kavalire! Mas u me svacinu...");
	else printf("Chcipl jsi na zivoty nebo jsi to leavnul, srabe!");

	return 0;
}
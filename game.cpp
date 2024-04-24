#define _CRT_SECURE_NO_WARNINGS 1
#include <string.h>
#include <iostream>
#include <conio.h>

#define MAX 8

int poziceX = 0;
int poziceY = 0;

void vypisSachovnici(void) {

	int sloupec;
	int radek;

	system("cls"); //systemovy prikaz clear screen

	printf("Pouzij klavesy W,A,S,D pro pohyb:");
	printf("\nStiskni klavesu Q pro ukonceni: ");
	printf("\n");

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
	char znak = 'f'; //musim zvolit random pismeno

	vypisSachovnici();

	do {
		if (_kbhit() != 0) { //kontroluje, zda je zmacknuta klavesa
			znak = _getch(); //vylepseny getchar; dokaze cist vstup z vice zarizeni
			switch (znak) {
			case 'a': if(poziceX > 0) poziceX--;
				break;
			case 'd': if(poziceX < (MAX-1)) poziceX++;
				break;
			case 'w': if(poziceY > 0) poziceY--;
				break;
			case 's': if(poziceY < (MAX -1))poziceY++;
				break;
			}
			vypisSachovnici(); //na konci cyklu musim znovu vypsat sachovnici
		}

	} while (znak != 'q');


	return 0;
}
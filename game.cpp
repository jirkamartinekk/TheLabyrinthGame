#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string.h>
#include <conio.h>

#define MAX 8

int poziceX = 0;
int poziceY = 0;
int zivoty = 3;
char hraciPole[MAX][MAX];

void nactiHraciPole() {

	int sloupec, radek;

	for (radek = 0; radek < MAX; radek++){

		for (sloupec = 0; sloupec < MAX; sloupec++)
			hraciPole[radek][sloupec] = ' ';

	}
	hraciPole[1][1] = '#';

	return;
}

int nactiHraciPoleZeSouboru() {

	int sloupec, radek, znak;

	FILE* soubor;
	if (soubor = fopen("H:\\Seminář\\Cčko\\24.01.2024\\sachovniceSeCtenimZeSouboru\\sachovnice\\maps\\02.txt", "r")) {

		for (radek = 0; radek < MAX; radek++) {

			for (sloupec = 0; sloupec < MAX; sloupec++) {

				hraciPole[radek][sloupec] = getc(soubor);

			}
			while ((znak = getc(soubor)) != '\n' && znak != EOF); //vse, co je navic (z importovaneho souboru) pošle do faka //pokud ma stale co importovat a nezjistil enter nebo neni konec souboru, pokracuje dal
		}

		fclose(soubor);

		return 1;
	}
	else printf("Nastala chyba pri nacitani souboru!");

	return 0;
}

	void vypisSachovnici() {
		int sloupec, radek;

		system("cls"); //vycisti obrazovku pri dalsim cyklu

		printf("Pouzij klavesy W,A,S,D,Q,E,Z,C pro pohyb:");
		printf("\n");
		printf("Stiskni klavesu L pro ukonceni:");
		printf("\n");
		printf("----------------------------------------------");
		printf("\nZivoty: %d", zivoty);
		printf("\n");
		printf("----------------------------------------------\n");

		for (radek = 0; radek < MAX; radek++) {
			for (sloupec = 0; sloupec < MAX; sloupec++)
				printf("+-");
			printf("+\n");
			for (sloupec = 0; sloupec < MAX; sloupec++)
				if (sloupec == poziceX && radek == poziceY)
					printf("|*");
				else if (sloupec == MAX - 1 && radek == MAX - 1)
					printf("|C");
				else
					printf("|%c", hraciPole[radek][sloupec]);
			printf("|\n");
		}
		for (sloupec = 0; sloupec < MAX; sloupec++)
			printf("+-");
		printf("+\n");
		return;
	}


int main()
{
	char znak = 'm';

	if (!nactiHraciPoleZeSouboru()) {
		printf("Soubor se nepodarilo otevrit!");
		return 0;
	}

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
			case 'q':
				if (poziceX > 0 && poziceY > 0) poziceX--, poziceY--;
				else zivoty--;
				break;
			case 'e':
				if (poziceX < (MAX - 1) && poziceY > 0) poziceX++, poziceY--;
				else zivoty--;
				break;
			case 'z':
				if (poziceX > 0 && poziceY < (MAX - 1)) poziceX--, poziceY++;
				else zivoty--;
				break;
			case 'c':
				if (poziceX < (MAX - 1) && poziceY < (MAX - 1)) poziceX++, poziceY++;
				else zivoty--;
				break;

			}
			vypisSachovnici();
		}

	} while (znak != 'l' && !(poziceX == (MAX - 1) && (poziceY == MAX - 1)) && !zivoty == 0);
	if (poziceX == (MAX - 1) && (poziceY == MAX - 1)) {
		printf("----------------------------------------------\n");
		printf("Gratuluji, kavalire! Mas u me svacinu...\n");
		printf("----------------------------------------------\n");
	}
	else{
		printf("------------------------------\n");
		printf("Chcipl jsi na zivoty nebo jsi to leavnul, srabe!\n");
		printf("------------------------------\n");
	}
	return 0;
}
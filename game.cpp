#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string.h>
#include <conio.h>
#include <time.h> //knihovna casu

#define MAX 8
#define CASKONCE 20 

int poziceX = 0;
int poziceY = 0;
int zivoty = 3;
char hraciPole[MAX][MAX];
unsigned long cas, casAktualni, casSpusteniHry; //unsigned =velke cele cislo; long = ma dvounasobnou velikost bytu
	//cas v pocitaci se pocita od 1.1.1970 00:00:00
void nactiHraciPole() {

	int sloupec, radek;

	for (radek = 0; radek < MAX; radek++) {

		for (sloupec = 0; sloupec < MAX; sloupec++)
			hraciPole[radek][sloupec] = ' ';

	}
	hraciPole[1][1] = '#';

	return;
}

int nactiHraciPoleZeSouboru() {

	int sloupec, radek, znak;

	FILE* soubor;
	if (soubor = fopen("H:\\Seminář\\Cčko\\31.01.2024\\sachovnice4.0\\maps\\01.txt", "r")) {

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
	cas = time(0);
	printf("----------------------------------------------");
	printf("\nZivoty: %d", zivoty);
	printf("                             ");
	printf("Cas: %u", CASKONCE - (casAktualni - casSpusteniHry)); //%u for unsigned
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

	casSpusteniHry = time(0); //ulozeni casu startu

	vypisSachovnici();

	do {
		if (_kbhit() != 0) {
			znak = _getch();
			if (znak == 224) znak = _getch();
			switch (znak) {
			case 75:
			case 'a': if (poziceX > 0 && (hraciPole[poziceY][poziceX-1] != '&')) poziceX--;
					else zivoty--;
				break;
			case 77:
			case 'd': if (poziceX < (MAX - 1) && (hraciPole[poziceY][poziceX+1] != '&')) poziceX++;
					else zivoty--;
				break;
			case 72:
			case 'w': if (poziceY > 0 && (hraciPole[poziceY-1][poziceX] != '&')) poziceY--;
					else zivoty--;
				break;
			case 80:
			case 's': if (poziceY < (MAX - 1) && (hraciPole[poziceY+1][poziceX] != '&'))poziceY++;
					else zivoty--;
				break;
			//diagonalni pohyb
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
		casAktualni = time(0);
		if ((casAktualni - cas) > 0)
		{
			vypisSachovnici();
		}

	} while (znak != 'l' && !(poziceX == (MAX - 1) && (poziceY == MAX - 1)) && !zivoty == 0 && (CASKONCE-(casAktualni-casSpusteniHry)));
	if (poziceX == (MAX - 1) && (poziceY == MAX - 1)) {
		printf("----------------------------------------------\n");
		printf("Gratuluji, kavalire! Mas u me svacinu...\n");
		printf("----------------------------------------------\n");
	}
	else {
		printf("------------------------------\n");
		printf("Chcipl jsi na zivoty nebo jsi to leavnul, srabe!\n");
		printf("------------------------------\n");
	}
	return 0;
}
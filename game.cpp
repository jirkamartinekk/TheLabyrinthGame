#define _CRT_SECURE_NO_WARNINGS 1
#include <string.h>
#include <iostream>

#define MAX 8 //lze definovat promennou, kterou lze pozdeji uzit v kodu

int poziceX = 4;
int poziceY = 6;

void vypisSachovnici(void) { 

	int sloupec;
	int radek;

	for (radek = 0; radek < MAX; radek++) { //uziti MAX
		for (sloupec = 0; sloupec < MAX; sloupec++) {
			printf("+-");
		}
		printf("+");
		printf("\n");
		for (sloupec = 0; sloupec < MAX; sloupec++) {

			if (sloupec == poziceX && radek == poziceY) {
				printf("|*");
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

	return;
}


int main()
{

	vypisSachovnici();

	return 0;
}
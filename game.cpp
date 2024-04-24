#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <windows.h>
#include <string.h>
#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <time.h>

#define MAX 8
#define CASKONCE 25

int poziceX = 0;
int poziceY = 0;
int zivoty = 3;
int menuActive;
int mapSettings = 1;
char znak = 'm';
char hraciPole[MAX][MAX];
unsigned long cas, casAktualni, casSpusteniHry;

void nactiHraciPole()
{

    int sloupec, radek;

    for (radek = 0; radek < MAX; radek++)
    {

        for (sloupec = 0; sloupec < MAX; sloupec++)
            hraciPole[radek][sloupec] = ' ';
    }
    hraciPole[1][1] = '#';

    return;
}

void setTextColor(int colorCode)
{ // barvicky - https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
    fprintf(stdout, "\033[1;%dm", colorCode);
}

void vypisSachovnici()
{
    int sloupec, radek;

    system("cls");

    printf("Pouzij klavesy W,A,S,D pro pohyb:");
    printf("\n");
    printf("Stiskni ESC pro ukonceni:");
    printf("\n");
    cas = time(0);
    printf("----------------------------------------------");
    printf("\nZivoty: %d", zivoty);
    printf("                             ");
    printf("Cas: %u", CASKONCE - (casAktualni - casSpusteniHry));
    printf("\n");
    printf("----------------------------------------------\n");

    // debug
    setTextColor(41);
    printf("Debug: ");
    printf("Y: %d", poziceY);
    printf(" | ");
    printf("X: %d", poziceX);
    printf(" | ");
    if (poziceY == 3 && poziceX == 5 || poziceY == 6 && poziceX == 1)
    {
        printf("TP in use");
    }
    printf("\n");
    //
    setTextColor(40);

    for (radek = 0; radek < MAX; radek++)
    {
        for (sloupec = 0; sloupec < MAX; sloupec++)
        {
            setTextColor(37); // bílá
            printf("+-");
        }
        setTextColor(37);
        printf("+\n");
        for (sloupec = 0; sloupec < MAX; sloupec++)
            if (sloupec == poziceX && radek == poziceY)
            {
                setTextColor(37);
                printf("|");
                setTextColor(31); // červená
                printf("*");
            }
            else if (sloupec == MAX - 1 && radek == MAX - 1)
            {
                setTextColor(37);
                printf("|");
                setTextColor(34); // modrá
                printf("E");
            }
            else if (sloupec == MAX - 3 && radek == MAX - 5)
            {
                setTextColor(37);
                printf("|");
                setTextColor(32); // zelená
                printf("T");
            }
            else if (sloupec == MAX - 7 && radek == MAX - 2)
            {
                setTextColor(37);
                printf("|");
                setTextColor(32);
                printf("T");
            }
            else
            {
                setTextColor(37);
                printf("|%c", hraciPole[radek][sloupec]);
            }
        setTextColor(37);
        printf("|\n");
    }
    for (sloupec = 0; sloupec < MAX; sloupec++)
    {
        setTextColor(37);
        printf("+-");
    }

    setTextColor(37);
    printf("+\n");

    return;
}

void teleport()
{
    if (poziceY == 3 && poziceX == 5)
    {
        poziceY = 6;
        poziceX = 1;
    }
    else if (poziceY == 6 && poziceX == 1)
    {
        poziceY = 3;
        poziceX = 5;
    }

    return;
}

bool menuCheck()
{

    znak = _getch();

    if (znak == 's')
    {
        menuActive = 1;
    }
    else if (znak == 'p')
    {
        menuActive = 2;
    }
    else if (znak == 'n')
    {
        menuActive = 3;
    }
    else if (znak == 'b')
    {
        menuActive = 0;
        return true;
    }
    else
    {
        menuActive = 0;
    }

    return false;
}

int nactiHraciPoleZeSouboru()
{

    int sloupec, radek, znak;

    FILE* soubor;
    if (mapSettings == 1) {
        if (soubor = fopen("maps\\01.txt", "r"))
        {

            for (radek = 0; radek < MAX; radek++)
            {

                for (sloupec = 0; sloupec < MAX; sloupec++)
                {

                    hraciPole[radek][sloupec] = getc(soubor);
                }
                while ((znak = getc(soubor)) != '\n' && znak != EOF)
                    ;
            }

            fclose(soubor);

            return 1;
        }
        else
            printf("Nastala chyba pri nacitani souboru!\n");
    }
    else {
        if (soubor = fopen("maps\\02.txt", "r"))
        {

            for (radek = 0; radek < MAX; radek++)
            {

                for (sloupec = 0; sloupec < MAX; sloupec++)
                {

                    hraciPole[radek][sloupec] = getc(soubor);
                }
                while ((znak = getc(soubor)) != '\n' && znak != EOF)
                    ;
            }

            fclose(soubor);

            return 1;
        }
        else
            printf("Nastala chyba pri nacitani souboru!\n");
    }

    return 0;
}

int main()
{
    do
    {
        system("cls");

        setTextColor(37);
        std::cout << " _______ _             _____            _                      _             _____     \n"
            "|__   __| |           / ____|          | |                    (_)           / ____|    \n"
            "   | |  | |__   ___  | (___   __ _  ___| |__   _____   ___ __  _  ___ ___  | |  __  __ _ _ __ ___   ___ \n"
            "   | |  | '_ \\ / _ \\  \\___ \\ / _` |/ __| '_ \\ / _ \\ \\ / / '_ \\| |/ __/ _ \\ | | |_ |/ _` | '_ ` _ \\ / _ \\\n"
            "   | |  | | | |  __/  ____) | (_| | (__| | | | (_) \\ V /| | | | | (_|  __/ | |__| | (_| | | | | | |  __/\n"
            "   |_|  |_| |_|\\___| |_____/ \\__,_|\\___|_| |_|\\___/ \\_/ |_| |_|_|\\___\\___|  \\_____|\\__,_|_| |_| |_|\\___|\n";
        printf("version: 4.2.0\n");
        printf("\n\n");
        printf("Pro spusteni hry stiskni klavesu");
        printf(" ");
        setTextColor(36);
        printf("S");
        setTextColor(37);
        printf("!\n");
        printf("Pro prechod do nastaveni stiskni klavesu");
        printf(" ");
        setTextColor(36);
        printf("N");
        setTextColor(37);
        printf("!\n");
        printf("Pro prechod k pravidlum stiskni klavesu");
        printf(" ");
        setTextColor(36);
        printf("P");
        setTextColor(37);
        printf("!\n");
        printf("Pro ukonceni stiskni klavesu");
        printf(" ");
        setTextColor(36);
        printf("ESC");
        setTextColor(37);
        printf("!\n");

        menuCheck();

        if (menuActive == 1)
        {
            if (!nactiHraciPoleZeSouboru())
            {
                printf("Soubor se nepodarilo otevrit!\n");
                return 0;
            }

            casSpusteniHry = time(0);

            vypisSachovnici();

            do
            {
                if (_kbhit() != 0)
                {
                    znak = _getch();
                    if (znak == 224)
                        znak = _getch();
                    switch (znak)
                    {
                    case 75:
                    case 'a':
                        if (poziceX > 0 && (hraciPole[poziceY][poziceX - 1] != 'X'))
                            poziceX--;
                        else
                            zivoty--;
                        break;
                    case 77:
                    case 'd':
                        if (poziceX < (MAX - 1) && (hraciPole[poziceY][poziceX + 1] != 'X'))
                            poziceX++;
                        else
                            zivoty--;
                        break;
                    case 72:
                    case 'w':
                        if (poziceY > 0 && (hraciPole[poziceY - 1][poziceX] != 'X'))
                            poziceY--;
                        else
                            zivoty--;
                        break;
                    case 80:
                    case 's':
                        if (poziceY < (MAX - 1) && (hraciPole[poziceY + 1][poziceX] != 'X'))
                            poziceY++;
                        else
                            zivoty--;
                        break;
                    }

                    teleport();
                    vypisSachovnici();
                }

                casAktualni = time(0);
                if ((casAktualni - cas) > 0)
                {
                    vypisSachovnici();
                }

            } while (znak != 27 && !(poziceX == (MAX - 1) && (poziceY == MAX - 1)) && !zivoty == 0 && (CASKONCE - (casAktualni - casSpusteniHry)));

            if (poziceX == (MAX - 1) && (poziceY == MAX - 1))
            {
                setTextColor(33);
                printf("----------------------------------------------\n");
                printf("Gratuluji ti, kavalire! Mas u me svacinu!\n");
                printf("----------------------------------------------\n");
                setTextColor(37);
                exit(0);
            }
            else if (znak == 27)
            {
                setTextColor(33);
                printf("----------------------------------------------\n");
                printf("Ukoncil jsi hru, srabe!\n");
                printf("----------------------------------------------\n");
                setTextColor(37);
                exit(0);
            }
            else if ((casAktualni - casSpusteniHry) == CASKONCE)
            {
                setTextColor(33);
                printf("----------------------------------------------\n");
                printf("Vyprsel ti cas!\n");
                printf("----------------------------------------------\n");
                setTextColor(37);
                exit(0);
            }
            else
            {
                setTextColor(33);
                printf("----------------------------------------------\n");
                printf("Umrel jsi :(\n");
                printf("----------------------------------------------\n");
                setTextColor(37);
                exit(0);
            }
        }
        else if (menuActive == 2)
        {
            system("cls");
            setTextColor(37);
            printf("----------------------------------------------\n");
            printf("PRAVIDLA\n");
            printf("----------------------------------------------\n");
            printf("1.Na dokonceni hry mas pouze %d sekund.\n", CASKONCE);
            printf("2.Behem pohybu po mape se nesmis dotykat X. Pri dotyku ti bude odebran -1 zivot.\n");
            printf("3.Muzes pouzit teleport (T). Ten te presune na dalsi policko T.\n");
            printf("4. Pro dokonceni hry se musis dostat na konecne policko (E).\n");
            printf("\n\n");
            printf("Pro prejiti zpet do hlavniho menu stiskni klavesu");
            printf(" ");
            setTextColor(36);
            printf("B");
            setTextColor(37);
            printf("!\n");

            if (menuCheck())
            {
                continue;
            }
        }
        else if (menuActive == 3)
        {
            system("cls");
            do {
                system("cls");

                setTextColor(37);
                printf("----------------------------------------------\n");
                printf("NASTAVENI\n");
                printf("----------------------------------------------\n");
                printf("Vyber mapu: ");
                printf("<%d>", mapSettings);
                printf("\n");
                printf("\n\n");
                printf("Pro prejiti zpet do hlavniho menu stiskni 2x klavesu");
                printf(" ");
                setTextColor(36);
                printf("B");
                setTextColor(37);
                printf("!\n");
                znak = _getch();
                if (znak == 77) {
                    mapSettings = 2;
                }
                else if (znak == 75) {
                    mapSettings = 1;
                }
            } while (znak != 'b' && znak != 'B');

            if (menuCheck())
            {
                continue;
            }
        }

    } while (znak != 27);

    return 0;
}
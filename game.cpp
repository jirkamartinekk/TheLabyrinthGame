#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <windows.h>
#include <string.h>
#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <time.h>

#define MAX 8

int poziceX = 0;
int poziceY = 0;
int zivoty = 3;
int menuActive;
int positionOfEndX;
int positionOfEndY;
int mapSettings = 1;
int settingsRadek = 1;
int CASKONCE = 25;
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

    printf("Pouzij klavesy ");
    setTextColor(36);
    printf("W");
    setTextColor(37);
    printf(", ");
    setTextColor(36);
    printf("A");
    setTextColor(37);
    printf(", ");
    setTextColor(36);
    printf("S");
    setTextColor(37);
    printf(", ");
    setTextColor(36);
    printf("D");
    setTextColor(37);
    printf(" pro pohyb:");
    printf("\n");
    printf("Stiskni ");
    setTextColor(36);
    printf("ESC");
    setTextColor(37);
    printf(" pro ukonceni:");
    printf("\n");
    cas = time(0);
    printf("----------------------------------------------");
    printf("\nZivoty: %d", zivoty);
    printf("                          ");
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
    if (poziceY == 3 && poziceX == 5 || poziceY == 6 && poziceX == 1 || poziceY == 7 && poziceX == 0 || poziceY == 1 && poziceX == 7)
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
            setTextColor(37);
            printf("+-");
        }
        setTextColor(37);
        printf("+\n");
        for (sloupec = 0; sloupec < MAX; sloupec++)
            if (mapSettings == 1)
            {
                if (sloupec == poziceX && radek == poziceY)
                {
                    setTextColor(37);
                    printf("|");
                    setTextColor(31);
                    printf("*");
                }
                else if (sloupec == MAX - 1 && radek == MAX - 1)
                {
                    setTextColor(37);
                    printf("|");
                    setTextColor(34);
                    printf("E");
                }
                else if (sloupec == MAX - 3 && radek == MAX - 5)
                {
                    setTextColor(37);
                    printf("|");
                    setTextColor(32);
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
            }
            else if (mapSettings == 2)
            {
                if (sloupec == poziceX && radek == poziceY)
                {
                    setTextColor(37);
                    printf("|");
                    setTextColor(31);
                    printf("*");
                }
                else if (sloupec == 3 && radek == 4)
                {
                    setTextColor(37);
                    printf("|");
                    setTextColor(34);
                    printf("E");
                }
                else if (sloupec == 7 && radek == 1)
                {
                    setTextColor(37);
                    printf("|");
                    setTextColor(32);
                    printf("T");
                }
                else if (sloupec == 0 && radek == 7)
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
    if (mapSettings == 1)
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
    }
    else if (mapSettings == 2)
    {
        if (poziceY == 1 && poziceX == 7)
        {
            poziceY = 7;
            poziceX = 0;
        }
        else if (poziceY == 7 && poziceX == 0)
        {
            poziceY = 1;
            poziceX = 7;
        }
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

    FILE *soubor;
    if (mapSettings == 1)
    {
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
        {
            printf("\n");
            setTextColor(41);
            printf("Nastala chyba pri nacitani souboru!\n");
            setTextColor(40);
        }
    }
    else
    {
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
        {
            printf("\n");
            setTextColor(41);
            printf("Nastala chyba pri nacitani souboru!\n");
            setTextColor(40);
        }
    }

    return 0;
}

int main()
{
    do
    {
        system("cls");

        setTextColor(35);
        std::cout << " _______ _             _____            _                      _             _____     \n"
                     "|__   __| |           / ____|          | |                    (_)           / ____|    \n"
                     "   | |  | |__   ___  | (___   __ _  ___| |__   _____   ___ __  _  ___ ___  | |  __  __ _ _ __ ___   ___ \n"
                     "   | |  | '_ \\ / _ \\  \\___ \\ / _` |/ __| '_ \\ / _ \\ \\ / / '_ \\| |/ __/ _ \\ | | |_ |/ _` | '_ ` _ \\ / _ \\\n"
                     "   | |  | | | |  __/  ____) | (_| | (__| | | | (_) \\ V /| | | | | (_|  __/ | |__| | (_| | | | | | |  __/\n"
                     "   |_|  |_| |_|\\___| |_____/ \\__,_|\\___|_| |_|\\___/ \\_/ |_| |_|_|\\___\\___|  \\_____|\\__,_|_| |_| |_|\\___|\n";
        setTextColor(33);
        printf("version: 4.3.0\n");
        setTextColor(37);
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
                setTextColor(41);
                printf("Soubor se nepodarilo otevrit!\n");
                setTextColor(40);
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

                if (mapSettings == 1)
                {
                    positionOfEndX = 7;
                    positionOfEndY = 7;
                }
                else if (mapSettings == 2)
                {
                    positionOfEndX = 3;
                    positionOfEndY = 4;
                }

            } while (znak != 27 && !((poziceX == positionOfEndX) && (poziceY == positionOfEndY)) && !zivoty == 0 && (CASKONCE - (casAktualni - casSpusteniHry)));

            if (poziceX == positionOfEndX && poziceY == positionOfEndY)
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
            do
            {
                system("cls");

                setTextColor(37);
                printf("----------------------------------------------\n");
                printf("NASTAVENI\n");
                printf("----------------------------------------------\n");
                printf("Vyber mapu: ");
                if (settingsRadek == 1)
                {
                    setTextColor(33);
                }
                printf("<%d>", mapSettings);
                setTextColor(37);
                printf("\n");
                printf("Cas do konce hry: ");
                if (settingsRadek == 2)
                {
                    setTextColor(33);
                }
                printf("<%d>", CASKONCE);
                setTextColor(37);
                printf("\n");
                printf("\n\n");
                printf("Pro prejiti zpet do hlavniho menu stiskni");
                printf(" ");
                setTextColor(36);
                printf("2x");
                setTextColor(37);
                printf(" ");
                printf("klavesu");
                setTextColor(36);
                printf(" ");
                printf("B");
                setTextColor(37);
                printf("!\n");
                znak = _getch();

                if (znak == 80)
                {
                    settingsRadek = 2;
                }
                else if (znak == 72)
                {
                    settingsRadek = 1;
                }

                if (settingsRadek == 1)
                {
                    if (znak == 77)
                    {
                        mapSettings = 2;
                    }
                    else if (znak == 75)
                    {
                        mapSettings = 1;
                    }
                }
                else if (settingsRadek == 2)
                {
                    if (CASKONCE >= 6)
                    {
                        if (znak == 75)
                        {
                            CASKONCE--;
                        }
                    }

                    if (CASKONCE <= 64)
                    {
                        if (znak == 77)
                        {
                            CASKONCE++;
                        }
                    }
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
/*************************************************************************
 *                Zaklady proceduralneho programovania 1                 *
 *                              Projekt                                  *
 *  Autor: Adam Jurcisin                            Termin: 19.11.2021   *
 *************************************************************************/

#include <stdio.h> //vlozenie kniznic
#include <stdlib.h>
#include <string.h>

char meno[100][255]; //globalne premenne
char pohlavie[100][2];
char narodenie[100][5];
char znackaAuta[100][50];
char cas1[100][10];
char cas2[100][10];
char cas3[100][10];
char cas4[100][10];
char cas5[100][10];
int pocetJazdcov;

char zadajZnak()
{
    char znak;
    printf("\nZnaky na vyber: s, d, l, g, b, y, a, u, c, n, r, x\n");
    printf("Zadajte znak:");
    znak = getchar();
    return znak;
}

int nacitanieTabulky()
{
    FILE *tabulka;
    char riadok[100];
    char *token;
    char rozdelovaciZnak[2] = ";";
    pocetJazdcov = 0;

    tabulka = fopen("tabulka.csv", "r");
    if (tabulka == NULL)
    {
        printf("Subor nie je mozne precitat");
        return 0;
    }
    while ((fgets(riadok, 100, tabulka)) != NULL)
    {
        pocetJazdcov++;
        token = strtok(riadok, rozdelovaciZnak);
        strcpy(meno[pocetJazdcov], token);

        token = strtok(NULL, rozdelovaciZnak);
        strcpy(pohlavie[pocetJazdcov], token);

        token = strtok(NULL, rozdelovaciZnak);
        strcpy(narodenie[pocetJazdcov], token);

        token = strtok(NULL, rozdelovaciZnak);
        strcpy(znackaAuta[pocetJazdcov], token);

        token = strtok(NULL, rozdelovaciZnak);
        strcpy(cas1[pocetJazdcov], token);
        token = strtok(NULL, rozdelovaciZnak);
        strcpy(cas2[pocetJazdcov], token);
        token = strtok(NULL, rozdelovaciZnak);
        strcpy(cas3[pocetJazdcov], token);
        token = strtok(NULL, rozdelovaciZnak);
        strcpy(cas4[pocetJazdcov], token);
        token = strtok(NULL, rozdelovaciZnak);
        strcpy(cas5[pocetJazdcov], token);
    }

    fclose(tabulka);
    return 0;
}

int sum()
{
    FILE *tabulka;
    char riadok[200];
    char *token;
    char menosum[100], pohlaviesum[1], narodeniesum[4], automobilsum[20], cassum[30];
    const char rozdelovaciZnak[] = ";";

    tabulka = fopen("tabulka.csv", "r");
    if (tabulka == NULL)
    {
        printf("Subor nie je mozne precitat");
        return 0;
    }

    while (fgets(riadok, 200, tabulka) != NULL)
    {
        token = strtok(riadok, rozdelovaciZnak);
        strcpy(menosum, token);
        printf("%s, ", menosum);
        token = strtok(NULL, rozdelovaciZnak);
        strcpy(pohlaviesum, token);
        token = strtok(NULL, rozdelovaciZnak);
        strcpy(narodeniesum, token);
        printf("nar. %s, ", narodeniesum);
        if (strcmp(pohlaviesum, "m"))
            printf("muz, ");
        else if (strcmp(pohlaviesum, "f"))
            printf("zena, ");
        token = strtok(NULL, rozdelovaciZnak);
        strcpy(automobilsum, token);
        printf("Automobil: %s\n", automobilsum);
        printf("Casy okruhov: ");
        for (int i = 0; i < 4; i++)
        {
            token = strtok(NULL, rozdelovaciZnak);
            strcpy(cassum, token);
            printf("%s;", cassum);
        }
        token = strtok(NULL, rozdelovaciZnak);
        strcpy(cassum, token);
        printf("%s\n", cassum);
    }
    fclose(tabulka);
    return 0;
}

int driver()
{
    nacitanieTabulky();
    char zadanePriezvisko[50] = " ";
    char priezvisko[50];
    char nacitanePriezvisko[10];
    int cisloJazdca = 1;
    char *ret;
    float okruhyJazdca[5], najlepsieKolo, najhorsieKolo, sucetKol = 0, priemerneKolo;

    printf("Zadajte priezvisko jazdca: ");
    scanf("%s", &priezvisko); //Zadam si priezvisko

    //Pridam ku zadanemu priezvisku medzeru pretoze strrchr nam vrati priezvisko s medzerou
    strcat(zadanePriezvisko, priezvisko);

    while (1)
    {
        ret = strrchr(meno[cisloJazdca], ' ');
        strcpy(nacitanePriezvisko, ret);

        if (strcmp(zadanePriezvisko, nacitanePriezvisko) == 0)
        {
            break;
        }
        cisloJazdca++;

        if (cisloJazdca > pocetJazdcov)
        {
            printf("Taketo priezvisko nemame v tabulke.\n\n");
            return 0;
        }
    }

    printf("%s\n", meno[cisloJazdca]);
    printf("nar. %s, ", narodenie[cisloJazdca]);
    if (strcmp(pohlavie[cisloJazdca], "m") == 0)
        printf("muz\n");
    else if (strcmp(pohlavie[cisloJazdca], "f") == 0)
        printf("zena\n");
    printf("Automobil: %s\n\n", znackaAuta[cisloJazdca]);
    printf("Casy okruhov: %s;%s;%s;%s;%s\n", cas1[cisloJazdca], cas2[cisloJazdca], cas3[cisloJazdca], cas4[cisloJazdca], cas5[cisloJazdca]);

    okruhyJazdca[0] = atof(cas1[cisloJazdca]);
    okruhyJazdca[1] = atof(cas2[cisloJazdca]);
    okruhyJazdca[2] = atof(cas3[cisloJazdca]);
    okruhyJazdca[3] = atof(cas4[cisloJazdca]);
    okruhyJazdca[4] = atof(cas5[cisloJazdca]);

    najhorsieKolo = okruhyJazdca[0];
    najlepsieKolo = okruhyJazdca[0];
    for (int x = 0; x < 5; x++)
    {
        if (najhorsieKolo < okruhyJazdca[x])
            najhorsieKolo = okruhyJazdca[x];
        if (najlepsieKolo > okruhyJazdca[x])
            najlepsieKolo = okruhyJazdca[x];
        sucetKol += okruhyJazdca[x];
    }
    priemerneKolo = sucetKol / 5;

    printf("Najlepsie kolo: %.3f\n", najlepsieKolo);
    printf("Najhorsie kolo: %.3f\n", najhorsieKolo);
    printf("Priemerne kolo: %.3f\n\n", priemerneKolo);

    return 0;
}

void lap()
{
    nacitanieTabulky();
    float najlepsieKolo;
    int cisloJazdca, cisloKola;

    najlepsieKolo = atof(cas1[1]);

    for (int i = 1; i <= pocetJazdcov; i++)
    {
        if (atof(cas1[i]) < najlepsieKolo)
        {
            najlepsieKolo = atof(cas1[i]);
            cisloJazdca = i;
            cisloKola = 1;
        }
        if (atof(cas2[i]) < najlepsieKolo)
        {
            najlepsieKolo = atof(cas2[i]);
            cisloJazdca = i;
            cisloKola = 2;
        }
        if (atof(cas3[i]) < najlepsieKolo)
        {
            najlepsieKolo = atof(cas3[i]);
            cisloJazdca = i;
            cisloKola = 3;
        }
        if (atof(cas4[i]) < najlepsieKolo)
        {
            najlepsieKolo = atof(cas4[i]);
            cisloJazdca = i;
            cisloKola = 4;
        }
        if (atof(cas5[i]) < najlepsieKolo)
        {
            najlepsieKolo = atof(cas5[i]);
            cisloJazdca = i;
            cisloKola = 5;
        }
    }
    printf("Najlepsie kolo: %.3f\n", najlepsieKolo);
    printf("Jazdec: %s\n", meno[cisloJazdca]);
    printf("Cislo kola: %d\n\n", cisloKola);
}

int gender()
{
    nacitanieTabulky();
    char zadanePohlavie[2];
    int cisloKola, cisloJazdca;
    float najlepsieKolo = 999;

    while (1)
    {
        printf("Zadajte pohlavie(m alebo f): ");
        scanf("%s", &zadanePohlavie);
        if (strcmp(zadanePohlavie, "m") == 0 || strcmp(zadanePohlavie, "f") == 0)
        {
            break;
        }
        else
        {
            printf("Zadali ste nespravne pohlavie\n");
        }
    }

    for (int i = 1; i <= pocetJazdcov; i++)
    {
        if (strcmp(zadanePohlavie, pohlavie[i]) == 0)
        {
            if (atof(cas1[i]) < najlepsieKolo)
            {
                najlepsieKolo = atof(cas1[i]);
                cisloKola = 1;
                cisloJazdca = i;
            }
            if (atof(cas2[i]) < najlepsieKolo)
            {
                najlepsieKolo = atof(cas2[i]);
                cisloKola = 2;
                cisloJazdca = i;
            }
            if (atof(cas3[i]) < najlepsieKolo)
            {
                najlepsieKolo = atof(cas3[i]);
                cisloKola = 3;
                cisloJazdca = i;
            }
            if (atof(cas4[i]) < najlepsieKolo)
            {
                najlepsieKolo = atof(cas4[i]);
                cisloKola = 4;
                cisloJazdca = i;
            }
            if (atof(cas5[i]) < najlepsieKolo)
            {
                najlepsieKolo = atof(cas5[i]);
                cisloKola = 5;
                cisloJazdca = i;
            }
        }
    }

    if (najlepsieKolo == 999)
    {
        printf("Jazdca tohto pohlavia nemame\n\n");
        return 0;
    }

    printf("\nNajlepsie kolo: %.3f\n", najlepsieKolo);
    printf("Jazdec: %s\n", meno[cisloJazdca]);
    printf("Cislo kola: %d\n\n", cisloKola);

    return 0;
}

void brand()
{
    struct Auto
    {
        int cisloJazdca;
        float najlepsieKolo;
        int cisloKola;
    };
    struct Auto znackaPorsche;
    struct Auto znackaBugatti;
    struct Auto znackaHonda;
    struct Auto znackaFerrari;

    znackaPorsche.najlepsieKolo = 999;
    znackaBugatti.najlepsieKolo = 999;
    znackaHonda.najlepsieKolo = 999;
    znackaFerrari.najlepsieKolo = 999;
    nacitanieTabulky();

    for (int i = 1; i <= pocetJazdcov; i++)
    {
        if (strcmp(znackaAuta[i], "porsche") == 0)
        {
            if (atof(cas1[i]) < znackaPorsche.najlepsieKolo)
            {
                znackaPorsche.najlepsieKolo = atof(cas1[i]);
                znackaPorsche.cisloKola = 1;
                znackaPorsche.cisloJazdca = i;
            }
            if (atof(cas2[i]) < znackaPorsche.najlepsieKolo)
            {
                znackaPorsche.najlepsieKolo = atof(cas2[i]);
                znackaPorsche.cisloKola = 2;
                znackaPorsche.cisloJazdca = i;
            }
            if (atof(cas3[i]) < znackaPorsche.najlepsieKolo)
            {
                znackaPorsche.najlepsieKolo = atof(cas3[i]);
                znackaPorsche.cisloKola = 3;
                znackaPorsche.cisloJazdca = i;
            }
            if (atof(cas4[i]) < znackaPorsche.najlepsieKolo)
            {
                znackaPorsche.najlepsieKolo = atof(cas4[i]);
                znackaPorsche.cisloKola = 4;
                znackaPorsche.cisloJazdca = i;
            }
            if (atof(cas5[i]) < znackaPorsche.najlepsieKolo)
            {
                znackaPorsche.najlepsieKolo = atof(cas5[i]);
                znackaPorsche.cisloKola = 5;
                znackaPorsche.cisloJazdca = i;
            }
        }
        if (strcmp(znackaAuta[i], "bugatti") == 0)
        {
            if (atof(cas1[i]) < znackaBugatti.najlepsieKolo)
            {
                znackaBugatti.najlepsieKolo = atof(cas1[i]);
                znackaBugatti.cisloKola = 1;
                znackaBugatti.cisloJazdca = i;
            }
            if (atof(cas2[i]) < znackaBugatti.najlepsieKolo)
            {
                znackaBugatti.najlepsieKolo = atof(cas2[i]);
                znackaBugatti.cisloKola = 2;
                znackaBugatti.cisloJazdca = i;
            }
            if (atof(cas3[i]) < znackaBugatti.najlepsieKolo)
            {
                znackaBugatti.najlepsieKolo = atof(cas3[i]);
                znackaBugatti.cisloKola = 3;
                znackaBugatti.cisloJazdca = i;
            }
            if (atof(cas4[i]) < znackaBugatti.najlepsieKolo)
            {
                znackaBugatti.najlepsieKolo = atof(cas4[i]);
                znackaBugatti.cisloKola = 4;
                znackaBugatti.cisloJazdca = i;
            }
            if (atof(cas5[i]) < znackaBugatti.najlepsieKolo)
            {
                znackaBugatti.najlepsieKolo = atof(cas5[i]);
                znackaBugatti.cisloKola = 5;
                znackaBugatti.cisloJazdca = i;
            }
        }
        if (strcmp(znackaAuta[i], "honda") == 0)
        {
            if (atof(cas1[i]) < znackaHonda.najlepsieKolo)
            {
                znackaHonda.najlepsieKolo = atof(cas1[i]);
                znackaHonda.cisloKola = 1;
                znackaHonda.cisloJazdca = i;
            }
            if (atof(cas2[i]) < znackaHonda.najlepsieKolo)
            {
                znackaHonda.najlepsieKolo = atof(cas2[i]);
                znackaHonda.cisloKola = 2;
                znackaHonda.cisloJazdca = i;
            }
            if (atof(cas3[i]) < znackaHonda.najlepsieKolo)
            {
                znackaHonda.najlepsieKolo = atof(cas3[i]);
                znackaHonda.cisloKola = 3;
                znackaHonda.cisloJazdca = i;
            }
            if (atof(cas4[i]) < znackaHonda.najlepsieKolo)
            {
                znackaHonda.najlepsieKolo = atof(cas4[i]);
                znackaHonda.cisloKola = 4;
                znackaHonda.cisloJazdca = i;
            }
            if (atof(cas5[i]) < znackaHonda.najlepsieKolo)
            {
                znackaHonda.najlepsieKolo = atof(cas5[i]);
                znackaHonda.cisloKola = 5;
                znackaHonda.cisloJazdca = i;
            }
        }
        if (strcmp(znackaAuta[i], "ferrari") == 0)
        {
            if (atof(cas1[i]) < znackaFerrari.najlepsieKolo)
            {
                znackaFerrari.najlepsieKolo = atof(cas1[i]);
                znackaFerrari.cisloKola = 1;
                znackaFerrari.cisloJazdca = i;
            }
            if (atof(cas2[i]) < znackaFerrari.najlepsieKolo)
            {
                znackaFerrari.najlepsieKolo = atof(cas2[i]);
                znackaFerrari.cisloKola = 2;
                znackaFerrari.cisloJazdca = i;
            }
            if (atof(cas3[i]) < znackaFerrari.najlepsieKolo)
            {
                znackaFerrari.najlepsieKolo = atof(cas3[i]);
                znackaFerrari.cisloKola = 3;
                znackaFerrari.cisloJazdca = i;
            }
            if (atof(cas4[i]) < znackaFerrari.najlepsieKolo)
            {
                znackaFerrari.najlepsieKolo = atof(cas4[i]);
                znackaFerrari.cisloKola = 4;
                znackaFerrari.cisloJazdca = i;
            }
            if (atof(cas5[i]) < znackaFerrari.najlepsieKolo)
            {
                znackaFerrari.najlepsieKolo = atof(cas5[i]);
                znackaFerrari.cisloKola = 5;
                znackaFerrari.cisloJazdca = i;
            }
        }
    }
    if (znackaPorsche.najlepsieKolo != 999)
    {
        printf("Znacka: porsche\nNajlepsie kolo: %.3f\nJazdec: %s\nCislo kola: %d\n\n", znackaPorsche.najlepsieKolo, meno[znackaPorsche.cisloJazdca], znackaPorsche.cisloKola);
    }
    else
        printf("Znacka porsche nema jazdca.\n\n");
    if (znackaBugatti.najlepsieKolo != 999)
    {
        printf("Znacka: bugatti\nNajlepsie kolo: %.3f\nJazdec: %s\nCislo kola: %d\n\n", znackaBugatti.najlepsieKolo, meno[znackaBugatti.cisloJazdca], znackaBugatti.cisloKola);
    }
    else
        printf("Znacka bugatti nema jazdca.\n\n");
    if (znackaHonda.najlepsieKolo != 999)
    {
        printf("Znacka: honda\nNajlepsie kolo: %.3f\nJazdec: %s\nCislo kola: %d\n\n", znackaHonda.najlepsieKolo, meno[znackaHonda.cisloJazdca], znackaHonda.cisloKola);
    }
    else
        printf("Znacka honda nema jazdca.\n\n");
    if (znackaFerrari.najlepsieKolo != 999)
    {
        printf("Znacka: ferrari\nNajlepsie kolo: %.3f\nJazdec: %s\nCislo kola: %d\n\n", znackaFerrari.najlepsieKolo, meno[znackaFerrari.cisloJazdca], znackaFerrari.cisloKola);
    }
    else
        printf("Znacka ferrari nema jazdca.\n\n");
}

int year()
{
    nacitanieTabulky();
    int zadanyRok = 999, cisloKola, cisloJazdca, rokStatus = 0;
    float najlepsieKolo = 999;

    while (zadanyRok < 1000 || zadanyRok > 9999)
    {
        printf("Zadajte rok narodenia vo formate YYYY:");
        scanf("%d", &zadanyRok);
    }

    for (int i = 1; i <= pocetJazdcov; i++)
    {
        if (zadanyRok > atoi(narodenie[i]))
        {

            if (atof(cas1[i]) < najlepsieKolo)
            {
                najlepsieKolo = atof(cas1[i]);
                cisloKola = 1;
                cisloJazdca = i;
            }
            if (atof(cas2[i]) < najlepsieKolo)
            {
                najlepsieKolo = atof(cas2[i]);
                cisloKola = 2;
                cisloJazdca = i;
            }
            if (atof(cas3[i]) < najlepsieKolo)
            {
                najlepsieKolo = atof(cas3[i]);
                cisloKola = 3;
                cisloJazdca = i;
            }
            if (atof(cas4[i]) < najlepsieKolo)
            {
                najlepsieKolo = atof(cas4[i]);
                cisloKola = 4;
                cisloJazdca = i;
            }
            if (atof(cas5[i]) < najlepsieKolo)
            {
                najlepsieKolo = atof(cas5[i]);
                cisloKola = 5;
                cisloJazdca = i;
            }

            rokStatus = 1;
        }
    }

    if (rokStatus == 0)
    {
        printf("Jazdca narodeneho pred rokom %d v tabulke nemame.\n\n", zadanyRok);
        return 0;
    }

    printf("%s\n", meno[cisloJazdca]);
    printf("nar. %s\n", narodenie[cisloJazdca]);
    printf("Najlepsie kolo: %.3f\n", najlepsieKolo);
    printf("Cislo kola: %d\n\n", cisloKola);

    return 0;
}

void average()
{
    nacitanieTabulky();
    float sucetKol, priemerKol, najlepsiPriemer;
    int najlepsiJazdec;

    for (int i = 1; i <= pocetJazdcov; i++)
    {
        if (i == 1)
        {
            sucetKol = atof(cas1[1]) + atof(cas2[1]) + atof(cas3[1]) + atof(cas4[1]) + atof(cas5[1]);
            priemerKol = sucetKol / 5;
            najlepsiPriemer = priemerKol;
            najlepsiJazdec = 1;
            printf("%s - %.3f\n", meno[1], priemerKol);
        }
        else
        {
            sucetKol = atof(cas1[i]) + atof(cas2[i]) + atof(cas3[i]) + atof(cas4[i]) + atof(cas5[i]);
            priemerKol = sucetKol / 5;
            if (priemerKol < najlepsiPriemer)
            {
                najlepsiPriemer = priemerKol;
                najlepsiJazdec = i;
            }
            printf("%s - %.3f\n", meno[i], priemerKol);
        }
    }
    printf("\nNajlepsie:\n%s - %.3f\n\n", meno[najlepsiJazdec], najlepsiPriemer);
}

void under()
{
    nacitanieTabulky();
    float zadanyCas;
    int pocetKol = 0, cisloKola[6] = {0, 0, 0, 0, 0, 0};

    printf("Zadajte cas kola: ");
    scanf("%f", &zadanyCas);

    while (zadanyCas < 0)
    {
        printf("Zadali ste cas mensi ako 0. Zadajte spravny cas:");
        scanf("%f", &zadanyCas);
    }
    printf("\n");

    for (int i = 1; i <= pocetJazdcov; i++)
    {
        printf("%s - ", meno[i]);
        if (atof(cas1[i]) <= zadanyCas)
        {
            cisloKola[1] = 1;
            pocetKol++;
        }
        if (atof(cas2[i]) <= zadanyCas)
        {
            cisloKola[2] = 2;
            pocetKol++;
        }
        if (atof(cas3[i]) <= zadanyCas)
        {
            cisloKola[3] = 3;
            pocetKol++;
        }
        if (atof(cas4[i]) <= zadanyCas)
        {
            cisloKola[4] = 4;
            pocetKol++;
        }
        if (atof(cas5[i]) <= zadanyCas)
        {
            cisloKola[5] = 5;
            pocetKol++;
        }

        if (pocetKol == 0 || pocetKol > 4)
        {
            printf("%d kol", pocetKol);
        }
        else if (pocetKol == 1)
        {
            printf("%d kolo", pocetKol);
        }
        else
        {
            printf("%d kola", pocetKol);
        }

        for (int j = 1; j <= 5; j++)
        {
            if (cisloKola[j] == 1)
            {
                printf(", %d (%s)", cisloKola[j], cas1[i]);
                cisloKola[j] = 0;
            }
            if (cisloKola[j] == 2)
            {
                printf(", %d (%s)", cisloKola[j], cas2[i]);
                cisloKola[j] = 0;
            }
            if (cisloKola[j] == 3)
            {
                printf(", %d (%s)", cisloKola[j], cas3[i]);
                cisloKola[j] = 0;
            }
            if (cisloKola[j] == 4)
            {
                printf(", %d (%s)", cisloKola[j], cas4[i]);
                cisloKola[j] = 0;
            }
            if (cisloKola[j] == 5)
            {
                printf(", %d (%.3f)", cisloKola[j], atof(cas5[i]));
                cisloKola[j] = 0;
            }
        }
        printf("\n");
        pocetKol = 0;
    }
    printf("\n");
}

int change()
{
    nacitanieTabulky();
    FILE *tabulka;
    char zadanePriezvisko[50] = " ";
    char priezvisko[50];
    char nacitanePriezvisko[50];
    char *ret;
    int zadaneKolo;
    float zadanyCas;
    int priezviskoStatus = 0;

    tabulka = fopen("tabulka.csv", "w+");
    if (tabulka == NULL)
    {
        printf("Subor nie je mozne precitat");
        return 0;
    }

    printf("Zadajte priezvisko jazdca: ");
    scanf("%s", &priezvisko);
    strcat(zadanePriezvisko, priezvisko);
    printf("Zadajte poradove cislo kola(1-5) a novy cas:");
    scanf("%d %f", &zadaneKolo, &zadanyCas);
    while (zadaneKolo < 1 || zadaneKolo > 5)
    {
        printf("Zadali ste nespravne kolo. Zadajte kolo(1-5):");
        scanf("%d", &zadaneKolo);
    }
    while (zadanyCas < 0)
    {
        printf("Zadali ste zaporny cas. Zadajte cas kola: ");
        scanf("%f", &zadanyCas);
    }

    for (int i = 1; i <= pocetJazdcov; i++)
    {
        ret = strrchr(meno[i], ' ');
        strcpy(nacitanePriezvisko, ret);
        if (strcmp(zadanePriezvisko, nacitanePriezvisko) == 0)
        {
            if (zadaneKolo == 1)
                sprintf(cas1[i], "%.3f", zadanyCas);
            if (zadaneKolo == 2)
                sprintf(cas2[i], "%.3f", zadanyCas);
            if (zadaneKolo == 3)
                sprintf(cas3[i], "%.3f", zadanyCas);
            if (zadaneKolo == 4)
                sprintf(cas4[i], "%.3f", zadanyCas);
            if (zadaneKolo == 5)
                sprintf(cas5[i], "%.3f", zadanyCas);
            priezviskoStatus = 1;
        }
        fprintf(tabulka, "%s;%s;%s;%s;", meno[i], pohlavie[i], narodenie[i], znackaAuta[i]);
        fprintf(tabulka, "%s;%s;%s;%s;%s", cas1[i], cas2[i], cas3[i], cas4[i], cas5[i]);
    }

    if (priezviskoStatus == 0)
        printf("Jazdca tohto priezviska nemame v tabulke");

    fclose(tabulka);

    printf("\n\n");
    sum();
    printf("\n\n");

    return 0;
}

int newdriver()
{
    nacitanieTabulky();

    FILE *tabulka;
    char zadaneMeno[20];
    int zadaneNarodenie;
    char zadaneAuto[50];
    char zadanePohlavie[5];
    float zadaneCasy;
    char zadanePriezvisko[50];

    tabulka = fopen("tabulka.csv", "a");
    if (tabulka == NULL)
    {
        printf("Subor nie je mozne precitat");
        return 0;
    }

    printf("Zadajte Meno a Priezvisko noveho jazdca: ");
    scanf("%s %s", &zadaneMeno, &zadanePriezvisko);
    printf("Zadajte rok narodenia noveho jazdca (format YYYY): ");
    scanf("%d", &zadaneNarodenie);
    printf("Zadajte pohlavie noveho jazdca: ");
    scanf("%s", &zadanePohlavie);
    while (1)
    {
        if ((strcmp(zadanePohlavie, "zena") == 0) || (strcmp(zadanePohlavie, "muz") == 0))
        {
            break;
        }
        printf("Zadali ste nezname pohlavie. Zadajte pohlavie: ");
        scanf("%s", &zadanePohlavie);
    }
    printf("Zadajte znacku auta noveho jazdca (bugatti, honda, ferrari, porsche): ");
    scanf("%s", &zadaneAuto);
    while (1)
    {
        if (strcmp(zadaneAuto, "bugatti") == 0 || strcmp(zadaneAuto, "honda") == 0 || strcmp(zadaneAuto, "ferrari") == 0 || strcmp(zadaneAuto, "porsche") == 0)
        {
            break;
        }
        printf("Zadali ste nespravnu znacku. Zadajte znacku(bugatti, honda, ferrari, porsche): ");
        scanf("%s", &zadaneAuto);
    }

    fputc('\n', tabulka);
    fprintf(tabulka, "%s %s;", zadaneMeno, zadanePriezvisko);

    if (strcmp(zadanePohlavie, "muz") == 0)
        fprintf(tabulka, "m;");
    else
        fprintf(tabulka, "f;");

    fprintf(tabulka, "%d;%s", zadaneNarodenie, zadaneAuto);

    printf("Zadajte casy 5 jazd noveho jazdca: \n");
    for (int x = 1; x < 6; x++)
    {
        printf("Cas kola %d: ", x);
        scanf("%f", &zadaneCasy);
        fprintf(tabulka, ";%.3f", zadaneCasy);
    }

    fclose(tabulka);

    sum();

    return 0;
}

int rmdriver()
{
    nacitanieTabulky();
    FILE *tabulka;
    char zadanePriezvisko[50] = " ";
    char priezvisko[50];
    char nacitanePriezvisko[50];
    char *ret;
    int uvodzovky = 34;
    int priezviskoStatus = 0;

    tabulka = fopen("tabulka.csv", "w+");
    if (tabulka == NULL)
    {
        printf("Subor nie je mozne precitat");
        return 0;
    }

    printf("Zadajte priezvisko jazdca, ktoreho chcete odstranit: ");
    scanf("%s", &priezvisko);
    strcat(zadanePriezvisko, priezvisko);
    for (int i = 1; i <= pocetJazdcov; i++)
    {
        ret = strrchr(meno[i], ' ');
        strcpy(nacitanePriezvisko, ret);
        if (strcmp(zadanePriezvisko, nacitanePriezvisko) == 0)
        {
            printf("Jazdec menom %c%s%c bol vymazany.\n\n ", uvodzovky, meno[i], uvodzovky);
            priezviskoStatus = 1;
            continue;
        }
        fprintf(tabulka, "%s;%s;%s;%s;%s;%s;%s;%s;%s", meno[i], pohlavie[i], narodenie[i], znackaAuta[i], cas1[i], cas2[i], cas3[i], cas4[i], cas5[i]);

        if (i == pocetJazdcov && priezviskoStatus == 0)
        {
            printf("Jazdec s priezviskom%s sa v tabulke nenachadza.\n\n", zadanePriezvisko);
        }
    }

    fclose(tabulka);

    return 0;
}

int main()
{
    char znak;
    while (znak != 'x')
    {
        znak = zadajZnak();

        if (znak == 's')
            sum();
        else if (znak == 'd')
            driver();
        else if (znak == 'l')
            lap();
        else if (znak == 'g')
            gender();
        else if (znak == 'b')
            brand();
        else if (znak == 'y')
            year();
        else if (znak == 'a')
            average();
        else if (znak == 'u')
            under();
        else if (znak == 'c')
            change();
        else if (znak == 'n')
            newdriver();
        else if (znak == 'r')
            rmdriver();
    }
    return 0;
}
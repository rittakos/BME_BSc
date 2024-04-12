#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct Szo
{
    char magyar[50+1];
    char angol[50+1];
} Szo;

typedef struct Szotar
{
    Szo szavak[200];
    int db;
    int indexHu[200];
    int indexE[200];
} Szotar;

typedef enum nyelv
{
    angol,
    magyar
}nyelv;




void Sort(Szo *szok, int *index, int db, nyelv nyelv)
{
    for (int i = 0; i < db-1; ++i)
    {
        int minindex = i;
        for (int j = i+1; j < db; ++j)
        {
            if(nyelv == angol)
            {
                if (strcmp(szok[index[j]].angol, szok[index[minindex]].angol) < 0)
                    minindex = j;
            }
            else
            {
                if (strcmp(szok[index[j]].magyar, szok[index[minindex]].magyar) < 0)
                    minindex = j;
            }


        }

        if (minindex != i)
        {
            int temp = index[minindex];

            index[minindex] = index[i];
            index[i] = temp;
        }
    }
}

int *Init(int index[100], int size)
{
    for(int idx = 0; idx < 100; ++idx)
        index[idx] = idx;
    return index;
}

void Rendez(Szotar sz, nyelv nyelv, int index[100])
{
    for(int idx = 0; idx < 100; ++idx)
        index[idx] = idx;
    Sort(sz.szavak, index, sz.db, nyelv);

}


/**
 * Felvesz egy új szót a szótárba.
 * Ha már benne van, nem csinál semmit.
 * @return True, ha bekerült a szó, false, ha megtelt a szótár.
 */
bool felvesz(Szotar *szt, Szo uj)
{
    /* benne van? */
    for (int i = 0; i < szt->db; ++i)
        if (strcmp(szt->szavak[i].magyar, uj.magyar) == 0
                && strcmp(szt->szavak[i].angol, uj.angol) == 0)
            return true;
    /* megtelt? */
    if (szt->db == 200)
        return false;
    /* betesszük */
    strcpy(szt->szavak[szt->db].magyar, uj.magyar);
    strcpy(szt->szavak[szt->db].angol, uj.angol);
    szt->db += 1;

    Rendez(*szt, angol, szt->indexE);
    Rendez(*szt, magyar, szt->indexHu);

    return true;
}

/**
 * Megkeres egy szót. A megadott szó akár angol,
 * akár magyar nyelvű lehet.
 * @return A találatra mutató pointer, vagy NULL.
 */

Szo * keres(Szotar *szt, char *szo)
{
    int db = szt->db;
    int *indexE = szt->indexE;
    int *indexHu = szt->indexHu;

    int min, max, mid;


    min = 0;
    max = db - 1;
    mid = (min + max)/2;

    while(min <= max && strcmp(szt->szavak[indexE[mid]].angol, szo) != 0)
    {
        if (strcmp(szt->szavak[indexE[mid]].angol, szo) == 1)
            max = mid - 1;
        else
            min = mid + 1;


        mid = (min + max)/2;
    }

    if(strcmp(szt->szavak[indexE[mid]].angol, szo) == 0)
        return &(szt->szavak[indexE[mid]]);

    min = 0;
    max = db - 1;
    mid = (min + max)/2;

    while(min <= max && strcmp(szt->szavak[indexHu[mid]].magyar, szo) != 0)
    {
        if (strcmp(szt->szavak[indexHu[mid]].magyar, szo) == 1)
            max = mid - 1;
        else
            min = mid + 1;

        mid = (min + max)/2;
    }

    if(strcmp(szt->szavak[indexHu[mid]].magyar, szo) == 0)
        return &(szt->szavak[indexHu[mid]]);

    return NULL;
}

/**
 * Fájlba írja a szótárat.
 * @return true, ha sikeres volt a művelet.
 * Ha nem, hibaüzenetet is ad a kimeneten.
 */
bool ment(Szotar *szt, char *fajlnev)
{
    FILE *f = fopen(fajlnev, "wt");
    if (f == NULL)
    {
        perror("Nem sikerült menteni a szótárat");
        return false;
    }
    for (int i = 0; i < szt->db; ++i)
        fprintf(f, "%s\t%s\n", szt->szavak[i].magyar,
                szt->szavak[i].angol);
    fclose(f);
    return true;
}


/**
 * Betölti a szótárat. Teljesen felülírja az
 * addigi tartalmat a fájlból beolvasott adatokkal.
 * @return true, ha sikeres volt.
 */
bool betolt(Szotar *szt, char *fajlnev)
{
    FILE *f = fopen(fajlnev, "rt");
    if (f == NULL)
    {
        perror("Nem sikerült betölteni a szótárat");
        return false;
    }
    szt->db = 0;
    Szo uj;
    while (fscanf(f, " %[^\t] %[^\n]", uj.magyar, uj.angol) == 2)
    {
        szt->szavak[szt->db] = uj;
        szt->db += 1;
    }
    fclose(f);
    Rendez(*szt, angol, szt->indexE);
    Rendez(*szt, magyar, szt->indexHu);
    return true;
}


/**
 * Kilistázza a szótár teljes tartalmát a képernyőre.
 */
void Listaz(Szotar *szt,  nyelv nyelv)
{
    int *index;
    if(nyelv == angol)
        index = szt->indexE;
    else
        index = szt->indexHu;
    for (int idx = 0; idx < szt->db; ++idx)
    {
        int wordId = index[idx];
        if(nyelv == angol)
            printf("%s = %s\n", szt->szavak[wordId].angol, szt->szavak[wordId].magyar);
        else
            printf("%s = %s\n", szt->szavak[wordId].magyar, szt->szavak[wordId].angol);
    }
}

int main(void)
{

    Szotar sz;
    sz.db = 0;  /* inicializálás; a többit nem kell */


    felvesz(&sz, (Szo){ "alma", "apple"});
    felvesz(&sz, (Szo){ "korte", "pear"});
    felvesz(&sz, (Szo){ "barack", "peach"});
    felvesz(&sz, (Szo){ "tabla csoki", "bar of chocolate"});
    felvesz(&sz, (Szo){ "doboz gyufa", "box of matches"});
    felvesz(&sz, (Szo){ "idegroncs", "nervous wreck"});


    printf("Kereses =====\n");
    Szo * talalat = keres(&sz, "alma");
    if (talalat == NULL)
        printf("Nincs meg");
    else
        printf("Talalat: %s = %s\n", talalat->magyar, talalat->angol);
    printf("\n");

    printf("Fajlkezeles =====\n");
    ment(&sz, "szotar.txt");
    sz.db = 0;
    betolt(&sz, "szotar.txt");
    printf("%d szo beolvasva.\n", sz.db);
    printf("\n");


    printf("A szotar tartalma =====\n");
    Listaz(&sz, angol);
    printf("\n");
    Listaz(&sz, magyar);
    printf("\n");
}

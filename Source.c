#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE (1024)
#define MAX_SIZE (128)

typedef struct {
    char ime[MAX_SIZE];
    char prezime[MAX_SIZE];
    double bodovi;
}student;

int brojStudenata(char* imeDatoteke)
{
    int brojac = 0;
    FILE* dat = NULL;
    char buffer[MAX_LINE] = { 0 };

    dat = fopen(imeDatoteke, "r");

    if (!dat)
    {
        printf("Greska");
        return -1;
    }
    while (!feof(dat))
    {
        fgets(buffer, MAX_LINE, dat);
        brojac++;
    }

    fclose(dat);

    return brojac;
}

student* alokacijaMemorije(int brStudenata, char* imeDatoteke)
{
    int i = 0;
    FILE* dat = NULL;
    student* studenti = NULL;

    studenti = (student*)malloc(brStudenata * sizeof(student));
    dat = fopen(imeDatoteke, "r");

    if (!dat)
    {
        printf("Greska");
        free(studenti);
        return NULL;
    }
    while (!feof(dat))
    {
        fscanf(dat, " %s %s %lf", studenti[i].ime, studenti[i].prezime, &studenti[i].bodovi);
        i++;
    }
    fclose(dat);
    return studenti;
}

double relativniBodovi(char* imeDatoteke, int index)
{

    int i = 0;
    student* studenti = NULL;
    int brojStud = 0;
    double relativanBrojBodova = 0;
    double max = 0;

    brojStud = brojStudenata(imeDatoteke);
    studenti = alokacijaMemorije(brojStud, imeDatoteke);

    for (i = 0; i < brojStud; i++) {
        if (studenti[i].bodovi >= max)
        {
            max = studenti[i].bodovi;
        }
    }
    relativanBrojBodova = studenti[index].bodovi / (max) * 100;
    return relativanBrojBodova;
}

int ispis(char* imeDatoteke)
{
    int brojStud = 0, i = 0;
    student* studenti = NULL;
    double relBod = 0;

    brojStud = brojStudenata(imeDatoteke);
    studenti = alokacijaMemorije(brojStud, imeDatoteke);

    printf("Broj stud je: %d\n", brojStud);

    for (i = 0; i < brojStud; i++)
    {
        printf("Ime \t Prezime \t Bodovi \t Rel bodovi \n");
        printf("%s \t  %s \t\t  %lf \t", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi);
        relBod = relativniBodovi(imeDatoteke, i);
        printf(" %lf \n", relBod);
    }

    return 0;
}

int main()
{
    ispis("datoteka.txt");
    return 0;
}
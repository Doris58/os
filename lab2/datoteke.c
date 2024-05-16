/* Operacije nad datotekama */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "datoteke.h"

/* implementacija funkcija, vec opisanih u lab1 + dohvati_iz_cijevi */

int procitaj_status() { return 0; }

void zapisi_status(int br)
{
	FILE *fp;
	fp = fopen(f_status, "w");
	if(fp == NULL)
    {
		printf("Ne mogu otvoriti datoteku %s\n", f_status);
        exit(1);
	}

	if(fprintf(fp, "%d\n", br) < 1) 
    {
		printf("Nije upisan broj u %s!\n", f_status);
		exit(1);
	}

	fclose(fp);
}

void dodaj_broj(int br)
{
	FILE *fp;
	fp = fopen(f_obrada, "a");
	if(fp == NULL)
    {
		printf("Ne mogu otvoriti datoteku %s\n", f_obrada);
        exit(1);
	}

	if(fprintf(fp, "%d\n", br) < 1) 
    {
		printf("Nije upisan broj u %s!\n", f_obrada);
		exit(1);
	}

	fclose(fp);
}


int pronadi_zadnji_broj() { return 0; }

int dohvati_iz_cijevi()
{
	FILE *fp;
	fp = fopen(dat_mreza, "r");
	if(fp == NULL) 
	{
		fprintf(stderr, "Ne mogu otvoriti cijev %s\n", dat_mreza);
		exit(1);
	}

	int x, y = -1;

	if(fscanf(fp, "%d", &x) > 0)
		y = x;

	fclose(fp);

	return y;
}
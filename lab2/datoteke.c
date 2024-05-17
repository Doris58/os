/* Operacije nad datotekama */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "datoteke.h"

/* implementacija funkcija, vec opisanih u lab1 + dohvati_iz_cijevi */

int procitaj_status()
{
	FILE *fp;
	fp = fopen(dat_status, "r");
	if (fp == NULL)
	{
		printf("Ne mogu otvoriti datoteku %s\n", dat_status);
		exit(1);
	}

	int br;
	if (fscanf(fp, "%d", &br) != 1)
	{
		printf("Nije procitan broj iz %s!\n", dat_status);
		exit(1);
	}

	fclose(fp);

	return br;

	// return 0;
}

void zapisi_status(int br)
{
	FILE *fp;
	fp = fopen(dat_status, "w");
	if (fp == NULL)
	{
		printf("Ne mogu otvoriti datoteku %s\n", dat_status);
		exit(1);
	}

	if (fprintf(fp, "%d\n", br) < 1)
	{
		printf("Nije upisan broj u %s!\n", dat_status);
		exit(1);
	}

	fclose(fp);
}

void dodaj_broj(int br)
{
	FILE *fp;
	fp = fopen(dat_obrada, "a");
	if (fp == NULL)
	{
		printf("Ne mogu otvoriti datoteku %s\n", dat_obrada);
		exit(1);
	}

	if (fprintf(fp, "%d\n", br) < 1)
	{
		printf("Nije upisan broj u %s!\n", dat_obrada);
		exit(1);
	}

	fclose(fp);
}

int pronadi_zadnji_broj()
{
	int br = -1;

	FILE *fp;
	fp = fopen(dat_obrada, "r");
	if (fp == NULL)
	{
		printf("Ne mogu otvoriti datoteku %s\n", dat_obrada);
		exit(1);
	}

	while (!feof(fp))
		if (fscanf(fp, "%d", &br) != 1)
			break;

	fclose(fp);

	return br;

	// return 0;
}

int dohvati_iz_cijevi()
{
	FILE *fp;
	fp = fopen(dat_mreza, "r");
	if (fp == NULL)
	{
		fprintf(stderr, "Ne mogu otvoriti cijev %s\n", dat_mreza);
		exit(1);
	}

	int x, y = -1;

	if (fscanf(fp, "%d", &x) > 0)
		y = x;

	fclose(fp);

	return y;
}
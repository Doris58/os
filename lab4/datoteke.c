#include <stdio.h>
#include <string.h>
#include "datoteke.h"
#include "disk.h"

//neka u simulaciji (radi jednostavnosti) datotečna tablica bude u memoriji
static struct opisnik datotecna_tablica[MAX_DATOTEKA];

//slobodni blokovi na disku
static char slobodni_blokovi[BLOCKS];

void inicijaliziraj_prazni_disk()
{
	int i, j;

	memset(datotecna_tablica, 0, sizeof(struct opisnik) * MAX_DATOTEKA);
	for (i = 0; i < MAX_DATOTEKA; i++) {
		datotecna_tablica[i].kazaljka = -1;
		for (j = 0; j < BLOCKS; j++)
			datotecna_tablica[i].blokovi[j] = -1;
	}
	memset(slobodni_blokovi, 0, BLOCKS);
}
int otvori_datoteku(char *ime, int nacin)
{
	int i, slobodni_opisnik = -1;
	if (nacin != ZA_CITANJE && nacin != ZA_PISANJE) {
		fprintf(stderr, "'nacin' mora biti ZA_CITANJE ili ZA_PISANJE!\n");
		return -1;
	}
	for (i = 0; i < MAX_DATOTEKA; i++)
		if (datotecna_tablica[i].ime[0] == 0)
			slobodni_opisnik = i;
		else if (!strncmp(datotecna_tablica[i].ime, ime, IME_DULJINA))
			break;
	if (i < MAX_DATOTEKA) { //postoji, otvori je kako je zadano
		if (datotecna_tablica[i].kazaljka > -1) {
			fprintf(stderr, "Datoteka je vec otvorena!\n");
			return -1;
		}
		datotecna_tablica[i].kazaljka = 0;
		datotecna_tablica[i].nacin_rada = nacin;
		return i;
	}
	else if (nacin == ZA_CITANJE) {
		fprintf(stderr, "Datoteka ne postoji, ne moze se citati!\n");
		return -1;
	}
	else { //nacin == ZA_PISANJE
		if (slobodni_opisnik >= 0) {
			fprintf(stdout, "Datoteka ne postoji, stvaram novu!\n");
			i = slobodni_opisnik;
			strncpy(datotecna_tablica[i].ime, ime, IME_DULJINA);
			datotecna_tablica[i].velicina = 0;
			datotecna_tablica[i].kazaljka = 0;
			datotecna_tablica[i].nacin_rada = nacin;
			//ne treba inicijalizirati "blokove"
			return i;
		}
		else {
			fprintf(stderr, "Nema mjesta za novu datoteku\n");
			return -1;
		}
	}
	return i; //ne bi trebao nikada doci do tu...
}
int zatvori_datoteku(int id)
{
	datotecna_tablica[id].kazaljka = -1;

	return 0;
}

int procitaj(int id, void *p, size_t koliko)
{
	if (id < 0 || id >= MAX_DATOTEKA ||
		datotecna_tablica[id].ime[0] == 0 ||
		datotecna_tablica[id].kazaljka == -1)
	{
		fprintf(stderr, "Krivi id\n");
		return -1;
	}

	char buffer[BLOCK_SIZE];
	size_t kopirati;

	struct opisnik dat = datotecna_tablica[id];
	ssize_t blok_datoteke = dat.kazaljka / BLOCK_SIZE;
	int blok_diska = dat.blokovi[blok_datoteke];
	size_t jos = koliko;

	//dok se još može čitati, dok ima još u datoteci, i dok postoji taj blok datoteke
	while(jos > 0 && dat.kazaljka < dat.velicina && blok_diska >= 0)
	{
		//ako blok ne postoji, prekinuti s čitanjem i vratiti do sada procitano

		//procitaj blok diska u privremeni buffer s dohvati_blok()
		dohvati_blok(blok_diska, buffer);

		//kopiraj u p od datotecna_tablica[id].kazaljka do koliko ili do
		//kraja bloka ili do datotecna_tablica[id].velicina, što prije dođe
		kopirati = min(jos, dat.velicina - dat.kazaljka, BLOCK_SIZE - dat.kazaljka % BLOCK_SIZE);

		// kopiraj kopirati bajtova iz buffer + dat.kazaljka % VEL_BLOKA u p
		memcpy(p, buffer + dat.kazaljka % BLOCK_SIZE, kopirati);

		p += kopirati;
		dat.kazaljka += kopirati;
		jos -= kopirati;

		//ako treba jos, dohvati iduci blok, itd.

		blok_datoteke++;
		blok_diska = dat.blokovi[blok_datoteke];
	}

	return koliko - jos;
}

int zapisi(int id, void *p, size_t koliko)
{
	if (id < 0 || id >= MAX_DATOTEKA ||
		datotecna_tablica[id].ime[0] == 0 ||
		datotecna_tablica[id].kazaljka == -1)
	{
		fprintf(stderr, "Krivi id\n");
		return -1;
	}

	char buffer[BLOCK_SIZE];
	size_t kopirati;

	struct opisnik dat = datotecna_tablica[id];
	ssize_t blok_datoteke = dat.kazaljka / BLOCK_SIZE;
	int blok_diska = dat.blokovi[blok_datoteke];
	size_t jos = koliko;
	size_t max_velicina_datoteke = BLOCK_SIZE * BLOCKS;
	
	while(jos > 0 && dat.kazaljka < max_velicina_datoteke)
	{
		//ako blok ne postoji (-1), potražiti slobodni blok i dati ga datoteci;
		if(blok_diska == -1)
		{
			//nađi slobodni blok i ažuriraj dat.blokovi
			//ako nema više slobodnih blokova stati s pisanjem i izaci iz petlje
		}
		else
		{
			//procitaj blok diska u privremeni buffer s dohvati_blok()
			dohvati_blok(blok_diska, buffer);
		}

		kopirati = min(jos, BLOCK_SIZE - dat.kazaljka % BLOCK_SIZE);

		//kopiraj kopirati bajtova iz p u buffer + dat.kazaljka % VEL_BLOKA
		//kopiraj iz p u buffer+datotecna_tablica[id].kazaljka 'koliko' bajtova
		//ili kraja bloka
		memcpy(buffer + dat.kazaljka % BLOCK_SIZE, p, kopirati);

		//zapiši blok na disk (buffer => dat.blokovi[blok_dat])
		pohrani_blok(blok_diska, buffer);

		p += kopirati;
		dat.kazaljka += kopirati;
		jos -= kopirati;

		//ako treba jos, dohvati/dodaj iduci blok, itd.

		blok_datoteke++;
		blok_diska = dat.blokovi[blok_datoteke];
	}

	//dat.veličina = max(dat.kazaljka, prethodna veličina datoteke)
	//ili dat.veličina = dat.kazaljka
	//te osloboditi blokove od 'blok_dat' na dalje

	return koliko - jos;
}

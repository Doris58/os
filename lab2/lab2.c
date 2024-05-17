/* Glavna datoteka za lab2 s funkcijom main */

#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "signali.h"
#include "datoteke.h"

// globalne varijable; koriste se (ili će se koristiti) u funkcijama i obradama signala
char *dat_status, *dat_obrada, *dat_mreza;
int broj = 0;
int nije_kraj = 1;
int nije_kraj_obrade = 1;

/* funkcije koje rade dretve */
void *obrada(void *);
void *mreza(void *);

#define BROJ_DODATNIH_DRETVI 2

int main(int argc, char *argv[])
{
	if (argc < 4)
	{
		fprintf(stderr, "Koristenje: %s <status-datoteka> "
						"<datoteka-s-podacima> <cjevovod>\n",
				argv[0]);
		exit(1);
	}
	dat_status = argv[1];
	dat_obrada = argv[2];
	dat_mreza = argv[3];

	postavi_signale();

	printf("\nProgram je počeo s radom. PID = %ld .\n\n", (long)getpid());
	
	/* dohvati prvi broj i zapisi 0 u status */
	printf("Upišite prvi broj u konzolu. U status se upisuje 0. \n\n");
	int ucitani;
	scanf("%d", &ucitani);
	zapisi_status(0);

	/* stvori dretve: radnu i mreznu */

	printf("Stvaram nove dretve...\n\n");
	pthread_t opisnik[BROJ_DODATNIH_DRETVI];
	int id[BROJ_DODATNIH_DRETVI];
	void *(*fun_ptr)(void *);

	for (int i = 0; i < BROJ_DODATNIH_DRETVI; i++)
	{
		id[i] = i;

		if (i == 0)
			fun_ptr = &obrada;

		if (i == 1)
			fun_ptr = &mreza;

		if (pthread_create(&opisnik[i], NULL, *fun_ptr, &id[i]))
		{
			fprintf(stderr, "Ne mogu stvoriti novu dretvu!\n");
			exit(1);
		}
	}

	printf("ŽELJENI BROJ MOŽETE UPISIVATI U OVU KONZOLU! \n\n");
	while(nije_kraj)
	{
		// procitaj broj iz konzole, npr. sa scanf
		scanf("%d", &ucitani);

		// ako je > 0 onda ga postavi kao broj
		if(ucitani > 0)
			broj = ucitani;
		// inace prekini s radom => postavi nije_kraj = 0
		else
		{
			printf("Uneseni broj nije > 0. Glavni program prekida svoj rad. \n");
			nije_kraj = 0;
		}
	}

	// cekaj na kraj dretve obrada, ali ne i one druge mrezne
	pthread_join(opisnik[0], NULL);

	return 0;
}

void *obrada(void *p)
{
	printf("Dretva koja radi obradu brojeva je počela s radom. \n\n");
	/* vise-manje glavni dio iz lab1 */
	broj = procitaj_status();
	if (broj == 0)
	{
		printf("Tražim zadnji obrađeni broj u datoteci. \n");
		broj = pronadi_zadnji_broj();

		broj = (int)sqrt(broj);
	}

	zapisi_status(0);

	printf("Zadnji broj = %d . Krećem s radom.\n", broj);

	int x;
	while(nije_kraj_obrade)
	{
		broj = broj + 1;
		x = broj * broj;

		dodaj_broj(x);

		sleep(5);
	}

	return NULL;
}

void *mreza(void *p)
{
	printf("Dretva koja čita brojeve iz cijevi je počela s radom. \n\n");
	// u petlji cekaj da se nesto pojavi u cijevi
	// ako je procitano > 0 onda ga postavi u broj
	int procitani = -1;
	while(1)
	{
		while(procitani == -1)
			procitani = dohvati_iz_cijevi();

		printf("Broj pročitan iz cijevi: %d .\n", procitani);

		if (procitani > 0)
			broj = procitani;

		procitani = -1;
	}

	return NULL;
}

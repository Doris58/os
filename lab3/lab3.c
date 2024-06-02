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

int broj_dretvi = 1; // pocetno jedna dretva koja radi obradu
int postavljeni_broj_dretvi = 1;

pthread_mutex_t m;	// monitor
pthread_cond_t red; // red uvjeta

/* funkcije koje rade dretve */
void *obrada(void *);
void *mreza(void *);
void *kontrola_broja_dretvi(void *);

#define BROJ_DODATNIH_DRETVI 3 // pocetno dodatnih, uz glavnu, glavna ih stvara

void *kontrola_broja_dretvi(void *p)
{
	int x;

	while (1)
	{
		srand(time(0));
		x = 1 + (rand() % 200);

		if (x >= 1 && x <= 100) // ako je x unutar granica 1-100 tada
		{
			pthread_mutex_lock(&m);

			postavljeni_broj_dretvi = x;

			while (broj_dretvi < postavljeni_broj_dretvi)
			{
				// stvori_novu_dretvu(obrada)
				if (pthread_create(NULL, NULL, obrada, NULL))
				{
					fprintf(stderr, "Ne mogu stvoriti novu radnu dretvu!\n");
					exit(1);
				}
				broj_dretvi++;
			}

			pthread_mutex_unlock(&m);
		}
	}
}

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

	pthread_mutex_init(&m, NULL);
	pthread_cond_init(&red, NULL);

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

		if (i == 2)
			fun_ptr = &kontrola_broja_dretvi;

		if (pthread_create(&opisnik[i], NULL, *fun_ptr, &id[i]))
		{
			fprintf(stderr, "Ne mogu stvoriti novu dretvu!\n");
			exit(1);
		}
	}

	printf("ŽELJENI BROJ MOŽETE UPISIVATI U OVU KONZOLU! \n\n");
	while (nije_kraj)
	{
		// procitaj broj iz konzole, npr. sa scanf
		scanf("%d", &ucitani);

		// ako je > 0 onda ga postavi kao broj
		if (ucitani > 0)
		{
			pthread_mutex_lock(&m);

			broj = ucitani;

			pthread_mutex_unlock(&m);
		}
		// inace prekini s radom => postavi nije_kraj = 0
		else
		{
			printf("Uneseni broj nije > 0. Glavni program prekida svoj rad. \n");
			nije_kraj = 0;
		}
	}

	// cekaj na kraj dretve obrada, ali ne i one druge mrezne
	// pthread_join(opisnik[0], NULL);

	pthread_mutex_destroy(&m);
	pthread_cond_destroy(&red);

	return 0;
}

void *obrada(void *p)
{
	pthread_mutex_lock(&m);

	if (broj_dretvi > postavljeni_broj_dretvi)
	{
		broj_dretvi--;

		pthread_mutex_unlock(&m);

		return NULL; // ili pthread_exit
	}

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
	while (nije_kraj_obrade)
	{
		broj = broj + 1;
		x = broj * broj;

		pthread_mutex_unlock(&m);

		sleep(5); // simuliram trajanje obrade

		pthread_mutex_lock(&m);

		dodaj_broj(x);
	}

	pthread_mutex_unlock(&m);

	return NULL;
}

void *mreza(void *p)
{
	printf("Dretva koja čita brojeve iz cijevi je počela s radom. \n\n");
	// u petlji cekaj da se nesto pojavi u cijevi
	// ako je procitano > 0 onda ga postavi u broj
	int procitani = -1;
	while (1)
	{
		while (procitani == -1)
			procitani = dohvati_iz_cijevi();

		printf("Broj pročitan iz cijevi: %d .\n", procitani);

		pthread_mutex_lock(&m);

		if (procitani > 0)
			broj = procitani;

		pthread_mutex_unlock(&m);

		procitani = -1;
	}

	return NULL;
}

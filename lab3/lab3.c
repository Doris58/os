/* Glavna datoteka za lab3 s funkcijom main */

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

// pocetno dodatnih, uz glavnu, glavna ih stvara - mreza, obrada i kontrola dretvi
#define BROJ_DODATNIH_DRETVI 3
#define MAX_RADNIH_DRETVI 100

pthread_t opisnik[BROJ_DODATNIH_DRETVI + MAX_RADNIH_DRETVI - 1]; // - 1 jer je jedna radna u dodatnim
int id[BROJ_DODATNIH_DRETVI + MAX_RADNIH_DRETVI - 1];

void *kontrola_broja_dretvi(void *p)
{
	printf("Dretva koja kontrolira broj radnih dretvi je počela s radom. \n\n");

	int x;

	while (1)
	{
		srand(time(0));
		x = 1 + (rand() % 10);

		//printf("ŽELJENI BROJ DRETVI KOJE RADE OBRADU MOŽETE UPISATI U OVU KONZOLU! \n\n");
		//scanf("%d", &x);

		if (x >= 1 && x <= MAX_RADNIH_DRETVI) // ako je x unutar granica 1-100 tada
		{
			pthread_mutex_lock(&m);

			postavljeni_broj_dretvi = x;


			// while (broj_dretvi < postavljeni_broj_dretvi)
			//{
			//  stvori_novu_dretvu(obrada)

			for (int i = BROJ_DODATNIH_DRETVI - 1; broj_dretvi < postavljeni_broj_dretvi && i < BROJ_DODATNIH_DRETVI + MAX_RADNIH_DRETVI - 1; i++)
			{
				if (id[i] == 0)
				{
					id[i] = i;

					if (pthread_create(&opisnik[id[i]], NULL, obrada, &id[i]))
					{
						fprintf(stderr, "Ne mogu stvoriti novu radnu dretvu!\n");
						exit(1);
					}

					broj_dretvi++;

					// break;
				}
			}

			//printf("Želim da bude %d radnih dretvi.\n\n", postavljeni_broj_dretvi);

			pthread_mutex_unlock(&m);

			//}
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

	// inicijalizacija globalnog polja id nulama
	for (int i = 0; i < BROJ_DODATNIH_DRETVI + MAX_RADNIH_DRETVI - 1; i++)
		id[i] = 0;

	/* stvori dretve: radnu i mreznu */
	void *(*fun_ptr)(void *);
	printf("Stvaram nove dretve...\n\n");

	for (int i = BROJ_DODATNIH_DRETVI - 1; i >= 0; i--)
	{
		id[i] = i;

		if (i == 2)
			fun_ptr = &obrada;

		if (i == 1)
			fun_ptr = &mreza;

		if (i == 0)
			fun_ptr = &kontrola_broja_dretvi;

		if (pthread_create(&opisnik[i], NULL, *fun_ptr, &id[i]))
		{
			fprintf(stderr, "Ne mogu stvoriti novu dretvu!\n");
			exit(1);
		}
	}

	printf("ŽELJENI BROJ ZA OBRADU MOŽETE UPISATI U OVU KONZOLU! \n\n");
	while (nije_kraj)
	{
		// procitaj broj iz konzole, npr. sa scanf
		scanf("%d", &ucitani);

		// ako je > 0 onda ga postavi kao broj
		if (ucitani > 0)
		{
			pthread_mutex_lock(&m);

			printf("Broj učitan iz konzole: %d \n\n", ucitani);
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
		printf("Dretva %d  koja radi obradu brojeva prestaje s radom. \n\n", *((int*) p));
		*((int*) p) = 0; 
		broj_dretvi--;

		pthread_mutex_unlock(&m);

		return NULL; // ili pthread_exit
	}

	printf("Dretva %d  koja radi obradu brojeva je počela s radom. \n\n", *((int*) p));
	/* vise-manje glavni dio iz lab1 */
	broj = procitaj_status();
	if (broj == 0)
	{
		printf("Dretva %d traži zadnji obrađeni broj u datoteci. \n", *((int*) p));
		broj = pronadi_zadnji_broj();

		broj = (int)sqrt(broj);
	}

	zapisi_status(0);

	printf("Dretva %d kaže: Zadnji broj = %d . Krećemo s tim brojem.\n\n", *((int*) p), broj);

	int x;
	while (nije_kraj_obrade)
	{
		if (broj_dretvi > postavljeni_broj_dretvi)
		{
			printf("Dretva %d  koja radi obradu brojeva prestaje s radom. \n\n", *((int*) p));
			*((int*) p) = 0; 
			broj_dretvi--;

			pthread_mutex_unlock(&m);

			return NULL; // ili pthread_exit
		}

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

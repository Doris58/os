#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <signal.h>

char f_status[11] = "status.txt";
char f_obrada[11] = "obrada.txt";

int broj = 0;

int procitaj_status();
void zapisi_status(int br);
void dodaj_broj(int br);
int pronadi_zadnji_broj();

void obradi_dogadaj(int sig);
void obradi_sigterm(int sig);

int main()
{
    struct sigaction act;

	/* maskiranje signala SIGUSR1 */
	act.sa_handler = obradi_dogadaj;

	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGTERM);

	act.sa_flags = 0; 

	sigaction(SIGUSR1, &act, NULL);

	/* maskiranje signala SIGTERM */
	act.sa_handler = obradi_sigterm;

	sigemptyset(&act.sa_mask);

	sigaction(SIGTERM, &act, NULL);


    broj = procitaj_status();
    if(broj == 0)
    {
        printf("Program je bio prekinut. Tražim broj. \n");
        broj = pronadi_zadnji_broj();

        broj = (int)sqrt(broj);
    }

    zapisi_status(0);

    printf("Zadnji broj = %d . Krećem s radom. PID = %ld \n", broj, (long)getpid());

    int x;
    while(1)
    {
        broj = broj + 1;
        x = broj * broj;

        dodaj_broj(x);

        sleep(5);
    }

    return 0;
}

int procitaj_status()
{
    FILE *fp;
    fp = fopen(f_status, "r");
    if(fp == NULL)
    {
        printf("Ne mogu otvoriti datoteku %s\n", f_status);
        exit(1);
    }

    int br;
    if(fscanf(fp, "%d", &br) != 1) 
    {
		printf("Nije procitan broj iz %s!\n", f_status);
		exit(1);
	}

	fclose(fp);

	return br;
}

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

int pronadi_zadnji_broj()
{
	int br = -1;

    FILE *fp;
	fp = fopen(f_obrada, "r");
	if(fp == NULL)
    {
		printf("Ne mogu otvoriti datoteku %s\n", f_obrada);
        exit(1);
	}

	while(!feof(fp))
		if(fscanf(fp, "%d", &br) != 1)
			break;

	fclose(fp);

	return br;
}

void obradi_dogadaj(int sig)
{
	printf("Signal SIGUSR1.\n");
	
    printf("Trenutni broj koji se koristi u obradi = %d\n", broj);
}

void obradi_sigterm(int sig)
{
	printf("Primio signal SIGTERM. Pišem zadnji broj u status.txt i završavam s radom. \n");

    zapisi_status(broj);

    exit(1);
}


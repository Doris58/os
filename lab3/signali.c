/* Operacije nad signalima */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "signali.h"
#include "datoteke.h"

void postavi_signale()
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
}

void obradi_dogadaj(int sig)
{
    printf("Signal SIGUSR1.\n");

    printf("Trenutni broj koji se koristi u obradi = %d . Nastavljamo dalje. \n", broj);
}

void obradi_sigterm(int sig)
{
    printf("Primio signal SIGTERM. Pišem zadnji broj u status.txt. \n Dretve koje obrađuju brojeve završavaju s radom. \n");

    zapisi_status(broj);

    nije_kraj_obrade = 0;
}

// void obradi_sigint(int sig) {}
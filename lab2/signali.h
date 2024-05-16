/* Zaglavlje za sučelja s operacijama nad signalima */

#pragma once 

extern int broj, nije_kraj;

/* funkcije za obradu signala */
void postavi_signale();
void obradi_dogadaj(int sig);
void obradi_sigterm(int sig);
// void obradi_sigint(int sig);
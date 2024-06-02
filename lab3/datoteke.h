/* Zaglavlje za sučelja s operacijama nad datotekama */

#pragma once

extern char *dat_status, *dat_obrada, *dat_mreza;

/* funkcije za rad s datotekama */
int procitaj_status();
void zapisi_status(int br);
void dodaj_broj(int br);
int pronadi_zadnji_broj();
int dohvati_iz_cijevi();
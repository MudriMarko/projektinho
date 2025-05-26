#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#ifndef CVIJECE_H
#define CVIJECE_H

#include <stdio.h>

#define ERROR_MSG(msg) fprintf(stderr, "Greska: %s\n", msg)

typedef struct {
	char naziv[50];
	float cijena;
	char vrsta[30];
	int kolicina;
} Cvijet;

typedef struct {
	char imeKupca[50];
	char nazivCvijeca[50];
	int kolicina;
	float ukupnaCijena;
} Prodaja;

typedef enum {
	IZBOR_IZLAZ,
	IZBOR_DODAJ,
	IZBOR_ISPISI,
	IZBOR_PRODAJA,
	IZBOR_AZURIRAJ,
	IZBOR_BRISE,
	IZBOR_SPREMI,
	IZBOR_SORTIRAJ
} Izbornik;

void dodajCvijet(Cvijet** skladiste, int* brojCvjetova, int* kapacitet);
void ispisiSkladiste(const Cvijet* skladiste, int brojCvjetova);
void prodajaCvijeca(Cvijet* skladiste, int brojCvjetova, Prodaja** prodaje, int* brojProdaja, int* kapacitetProdaja);
void azurirajCvijet(Cvijet* skladiste, int brojCvjetova);
void obrisiCvijet(Cvijet** skladiste, int* brojCvjetova);
void spremiSkladisteUdatoteku(const Cvijet* skladiste, int brojCvjetova);
void ucitajSkladisteIzdatoteke(Cvijet** skladiste, int* brojCvjetova, int* kapacitet);
void oslobodiMemoriju(Cvijet** skladiste, Prodaja** prodaje);
int usporediCvijet(const void* a, const void* b);
Cvijet* pronadjiCvijet(const Cvijet* skladiste, int brojCvjetova, const char* naziv);

#endif

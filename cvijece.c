#include "cvijece.h"
#include <stdlib.h>
#include <string.h>

#define POCETNI_KAPACITET 10

void dodajCvijet(Cvijet** skladiste, int* brojCvjetova, int* kapacitet) {
	if (!skladiste || !brojCvjetova || !kapacitet) {
		ERROR_MSG("Neispravan parametar u dodajCvijet");
		return;
	}

	if (*brojCvjetova >= *kapacitet) {
		*kapacitet *= 2;
		Cvijet* temp = realloc(*skladiste, (*kapacitet) * sizeof(Cvijet));
		if (!temp) {
			ERROR_MSG("Neuspjelo alociranje memorije!");
			return;
		}
		*skladiste = temp;
	}

	Cvijet noviCvijet;
	printf("Unesite naziv cvijeta: ");
	scanf("%49s", noviCvijet.naziv);
	printf("Unesite cijenu cvijeta: ");
	scanf("%f", &noviCvijet.cijena);
	printf("Unesite vrstu cvijeta: ");
	scanf("%29s", noviCvijet.vrsta);
	printf("Unesite kolicinu cvijeta: ");
	scanf("%d", &noviCvijet.kolicina);

	(*skladiste)[*brojCvjetova] = noviCvijet;
	(*brojCvjetova)++;

	printf("Cvijet dodan u skladiste.\n");
}

void ispisiSkladiste(const Cvijet* skladiste, int brojCvjetova) {
	if (!skladiste) {
		ERROR_MSG("Skladiste je NULL");
		return;
	}
	if (brojCvjetova == 0) {
		printf("Skladiste je prazno.\n");
		return;
	}

	printf("\n--- Skladiste cvijeca ---\n");
	for (int i = 0; i < brojCvjetova; i++) {
		printf("Naziv: %s, Cijena: %.2f, Vrsta: %s, Kolicina: %d\n",
			skladiste[i].naziv, skladiste[i].cijena, skladiste[i].vrsta, skladiste[i].kolicina);
	}
	printf("------------------------\n");
}

void prodajaCvijeca(Cvijet* skladiste, int brojCvjetova, Prodaja** prodaje, int* brojProdaja, int* kapacitetProdaja) {
	if (!skladiste || !prodaje || !brojProdaja || !kapacitetProdaja) {
		ERROR_MSG("Neispravan parametar u prodajaCvijeca");
		return;
	}
	if (*brojProdaja >= *kapacitetProdaja) {
		*kapacitetProdaja *= 2;
		Prodaja* temp = realloc(*prodaje, (*kapacitetProdaja) * sizeof(Prodaja));
		if (!temp) {
			ERROR_MSG("Neuspjelo alociranje memorije za prodaje!");
			return;
		}
		*prodaje = temp;
	}

	char naziv[50];
	int kolicina;
	char imeKupca[50];

	printf("Unesite naziv cvijeta koji želite kupiti: ");
	scanf("%49s", naziv);
	printf("Unesite kolicinu: ");
	scanf("%d", &kolicina);
	printf("Unesite ime kupca: ");
	scanf("%49s", imeKupca);

	for (int i = 0; i < brojCvjetova; i++) {
		if (strcmp(skladiste[i].naziv, naziv) == 0) {
			if (skladiste[i].kolicina >= kolicina) {
				float ukupnaCijena = kolicina * skladiste[i].cijena;
				skladiste[i].kolicina -= kolicina;

				Prodaja novaProdaja;
				strcpy(novaProdaja.imeKupca, imeKupca);
				strcpy(novaProdaja.nazivCvijeca, naziv);
				novaProdaja.kolicina = kolicina;
				novaProdaja.ukupnaCijena = ukupnaCijena;

				(*prodaje)[*brojProdaja] = novaProdaja;
				(*brojProdaja)++;

				printf("Prodaja uspjesna! Ukupna cijena: %.2f\n", ukupnaCijena);
				return;
			}
			else {
				printf("Nemamo dovoljno cvijeca na skladistu.\n");
				return;
			}
		}
	}
	printf("Cvijet nije pronaden u skladistu.\n");
}

void azurirajCvijet(Cvijet* skladiste, int brojCvjetova) {
	if (!skladiste) {
		ERROR_MSG("Skladiste je NULL u azurirajCvijet");
		return;
	}

	char naziv[50];
	printf("Unesite naziv cvijeta kojeg želite ažurirati: ");
	scanf("%49s", naziv);

	for (int i = 0; i < brojCvjetova; i++) {
		if (strcmp(skladiste[i].naziv, naziv) == 0) {
			printf("Unesite novu cijenu: ");
			scanf("%f", &skladiste[i].cijena);
			printf("Unesite novu kolicinu: ");
			scanf("%d", &skladiste[i].kolicina);
			printf("Podaci o cvijetu su azurirani.\n");
			return;
		}
	}
	printf("Cvijet nije pronaden.\n");
}

void obrisiCvijet(Cvijet** skladiste, int* brojCvjetova) {
	if (!skladiste || !*skladiste || !brojCvjetova) {
		ERROR_MSG("Neispravan parametar u obrisiCvijet");
		return;
	}

	char naziv[50];
	printf("Unesite naziv cvijeta kojeg zelite obrisati: ");
	scanf("%49s", naziv);

	int index = -1;
	for (int i = 0; i < *brojCvjetova; i++) {
		if (strcmp((*skladiste)[i].naziv, naziv) == 0) {
			index = i;
			break;
		}
	}

	if (index == -1) {
		printf("Cvijet nije pronaden.\n");
		return;
	}

	// Pomakni elemente lijevo da izbrišeš element
	for (int i = index; i < *brojCvjetova - 1; i++) {
		(*skladiste)[i] = (*skladiste)[i + 1];
	}
	(*brojCvjetova)--;

	printf("Cvijet je obrisan iz skladista.\n");
}

void spremiSkladisteUdatoteku(const Cvijet* skladiste, int brojCvjetova) {
	if (!skladiste) {
		ERROR_MSG("Skladiste je NULL u spremiSkladisteUdatoteku");
		return;
	}

	// Backup stare datoteke
	if (remove("skladiste.bak") != 0) {
		// Backup možda ne postoji, nije kritično
	}
	if (rename("skladiste.txt", "skladiste.bak") != 0) {
		// Ako nema stare datoteke, nije problem
	}

	FILE* file = fopen("skladiste.txt", "w");
	if (!file) {
		perror("Greska prilikom otvaranja datoteke");
		return;
	}

	for (int i = 0; i < brojCvjetova; i++) {
		fprintf(file, "%s %.2f %s %d\n", skladiste[i].naziv, skladiste[i].cijena, skladiste[i].vrsta, skladiste[i].kolicina);
	}

	fclose(file);
	printf("Skladiste je spremljeno u datoteku.\n");
}

void ucitajSkladisteIzdatoteke(Cvijet** skladiste, int* brojCvjetova, int* kapacitet) {
	if (!skladiste || !brojCvjetova || !kapacitet) {
		ERROR_MSG("Neispravan parametar u ucitajSkladisteIzdatoteke");
		return;
	}

	FILE* file = fopen("skladiste.txt", "r");
	if (!file) {
		printf("Datoteka skladiste.txt ne postoji. Kreiram novo skladiste.\n");
		*brojCvjetova = 0;
		*kapacitet = POCETNI_KAPACITET;
		*skladiste = malloc(*kapacitet * sizeof(Cvijet));
		if (!*skladiste) {
			ERROR_MSG("Neuspjelo alociranje memorije!");
			exit(1);
		}
		return;
	}

	*kapacitet = POCETNI_KAPACITET;
	*skladiste = malloc(*kapacitet * sizeof(Cvijet));
	if (!*skladiste) {
		ERROR_MSG("Neuspjelo alociranje memorije!");
		fclose(file);
		exit(1);
	}

	*brojCvjetova = 0;
	while (fscanf(file, "%49s %f %29s %d", (*skladiste)[*brojCvjetova].naziv, &(*skladiste)[*brojCvjetova].cijena, (*skladiste)[*brojCvjetova].vrsta, &(*skladiste)[*brojCvjetova].kolicina) == 4) {
		(*brojCvjetova)++;
		if (*brojCvjetova >= *kapacitet) {
			*kapacitet *= 2;
			Cvijet* temp = realloc(*skladiste, (*kapacitet) * sizeof(Cvijet));
			if (!temp) {
				ERROR_MSG("Neuspjelo alociranje memorije!");
				fclose(file);
				exit(1);
			}
			*skladiste = temp;
		}
	}

	fclose(file);
	printf("Skladiste je ucitano iz datoteke.\n");
}

void oslobodiMemoriju(Cvijet** skladiste, Prodaja** prodaje) {
	if (skladiste && *skladiste) {
		free(*skladiste);
		*skladiste = NULL;
	}
	if (prodaje && *prodaje) {
		free(*prodaje);
		*prodaje = NULL;
	}
}

static int usporediCvijet(const void* a, const void* b) {
	const Cvijet* cv1 = (const Cvijet*)a;
	const Cvijet* cv2 = (const Cvijet*)b;
	return strcmp(cv1->naziv, cv2->naziv);
}

Cvijet* pronadjiCvijet(const Cvijet* skladiste, int brojCvjetova, const char* naziv) {
	if (!skladiste || !naziv) return NULL;

	Cvijet key;
	strncpy(key.naziv, naziv, sizeof(key.naziv));
	key.naziv[sizeof(key.naziv) - 1] = '\0';

	return (Cvijet*)bsearch(&key, skladiste, brojCvjetova, sizeof(Cvijet), usporediCvijet);
}


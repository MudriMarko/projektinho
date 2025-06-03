#include "cvijece.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
	Cvijet* skladiste = NULL;
	Prodaja* prodaje = NULL;
	int brojCvjetova = 0, kapacitet = 0;
	int brojProdaja = 0, kapacitetProdaja = 10;

	ucitajSkladisteIzdatoteke(&skladiste, &brojCvjetova, &kapacitet);

	prodaje = malloc(kapacitetProdaja * sizeof(Prodaja));
	if (!prodaje) {
		ERROR_MSG("Neuspjelo alociranje memorije za prodaje!");
		oslobodiMemoriju(&skladiste, NULL);
		return 1;
	}

	Izbornik izbor;
	do {
		printf("\n--- Izbornik ---\n");
		printf("1. Dodaj cvijet\n");
		printf("2. Prikazi skladiste\n");
		printf("3. Prodaja cvijeca\n");
		printf("4. Azuriraj cvijet\n");
		printf("5. Obrisi cvijet\n");
		printf("6. Spremi skladiste\n");
		printf("7. Sortiraj skladiste\n");
		printf("0. Izlaz\n");
		printf("Unesite izbor: ");
		int tempIzbor;
		if (scanf("%d", &tempIzbor) != 1) {
			printf("Neispravan unos!\n");
			while (getchar() != '\n');
			continue;
		}
		izbor = (Izbornik)tempIzbor;

		switch (izbor) {
		case IZBOR_DODAJ:
			dodajCvijet(&skladiste, &brojCvjetova, &kapacitet);
			break;
		case IZBOR_ISPISI:
			ispisiSkladiste(skladiste, brojCvjetova);
			break;
		case IZBOR_PRODAJA:
			prodajaCvijeca(skladiste, brojCvjetova, &prodaje, &brojProdaja, &kapacitetProdaja);
			break;
		case IZBOR_AZURIRAJ:
			azurirajCvijet(skladiste, brojCvjetova);
			break;
		case IZBOR_BRISE:
			obrisiCvijet(&skladiste, &brojCvjetova);
			break;
		case IZBOR_SPREMI:
			spremiSkladisteUdatoteku(skladiste, brojCvjetova);
			break;
		case IZBOR_SORTIRAJ:
			qsort(skladiste, brojCvjetova, sizeof(Cvijet), usporediCvijet);
			printf("Skladiste je sortirano po nazivu.\n");
			break;
		case IZBOR_IZLAZ:
			printf("Izlaz iz programa.\n");
			break;
		default:
			printf("Nepoznat izbor, probajte ponovo.\n");
			break;
		}

	} while (izbor != IZBOR_IZLAZ);

	oslobodiMemoriju(&skladiste, &prodaje);
	return 0;
}

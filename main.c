#include "cvijece.h"

void main_menu(void) {
    int choice = 0;
    do {
        printf("\n--- Glavni izbornik ---\n");
        printf("1. Dodaj cvijet\n");
        printf("2. Prikaz cvjetova\n");
        printf("3. Ažuriraj cvijet\n");
        printf("4. Obrisi cvijet\n");
        printf("5. Sortiraj cvjetove\n");
        printf("6. Pretraži cvijet\n");
        printf("7. Kupi cvijeće\n");
        printf("8. Operacije na datotekama\n");
        printf("9. Izlaz\n");
        printf("Odaberite opciju: ");

        if (scanf("%d", &choice) != 1) {
            printf("Neispravan unos.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        switch (choice) {
        case MAIN_MENU_ADD:
            add_flower();
            break;
        case MAIN_MENU_LIST:
            list_flowers();
            break;
        case MAIN_MENU_UPDATE:
            update_flower();
            break;
        case MAIN_MENU_DELETE:
            delete_flower();
            break;
        case MAIN_MENU_SORT:
            sort_flowers();
            break;
        case MAIN_MENU_SEARCH:
            search_flowers();
            break;
        case MAIN_MENU_BUY:
            buy_flowers();
            break;
        case MAIN_MENU_FILE_OPS:
            file_ops_menu();
            break;
        case MAIN_MENU_EXIT:
            printf("Spremanje podataka...\n");
            if (save_flowers() == 0) {
                printf("Podaci su spremljeni.\n");
            }
            else {
                printf("Greška pri spremanju podataka!\n");
            }
            safe_free((void**)&flower_list);
            flower_count = 0;
            printf("Izlaz iz programa.\n");
            break;
        default:
            printf("Nevažeći odabir. Pokušajte ponovno.\n");
            break;
        }
    } while (choice != MAIN_MENU_EXIT);
}

int main(void) {
    if (load_flowers() != 0) {
        printf("Došlo je do problema pri učitavanju baze cvjetova.\n");
        flower_list = NULL;
        flower_count = 0;
    }
    else {
        printf("Baza cvjetova učitana. Broj cvjetova: %d\n", flower_count);
    }

    main_menu();

    return 0;
}

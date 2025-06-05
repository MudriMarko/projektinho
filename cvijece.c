#include "cvijece.h"

Flower* flower_list = NULL;
int flower_count = 0;

#define SAFE_FREE(p) do { if ((p) != NULL) { free(p); (p) = NULL; } } while(0)

void* safe_malloc(size_t size) {
    void* ptr = malloc(size);
    if (!ptr) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void* safe_realloc(void* ptr, size_t size) {
    void* new_ptr = realloc(ptr, size);
    if (!new_ptr) {
        perror("realloc failed");
        free(ptr);
        exit(EXIT_FAILURE);
    }
    return new_ptr;
}

void safe_free(void** ptr) {
    if (ptr && *ptr) {
        free(*ptr);
        *ptr = NULL;
    }
}

void clear_input_buffer(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void print_flower(const Flower* f) {
    if (!f) return;
    printf("ID: %d | Name: %s | Price: %.2f | ",
        f->Id, f->Name, f->Price);
    if (f->AttributeType == STOCK_QUANTITY)
        printf("Quantity: %d\n", f->Attribute.quantity);
    else
        printf("Weight: %.3f kg\n", f->Attribute.weight);
}

void add_flower(void) {
    flower_list = safe_realloc(flower_list, (flower_count + 1) * sizeof(Flower));
    Flower* f = &flower_list[flower_count];

    printf("Unesite ID cvijeta: ");
    if (scanf("%d", &f->Id) != 1) {
        printf("Neispravan unos.\n");
        clear_input_buffer();
        return;
    }

    clear_input_buffer();
    printf("Unesite ime cvijeta: ");
    fgets(f->Name, MAX_NAME_LENGTH, stdin);
    f->Name[strcspn(f->Name, "\n")] = 0;

    printf("Unesite cijenu cvijeta: ");
    if (scanf("%f", &f->Price) != 1) {
        printf("Neispravan unos.\n");
        clear_input_buffer();
        return;
    }

    printf("Odaberite tip atributa (1 - količina, 2 - težina): ");
    int attr_type;
    if (scanf("%d", &attr_type) != 1) {
        printf("Neispravan unos.\n");
        clear_input_buffer();
        return;
    }

    if (attr_type == 1) {
        f->AttributeType = STOCK_QUANTITY;
        printf("Unesite količinu cvijeća: ");
        if (scanf("%d", &f->Attribute.quantity) != 1) {
            printf("Neispravan unos.\n");
            clear_input_buffer();
            return;
        }
    }
    else if (attr_type == 2) {
        f->AttributeType = STOCK_WEIGHT;
        printf("Unesite težinu cvijeća (kg): ");
        if (scanf("%f", &f->Attribute.weight) != 1) {
            printf("Neispravan unos.\n");
            clear_input_buffer();
            return;
        }
    }
    else {
        printf("Neispravan tip atributa.\n");
        clear_input_buffer();
        return;
    }

    flower_count++;
    printf("Cvijet dodan.\n");
}

void list_flowers(void) {
    if (flower_count == 0) {
        printf("Nema unesenih cvjetova.\n");
        return;
    }
    for (int i = 0; i < flower_count; i++) {
        print_flower(&flower_list[i]);
    }
}

void update_flower(void) {
    if (flower_count == 0) {
        printf("Nema unesenih cvjetova.\n");
        return;
    }
    int id;
    printf("Unesite ID cvijeta koji želite ažurirati: ");
    if (scanf("%d", &id) != 1) {
        printf("Neispravan unos.\n");
        clear_input_buffer();
        return;
    }

    for (int i = 0; i < flower_count; i++) {
        if (flower_list[i].Id == id) {
            clear_input_buffer();
            printf("Unesite novo ime cvijeta: ");
            fgets(flower_list[i].Name, MAX_NAME_LENGTH, stdin);
            flower_list[i].Name[strcspn(flower_list[i].Name, "\n")] = 0;

            printf("Unesite novu cijenu: ");
            if (scanf("%f", &flower_list[i].Price) != 1) {
                printf("Neispravan unos.\n");
                clear_input_buffer();
                return;
            }

            printf("Odaberite tip atributa (1 - količina, 2 - težina): ");
            int attr_type;
            if (scanf("%d", &attr_type) != 1) {
                printf("Neispravan unos.\n");
                clear_input_buffer();
                return;
            }

            if (attr_type == 1) {
                flower_list[i].AttributeType = STOCK_QUANTITY;
                printf("Unesite količinu: ");
                if (scanf("%d", &flower_list[i].Attribute.quantity) != 1) {
                    printf("Neispravan unos.\n");
                    clear_input_buffer();
                    return;
                }
            }
            else if (attr_type == 2) {
                flower_list[i].AttributeType = STOCK_WEIGHT;
                printf("Unesite težinu (kg): ");
                if (scanf("%f", &flower_list[i].Attribute.weight) != 1) {
                    printf("Neispravan unos.\n");
                    clear_input_buffer();
                    return;
                }
            }
            else {
                printf("Nepravilan tip atributa.\n");
                clear_input_buffer();
                return;
            }
            printf("Cvijet ažuriran.\n");
            return;
        }
    }
    printf("Cvijet s tim ID-em nije pronađen.\n");
}

void delete_flower(void) {
    if (flower_count == 0) {
        printf("Nema unesenih cvjetova.\n");
        return;
    }
    int id;
    printf("Unesite ID cvijeta koji želite obrisati: ");
    if (scanf("%d", &id) != 1) {
        printf("Neispravan unos.\n");
        clear_input_buffer();
        return;
    }

    for (int i = 0; i < flower_count; i++) {
        if (flower_list[i].Id == id) {
            for (int j = i; j < flower_count - 1; j++) {
                flower_list[j] = flower_list[j + 1];
            }
            flower_count--;
            flower_list = safe_realloc(flower_list, flower_count * sizeof(Flower));
            printf("Cvijet obrisan.\n");
            return;
        }
    }
    printf("Cvijet s tim ID-em nije pronađen.\n");
}

int compare_by_id(const void* a, const void* b) {
    const Flower* f1 = (const Flower*)a;
    const Flower* f2 = (const Flower*)b;
    if (f1->Id < f2->Id) return -1;
    else if (f1->Id > f2->Id) return 1;
    else return 0;
}

int compare_by_price(const void* a, const void* b) {
    const Flower* f1 = (const Flower*)a;
    const Flower* f2 = (const Flower*)b;
    if (f1->Price < f2->Price) return -1;
    else if (f1->Price > f2->Price) return 1;
    else return 0;
}

void quicksort_recursive(void* base, int left, int right, int (*cmp)(const void*, const void*)) {
    if (left >= right) return;

    int i = left, j = right;
    Flower pivot = ((Flower*)base)[(left + right) / 2];

    while (i <= j) {
        while (cmp(&((Flower*)base)[i], &pivot) < 0) i++;
        while (cmp(&((Flower*)base)[j], &pivot) > 0) j--;
        if (i <= j) {
            Flower temp = ((Flower*)base)[i];
            ((Flower*)base)[i] = ((Flower*)base)[j];
            ((Flower*)base)[j] = temp;
            i++; j--;
        }
    }
    if (left < j) quicksort_recursive(base, left, j, cmp);
    if (i < right) quicksort_recursive(base, i, right, cmp);
}

void sort_flowers(void) {
    if (flower_count == 0) {
        printf("Nema cvjetova za sortiranje.\n");
        return;
    }

    printf("Sortiraj po:\n");
    printf("1. ID\n");
    printf("2. Cijena\n");
    int choice = 0;
    if (scanf("%d", &choice) != 1) {
        printf("Neispravan unos.\n");
        clear_input_buffer();
        return;
    }

    if (choice == 1) {
        qsort(flower_list, flower_count, sizeof(Flower), compare_by_id);
        printf("Sortirano po ID-u.\n");
    }
    else if (choice == 2) {
        qsort(flower_list, flower_count, sizeof(Flower), compare_by_price);
        printf("Sortirano po cijeni.\n");
    }
    else {
        printf("Nevažeći izbor.\n");
        clear_input_buffer();
    }
}

void search_flowers(void) {
    if (flower_count == 0) {
        printf("Nema cvjetova za pretraživanje.\n");
        return;
    }

    printf("Pretražuj po ID-u: ");
    int id;
    if (scanf("%d", &id) != 1) {
        printf("Neispravan unos.\n");
        clear_input_buffer();
        return;
    }

    qsort(flower_list, flower_count, sizeof(Flower), compare_by_id);

    Flower key;
    key.Id = id;
    Flower* found = (Flower*)bsearch(&key, flower_list, flower_count, sizeof(Flower), compare_by_id);
    if (found) {
        printf("Pronađen cvijet:\n");
        print_flower(found);
    }
    else {
        printf("Nema cvijeta s ID-em %d.\n", id);
    }
}

int copy_file(const char* src, const char* dest) {
    FILE* f_src = fopen(src, "rb");
    if (!f_src) {
        perror("Otvaranje izvornog fajla neuspjelo");
        return -1;
    }
    FILE* f_dest = fopen(dest, "wb");
    if (!f_dest) {
        perror("Otvaranje odredišnog fajla neuspjelo");
        fclose(f_src);
        return -1;
    }

    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), f_src)) > 0) {
        if (fwrite(buffer, 1, bytes, f_dest) != bytes) {
            perror("Greška pri pisanju u datoteku");
            fclose(f_src);
            fclose(f_dest);
            return -1;
        }
    }

    if (ferror(f_src)) {
        perror("Greška pri čitanju iz datoteke");
    }

    fclose(f_src);
    fclose(f_dest);
    return 0;
}

int load_flowers(void) {
    FILE* f = fopen(FILE_NAME, "rb");
    if (!f) {
        if (errno == ENOENT) {
            printf("Datoteka ne postoji, kreira se nova baza.\n");
            flower_list = NULL;
            flower_count = 0;
            return 0;
        }
        else {
            perror("Pogreška pri otvaranju datoteke");
            return -1;
        }
    }

    if (fseek(f, 0, SEEK_END) != 0) {
        perror("fseek neuspješan");
        fclose(f);
        return -1;
    }
    long size = ftell(f);
    if (size < 0) {
        perror("ftell neuspješan");
        fclose(f);
        return -1;
    }
    rewind(f);

    flower_count = (int)(size / sizeof(Flower));
    flower_list = safe_malloc(flower_count * sizeof(Flower));
    size_t read_count = fread(flower_list, sizeof(Flower), flower_count, f);

    if (read_count != (size_t)flower_count) {
        perror("fread nije pročitao ispravan broj zapisa");
        free(flower_list);
        flower_list = NULL;
        flower_count = 0;
        fclose(f);
        return -1;
    }

    fclose(f);
    return 0;
}

int save_flowers(void) {
    FILE* f = fopen(FILE_NAME, "wb");
    if (!f) {
        perror("Neuspješno otvaranje datoteke za pisanje");
        return -1;
    }

    size_t write_count = fwrite(flower_list, sizeof(Flower), flower_count, f);
    if (write_count != (size_t)flower_count) {
        perror("Greška pri pisanju u datoteku");
        fclose(f);
        return -1;
    }
    fclose(f);
    return 0;
}
void buy_flowers(void) {
    if (flower_count == 0) {
        printf("Nema cvijeća u skladištu.\n");
        return;
    }

    list_flowers();

    int id, quantity;
    float weight;

    printf("\nUnesite ID cvijeća koje želite kupiti: ");
    if (scanf("%d", &id) != 1) {
        printf("Neispravan unos ID-a.\n");
        clear_input_buffer();
        return;
    }

    Flower* flower = NULL;
    for (int i = 0; i < flower_count; i++) {
        if (flower_list[i].Id == id) {
            flower = &flower_list[i];
            break;
        }
    }

    if (flower == NULL) {
        printf("Cvijet s ID-om %d nije pronađen.\n", id);
        return;
    }

    if (flower->AttributeType == STOCK_QUANTITY) {
        printf("Trenutna količina: %d\n", flower->Attribute.quantity);
        printf("Unesite količinu koju želite kupiti: ");

        if (scanf("%d", &quantity) != 1) {
            printf("Neispravan unos količine.\n");
            clear_input_buffer();
            return;
        }

        if (quantity <= 0) {
            printf("Količina mora biti pozitivan broj.\n");
            return;
        }

        if (quantity > flower->Attribute.quantity) {
            printf("Nema dovoljno zaliha. Dostupno: %d\n", flower->Attribute.quantity);
            return;
        }

        flower->Attribute.quantity -= quantity;
        printf("Kupljeno %d komada cvijeća %s. Nova količina: %d\n",
            quantity, flower->Name, flower->Attribute.quantity);

        if (flower->Attribute.quantity == 0) {
            char choice;
            printf("Količina je sada 0. Želite li obrisati ovaj cvijet iz skladišta? (d/n): ");
            scanf(" %c", &choice);
            if (choice == 'd' || choice == 'D') {
                delete_flower_by_id(id);
            }
        }
    }
    else {
        printf("Trenutna težina: %.3f kg\n", flower->Attribute.weight);
        printf("Unesite težinu koju želite kupiti (kg): ");

        if (scanf("%f", &weight) != 1) {
            printf("Neispravan unos težine.\n");
            clear_input_buffer();
            return;
        }

        if (weight <= 0) {
            printf("Težina mora biti pozitivan broj.\n");
            return;
        }

        if (weight > flower->Attribute.weight) {
            printf("Nema dovoljno zaliha. Dostupno: %.3f kg\n", flower->Attribute.weight);
            return;
        }
        flower->Attribute.weight -= weight;
        printf("Kupljeno %.3f kg cvijeća %s. Nova težina: %.3f kg\n",
            weight, flower->Name, flower->Attribute.weight);

        if (flower->Attribute.weight <= 0.001f) { 
            char choice;
            printf("Težina je sada 0. Želite li obrisati ovaj cvijet iz skladišta? (d/n): ");
            scanf(" %c", &choice);
            if (choice == 'd' || choice == 'D') {
                delete_flower_by_id(id);
            }
        }
    }
}
void rename_file(const char* old_name, const char* new_name) {
    if (rename(old_name, new_name) == 0) {
        printf("Datoteka preimenovana s %s na %s.\n", old_name, new_name);
    }
    else {
        perror("Neuspjeh pri preimenovanju datoteke");
    }
}

void remove_file(const char* filename) {
    if (remove(filename) == 0) {
        printf("Datoteka %s obrisana.\n", filename);
    }
    else {
        perror("Neuspjeh pri brisanju datoteke");
    }
}
void delete_flower_by_id(int id) {
    for (int i = 0; i < flower_count; i++) {
        if (flower_list[i].Id == id) {
            for (int j = i; j < flower_count - 1; j++) {
                flower_list[j] = flower_list[j + 1];
            }
            flower_count--;
            flower_list = safe_realloc(flower_list, flower_count * sizeof(Flower));
            printf("Cvijet obrisan.\n");
            return;
        }
    }
    printf("Cvijet s ID-em %d nije pronađen.\n", id);
}

void file_ops_menu(void) {
    int choice = 0;
    char old_name[100], new_name[100];

    do {
        printf("\n--- Operacije na datotekama ---\n");
        printf("1. Preimenuj datoteku\n");
        printf("2. Kopiraj datoteku\n");
        printf("3. Obriši datoteku\n");
        printf("4. Povratak na glavni izbornik\n");
        printf("Odaberite opciju: ");

        if (scanf("%d", &choice) != 1) {
            printf("Neispravan unos, pokušajte ponovo.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        switch (choice) {
        case FILE_OPS_RENAME:
            printf("Unesite staro ime datoteke: ");
            fgets(old_name, sizeof(old_name), stdin);
            old_name[strcspn(old_name, "\n")] = 0;
            printf("Unesite novo ime datoteke: ");
            fgets(new_name, sizeof(new_name), stdin);
            new_name[strcspn(new_name, "\n")] = 0;
            rename_file(old_name, new_name);
            break;
        case FILE_OPS_COPY:
            printf("Unesite ime izvornog fajla: ");
            fgets(old_name, sizeof(old_name), stdin);
            old_name[strcspn(old_name, "\n")] = 0;
            printf("Unesite ime fajla kopije: ");
            fgets(new_name, sizeof(new_name), stdin);
            new_name[strcspn(new_name, "\n")] = 0;
            if (copy_file(old_name, new_name) == 0) {
                printf("Datoteka kopirana.\n");
            }
            break;
        case FILE_OPS_REMOVE:
            printf("Unesite ime datoteke za brisanje: ");
            fgets(old_name, sizeof(old_name), stdin);
            old_name[strcspn(old_name, "\n")] = 0;
            remove_file(old_name);
            break;
        case FILE_OPS_BACK:
            printf("Povratak na glavni izbornik...\n");
            break;
        default:
            printf("Neispravna opcija, pokušajte ponovno.\n");
            break;
        }
    } while (choice != FILE_OPS_BACK);
}

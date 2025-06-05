#ifndef CVIJECE_H
#define CVIJECE_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_NAME_LENGTH 50
#define FILE_NAME "cvijece.dat"

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

typedef union {
    int quantity;        
    float weight;         
} FlowerAttribute;

typedef struct {
    int Id;
    char Name[MAX_NAME_LENGTH];
    float Price;
    FlowerAttribute Attribute;
    enum { STOCK_QUANTITY, STOCK_WEIGHT } AttributeType;
} Flower;

typedef enum {
    MAIN_MENU_ADD = 1,
    MAIN_MENU_LIST,
    MAIN_MENU_UPDATE,
    MAIN_MENU_DELETE,
    MAIN_MENU_SORT,
    MAIN_MENU_SEARCH,
    MAIN_MENU_BUY,
    MAIN_MENU_FILE_OPS,
    MAIN_MENU_EXIT
} MainMenuOption;

typedef enum {
    FILE_OPS_RENAME = 1,
    FILE_OPS_COPY,
    FILE_OPS_REMOVE,
    FILE_OPS_BACK
} FileOpsOption;


extern Flower* flower_list;
extern int flower_count;

void add_flower(void);
void list_flowers(void);
void update_flower(void);
void delete_flower(void);
void sort_flowers(void);
void search_flowers(void);
int compare_by_id(const void* a, const void* b);
int compare_by_price(const void* a, const void* b);
void quicksort_recursive(void* base, int left, int right, int (*cmp)(const void*, const void*));
void print_flower(const Flower* f);
void clear_input_buffer(void);
int load_flowers(void);
int save_flowers(void);
int copy_file(const char* src, const char* dest);
void rename_file(const char* old_name, const char* new_name);
void remove_file(const char* filename);
void main_menu(void);
void file_ops_menu(void);
void* safe_malloc(size_t size);
void* safe_realloc(void* ptr, size_t size);
void safe_free(void** ptr);
void buy_flowers(void);
void delete_flower_by_id(int id);

#endif

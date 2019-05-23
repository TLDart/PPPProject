#ifndef STRUCTLOCAISPDIS_H_INCLUDED
#define STRUCTLOCAISPDIS_H_INCLUDED

#include "pdis.h"

struct local{
    char *name;
    int popularity;
    struct pdi_pointers *info;
    struct user_pointers *users_info;
    struct local *next;
};

struct local_pointers{
    struct local* info;
    struct local_pointers* next;

};


struct local* create_list_local(void);
struct local* load_local(struct PDI* pdi_head, struct local* local_head);
struct local* local_exists(struct local* head, char* name);
void searching_local(struct local* list, char* key, struct local** ant, struct local** actual);
int print_local_list(struct local *head);
void print_only_locals(struct local *head);
void parse_local(struct local* local_head, struct local_pointers* insert, char *name);
struct local_pointers* create_locals_pointers(void);
void print_local_pointers( struct local_pointers* locals);
void insert_popularity_local(struct local* head);
int count_local(struct local *head);
struct local** create_popularity_order(struct local* local_head, int size);
struct local** add_pointers_locals(struct local *local_head, int size);
void print_popularity_order(struct local** popularity_array,int size);
void bubble_sort_popularity_local(struct local** array,int n);
void print_local_and_pdi_pop(struct local** local_array_popularity, struct PDI** local_pdi_popularity, int local_size, int size_pdi);
void update_pdi_and_local_popularity(struct local **local_array_popularity,struct PDI** pdi_array_popularity,int local_nr, int pdi_nr, struct local* local_head, struct PDI* pdi_head);


#endif // STRUCTLOCAISPDIS_H_INCLUDED

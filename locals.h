#ifndef STRUCTLOCAISPDIS_H_INCLUDED
#define STRUCTLOCAISPDIS_H_INCLUDED

#include "pdis.h"

struct local{
    char *name;
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


#endif // STRUCTLOCAISPDIS_H_INCLUDED

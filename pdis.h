//
// Created by tld on 10/05/19.
//

#ifndef NEW_PROJECT_AND_THIS_TIME_IT_WILL_WORK____PDIS_H
#define NEW_PROJECT_AND_THIS_TIME_IT_WILL_WORK____PDIS_H

struct PDI{
    char *name;
    char *local;
    char *description;
    char *schedule;
    int popularity;
    struct user_pointers *users_info;
    struct PDI *next;
};

struct pdi_pointers{
    struct PDI* info;
    struct pdi_pointers* next;
};

struct PDI* create_list_pdi(void);
int load_pdi_data(struct PDI* head,char *path);
void searching_pdi(struct PDI* list, char* key, struct PDI** ant, struct PDI** actual);
void print_pdi_data(struct PDI* head);
void print_single_pdi(struct PDI* u);
struct PDI* pdi_exists(struct PDI* head, char* name);
void print_only_pdis(struct PDI *head);
struct pdi_pointers* create_pdi_pointers(void);
void parse_pdi(struct PDI* pdi_head, struct pdi_pointers* insert, char *name);
void tail_insert_pdi_pointers(struct pdi_pointers* head, struct PDI* pdi);
void print_pdi_pointers(struct pdi_pointers*);

struct PDI** add_pointers_pdi(struct PDI *pdi_head, int size);
void insert_popularity_pdi(struct PDI* head);
int count_pdi_number(struct PDI *head);
struct PDI** create_popularity_order_pdi(struct PDI* pdi_head, int size);
void print_popularity_order_pdi(struct PDI** popularity_array,int size);
void bubble_sort_popularity_pdi(struct PDI** array,int n);

void search_pdi_database(struct PDI* pdi_head);
#endif //NEW_PROJECT_AND_THIS_TIME_IT_WILL_WORK____PDIS_H

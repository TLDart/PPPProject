//
// Created by tld on 10/05/19.
//

#include "pdis.h"
#include "user.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct PDI* create_list_pdi(void){
    /* Creates a linked list for PDIs*/
    struct PDI* aux;
    aux = (struct PDI*) malloc(sizeof(struct PDI));
    if(aux != NULL){
        aux->next = NULL;
    }
    return aux;
}


void load_pdi_data(struct PDI* head,char *path) {
    /*Pre-loads pdi data from a file to a linked list */
    char buffer[250]; const char s[2] = "-"; char *token;
    struct PDI *new, *ant, *useless;
    FILE *fp;
    fp = fopen(path, "r");

    /*Check if fp exists*/
    if (fp == NULL)
        puts("Invalid File");
    else {
        while (fgets(buffer, 250, fp) != NULL) {
            new = malloc(sizeof(struct PDI));
            if (new != NULL) {
                token = strtok(buffer, s);
                new->name = malloc(strlen(token));
                strcpy(new->name, token);

                token = strtok(NULL, s);
                new->local = malloc(strlen(token));
                strcpy(new->local, token);

                token = strtok(NULL, s);
                new->description = malloc(strlen(token));
                strcpy(new->description, token);

                token = strtok(NULL, s);
                new->schedule = malloc(strlen(token));
                strcpy(new->schedule, token);

                new->users_info = create_user_pointers();

                searching_pdi(head, new->name, &ant, &useless);
                new->next = ant->next;
                ant->next = new;
            }
        }
        fclose(fp);
    }

}
void searching_pdi(struct PDI* list, char* key, struct PDI** ant, struct PDI** actual){
    /*Finds the correct position of the PDI (aka element before) in order correctly insert according to the key*/
    *ant = list; *actual = list->next;
    while ((*actual) != NULL && strcmp((*actual)->name,key) < 0)
    {
        *ant = *actual;
        *actual = (*actual)->next;
    }
    if ((*actual) != NULL && (*actual)->name != key)
        *actual = NULL; /* If the element was not found*/
}

void print_pdi_data(struct PDI* head){
    /*Prints PDi data*/
    struct PDI*u = head->next; /* Skips the header*/
    while(u){
        print_single_pdi(u);
        u = u->next;
    }
}
void print_single_pdi(struct PDI* u){
    /*Prints a single PDi*/
    {
        printf("\t\tName: %s\n"
               "\t\tLocal: %s\n"
               "\t\tDescription: %s \n"
               "\t\tSchedule: %s \n"
               "\t\tPopularity: %d", u->name, u->local, u->description, u->schedule, u->popularity);
        puts("");
    }
}
struct PDI* pdi_exists(struct PDI* head, char* name){
    /* s if there is a PDI {NAME}*/
    head = head->next; /* Ignore header*/
    if(head != NULL) {
        while (head != NULL) {
            if (strcmp(head->name, name) == 0) {
                return head;
            }
            head = head->next;
        }
    }
    return NULL;
}

void print_only_pdis(struct PDI *head){
    /*Prints only the PDI name*/
    head = head->next;
    printf("PDI's in the Database \n");
    while (head){
        printf("\t->%s\n",head ->name);
        head =head->next;
    }
}
/*------------------------------------------------------------------------------------------------------------------------------------*/
struct pdi_pointers* create_pdi_pointers(void){
    /* Creates a linked list for PDIs*/
    struct pdi_pointers* aux;
    aux = (struct pdi_pointers*) malloc(sizeof(struct PDI));
    if(aux != NULL){
        aux->next = NULL;
    }
    return aux;
}
void parse_pdi(struct PDI* pdi_head, struct pdi_pointers* insert, char *name){
    /*parses a given {PDIName} into a pdi_pointers linked lists and inserts in the end*/
    while(insert->next != NULL){
        insert = insert->next;
    }
    struct pdi_pointers* temp = malloc(sizeof(struct pdi_pointers));
    struct PDI* pdi = pdi_exists(pdi_head, name);
    if(pdi){
        temp->info = pdi;
        temp->next = NULL;
        insert->next = temp;

    }
    else{
        puts(name);
        puts("Error parsing PDI");
    }

}

void tail_insert_pdi_pointers(struct pdi_pointers* head, struct PDI* pdi){
    /*Inserts pdi to the end of PDI pointers*/
    struct pdi_pointers* new;
    if(head->next != NULL){
        head = head->next;
    }
    while(head->next != NULL){
        head = head->next;
    }
    new = malloc(sizeof(struct pdi_pointers));
    new->info = pdi;
    new->next = NULL;
    head->next = new;
}

void print_pdi_pointers(struct pdi_pointers* pdis){
    /*Prints a list of pdi pointers, or None if NULL*/
    pdis = pdis->next;
    while(pdis != NULL){
        if(pdis->info != NULL){
            printf("\t\t\t-> %s\n",pdis->info->name);
        }
        else{
            printf("\t\t\t-> None \n");
        }
        pdis = pdis->next;
    }
}
/*------------------------------------------------------------------------------------------------------------*/
void insert_popularity_pdi(struct PDI* head){
    /*Changes the popularity parameter for all  PDI's*/
    head = head->next;
    while(head){
        head->popularity = count_popularity(head->users_info);
        head = head->next;
    }
}
int count_pdi_number(struct PDI *head){
    /*Counts the number of locals on a local list*/
    int count=0;
    struct PDI *current = head->next;
    while(current){
        count++;
        current=current->next;
    }
    return count;
}

struct PDI** create_popularity_order_pdi(struct PDI* pdi_head, int size){
    /*Function that generates a sorted-by-popularity PDI array*/
    struct PDI** pdi_head_popularity = add_pointers_pdi(pdi_head, size);
    bubble_sort_popularity_pdi(pdi_head_popularity,size);
    //print_popularity_order_pdi(pdi_head_popularity,n);
    //printf("%d", n);
    return pdi_head_popularity;
}

struct PDI** add_pointers_pdi(struct PDI *pdi_head, int size){
    /* Returns an array with the PDI organized by popularity*/
    int i;
    pdi_head = pdi_head->next;
    struct PDI** pdi_head_popularity = (struct PDI**)malloc(size*sizeof(struct PDI*));;
    for (i=0;pdi_head;i++){
        pdi_head_popularity[i]=pdi_head;
        pdi_head=pdi_head->next;
    }
    return pdi_head_popularity;
}

void print_popularity_order_pdi(struct PDI** popularity_array,int size){
    /*Prints the PDI name alongside is popularity*/
    int i = 0;
    for(i = 0; i < size ; i++){
        printf("%s ->%d \n",popularity_array[i]->name,popularity_array[i]->popularity);
    }
}

void bubble_sort_popularity_pdi(struct PDI** array,int n){
    /*Bubble sorts the array of locals by popularity*/
    struct PDI * temp;
    int i, j;
        for (i = 0; i < n - 1; i++) {
            // Last i elements are already in place
            for (j = 0; j < n - i - 1; j++) {
                if (array[j]->popularity < array[j + 1]->popularity) {
                    temp = array[j + 1];
                    array[j + 1] = array[j];
                    array[j] = temp;
                }
            }
        }
}

void search_pdi_database(struct PDI* pdi_head){
    char buffer[50];
    struct PDI* temp;
    getchar();
    while(1){
        puts("Insert PDI name");
        fgets(buffer,50,stdin);
        if (strcmp(buffer, "\n") == 0){
            break;
        }
        else{
            buffer[strcspn(buffer, "\n")] = 0;
            temp = pdi_exists(pdi_head, buffer);
            if(temp != NULL){
                print_single_pdi(temp);
            }
            else{
                puts("There is no such PDI");
            }
        }
    }
}
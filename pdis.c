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
    char buffer[250]; const char s[2] = ","; char *token;
    struct PDI *new, *ant, *useless;
    FILE *fp;
    fp = fopen(path, "r");

    /*Check if fp exists*/
    if (fp == NULL)
        puts("Invalid File");


    while(fgets(buffer, 250, fp) != NULL){
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

            searching_pdi(head,new->name,&ant,&useless);
            new->next = ant->next;
            ant->next = new;
        }

    }
    fclose(fp);

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

int count_pdis(struct PDI *head,char *local){
    /*Runs through a PDI list and counts the number of PDI's from a certain local*/
    int count=0;
    head = head->next;
    while(head != NULL){
        if(strcmp(head->local,local) == 0){
            count++;
        }
        head = head->next;
    }
    return count;
}

void print_pdi_data(struct PDI* head){
    /*Prints PDi data*/
    struct PDI*u = head->next; /* Skips the header*/
    while(u)
    {
        printf("Name: %s\n"
               "Local: %s\n"
               "Description: %s \n"
               "Schedule: %s \n", u->name, u->local, u->description, u->schedule);
        puts("");

        u=u->next;
    }
}

void print_single_pdi(struct PDI* u){
    /*Prints a single PDi*/
    {
        printf("Name: %s\n"
               "Local: %s\n"
               "Description: %s \n"
               "Schedule: %s \n", u->name, u->local, u->description, u->schedule);
        puts("");
    }
}

struct PDI* pdi_exists(struct PDI* head, char* name){
    /* Check if there is a PDI {NAME}*/
    head = head->next; /* Ignore header*/
    if(head != NULL) {
        while (head != NULL) {
            //printf(" |||%s %s ||| \n",head->name, name );
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
    pdi_head = pdi_head->next; /*Skips header*/
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
        temp->info = NULL;
        temp->next = NULL;
        insert->next = temp;
    }

}

void tail_insert_pdi_pointers(struct pdi_pointers* head, struct PDI* pdi){
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
    pdis = pdis->next;
    while(pdis != NULL){
        if(pdis->info != NULL){
            printf("\t-> %s\n",pdis->info->name);
        }
        else{
            printf("\t-> None \n");
        }
        pdis = pdis->next;
    }
}
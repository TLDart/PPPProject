#include <stdio.h>
#include <stdlib.h>
#include "locals.h"
#include "pdis.h"
#include "user.h"
#include <string.h>
#define BUFFER_SIZE 50

/*Local*/

struct local* create_list_local(void){
    /* Creates a linked list for locals*/
    struct local* aux;
    aux = (struct local*) malloc(sizeof(struct local));
    if(aux != NULL){
        aux->next = NULL;
    }
    return aux;
}


struct local* load_local(struct PDI* pdi_head, struct local* local_head){
    /* Loads current local data into a linked list*/
    struct local* new_local, *local;
    struct local* ant, *useless;
    struct pdi_pointers* new;
    struct PDI* cpy_pdi = pdi_head->next; // Ignore header

    while(cpy_pdi != NULL){
        local = local_exists(local_head, cpy_pdi->local);
        /* If the local does not exist, we wanna create a new one*/
        if(!local){
            //Create the local and assign a name
            new_local = malloc(sizeof(struct local));
            new_local->name = malloc(strlen(cpy_pdi->local));
            strcpy(new_local->name, cpy_pdi->local);

            new_local->info = create_pdi_pointers();
            /*Insert the pdi in order*/

            new = malloc(sizeof(struct pdi_pointers));
            new->info = cpy_pdi;
            new_local->users_info = create_user_pointers();

            new->next = NULL;
            new_local->info->next = new;


            //puts(new->info->name);
            /*Insert the local in alpha order */
            searching_local(local_head, new_local->name, &ant, &useless);
            new_local->next = ant->next;
            ant->next = new_local;
        }
            /*If the local exists*/
        else{
            tail_insert_pdi_pointers(local->info, cpy_pdi);
            //puts(local->name);
            /*
            new = malloc(sizeof(struct pdi_pointers));
            new->info = cpy_pdi;
            new->next = NULL;
            //puts(new->info->name);
            searching_pdi_pointers(local->info, new->info->name, &ant1,&useless1);
            new->next = ant1->next;
            ant1->next = new;
            */
        }
        //print_local_list(local_head);
        cpy_pdi = cpy_pdi->next;
    }
}

struct local* local_exists(struct local* head, char* name){
    /* Check if there is a local {NAME}*/
    head = head->next; /* Ignore header*/
    if(head != NULL) { /* Fallback condition to suit the case where no local is empty*/
        //puts(head->name);
        while (head != NULL) {
            if (strcmp(head->name, name) == 0) {
                //printf(" |||%s %s ||| \n",head->name, name );
                return head;
            }
            head = head->next;
        }
    }
    return NULL;
}


void searching_local(struct local* list, char* key, struct local** ant, struct local** actual){
    /*Function that assist correct placing*/
    *ant = list; *actual = list->next;
    while ((*actual) != NULL && strcmp((*actual)->name,key) < 0)
    {
        *ant = *actual;
        *actual = (*actual)->next;
    }
    if ((*actual) != NULL && (*actual)->name != key)
        *actual = NULL; /* If the element was not found*/
}

int print_local_list(struct local *head){
    /*Prints local data*/
    head = head->next;
    while (head ){
        printf("->%s\n",head ->name);
        head->info = head->info->next;
        //puts("PDI's");
        //puts(head->info->info->name);
        while(head->info != NULL && head->info->info->name != NULL){
            printf("\t --->%s \n",head->info->info->name);
            head->info = head->info->next;
        }

        head =head ->next;
    }
    return 0;
}
void print_only_locals(struct local *head){
    head = head->next;
    printf("Locations in the Database \n");
    while (head){
        printf("->%s\n",head ->name);
        head =head->next;
    }
}

void parse_local(struct local* local_head, struct local_pointers* insert, char *name){
    while(insert->next != NULL){
        insert = insert->next;
    }
    struct local_pointers* temp = malloc(sizeof(struct local_pointers));
    struct local* local = local_exists(local_head, name);
    if(local){
        //puts(local->name);
        temp->info = local;
        temp->next = NULL;
        insert->next = temp;

    }
    else{
        temp->info = NULL;
        temp->next = NULL;
        insert->next = temp;
    }

}

struct local_pointers* create_locals_pointers(void){
    /* Creates a linked list for PDIs*/
    struct local_pointers* aux;
    aux = (struct local_pointers*) malloc(sizeof(struct PDI));
    if(aux != NULL){
        aux->next = NULL;
    }
    return aux;
}

void print_local_pointers(struct local_pointers * locals){
    locals = locals->next;
    while(locals != NULL){

        if(locals->info != NULL){
            printf("\t-> %s\n",locals->info->name);
        }
        else{
            printf("\t-> None \n");
        }
        locals = locals->next;
    }
}






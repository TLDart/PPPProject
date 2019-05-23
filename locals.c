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
            /*Insert the local in alpha order */
            searching_local(local_head, new_local->name, &ant, &useless);
            new_local->next = ant->next;
            ant->next = new_local;
        }
            /*If the local exists*/
        else{
            tail_insert_pdi_pointers(local->info, cpy_pdi);
        }
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
        print_pdi_pointers(head->info);
        head =head ->next;
    }
    return 0;
}

void print_only_locals(struct local *head){
    /*Function that prints only names of locals*/
    head = head->next;
    printf("Locations in the Database \n");
    while (head){
        printf("->%s ",head ->name);
        puts("");
        head =head->next;
    }
}

void parse_local(struct local* local_head, struct local_pointers* insert, char *name){
    /*Function that transform a char {LOCAL} into either a pointer to the corresponding local or NULL if None */
    while(insert->next != NULL){
        insert = insert->next;
    }
    struct local_pointers* temp = malloc(sizeof(struct local_pointers));
    struct local* local = local_exists(local_head, name);
    if(local)
        temp->info = local;
    else
        temp->info = NULL;

    temp->next = NULL;
    insert->next = temp;
}
/*-----------------------------------------------------------------------------------------------------------------------*/
struct local_pointers* create_locals_pointers(void){
    /* Creates a linked list for PDIs*/
    struct local_pointers* aux =(struct local_pointers*) malloc(sizeof(struct PDI));
    if(aux != NULL){
        aux->next = NULL;
    }
    return aux;
}

void print_local_pointers(struct local_pointers * locals){
    /*Runs though a local pointers and prints its content*/
    locals = locals->next;
    while(locals != NULL){
        if(locals->info != NULL){
            printf("\t\t\t-> %s\n",locals->info->name);
        }
        else{
            printf("\t\t\t-> None \n");
        }
        locals = locals->next;
    }
}

/*-----------------------------------------------------------------------------------------*/
void insert_popularity_local(struct local* head){
    /*Runs through all locals and insert their popularity parameter*/
    head = head->next;
    while(head){
        head->popularity = count_popularity(head->users_info);
        head = head->next;
    }
}


int count_local(struct local *head){
    /*Count the number of locals on a local list*/
    int count=0;
    struct local *current=head->next;
    while(current){
        count++;
        current=current->next;
    }
    return count;
}

struct local** create_popularity_order(struct local* local_head, int size){
    /*Main function that both creates and sorts local popularity array*/
    struct local** local_head_popularity = add_pointers_locals(local_head, size);
    bubble_sort_popularity_local(local_head_popularity,size);
    //print_popularity_order(local_head_popularity, n);
    return local_head_popularity;
    }

struct local** add_pointers_locals(struct local *local_head, int size){
    /*Add pointer to local to local array*/
    int i;
    local_head = local_head->next;
    struct local** local_head_popularity = (struct local**)malloc(size*sizeof(struct local*));;
    for (i=0;local_head;i++){
        local_head_popularity[i]=local_head;
        local_head=local_head->next;
    }
    return local_head_popularity;
}

void print_popularity_order(struct local** popularity_array,int size){
    /*Print locals array*/
    int i = 0;
    for(i = 0; i < size ; i++){
        printf("%s ->%d \n",popularity_array[i]->name,popularity_array[i]->popularity);
    }
}

void bubble_sort_popularity_local(struct local** array,int n){
    /*Bubble sorts the array of locals by popularity*/
    struct local * temp;
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
void print_local_and_pdi_pop(struct local** local_array_popularity, struct PDI** local_pdi_popularity, int local_size, int size_pdi){
    /*Prints a list with both locals PDI's organized by popularity*/
    int i = 0, j = 0;
    for(i = 0; i < local_size; i++){
        printf("-> %s: %d \n",local_array_popularity[i]->name,local_array_popularity[i]->popularity);
        for(j = 0; j < size_pdi; j++){
            if(strcmp(local_array_popularity[i]->name,local_pdi_popularity[j]->local) == 0){
                printf("\t---> %s : %d\n",local_pdi_popularity[j]->name, local_pdi_popularity[j]->popularity);
            }
        }
    }
}

void update_pdi_and_local_popularity(struct local **local_array_popularity,struct PDI** pdi_array_popularity,int local_nr, int pdi_nr, struct local* local_head, struct PDI* pdi_head){
    /*update both pdi and local popularity arrays, only works post Initizlization*/
    free(local_array_popularity);
    free(pdi_array_popularity);
    insert_popularity_pdi(pdi_head);
    insert_popularity_local(local_head);
    local_nr = count_local(local_head);
    pdi_nr = count_pdi_number(pdi_head);
    local_array_popularity = create_popularity_order(local_head, local_nr);
    pdi_array_popularity = create_popularity_order_pdi(pdi_head, pdi_nr);
}





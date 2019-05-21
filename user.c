#include "user.h"
#include "locals.h"
#include "pdis.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define BUFFER_SIZE 100

struct User* create_list(void){
    /* Creates a linked list for users*/
    struct User* aux;
    aux = (struct User*) malloc(sizeof(struct User));
    if(aux != NULL){
        aux->next = NULL;
    }
    return aux;
}

void load_user_data(struct User* head ,char *path, struct local* local_head, struct PDI* pdi_head) {
    /*Pre-loads user data from a file to a linked list */
    char buffer[250]; const char s[2] = ","; char *token;
    FILE *fp;
    int i = 0;
    struct User* tail;
    struct User* node;
    tail = head;
    fp = fopen(path, "r");
    /*Check if fp exists*/
    if (fp == NULL)
        puts("Invalid File");

    while(fgets(buffer, 350, fp) != NULL){
        node = (struct User*) malloc (sizeof (struct User));
        if (node != NULL) {
            token = strtok(buffer, s);
            node->username = malloc(strlen(token) * sizeof(char));
            strcpy(node->username, token);

            token = strtok(NULL, s);
            node->password = malloc(strlen(token) * sizeof(char));
            strcpy(node->password, token);

            token = strtok(NULL, s);
            node->name = malloc(strlen(token) * sizeof(char));
            strcpy(node->name, token);

            token = strtok(NULL, s);
            node->address = malloc(strlen(token) * sizeof(char));
            strcpy(node->address, token);

            /*--------------------------*/
            node->bdate = malloc(sizeof(struct date));
            token = strtok(NULL, s);
            node->bdate->day =(atoi(token));

            token = strtok(NULL, s);
            node->bdate->month =(atoi(token));

            token = strtok(NULL, s);
            node->bdate->year =(atoi(token));
            /*----------------------------------------*/
            token = strtok(NULL, s);
            node->phone_nr = malloc(strlen(token) * sizeof(char));
            strcpy(node->phone_nr, token);

            node->locals = create_locals_pointers();
            for(i = 0; i < 3; i++){
                token = strtok(NULL, s);
                parse_local(local_head,node->locals,token);
            }
            token = strtok(NULL, s);
            node->hot = malloc(strlen(token) * sizeof(char));
            strcpy(node->hot, token);
            node->hot[strcspn(node->hot, "\n")] = 0;

            token = strtok(NULL, s);
            node->pdis = create_pdi_pointers();
            while(token){
                token[strcspn(token, "\n")] = 0;
                parse_pdi(pdi_head, node->pdis, token);
                token = strtok(NULL, s);
            }
            /*----------------------*/
            tail->next = node;
            node->next = NULL;
            tail = tail->next;
        }
    }
}

void print_single_user(struct User* user){
    printf("1) Username: %s\n"
           "2) Password: %s\n"
           "3) Name: %s \n"
           "4) Address: %s \n"
           "5) Birth Date : %d-%d-%d \n"
           "6) Phone Number: %s \n"
           "7) Hot-PDI : %s\n"
           "8) Favorite Places \n", user->username, user->password, user->name, user->address,user->bdate->day,user->bdate->month,user->bdate->year,user->phone_nr, user->hot);
    print_local_pointers(user->locals);
    printf("9) Favorite PDI's:\n");
    print_pdi_pointers(user->pdis);
    puts("");
}

int get_option(){
    /*Gets an option*/
    int option, result, counter = 0;
    do{
        result = scanf("%d", &option);
        counter++;
        if(result != 1){ getchar(); if (counter < 2)puts("Invalid Option");}
    }
    while(result == 0);
    return option;
}

struct User* validate_login(struct User* head, char* username, char* password){
    /*This function evaluates if either the login is valid returns 1, or it is not return -1 */
    struct User* u = head->next;
    while (u)
    {
        if(strcmp(u->username,username) == 0 && strcmp(u->password,password)== 0)
            return u;
        u=u->next;
    }
    return NULL;
}
void edit_personal_info(struct User *user_head, struct User *user, struct local* local_head, struct PDI* pdi_head){
    /*This function lets the user change the default settings */
    char option;int number;
    char buffer[BUFFER_SIZE];
    /* Prompts user to change his info */
    while(1){
        print_single_user(user);
        puts("0) Exit");
        option = get_option();
        if (option == 0) {
            break;
        }
        if (option ==1){
            getchar();
            puts(" You can't change you username");
        }
        if (option == 2) {
            getchar();
            while (1) {
                printf("(No whitespace)Password: ");
                fgets(buffer, BUFFER_SIZE, stdin);
                buffer[strcspn(buffer, "\n")] = 0;
                if (check_space(buffer) && !contains_special(buffer) && strcmp(buffer,"") != 0) {
                    free(user->password);
                    user->password = malloc(strlen(buffer) * sizeof(char));
                    strcpy(user->password, buffer);
                    break;
                }
                else
                    puts("Invalid password");
                memset(buffer,0,strlen(buffer));
            }
        }
        if (option == 3) {
            getchar();
            while(1){
                printf("Name: ");
                fgets(buffer, BUFFER_SIZE, stdin);
                buffer[strcspn(buffer, "\n")] = 0;
                if(!contains_special(buffer) && strcmp(buffer,"") != 0) {
                    free(user->name);
                    user->name = malloc(strlen(buffer) * sizeof(char));
                    strcpy(user->name, buffer);
                    break;
                }
                else
                    puts("Invalid Name");
                memset(buffer, 0, strlen(buffer));
            }
        }
        if (option == 4){
            getchar();
            while(1){
            printf("Address: ");
            fgets(buffer,BUFFER_SIZE, stdin);
            buffer[strcspn(buffer, "\n")] = 0;
            if(!contains_special(buffer) && strcmp(buffer,"") != 0) {
                free(user->address);
                user->address = malloc(strlen(buffer)* sizeof(char));
                strcpy(user->address, buffer);
                break;
            }
            else
                puts("Invalid Address");
            memset(buffer,0,strlen(buffer));
            }
        }

        if (option ==5) {
            getchar();
            puts("Day/Month/Year:");
            while(1){
                do {
                    number = get_option();
                    if (number < 1 || number > 31)
                        puts("Invalid Number");
                } while (number < 1 || number > 31);
                user->bdate->day = number;
                do {
                    number = get_option();
                    if (number < 1 || number > 12)
                        puts("Invalid Number");
                } while (number < 1 || number > 12);
                user->bdate->month = number;
                do {
                    number = get_option();
                    if (number < 1900 || number > 2010)
                        puts("Invalid Number");
                } while (number < 1900 || number > 2010);
                user->bdate->year = number;
                if (valid_date(user->bdate))
                    break;
                puts("There is no such day as that");
            }
        }
        if (option == 6){
            getchar();
            while(1){
            printf("Phone Number: ");
            fgets(buffer,BUFFER_SIZE, stdin);
            buffer[strcspn(buffer, "\n")] = 0;
            if (valid_number(buffer) && !contains_special(buffer) && strcmp(buffer, "") != 0) {
                free(user->phone_nr);
                user->phone_nr = malloc(strlen(buffer) * sizeof(char));
                strcpy(user->phone_nr, buffer);
                break;
            }
            else
                puts("Invalid Phone Number");
            memset(buffer, 0, strlen(buffer));
            }
        }
        if(option == 7){
            pdi_hot(user_head,user,pdi_head);
        }

        if(option == 8){
            change_locals(user,local_head);
        }

        if(option == 9){
            change_pdis(user, pdi_head);
        }
    }
    update_local_popularity(user_head,local_head);
    update_pdi_popularity(user_head,pdi_head);
}

int check_space(char *string) {
    /*Checks if the string contains whitespace */
    int i = 0;
    for (i = 0; string[i] != '\0'; i++) {
        if (*(string + i) == ' ') {
            return 0;
        }
    }
    return 1;
}

int contains_special(char* string){
    /*Checks if the string contains special characters, if so returns 1*/
    int i = 0;
    for(i = 0; string[i] != '\0'; i++) {
        if ((string[i] < 65 || string[i] > 90) && (string[i] < 94 || string[i] > 123) &&  string[i] !=' ' && (string[i] < 48 || string[i] > 57)) {
            return 1;
        }
    }
    return 0;

}

int valid_number(char *ph_nr){
    /*Checks if it is a valid phone number*/
    if(atoi(ph_nr) > 100000000  && atoi(ph_nr) < 1000000000){
        return 1;
    }
        return 0;
}
int valid_date(struct date* d){
    /*Verifies if there is actually a day corresponding the date the user has just input*/
    int year = 2020;
    if((d->month == 4 || d->month == 6 || d->month == 9 || d->month == 11) && (d->day > 30))
        return 0;
    while(year > d->year){
        year -= 4;
    }
    if(year != d->year){
        if(d->month == 2 && d->day > 28)
            return 0;
    }
    else{
        if(d->month == 2 && d->day > 29)
            return 0;
    }
    return 1;
}

int user_exists(struct User* head, char* string){
    head = head->next;
    while(head){
        if(strcmp(head->name, string) == 0){
            return 1;
        }
        head = head->next;
    }
    return 0;
}
void write_out(char* path, struct User* head){
    int i = 0;
    FILE *fp;
    struct local_pointers* temp;
    struct pdi_pointers* pdis;
    fp = fopen(path, "w+");
    head = head->next; /* Jumps header */
    while (head != NULL){
        temp = head->locals->next;
        pdis = head->pdis->next;
        fprintf(fp,"%s,%s,%s,%s,%d,%d,%d,%s", head->username,head->password,head->name, head->address, head->bdate->day,head->bdate->month,head->bdate->year, head->phone_nr);
        for(i = 0; i < 3; i++) {
            fprintf(fp,",");
            if (temp->info == NULL)
                fprintf(fp, "None");
            else
                fprintf(fp, temp->info->name);
            temp = temp->next;
        }
        fprintf(fp,",");
        fprintf(fp,head->hot);
        while(pdis){
            fprintf(fp,",");
            fprintf(fp,pdis->info->name);
            pdis = pdis->next;
        }
        fprintf(fp,"\n");
        head = head->next;
    }
    fclose(fp);
}

void registration(struct User* head, struct local* local_head) {
    /* This function is able to register the current user into the database system */
    int number, i = 0;
    struct User *new = malloc(sizeof(struct User));
    char buffer[BUFFER_SIZE];
    getchar();
    /*Get user Input*/
    while (1) {
        printf("(No whitespace)Username: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0; /*Remove the trailing \n */
        if (check_space(buffer) && !user_exists(head, buffer) && !contains_special(buffer) && strcmp(buffer,"") != 0) {
            new->username = malloc(strlen(buffer) * sizeof(char));
            strcpy(new->username, buffer);
            break;
        }
        else
            puts("Username is invalid or already taken");
        memset(buffer,0,strlen(buffer));
    }
    while(1){
        printf("Name: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        if(!contains_special(buffer) && strcmp(buffer,"") != 0){
            new->name = malloc(strlen(buffer) * sizeof(char));
            strcpy(new->name, buffer);
            break;
        }
        else
            puts("Invalid Name");
        memset(buffer, 0, strlen(buffer));
    }

    while(1){
        printf("Address: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        if(!contains_special(buffer) && strcmp(buffer,"") != 0) {
            new->address = malloc(strlen(buffer) * sizeof(char));
            strcpy(new->address, buffer);
        break;
        }
        else
            puts("Invalid Address");
        memset(buffer, 0, strlen(buffer));
    }

    printf("Birth-date(Day/Month/Year): ");
    new->bdate = malloc(sizeof(struct date));
    while(1){
        do {
            number = get_option();
            if (number < 1 || number > 31)
                puts("Invalid Number");
        } while (number < 1 || number > 31);
        new->bdate->day = number;
        do {
            number = get_option();
            if (number < 1 || number > 12)
                puts("Invalid Number");
        } while (number < 1 || number > 12);
        new->bdate->month = number;
        do {
            number = get_option();
            if (number < 1900 || number > 2010)
                puts("Invalid Number");
        } while (number < 1900 || number > 2010);
        new->bdate->year = number;
        if (valid_date(new->bdate))
            break;
        puts("That date does not exist");
    }

    getchar();
    while(1){
        printf("Phone Number: ");
        fgets(buffer,BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        if (valid_number(buffer) && !contains_special(buffer) && strcmp(buffer,"") != 0){
            new->phone_nr = malloc(strlen(buffer) * sizeof(char));
            strcpy(new->phone_nr, buffer);

            break;

        }
        else
            puts("Invalid Phone Number");
        memset(buffer, 0, strlen(buffer));
    }


    while (1) {
        printf("(No whitespace)Password: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        if (check_space(buffer) && !contains_special(buffer) && strcmp(buffer,"") != 0) {
            new->password = malloc(strlen(buffer) * sizeof(char));
            strcpy(new->password, buffer);

            break;
        }
        else
            puts("Invalid Password");
        memset(buffer, 0, strlen(buffer));
    }

    new->locals = create_locals_pointers();
    for(i = 0; i < 3; i++){
        parse_local(local_head,new->locals,"None");
    }

    new->hot = malloc(strlen("None") * sizeof(char));
    strcpy(new->hot, "None");

    while (head->next != NULL) {
        /*Travel to the end of the list*/
        head = head->next;
    }
    new->pdis = create_pdi_pointers();
    new->next = NULL;
    head->next = new;
}

struct user_pointers* create_user_pointers(void){
    /* Creates a linked list for user_pointers*/
    struct user_pointers* aux;
    aux = (struct user_pointers*) malloc(sizeof(struct user_pointers));
    if(aux != NULL){
        aux->next = NULL;
    }
    return aux;
}

void update_local_popularity(struct User* u, struct local* local_head){
    /*Generates a linked list with all the users corresponding to locals*/
    local_head = local_head->next;
    while(local_head){
        reset_popularity(local_head->users_info);
        local_head->users_info = create_user_pointers();
        local_head = local_head->next;
    }
    u = u->next; /*Skip header*/
    while(u){
        update_locals_users_pointers(u->locals, u);
            u = u->next;
    }

}

void tail_insert_user_pointer(struct user_pointers* u, struct User* user){
    /*Inserts a user to the end of the user_pointers*/
    struct user_pointers* new = malloc(sizeof(struct user_pointers));
    while(u->next != NULL){
        u = u-> next;
    }
    new->user = user;
    new->next = NULL;
    u->next = new;
}



void update_locals_users_pointers(struct local_pointers* u, struct User* user){
    /*Have to use this in order not to modify inside content*/
    int i = 0;
    u = u->next;
    for(i = 0; i < 3; i++){
        if(u->info != NULL) {
            //puts(u->info->name);
            tail_insert_user_pointer(u->info->users_info, user);
        }
        u = u->next;
    }
}
/*-------------------------------------------------------------------------*/
void update_pdi_popularity(struct User* u, struct PDI* pdi_head){
    /*Generates a linked list with all the users corresponding to pdis*/
    pdi_head = pdi_head->next;
    while(pdi_head){
        reset_popularity(pdi_head->users_info);
        pdi_head->users_info = create_user_pointers();
        pdi_head = pdi_head->next;
    }
    u = u->next; /*Skip header*/
    while(u){
        update_pdi_users_pointers(u->pdis, u);
        u = u->next;
    }
}

void update_pdi_users_pointers(struct pdi_pointers* u, struct User* user) {
    /*Helps update pdi popularity (similar to lacal fucntions)*/
    int i = 0;
    if (u->next != NULL) {
        u = u->next;
        while (u)
            if (u->info != NULL) {
                //puts(u->info->name);
                tail_insert_user_pointer(u->info->users_info, user);
                u = u->next;
            }

    }
}
/*---------------------------------------------------------------------------------------*/

void change_locals(struct User *u, struct local* local_head) {
    /*Allows users to change favorite places*/
    int option;
    int valid = 0;
    char buffer[BUFFER_SIZE];
    while (1) {
        print_only_locals(local_head);
        print_user_locals(u->locals);
        printf("Choose an option, 0 to exit \n\t");
        option = get_option();
        if (option == 0 || option == 9) {
            break;
        }
        if (option == 1) {
            getchar();
            while (!valid) {
                printf("Choose Location or None: ");
                fgets(buffer, BUFFER_SIZE, stdin);
                buffer[strcspn(buffer, "\n")] = 0;
                valid = valid_local(local_head, u->locals->next,buffer); /* Verifies if the password contains a whitespace */
                memset(buffer, 0, strlen(buffer));
                if (valid == 0) {
                    printf("Invalid Local\n");
                }
            }
            break;
        }
        if (option == 2) {
            getchar();
            while (!valid) {
                printf("Choose Location or None: ");
                fgets(buffer, BUFFER_SIZE, stdin);
                buffer[strcspn(buffer, "\n")] = 0;
                valid = valid_local(local_head, u->locals->next->next,buffer); /* Verifies if the password contains a whitespace */
                memset(buffer, 0, strlen(buffer));
                if (valid == 0) {
                    printf("Invalid Local\n");
                }
            }
            break;
        }
        if (option == 3) {
            getchar();
            while (!valid) {
                printf("Choose Location or None: ");
                fgets(buffer, BUFFER_SIZE, stdin);
                buffer[strcspn(buffer, "\n")] = 0;
                valid = valid_local(local_head, u->locals->next->next->next,buffer); /* Verifies if the password contains a whitespace */
                memset(buffer, 0, strlen(buffer));
                if (valid == 0) {
                    printf("Invalid Local\n");
                }
            }
            break;
        }
    }
}

void print_user_locals(struct local_pointers* u){
    /*Prints Menu with user locals , either  {NAME} OR {NONE}*/
    int i = 0;
    u = u->next;
    for(i = 0; i < 3 ; i++){
        if(u->info == NULL)
            printf("\t%d) None\n",i + 1);
        else
            printf("\t%d) %s\n",i + 1, u->info->name);
        u = u->next;
    }
        printf("\t0) Exit\n");

}

int valid_local(struct local* local_head,struct local_pointers * current, char * name){
    /* Checks if the local is valid or the input is "None"*/
    struct local* local;
    if(strcmp(name, "None") == 0){
        current->info = NULL;
        return 1;
    }
    local = local_exists(local_head, name);
    if (local){
        current->info = local;
        return 1;
    }
    else{
        return 0;
    }
}

void reset_popularity(struct user_pointers* head){
    /*Goes through a linked list of popularity and frees it*/
    struct user_pointers* temp;
    while(head != NULL){
        temp = head;
        head = head->next;
        free(temp);
    }
}

/*--------------------------------------------------------------------------------------------*/

void change_pdis(struct User *u, struct PDI* pdi_head){
    /*Main function that allows users to change preferred pdis*/
    int option, running = 1;
    int valid = 0;
    char buffer[BUFFER_SIZE];
    while (running) {
        print_only_pdis(pdi_head);
        puts("");
        puts("Your Interest Points");
        print_pdi_pointers(u->pdis);

        puts("");
        puts("\t1) Add a PDI");
        puts("\t2) Remove a PDI");
        puts("\t0) Exit");

        option = get_option();
        if (option == 0 || option == 9) {
            running = 0;
        }
        if (option == 1) {
            getchar();
            while (!valid) {
                printf("Choose PDI: ");
                fgets(buffer, BUFFER_SIZE, stdin);
                buffer[strcspn(buffer, "\n")] = 0;
                valid = valid_pdi(pdi_head, u->pdis,buffer);
                memset(buffer, 0, strlen(buffer));
                if (valid == 0) {
                    printf("Invalid PDI\n");
                }
            }
        }
        valid = 0;
        if (option == 2) {
            getchar();
            while (!valid) {
                printf("Choose PDI: ");
                fgets(buffer, BUFFER_SIZE, stdin);
                buffer[strcspn(buffer, "\n")] = 0;
                valid = search_and_destroy_pdi(pdi_head, u->pdis,buffer);
                memset(buffer, 0, strlen(buffer));
                if (valid == 0) {
                    printf("Invalid Local\n");
                }
            }
        }
        valid = 0;
    }
}

int valid_pdi(struct PDI* pdi_head,struct pdi_pointers *insert_head, char * name) {
    /* Checks if the pdi exist, if so it tails inserts it*/
    struct PDI *pdi;
    pdi = pdi_exists(pdi_head, name);
    if (pdi) {
        tail_insert_pdi_pointers(insert_head, pdi);
        return 1;
    } else {
        return 0;
    }
}

int search_and_destroy_pdi(struct PDI* pdi_head,struct pdi_pointers *insert_head, char * name){
    /*Searches for a pdi in the favs_pdis and removes it*/
    struct PDI *pdi;
    pdi = pdi_exists(pdi_head, name);
    if (pdi) {
        remove_pdi(insert_head, pdi);
        return 1;
    } else {
        return 0;
    }

}

void remove_pdi(struct pdi_pointers* head, struct PDI* pdi){
    /*Searches for a specific PDI and removes it*/
    struct pdi_pointers *aux = head;
    int valid = 0;
    head = head->next;
    while(head != NULL){
        if(strcmp(pdi->name, head->info->name) == 0){
            aux->next = head->next;
            free(head);
            valid = 1;
            break;
        }
        aux = head;
        head = head->next;
    }
    if(!valid){
        puts("Valid PDI but not in the list");
    }
}


/*-------------------------------------------------------------------------------------------------*/

void pdi_hot(struct User* user_head, struct User* user, struct PDI* pdi_head) {
    /*Main menu to change Hot PDI*/
    char temp[BUFFER_SIZE];
    int option;
    print_only_pdis(pdi_head);
            do {
                printf("Choose your PDI: ");
                fgets(temp, BUFFER_SIZE, stdin);
                temp[strcspn(temp, "\n")] = 0;
                free(user->hot);
                user->hot = malloc(strlen(temp) * sizeof(char));
                strcpy(user->hot, temp);
            } while (!(pdi_exists(pdi_head, temp) != NULL || strcmp(temp, "None") == 0));

}
/*-------------------------------------------------------------------------------*/
int count_popularity(struct user_pointers* head){
    /*Counts the popularity of a given PDI / local, returns the popularity number*/
    int counter = 0;
    while(head){
        counter++;
        head = head->next;
    }
    return counter - 1;
}

void generate_trip(struct User * u, struct PDI* pdi_head, struct User* user_head, struct PDI** pdi_pop_array, int pdi_pop_array_size){
    /*Generates the desired trip for the user*/
    struct PDI** blockA, **blockB, **blockC;
    if(u->locals->next->info == NULL || u->locals->next->next->info == NULL || u->locals->next->next->next->info == NULL){
        puts("You need to input 3 places before you can generate a trip");
    }
    else{
        blockA = generate_per_local(pdi_head,u,u->locals->next->info, pdi_pop_array,pdi_pop_array_size);
        blockB = generate_per_local(pdi_head,u,u->locals->next->next->info, pdi_pop_array,pdi_pop_array_size);
        blockC = generate_per_local(pdi_head,u,u->locals->next->next->next->info,pdi_pop_array,pdi_pop_array_size);
        printf("Your trip is rated %.2lf%% according to our popularity tax calculator\n", popularity_tax_calculator(blockA, blockB, blockC, user_head, u, pdi_head));
    }
}

struct PDI ** generate_per_local(struct PDI* pdi_head,struct User *u,struct local* local, struct PDI** pdi_pop_array, int pdi_pop_array_size){
    /*Generates the pdi's per place, for 1 place*/
    struct PDI** array = malloc(3 * sizeof(struct PDI*));
    struct PDI* temp;
    printf("->%s\n", local->name);
    int counter = 0, i = 0;
    if(check_pdi_in_local(u->hot, local)){
        temp = pdi_exists(pdi_head,u->hot);
        printf("\t-->%s \n", u->hot);
        array[counter++] = temp;
    }
            for (i = 0; counter < 3 && i < (pdi_pop_array_size); i++) {
                if(strcmp(pdi_pop_array[i]->local, local->name) == 0 && pdi_in_user(u->pdis, pdi_pop_array[i]) && !check_array(array,counter,pdi_pop_array[i])){
                        printf("\t-->%s \n", pdi_pop_array[i]->name);
                        array[counter++] = pdi_pop_array[i];

                }
            }
        for (i = 0; counter < 3 && i < (pdi_pop_array_size ); i++) {
            if(strcmp(pdi_pop_array[i]->local, local->name) == 0 && !check_array(array,counter,pdi_pop_array[i])){
                printf("\t-->%s \n", pdi_pop_array[i]->name);
                array[counter++] = pdi_pop_array[i];
            }
        }
        return array;
}
int check_pdi_in_local(char *hot, struct local *local){
    /*Checks if hot pdi belongs to a local*/
    struct pdi_pointers* temp = local->info->next;
    while(temp){
        if(strcmp(hot,temp->info->name) == 0){
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

int pdi_in_user(struct pdi_pointers* user_pdis, struct PDI *pdi){
    /*Checks if a pdi belongs to a user */
    if(user_pdis->next == NULL)
        return 0;
    user_pdis = user_pdis->next;
    while(user_pdis){
        if(strcmp(user_pdis->info->name, pdi->name) == 0){
            return 1;
        }
        user_pdis = user_pdis->next;
    }
    return 0;
}

double popularity_tax_calculator(struct PDI** blockA, struct PDI** blockB,struct PDI** blockC,struct User* user_head,struct User* user, struct PDI* pdi_head){
    /*Calculates the popularity of a trip*/
    double valueA = 0, valueB = 0, valueC = 0, totalA = 0, totalB = 0, totalC = 0;
    int i = 0;
    totalA = count_users(user_head);
    totalB = totalA;
    totalC = total_popularity(pdi_head);
    valueA = user_local_selected(user_head, user->locals->next->info, user->locals->next->next->info, user->locals->next->next->next->info);
    for(i = 0; i < 3;i++){
        valueB += check_hot(user_head,blockA[i]) + check_hot(user_head,blockB[i]) + check_hot(user_head,blockC[i]);
        valueC += blockA[i]->popularity + blockB[i]->popularity + blockC[i]->popularity;
    }
    return ((valueA/totalA) * 0.33 + (valueB/totalB) * 0.33 + (valueC/totalC) * 0.33) *100;
}
int check_hot(struct User* user_head, struct PDI* pdi){
    /*Checks if a PDI is a user's hot for every user, returns the number of times that happens*/
    int value = 0;
    user_head = user_head->next;
    while(user_head){
        if(strcmp(user_head->hot, pdi->name) == 0){
            value++;
        }
        user_head = user_head->next;
    }
    return value;
}

int count_users(struct User* user_head){
    /*Counts the total number of users*/
    int counter = 0;
    user_head = user_head->next;
    while(user_head){
        counter++;
        user_head = user_head->next;
    }
    return counter;
}

int check_array(struct PDI** pdi_array, int size, struct PDI* pdi){
    /*Checks if the PDI already exists in the array. Returns 1 if true 0 if false*/
    int i = 0;
    for(i = 0; i < size; i++){
        if(strcmp(pdi_array[i]->name,pdi->name) ==0)
            return 1;
    }
    return 0;
}

int user_local_selected(struct User* user_head, struct local* localA, struct local* localB, struct local* localC){
    /*Checks every user if there is atleast one of LOCALA, LOCALB or LOCALC selected, returns teh number of times that happens*/
    user_head = user_head->next;
    int counter = 0, temp = 0;
    while(user_head){
        temp = 0;
        if(user_head->locals->next->info != NULL){
            if(strcmp(user_head->locals->next->info->name,localA->name)== 0 || strcmp(user_head->locals->next->info->name,localB->name)== 0 || strcmp(user_head->locals->next->info->name,localC->name)== 0)
                temp++;}
        if(user_head->locals->next->next->info != NULL){
            if(strcmp(user_head->locals->next->next->info->name,localA->name)== 0 || strcmp(user_head->locals->next->next->info->name,localB->name)== 0 || strcmp(user_head->locals->next->next->info->name,localC->name)== 0)
                temp++;}
        if(user_head->locals->next->next->next->info != NULL){
            if(strcmp(user_head->locals->next->next->next->info->name,localA->name)== 0 || strcmp(user_head->locals->next->next->next->info->name,localB->name)== 0 || strcmp(user_head->locals->next->next->next->info->name,localC->name)== 0)
                temp++;}
        if(temp > 0)
            counter++;
        user_head = user_head->next;
    }
    return counter;
}

int total_popularity(struct PDI* pdi_head){
    /*Returns de popularity of all PDI´s*/
    int count = 0;
    pdi_head = pdi_head->next;
    while(pdi_head){
        count += pdi_head->popularity;
        pdi_head = pdi_head->next;
    }
    return count;
}
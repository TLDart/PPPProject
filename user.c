//
// Created by tld on 20/04/19.
//
/*TODO: Load the remaining data
 * */
#include "user.h"
#include "locals.h"
#include "pdis.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define BUFFER_SIZE 100
#define PATH "/home/tld/Documents/New project and this time It will work :)/database2.txt"


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


    while(fgets(buffer, 250, fp) != NULL){
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

            token = strtok(NULL, s);
            node->birth_date = malloc(strlen(token) * sizeof(char));
            strcpy(node->birth_date, token);

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

void print_user_data(struct User* head){
    /*Prints user data for all users*/
    struct User* u = head->next; /* Salta o header */

    while (u)
    {
        printf("Username: %s\n"
               "Password: %s\n"
               "Name: %s \n"
               "Address: %s \n"
               "Birth Date : %s \n"
               "Phone Number: %s \n"
               "Hot-PDI : %s\n"
               "Favorite Places\n", u->username, u->password, u->name, u->address,u->birth_date,u->phone_nr, u->hot);
        print_local_pointers(u->locals);
        printf("Favorite PDI's:\n");
        print_pdi_pointers(u->pdis);
        puts("");
        u=u->next;
    }
}
void print_single_user(struct User* user){
    printf("1)Username: %s\n"
           "2)Password: %s\n"
           "3)Name: %s \n"
           "4)Address: %s \n"
           "5)Birth Date : %s \n"
           "6)Phone Number: %s \n"
           "7)Hot-PDI : %s\n"
           "8)Favorite Places \n", user->username, user->password, user->name, user->address,user->birth_date,user->phone_nr, user->hot);
    print_local_pointers(user->locals);
    printf("Favorite PDI's:\n");
    print_pdi_pointers(user->pdis);
    puts("");
}


int get_option(){
    /*Gets an option*/
    int option;
    scanf("%d", &option);
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
void edit_personal_info(struct User *head, struct User *user){
    /*This function lets the user change the default settings */
    char option;  int valid =0;
    char buffer[BUFFER_SIZE];

    /* Prompts user to change his info */
    while(1){
        print_single_user(user);
        printf("Select which one you want to change, 0 to exit \n");
        option = get_option();
        if (option == 0) {
            write_out(PATH, head);
            break;
        }
        if (option ==1){
            getchar();
            puts(" You can't change you username");
            //getchar();
        }
        if (option == 2) {
            getchar();
            while (!valid) {
                printf("(No whitespace)Password: ");
                fgets(buffer, BUFFER_SIZE, stdin);
                buffer[strcspn(buffer, "\n")] = 0;
                valid = check_if_valid(buffer); /* Verifies if the password contains a whitespace */
                free(user->password);
                user->password = malloc(strlen(buffer) * sizeof(char));
                strcpy(user->password, buffer);
                memset(buffer,0,strlen(buffer));
                if (valid == 0) {
                    printf("Invalid password");
                }
            }
        }
        if (option == 3) {
            getchar();
            printf("Name: ");
            fgets(buffer, BUFFER_SIZE, stdin);
            buffer[strcspn(buffer, "\n")] = 0;
            free(user->name);
            user->name = malloc(strlen(buffer)* sizeof(char));
            strcpy(user->name, buffer);
            memset(buffer,0,strlen(buffer));
        }
        if (option ==4){
            getchar();
            printf("Address: ");
            fgets(buffer,BUFFER_SIZE, stdin);
            buffer[strcspn(buffer, "\n")] = 0;
            free(user->address);
            user->address = malloc(strlen(buffer)* sizeof(char));
            strcpy(user->address, buffer);
            memset(buffer,0,strlen(buffer));

        }
        if (option ==5){
            getchar();
            printf("Birth-date: ");
            fgets(buffer,BUFFER_SIZE, stdin);
            buffer[strcspn(buffer, "\n")] = 0;
            free(user->birth_date);
            user->birth_date = malloc(strlen(buffer) * sizeof(char));
            strcpy(user->birth_date, buffer);
            memset(buffer,0,strlen(buffer));

        }
        if (option ==6){
            getchar();
            printf("Phone Number: ");
            fgets(buffer,BUFFER_SIZE, stdin);
            buffer[strcspn(buffer, "\n")] = 0;
            free(user->phone_nr);
            user->phone_nr = malloc(strlen(buffer) * sizeof(char));
            strcpy(user->phone_nr, buffer);
            memset(buffer,0,strlen(buffer));
        }
        valid = 0;
    }
}

int check_if_valid(char *string) {
    /*Checks if the string contains whitespace */
    int i = 0;
    for (i = 0; string[i] != '\0'; i++) {
        if (*(string + i) == ' ') {
            return 0;
        }
    }

    return 1;
}

void write_out(char* path, struct User* head){
    FILE *fp;
    fp = fopen(path, "w+");
    char * locals, *pdis;
    head = head->next; /* Jumps header */
    while (head != NULL){
        locals = generate_locals(head->locals);
        pdis = generate_pdis(head->pdis);
        fprintf(fp,"%s,%s,%s,%s,%s,%s,%s,%s%s\n", head->username,head->password,head->name, head->address, head->birth_date, head->phone_nr, locals,head->hot, pdis);
        //printf("%s,%s,%s,%s,%s,%s,%s,%s%s\n", head->username,head->password,head->name, head->address, head->birth_date, head->phone_nr, locals,head->hot, pdis);
        head = head->next;
        free(locals);
        free(pdis);
    }
    fclose(fp);
}

char *generate_locals(struct local_pointers* local){
    /*Generates the string with all the locals*/
    int i = 0;
    char string[200], *temp;
    memset(string,0,strlen(string));
    local = local->next; /*Skip Header*/
    for(i = 0; i < 3; i++){
        if(local->info == NULL){
            if( i == 2 ) {
                strcat(string, "None");
            }
            else
                strcat(string, "None,");
        }
        else{
            if( i ==2 ){
            temp = malloc((strlen(local->info->name) * sizeof(char)));
            strcpy(temp,local->info->name);
            }
            else {
                temp = malloc((strlen(local->info->name) + 1) * sizeof(char));
                strcpy(temp,local->info->name);
                strcat(temp, ",");
            }
            strcat(string,temp);
            free(temp);
        }
        local = local->next;
    }
    //puts(string);
    temp = malloc(strlen(string) * sizeof(char));
    strcpy(temp, string);
    return temp;
}

char* generate_pdis(struct pdi_pointers* pdis){
    /*Helps write-out -> Generates a string with all user pdis */
    char string[200], *temp;
    memset(string,0,strlen(string));
    if(pdis->next == NULL) {
        temp = malloc(0);
        return temp;
    }
    else{
        pdis = pdis->next; /*Skip Header*/
    }
    while(pdis){
        if(pdis->next == NULL) {
            temp = malloc((strlen(pdis->info->name)) * sizeof(char));
            strcpy(temp, pdis->info->name);
        }
        else{
            temp = malloc((strlen(pdis->info->name) + 1) * sizeof(char));
            strcpy(temp, pdis->info->name);
            strcat(temp,",");
        }
        strcat(string,temp);
        free(temp);
        pdis = pdis->next;
    }
    temp = malloc((strlen(string) + 1) * sizeof(char));
    strcat(temp,",");
    strcat(temp, string);
    return temp;
}

void registration(struct User* head, struct local* local_head) {
    /* This function is able to register the current user into the database system */
    struct User *new = malloc(sizeof(struct User));
    char buffer[BUFFER_SIZE];
    int valid = 0, i = 0;
    while (head->next != NULL) {
        /*travel to the end of the list*/
        head = head->next;
    }
    getchar();
    /*Get user Input*/
    while (!valid) {
        printf("(No whitespace)Username: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0; /*Remove the trailing \n */
        new->username = malloc(strlen(buffer) * sizeof(char));
        strcpy(new->username, buffer);
        valid = check_if_valid(new->username); /* Verifies if the user contains a whitespace */
        if (valid == 0) {
            printf("Invalid username");
        }
    }
    valid = 0;

    printf("Name: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    free(new->name);
    new->name = malloc(strlen(buffer)* sizeof(char));
    strcpy(new->name, buffer);
    memset(buffer,0,strlen(buffer));

    printf("Address: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    free(new->address);
    new->address = malloc(strlen(buffer) * sizeof(char));
    strcpy(new->address, buffer);
    memset(buffer, 0, strlen(buffer));


    printf("Birth-date: ");
    fgets(buffer,BUFFER_SIZE, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    free(new->birth_date);
    new->birth_date = malloc(strlen(buffer) * sizeof(char));
    strcpy(new->birth_date, buffer);
    memset(buffer,0,strlen(buffer));


    printf("Phone Number: ");
    fgets(buffer,BUFFER_SIZE, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    free(new->phone_nr);
    new->phone_nr = malloc(strlen(buffer) * sizeof(char));
    strcpy(new->phone_nr, buffer);
    memset(buffer,0,strlen(buffer));


    while (!valid) {
        printf("(No whitespace)Password: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        valid = check_if_valid(buffer); /* Verifies if the password contains a whitespace */
        new->password = malloc(strlen(buffer) * sizeof(char));
        strcpy(new->password, buffer);
        memset(buffer, 0, strlen(buffer));
        if (valid == 0) {
            printf("Invalid password");
        }
    }

    new->locals = create_locals_pointers();
    for(i = 0; i < 3; i++){
        parse_local(local_head,new->locals,"None");
    }

    new->hot = malloc(strlen("None") * sizeof(char));
    strcpy(new->hot, "None");
    new->hot[strcspn(new->hot, "\n")] = 0;

    new->pdis = create_pdi_pointers();
    new->next = NULL;
    head->next = new;
}

struct user_pointers* create_user_pointers(void){
    /* Creates a linked list for locals*/
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

void print_popularity_local(struct local* head){
    /*Prints which users have said preference by a locol*/
    head = head->next;
    while(head){
        head->users_info = head->users_info->next;
        while(head->users_info != NULL){
            printf("%s: %s \n",head->name,head->users_info->user->name);
            head->users_info = head->users_info->next;
        }
        head = head->next;
    }
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
    /*Generates a linked list with all the users corresponding to locals*/
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
    /*Have to use this in order not to modify inside content*/
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

void print_popularity_pdi(struct PDI* head){
    /*Prints user which have fovorite PDI's*/
    head = head->next;
    while(head){
        head->users_info = head->users_info->next;
        while(head->users_info != NULL){
            printf("%s: %s \n",head->name,head->users_info->user->name);
            head->users_info = head->users_info->next;
        }
        head = head->next;
    }
}

/*---------------------------------------------------------------------------------------*/

void change_locals(struct User *u, struct local* local_head) {
    /*Allows users to change favorite places*/
    /*TODO fix a stingy bug where after you do the first choice u can't choose anything else*/
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
                printf("Choose Location or None or None: ");
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
    struct user_pointers* temp;
    while(head != NULL){
        temp = head;
        head = head->next;
        free(temp);
    }
}

/*--------------------------------------------------------------------------------------------*/

void change_pdis(struct User *u, struct PDI* pdi_head){
    /*Main function that allows users to change preferredd pdis*/
    int option;
    int valid = 0;
    char buffer[BUFFER_SIZE];
    while (1) {
        print_only_pdis(pdi_head);
        puts("");
        puts("Your Interest Points");
        print_pdi_pointers(u->pdis);

        puts("");
        puts("\t1) Add a PDI");
        puts("\t2) Remove a PDI");


        printf("Choose an option, 0 to exit \n\t");
        option = get_option();
        if (option == 0 || option == 9) {
            break;
        }
        if (option == 1) {
            getchar();
            while (!valid) {

                printf("Choose PDI: ");
                fgets(buffer, BUFFER_SIZE, stdin);
                buffer[strcspn(buffer, "\n")] = 0;
                valid = valid_pdi(pdi_head, u->pdis,buffer); /* Verifies if the password contains a whitespace */
                memset(buffer, 0, strlen(buffer));
                if (valid == 0) {
                    printf("Invalid PDI\n");
                }
            }
        }
        if (option == 2) {
            getchar();
            while (!valid) {
                printf("Choose PDI: ");
                fgets(buffer, BUFFER_SIZE, stdin);
                buffer[strcspn(buffer, "\n")] = 0;
                valid = search_and_destroy_pdi(pdi_head, u->pdis,buffer); /* Verifies if the password contains a whitespace */
                memset(buffer, 0, strlen(buffer));
                if (valid == 0) {
                    printf("Invalid Local\n");
                }
            }
        }

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
    /*Changes Location Preferences*/
    char temp[BUFFER_SIZE];
    int option;
    print_only_pdis(pdi_head);
    while (1) {
        printf("\tYour Favorite PDI: \n"
               "\t1) %s \n"
               "\t0) Exit\n",user->hot);
        option = get_option();
        if (option == 0 || option == 9){
            break;
        }
        if (option == 1) {
            getchar();
            do {
                printf("Choose your PDI: ");
                fgets(temp, BUFFER_SIZE, stdin);
                temp[strcspn(temp, "\n")] = 0;
                free(user->hot);
                user->hot = malloc(strlen(temp) * sizeof(char));
                strcpy(user->hot, temp);
            } while (!(pdi_exists(pdi_head, temp) != NULL || strcmp(temp, "None") == 0));

        }
    }
}

//
// Created by tld on 20/04/19.
//
/*TODO: Load the remaining data
 * */

#include "user.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define BUFFER_SIZE 50
#define PATH "/home/tld/Documents/University/2 Semestre/PPP/Exercise Files/Project Test/Db/database.txt"

struct User* create_list(void){
    /* Creates a linked list for users*/
    struct User* aux;
    aux = (struct User*) malloc(sizeof(struct User));
    if(aux != NULL){
        aux->next = NULL;
    }
    return aux;
}

struct User* insert_user(struct User* tail, char *username, char *password, char* name, char* address, char* birth_date, char* phone_nr){
    /*Creates a new struct and inserts it to the end of the list*/
    struct User * node;
    node = (struct User*) malloc (sizeof (struct User));
    if (node != NULL) {
        /*Load the data*/
        node->username = malloc(strlen(username) * sizeof(char));
        strcpy(node->username,username);

        node->password = malloc(strlen(password) * sizeof(char));
        strcpy(node->password,password);

        node->name = malloc(strlen(name) * sizeof(char));
        strcpy(node->name,name);

        node->address = malloc(strlen(address) * sizeof(char));
        strcpy(node->address,address);

        node->birth_date = malloc(strlen(birth_date) * sizeof(char));
        strcpy(node->birth_date,birth_date);

        node->phone_nr = malloc(strlen(phone_nr) * sizeof(char));
        strcpy(node->phone_nr,phone_nr);

        /*--------------*/
        tail->next = node;
        node->next = NULL;
    }
    return node;
}

void print_user_data(struct User* head){
    struct User* u = head->next; /* Salta o header */
    while (u)
    {
        printf("Username: %s\n"
               "Password: %s\n"
               "Name: %s \n"
               "Address: %s \n"
               "Birth Date : %s \n"
               "Phone Number: %s \n", u->username, u->password, u->name, u->address,u->birth_date,u->phone_nr);
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
           "6)Phone Number: %s \n", user->username, user->password, user->name, user->address,user->birth_date,user->phone_nr);
    puts("");
}

int get_option(){
    int option;
    scanf("%d", &option);
    return option;
}

struct User* load_user_data(char *path) {
    /*Pre-loads user data from a file to a linked list */
    int i = 0;
    char buffer[250]; const char s[2] = ","; char *token;
    char password[BUFFER_SIZE], user[BUFFER_SIZE], username[BUFFER_SIZE], address[BUFFER_SIZE], birth_date[BUFFER_SIZE], phone_nr[BUFFER_SIZE];
    FILE *fp;
    struct User* head;
    struct User* tail;
    head = create_list();
    tail = head;
    fp = fopen(path, "r");

    /*Check if fp exists*/
    if (fp == NULL)
        puts("Invalid File");


    while(fgets(buffer, 250, fp) != NULL){
        token = strtok(buffer, s);
        strcpy(username, token);

        token = strtok(NULL, s);
        strcpy(password, token);

        token = strtok(NULL, s);
        strcpy(user, token);

        token = strtok(NULL, s);
        strcpy(address, token);

        token = strtok(NULL, s);
        strcpy(birth_date, token);

        token = strtok(NULL, s);
        strcpy(phone_nr, token);


        tail = insert_user(tail, username, password, user,address, birth_date,phone_nr);
    }
    return head;

}

int validate_login(struct User* head, char* username, char* password){
    /*This function evaluates if either the login is valid returns 1, or it is not return -1 */
    struct User* u = head->next;
    while (u)
    {
        if(strcmp(u->username,username) == 0 && strcmp(u->password,password)== 0)
            return 1;
        u=u->next;
    }
    return -1;
}

int registration(struct User* head){
    /* This function is able to register the current user into the database system */
    char password[BUFFER_SIZE], user[BUFFER_SIZE], username[BUFFER_SIZE], address[BUFFER_SIZE], birth_date[BUFFER_SIZE], phone_nr[BUFFER_SIZE];
    int valid = 0;
    while(head->next != NULL){
        /*travel to the end of the list*/
        head = head->next;
    }
    getchar();
    /*Get user Input*/
    while(!valid){
        printf("(No whitespace)Username: ");
        fgets(username,BUFFER_SIZE, stdin);
        username[strcspn(username, "\n")] = 0; /*Remove the trailing \n */
        valid = check_if_valid(username); /* Verifies if the user contains a whitespace */
        if(valid == 0){
            printf("Invalid username");
        }
    }
    valid = 0;
    printf("Name: ");
    fgets(user,BUFFER_SIZE, stdin);
    user[strcspn(user, "\n")] = 0;

    printf("Address: ");
    fgets(address,BUFFER_SIZE, stdin);
    address[strcspn(address, "\n")] = 0;

    printf("Birth-date: ");
    fgets(birth_date,BUFFER_SIZE, stdin);
    birth_date[strcspn(birth_date, "\n")] = 0;

    printf("Phone number: ");
    fgets(phone_nr,BUFFER_SIZE, stdin);
    phone_nr[strcspn(phone_nr, "\n")] = 0;

    while(!valid){
        printf("(No whitespace)Password: ");
        fgets(password,BUFFER_SIZE, stdin);
        password[strcspn(password, "\n")] = 0;
        valid = check_if_valid(password); /* Verifies if the password contains a whitespace */
        if(valid == 0){
            printf("Invalid password");
        }
    }
    insert_user(head,username,password,user, address, birth_date, phone_nr);
}


int check_if_valid(char *string) {
    /*Checks if the string contains whitespace */
    int i = 0;
    for (i = 0; string[i] != '\0'; i++) {
        if (*(string + i) == ' ') {
            return 0;
        }
    }
    /*Checks if the is another user with the same username
     * ...*/

    return 1;
}

void edit_personal_info(struct User *head, char *username){
    /*This function lets the user change the default settings */
    char option;  int valid =0;
    struct User* user;
    user = head;
    user = user->next;
    while(strcmp(user->username, username) !=0 ){
        user = user->next;
    }



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
                fgets(user->password, BUFFER_SIZE, stdin);
                user->password[strcspn(user->password, "\n")] = 0;
                valid = check_if_valid(user->password); /* Verifies if the password contains a whitespace */
                if (valid == 0) {
                    printf("Invalid password");
                }
            }
        }
        if (option == 3) {
            getchar();
            printf("Name: ");
            fgets(user->name, BUFFER_SIZE, stdin);
            user->name[strcspn(user->name, "\n")] = 0;
        }
        if (option ==4){
            getchar();
            printf("Address: ");
            fgets(user->address,BUFFER_SIZE, stdin);
            user->address[strcspn(user->address, "\n")] = 0;

        }
        if (option ==5){
            getchar();
            printf("Birth-date: ");
            fgets(user->birth_date,BUFFER_SIZE, stdin);
            user->birth_date[strcspn(user->birth_date, "\n")] = 0;

        }
        if (option ==6){
            getchar();
            printf("Phone Number: ");
            fgets(user->phone_nr,BUFFER_SIZE, stdin);
            user->phone_nr[strcspn(user->phone_nr, "\n")] = 0;

        }

        valid = 0;
    }

}

void write_out(char* path, struct User* head){
    FILE *fp;
    fp = fopen(path, "w+");
    head = head->next; /* Jumps header */
    while (head != NULL){
        if (fprintf(fp,"%s,%s,%s,%s,%s,%s", head->username,head->password,head->name, head->address, head->birth_date, head->phone_nr) > 0)
            //printf("%s,%s,%s,%s,%s,%s", head->username,head->password,head->name, head->address, head->birth_date, head->phone_nr);
        head = head->next;
    }
    fclose(fp);
}

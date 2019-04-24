//
// Created by tld on 20/04/19.
//
/*TODO: Create a find_correct_line function that finds the correct line for the output,
 *  Correct the Duplication glitch in the change settings tabs
 *  Find a way to output the changed settings and disregard the line overlapping
 *  Work out a way to add location / Pdi setting to the user tab
 *  Modifications:
 *      -> Register: Use a buffer and malloc
 *      -> Change struct to acommodate malloc (User)
 *      -> Create a linked list system based on the user
 *      -> Change legacy functions to work with the new linked list system
 *      -> Create a write out Function to rewrite ( FULLY!) the database after changing the settings*/

#include "login.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define BUFFER_SIZE 25

int registration(){
    /* This function is able to register the current user into the database system */
    /*Check If the file exists */
    struct User user1;
    FILE *fp;
    fp = fopen("/home/tld/Documents/University/2 Semestre/PPP/Project work/Db/database.txt", "r");
    int valid = 0;
    if(fp == NULL){
        /* If the file does not exist, create one */
        fp = fopen("/home/tld/Documents/University/2 Semestre/PPP/Project work/Db/database.txt", "w");
        fclose(fp);
    }
    /*Get user Input*/
    getchar();
    while(!valid){
    printf("(No whitespace)Username: ");
    fgets(user1.username,BUFFER_SIZE, stdin);
    user1.username[strcspn(user1.username, "\n")] = 0; /*Remove the trailing \n */
    valid = check_if_valid(user1.username); /* Verifies if the user contains a whitespace */
    if(valid == 0){
        printf("Invalid username");
    }
    }
    valid = 0;

    printf("Name: ");
    fgets(user1.name,BUFFER_SIZE, stdin);
    user1.name[strcspn(user1.name, "\n")] = 0;

    printf("Adress: ");
    fgets(user1.address,BUFFER_SIZE, stdin);
    user1.address[strcspn(user1.address, "\n")] = 0;

    printf("Birthdate: ");
    fgets(user1.birthdate,BUFFER_SIZE, stdin);
    user1.birthdate[strcspn(user1.birthdate, "\n")] = 0;

    printf("Phone nr: ");
    scanf("%lu", &user1.phone_nr);
    getchar();

    while(!valid){
    printf("(No whitespace)Password: ");
    fgets(user1.password,BUFFER_SIZE, stdin);
    user1.password[strcspn(user1.password, "\n")] = 0;
    valid = check_if_valid(user1.password); /* Verifies if the password contains a whitespace */
        if(valid == 0){
            printf("Invalid password");
        }
    }

    fp = fopen("/home/tld/Documents/University/2 Semestre/PPP/Project work/Db/database.txt", "a");
    if (fprintf(fp,"%s,%s,%s,%s,%s,%lu\n", user1.username,user1.password,user1.name, user1.address, user1.birthdate, user1.phone_nr) > 0)
        puts("Sucessfull \n\n"); /* Inputs to the file and prints a Success Message */
    fclose(fp);

}

int validate_login(char *username, char *password) {
    /* This function will return the line in db where the data is stored if the login is valid, -1 if the login is invalid */

    FILE *fp;
    fp = fopen("/home/tld/Documents/University/2 Semestre/PPP/Project work/Db/database.txt", "r");
    int i = 0;
    char buffer[100];
    char name[BUFFER_SIZE];
    char pass[BUFFER_SIZE];
    const char s[2] = ","; char *token;
    if(fp == NULL){
        /* If there is no file */
       puts("No user registered");
       return 0;
    }
    for(i = 0; fgets(buffer, 100, fp) != NULL; i++){
        if (buffer[0] == ' ' || strlen(buffer) < 2) {
            return -1;
        }
        token = strtok(buffer,s);
        strcpy(name, token);
        token = strtok(NULL, s);
        strcpy(pass, token);
        //printf("%s || %s \n", name, pass);
        if (strcmp(name,username) == 0 && strcmp(pass,password) == 0){
            return i;
        }
    }
    //puts("Here");
    return -1;
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

void edit_personal_info(char *username){
    /* edits user data */
    char option;  int valid =0;
    FILE *fp;
    struct User* user;
    user = load_user_data(username);
    print_user_data(user);
    /* Prompts user to change his info */
    while(1){

        printf("Select which one you want to change, 0 to exit \n");
        option = getchar();
        /*Duplication Bug */
        option -= 48;
        if (option == 0)
            break;
        if (option ==1){
            getchar();
            puts(" You can't change you username");
            //getchar();
        }
        if (option == 2) {
            getchar();
            printf("Name: ");
            fgets(user->name, BUFFER_SIZE, stdin);
            user->name[strcspn(user->name, "\n")] = 0;
        }
        if (option ==3){
            getchar();
            printf("Adress: ");
            fgets(user->address,BUFFER_SIZE, stdin);
            user->address[strcspn(user->address, "\n")] = 0;

        }
        if (option ==4){
            getchar();
            printf("Birthdate: ");
            fgets(user->birthdate,BUFFER_SIZE, stdin);
            user->birthdate[strcspn(user->birthdate, "\n")] = 0;

        }
        if (option == 5){
            getchar();
            printf("Phone nr: ");
            scanf("%lu", &user->phone_nr);

        }
        if (option == 6) {
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
        valid = 0;

    }

    /*Finally it writes the content to a file in the correct line */

    /*fp = fopen("/home/tld/Documents/University/2 Semestre/PPP/Project work/Db/database.txt", "r");
         Insert logic to find the correct line

        if (fprintf(fp,"%s,%s,%s,%s,%s,%lu\n", user->username,user->password,user->name, user->address, user->birthdate, user->phone_nr) > 0)
            puts("Sucessfull \n\n");
        fclose(fp);*/


}

struct User* load_user_data(char *username){
    /*Loads user current data*/
    FILE *fp;
    struct User* user;
    user = (struct User*) malloc(sizeof(struct User));
    char buffer[100]; const char s[2] = ","; char *token;
    int i = 0;
    fp = fopen("/home/tld/Documents/University/2 Semestre/PPP/Project work/Db/database.txt", "r");
    for(i = 0; fgets(buffer, 100, fp) != NULL; i++) {
        //printf("%s", buffer);
        token = strtok(buffer, s);
        if (strcmp(token, username) == 0) {
            strcpy(user->username, token); /*Load the username */
            token = strtok(NULL, s);
            strcpy(user->password, token); /*Load the password */
            token = strtok(NULL, s);
            strcpy(user->name, token);     /*Load the name */
            token = strtok(NULL, s);
            strcpy(user->address, token);  /*Load the address */
            token = strtok(NULL, s);
            strcpy(user->birthdate, token);/*Load the birthdate */
            token = strtok(NULL, s);
            user->phone_nr = atoi(token);  /*Load the phone_nr */
        }
    }
    return user; /* returns a struct User*  -> All the data for the current user is loaded there*/

}

void print_user_data(struct User* user){
    /*Prints user current data */
    printf("\t\t 1) Username: %s\n",user->username);
    printf("\t\t 2) Name: %s\n",user->name);
    printf("\t\t 3) Address: %s\n",user->address);
    printf("\t\t 4) Birthdate:%s\n", user->birthdate);
    printf("\t\t 5) Phone_nr: %lu\n", user->phone_nr);
    printf("\t\t 6) Password: %s\n", user->password);
};
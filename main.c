#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "user.h"
#define MAX_TRIES 3 /* Max number of tries for login*/
#define MAX_SIZE 50 /*max size for username and password */
#define PATH "/home/tld/Documents/University/2 Semestre/PPP/Exercise Files/Project Test/Db/database2.txt"

/* This files handles all UI functionality for the login system*/
void user_interface_main(char *username, struct User* head);
int show_main_menu();
char login(int max_tries , struct User* head);

int main() {
    int option, running = 1;
    struct User* head;
    head = load_user_data(PATH); /*Preload data */
    //print_user_data(head);
    while(running) {
        show_main_menu();
        option = get_option();
        if (option == 1){
            login(MAX_TRIES, head);
            break;}

        if (option == 2){
            registration(head);
            write_out(PATH,head);
            print_user_data(head);}

        if(option == 0)
            running = 0;
    }


}

int show_main_menu() {
    /* prints the man menu*/
    puts("\t\t Welcome To TripAdvisor");
    puts("\t\t Please select an option");
    puts("\t\t 1) Login");
    puts("\t\t 2) Register");

}

char login(int max_tries, struct User* head) {
    /*Login system */
    char username[MAX_SIZE], password[MAX_SIZE];int i;
    printf("Username: ");
    scanf("%s", username);

    for (i = 0; i < max_tries; i++) {
        printf("Password: ");
        scanf("%s", password);
        if (validate_login(head,username, password) >= 0) {
            user_interface_main(username, head);
            break;
        }
        else{
            puts("Invalid Username or Password");
        }
    }



}

void user_interface_main(char *username, struct User* head) {
    /*User interface Post-login */
    int option, running = 1;
    printf("\t\t Welcome, %s \n", username);
    puts("");
    while (running) {
        puts("\t\t 1) Edit Personal Info");
        puts("\t\t 2) Change Favorite Interest Points");
        puts("\t\t 3) Change Favorite Locations");
        puts("\t\t 4) List the most Popular places and Interest points");
        puts("\t\t 5) Generate a custom trip");
        puts("\t\t 0) Exit");
        printf("\t\t");
        option = get_option();
        if(option == 1){
            edit_personal_info(head,username);
            }
        if(option == 2){
            //change_ip();
            }
        if(option == 3){
            //change_locations();
            }

        if(option == 4){
            //list_most_popular();
            }
        if(option == 5){
            //generate_trip();
            }
        if(option == 0){
            running = 0;
        }
    }

}

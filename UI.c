//
// Created by tld on 19/04/19.
//
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "UI.h"
#include "login.h"


int main_menu() {
    int option;
    puts("\t\t Welcome To TripAdvisor");
    puts("\t\t Please select an option");
    puts("\t\t 1) Login");
    puts("\t\t 2) Register");
    do {
        printf("\t\t");
        scanf("%d", &option);
        if (option != 1 && option != 2) {
            puts("Invalid Option");
        }
    } while (option != 1 && option != 2);

    return option;

}

char *login() {
    char *username, *password;
    int max_tries = 3, i;
    username = malloc(25 * sizeof(char));
    password = malloc(25 * sizeof(char));
    printf("Username: ");
    scanf("%s", username);
    for (i = 0; i < max_tries; i++) {
        printf("Password: ");
        scanf("%s", password);
        //printf("%d",validate_login(username,password));
        if (validate_login(username, password) >= 0) {
            free(password);
            return username;

        }
    }
    return NULL;
}

void user_interface_main(char *username) {
    int option;
    printf("\t\t Welcome, %s \n", username);
    puts("");
    puts("\t\t 1) Edit Personal Info");
    puts("\t\t 2) Change Favorite Interest Points");
    puts("\t\t 3) Change Favorite Locations");
    puts("\t\t 4) List the most Popular places and Interest points");
    puts("\t\t 5) Generate a custom trip");
    printf("\t\t");
    scanf("%d", &option);
    switch (option) {
        case 1:
            edit_personal_info(username);
            break;

        case 2:
            //change_ip();
            break;
        case 3:
            //change_locations();
            break;

        case 4:
            //list_most_popular();
            break;
        case 5:
            //generate_trip();
            break;


        default:
            puts("Something went wrong : Debug code user_interface_menu option");
    }

}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "UI.h"
#include "login.h"

/* This files handles all UI functionality for the login system*/


int main() {
    int option;
    char *username = NULL;
    option = main_menu();
    switch (option) {
        case 1:
            username = login();
            break;

        case 2:
            registration();
            main();

        default:
            puts("Something went wrong : Debug code main_menu option");
    }
    if (username != NULL) {
        user_interface_main(username);
    } else {
        puts("Invalid Username or Password");
    }
}

//
// Created by tld on 20/04/19.
//

#ifndef PROJECT_WORK_LOGIN_H
#define PROJECT_WORK_LOGIN_H

#endif //PROJECT_WORK_LOGIN_H

struct User{
    char username[25];
    char password[25];
    char name[25];
    char address[25];
    char birthdate[25];
    unsigned long phone_nr;
};

int registration();
int validate_login(char *username, char *password);
int check_if_valid(char *string);
void edit_personal_info(char *username);
struct User* load_user_data(char *username);
void print_user_data(struct User* user);
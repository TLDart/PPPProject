//
// Created by tld on 20/04/19.
//

#ifndef PROJECT_WORK_LOGIN_H
#define PROJECT_WORK_LOGIN_H

#endif //PROJECT_WORK_LOGIN_H

struct User{
    char *username;
    char *password;
    char *name;
    char *address;
    char *birth_date;
    char *phone_nr;
    char *hot;
    struct User* next;
};
/*Linked List related Functions*/
struct User* create_list(void);
struct User* insert_user(struct User* tail, char *username, char *password, char* name, char* address, char* birth_date, char* phone_nr);
void print_user_data(struct User* head);
void print_single_user(struct User* user);
int get_option();

struct User* load_user_data(char *path);
int validate_login(struct User* head,char *username, char *password);
int check_if_valid(char *string);
int registration(struct User* head);
void edit_personal_info(struct User *head,char *username);
void write_out(char* path, struct User* head);
//
// Created by tld on 20/04/19.
//
#ifndef PROJECT_WORK_LOGIN_H
#define PROJECT_WORK_LOGIN_H

#include "locals.h"
#endif //PROJECT_WORK_LOGIN_H

struct User{
    char *username;
    char *password;
    char *name;
    char *address;
    char *birth_date;
    char *phone_nr;
    char *hot;
    struct local_pointers* locals;
    struct pdi_pointers* pdis;
    struct User* next;
};

struct user_pointers{
    struct User *user;
    struct user_pointers* next;
};

/*Linked List related Functions*/
struct User* create_list(void);
void load_user_data(struct User* head ,char *path, struct local* local_head, struct PDI* pdi_head);
void print_user_data(struct User* head);
void print_single_user(struct User* user);
int get_option();
struct User* validate_login(struct User* head, char* username, char* password);
void edit_personal_info(struct User *head, struct User *user);
int check_if_valid(char *string);

char *generate_locals(struct local_pointers* locals);
char *generate_pdis(struct pdi_pointers* locals);
void write_out(char* path, struct User* head);
void registration(struct User* head, struct local* local_head);

struct user_pointers* create_user_pointers(void);
void update_local_popularity(struct User* u, struct local* local_head);
void tail_insert_user_pointer(struct user_pointers* u, struct User* user);
void print_popularity_local(struct local* head);
void update_locals_users_pointers(struct local_pointers* u, struct User* user);

void update_pdi_popularity(struct User* u, struct PDI* pdi_head);
void update_pdi_users_pointers(struct pdi_pointers* u, struct User* user);
void print_popularity_pdi(struct PDI* head);

void print_user_locals(struct local_pointers* u);
void change_locals(struct User *u, struct local* local_head);
int valid_local(struct local* local_head,struct local_pointers * current, char * name);

void reset_popularity(struct user_pointers* head);

void change_pdis(struct User *u, struct PDI* pdi_head);
int valid_pdi(struct PDI* pdi_head,struct pdi_pointers *insert_head, char * name);

int search_and_destroy_pdi(struct PDI* pdi_head,struct pdi_pointers *insert_head, char * name);
void remove_pdi(struct pdi_pointers* head, struct PDI* pdi);

void pdi_hot(struct User* user_head, struct User* user, struct PDI* pdi_head);


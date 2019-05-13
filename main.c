#include <stdio.h>
#include "locals.h"
#include "pdis.h"
#include "user.h"
#define MAX_TRIES 3 /* Max number of tries for login*/
#define MAX_SIZE 50 /*max size for username and password */
#define PATH_USER "/home/tld/Documents/New project and this time It will work :)/database2.txt"
#define PATH_LOCALS "/home/tld/Documents/University/2 Semestre/PPP/Exercise Files/Project Test/Db/US.txt"

void user_interface_main(struct User* user, struct User* head, struct PDI* pdi_head, struct local* local_head);
int show_main_menu();
char login(int max_tries , struct User* head, struct PDI* pdi_head, struct local* local_head);

int main(){
    int option, running = 1;
    struct User* user_head; /*Preload data */
    struct PDI* pdi_head;
    struct local* local_head;
    pdi_head = create_list_pdi();
    local_head = create_list_local();
    user_head = create_list();
    load_pdi_data(pdi_head,PATH_LOCALS);
    load_local(pdi_head,local_head);
    load_user_data(user_head,PATH_USER,local_head, pdi_head);
    update_local_popularity(user_head,local_head);
    update_pdi_popularity(user_head,pdi_head);
    //print_popularity_pdi(pdi_head);
    //print_popularity_local(local_head);
    //print_user_data(user_head);
   //print_local_list(local_head);
   //puts(local_exists(local_head,"Arizona")->name);
    /* Debug
    print_pdi_data(pdi_head);
    print_local_list(local_head);
    print_user_data(user_head);
     */
    while(running) {
        show_main_menu();
        option = get_option();
        if (option == 1){
            login(MAX_TRIES, user_head,pdi_head,local_head);
            break;}

        if (option == 2){
            registration(user_head, local_head);
            //print_user_data(user_head);
        }

        if(option == 0)
            running = 0;
    }
    write_out(PATH_USER, user_head);

}

int show_main_menu() {
    /* prints the man menu*/
    puts("\t\t Welcome To TripAdvisor");
    puts("\t\t Please select an option");
    puts("\t\t 1) Login");
    puts("\t\t 2) Register");
    puts("\t\t 0) Exit");

}

char login(int max_tries, struct User* user_head, struct PDI* pdi_head, struct local* local_head) {
    /*Login system */
    char username[MAX_SIZE], password[MAX_SIZE];int i;
    struct User* user;
    printf("Username: ");
    scanf("%s", username);

    for (i = 0; i < max_tries; i++) {
        printf("Password: ");
        scanf("%s", password);
        user = validate_login(user_head,username, password);
        if (user) {
            user_interface_main(user, user_head,pdi_head, local_head);
            break;
        }
        else{
            puts("Invalid Username or Password");
        }
    }



}

void user_interface_main(struct User* user, struct User* user_head, struct PDI* pdi_head, struct local* local_head) {
    /*User interface Post-login */
    int option, running = 1;
    printf("\t\t Welcome, %s \n", user->username);
    puts("");
    while (running) {
        puts("\t\t 1) Edit Personal Info");
        puts("\t\t 2) List the most Popular places and Interest points");
        puts("\t\t 3) Generate a custom trip");
        puts("\t\t 0) Exit");
        printf("\t\t");
        option = get_option();
        if(option == 1){
            edit_personal_info(user_head,user, local_head, pdi_head);
        }
        if(option == 2){
            puts("\t\t 1) List Alphabetically");
            puts("\t\t 2) List by Popularity");
            puts("\t\t 0) Exit");
            option = get_option();
            if(option == 0){
                break;
            }
            if(option == 1){
                print_local_list(local_head);
            }
            if(option == 2){
                //List_by_popularity
                puts("Not available yet");
            }
        }
        if(option == 3){
            //generate_trip();
        }
        if(option == 0 || option == 9){
            running = 0;
        }
    }

}
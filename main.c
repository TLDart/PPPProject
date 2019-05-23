#include <stdio.h>
#include "locals.h"
#include "pdis.h"
#include "user.h"
#define MAX_TRIES 3 /* Max number of tries for login*/
#define MAX_SIZE 50 /*max size for username and password */
#define PATH_USER "/home/tld/Documents/New project and this time It will work :)/DatasetA.txt"
#define PATH_LOCALS  "/home/tld/Documents/New project and this time It will work :)/US.txt"

void user_interface_main(struct User* user, struct User* head, struct PDI* pdi_head, struct local* local_head);
int show_main_menu();
char login(int max_tries , struct User* head, struct PDI* pdi_head, struct local* local_head);

int main(){
    int option, running = 1;
    struct User* user_head = create_list(); /*Preload data */
    struct PDI* pdi_head = create_list_pdi();
    struct local* local_head = create_list_local();
    if(load_pdi_data(pdi_head, PATH_LOCALS) == 0 || load_user_data(user_head, PATH_USER, local_head, pdi_head) == 0) {
        puts("Invalid Load");
        return 0;
    }
    load_local(pdi_head, local_head);
    update_local_popularity(user_head,local_head);
    update_pdi_popularity(user_head,pdi_head);
    insert_popularity_pdi(pdi_head);
    insert_popularity_local(local_head);
    while(running) {
        show_main_menu();
        option = get_option();
        if (option == 1){
            login(MAX_TRIES, user_head,pdi_head,local_head);
            continue;
            }
        if (option == 2){
            registration(user_head, local_head);
            continue;
        }
        if(option == 0 || option == 9)
            running = 0;
        else
            puts("Invalid Option");
    }
    write_out(PATH_USER, user_head);
}

int show_main_menu() {
    /* prints the man menu*/
    puts("\t\t Welcome To MaregAdvisor");
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
            puts("\t\tInvalid Username or Password");
        }
    }
}

void user_interface_main(struct User* user, struct User* user_head, struct PDI* pdi_head, struct local* local_head) {
    /*User interface Post-login */
    struct local** local_array_popularity;
    struct PDI** pdi_array_popularity;
    int local_nr = count_local(local_head), pdi_nr = count_pdi_number(pdi_head), option,option2, running = 1;
    local_array_popularity = create_popularity_order(local_head, local_nr);
    pdi_array_popularity = create_popularity_order_pdi(pdi_head, pdi_nr);
    printf("\t\tWelcome, %s \n", user->username);
    puts("");
    while(running) {
        puts("\t\t 1) Edit Personal Info");
        puts("\t\t 2) List the most Popular places and Interest points");
        puts("\t\t 3) Generate a custom trip");
        puts("\t\t 4) Search PDI Database");
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
            option2 = get_option();
            if(option2 == 0 || option2 == 9){
                continue;
            }
            else if(option2 == 1){
                print_local_list(local_head);

            }
            else if(option2 == 2){
                update_pdi_and_local_popularity(local_array_popularity,pdi_array_popularity,local_nr, pdi_nr,local_head, pdi_head);
                print_local_and_pdi_pop(local_array_popularity,pdi_array_popularity,local_nr, pdi_nr);
            }
            else
                puts("\t\tInvalid Option");
        }
        if(option == 3){
            update_pdi_and_local_popularity(local_array_popularity,pdi_array_popularity,local_nr, pdi_nr,local_head, pdi_head);
            generate_trip(user,pdi_head,user_head, pdi_array_popularity, pdi_nr);
        }
        if(option == 4){
            search_pdi_database(pdi_head);
        }
        if(option == 0 || option == 9){
            running = 0;
        }
    }
}

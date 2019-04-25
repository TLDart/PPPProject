# PPPProject
Git repo for PPP group project

A basic C database using linked lists and files

### Documentation
#### *User.h* 
 * struct User* create_list(void);
   * Generates the user linked lists, returns a pointer to the list's head 
 * struct User* insert_user(struct User* tail, char \*username, char \*password, char\* name, char* address, char* birth_date, char* phone_nr);
    * Inserts a user to the end of the linked list,with the {PARAMETERS} caracteristics, returns pointer to tail of the linked list
 * void print_user_data(struct User\* head);
    * Prints the information about every user in a formatted form 
 * void print_single_user(struct User\* user);
   * prints Information about a single user
 * int get_option();
    * Option choosing function, Returns an integer
 * struct User* load_user_data(char *path);
   * Given a correct File path, this function parses data from the txt file to a linked list, returns point to the head of the linked list
 * int validate_login(struct User* head,char *username, char *password);
    * Checks if there is a user && password in the system, return 1 if true, -1 if false
 * int check_if_valid(char *string);
    * Ensures that the string inputted in the correct form(No whitespaces), returns 1 if valid, 0 otherwise 
 * int registration(struct User* head);
    * Allows the user to register into the system
 * void edit_personal_info(struct User *head,char *username);
    * Allows the user to edit his personal data
 * void write_out(char* path, struct User* head);
    * Saves changes made to the linked links to a *path* file
 
 
 #### *Main.c*
 | Functions here don't have a return value
 * void main();
    * Main Function
 * void show_main_menu();
    * prints the main menu, and by that I mean the first one that appears
 * void login(int max_tries, struct User* head);
   * Core Login system,  does  have return value
 * void user_interface_main(char *username, struct User\* head);
   * Post Login Interface,
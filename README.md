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
 * void registration(struct User* head, struct local* local_head)
    * Allows the user to register into the application
 * struct user_pointers* create_user_pointers(void)
    * Creates a linked list for user_pointers
 * void update_local_popularity(struct User* u, struct local* local_head)
    * Generates a linked list with all the users corresponding to locals
 * void tail_insert_user_pointer(struct user_pointers* u, struct User* user)
    * Inserts a user to the end of the user_pointers
 * void print_popularity_local(struct local* head)
    * Prints the a given local name and its popularity
 * void update_locals_users_pointers(struct local_pointers* u, struct User* user)
    * Helping function to update_local_popularity
 * void update_pdi_popularity(struct User* u, struct PDI* pdi_head)
    * Generates a linked list with all the users corresponding to pdis
 * void update_pdi_users_pointers(struct pdi_pointers* u, struct User* user)
    * Helps update pdi popularity (similar to lacal fucntions)
 * void print_popularity_pdi(struct PDI* head)
    * Prints users which have favorite PDI's and their respective PDI's
 * void change_locals(struct User* u, struct local* local_head)
    * Allows users to change favorite places
 * void print_user_locals(struct local_pointers* u);
    * Prints Menu with user locals , either  {NAME} OR {NONE}
 * int valid_local(struct local* local_head,struct local_pointers * current, char * name)
    * Checks if the local is valid or the input is "None", returns 1 if successful, 0 if unsuccessful
 * void reset_popularity(struct user_pointers* head)
    * Goes through a linked list of popularity and frees it
 * void change_pdis(struct User* u, struct PDI* pdi_head)
    * Main function that allows users to change preferred pdis
 * int valid_pdi(struct PDI* pdi_head,struct pdi_pointers *insert_head, char * name)
    * Checks if the pdi exist, if so it tails inserts it, returns 1 if successful, 0 if unsuccessful
 * int search_and_destroy_pdi(struct PDI* pdi_head,struct pdi_pointers *insert_head, char * name)
    * Searches for a pdi in the favorite_pdis and calls removal, returns 1 if removed, 0 if pdi does not exist
 * void remove_pdi(struct pdi_pointers* head, struct PDI* pdi)
    * Searches for a specific PDI and removes it
 * void pdi_hot(struct User* user_head, struct User* user, struct PDI* pdi_head)
    * Main menu to change Hot PDI
 * int count_popularity(struct user_pointers* head);
    * Counts the popularity of a given PDI / local, returns the popularity number
 * void generate_trip(struct User * u,struct local* local_head, struct PDI* pdi_head, struct User* user_head, struct PDI** pdi_pop_array, int pdi_pop_array_size)
    * Generates the desired trip for the user
 * struct PDI** generate_per_local(struct PDI* pdi_head,struct User* u,struct local* local, struct PDI** pdi_pop_array, int pdi_pop_array_size)
    * Generates the pdi's per place, for 1 place
 * int check_pdi_in_local(char *hot, struct local *local)
    * Checks if hot pdi belongs to a local, returns 1 if successful, 0 if unsuccessful
 * int pdi_in_user(struct pdi_pointers* user_pdis, struct PDI *pdi)
    * Checks if a pdi belongs to a user
 * int check_hot(struct User* user_head, struct PDI* pdi)
    * Checks if a PDI is a user's hot for every user, returns the number of times that happens
 * double popularity_tax_calculator(struct PDI** blockA, struct PDI** blockB,struct PDI** blockC,struct User* user_head,struct User* user, struct PDI* pdi_head)
    * Calculates the popularity of a trip, returns the popularity %
 * int count_users(struct User* user_head)
    * Counts the total number of users, returns that number
 * int user_local_selected(struct User* user_head, struct local* localA, struct local* localB, struct local* localC)
    * Checks every user if there is atleast one of LOCALA, LOCALB or LOCALC selected, returns teh number of times that happens
 * int check_array(struct PDI** pdi_array, int size, struct PDI* pdi)
    * Checks if the PDI already exists in the array. Returns 1 if true 0 if false
 * int add_popularity(struct PDI* pdi)
    * Returns the popularity of a PDI
 * int total_popularity(struct PDI* pdi_head)
    * Returns de popularity of all PDI´s*


#### pdis.c
 * struct PDI* create_list_pdi(void)
    * Creates a linked list for PDIs
 * void load_pdi_data(struct PDI* head,char *path)
    * Pre-loads pdi data from a file to a linked list
 * void searching_pdi(struct PDI* list, char* key, struct PDI** ant, struct PDI** actual)
    * Finds the correct position of the PDI (aka element before) in order correctly insert according to the key
 * void print_pdi_data(struct PDI* head);
    * Prints PDi data
 * void print_single_pdi(struct PDI* u);
    * Prints a single PDi
 * struct PDI* pdi_exists(struct PDI* head, char* name)
    * Checks if there is a PDI {NAME}
 * void print_only_pdis(struct PDI *head);
    * Prints only the PDI name
 * struct pdi_pointers* create_pdi_pointers(void);
    * Creates a linked list for PDIs, returns the head of the list  
 * void parse_pdi(struct PDI* pdi_head, struct pdi_pointers* insert, char *name)
    * parses a given {PDIName} into a pdi_pointers linked lists and inserts in the end   
 * void tail_insert_pdi_pointers(struct pdi_pointers* head, struct PDI* pdi);
    * Inserts pdi to the end of PDI pointers
 * void print_pdi_pointers(struct pdi_pointers*);
    * Prints a list of pdi pointers, or None if NULL
 * struct PDI** add_pointers_pdi(struct PDI *pdi_head, int size);
    * Returns an array with the PDI (unorganized)
 * void insert_popularity_pdi(struct PDI* head);
    * Changes the popularity parameter for all  PDI's
 * int count_pdi_number(struct PDI *head);
    * Counts the number of locals on a local list
 * struct PDI** create_popularity_order_pdi(struct PDI* pdi_head, int size);
    * Function that generates a sorted-by-popularity PDI array
 void print_popularity_order_pdi(struct PDI** popularity_array,int size);
    * Prints the PDI name alongside is popularity 
 void bubble_sort_popularity_pdi(struct PDI** array,int n, int ascending);
    * Bubble sorts the array of locals by popularity
    
 #### *locals.c*"
 * struct local* create_list_local(void);
    * Creates a linked list for locals
 * struct local* load_local(struct PDI* pdi_head, struct local* local_head);
    * Loads current local data into a linked list
 * struct local* local_exists(struct local* head, char* name);
    * Check if there is a local {NAME}
 * void searching_local(struct local* list, char* key, struct local** ant, struct local** actual);
    * Function that assist correct placing
 * int print_local_list(struct local *head);
    * Prints local data
 * void print_only_locals(struct local *head);
    * Function that prints only names of locals
 * void parse_local(struct local* local_head, struct local_pointers* insert, char *name);
    * Function that transform a char {LOCAL} into either a pointer to the corresponding local or NULL if None
 * struct local_pointers* create_locals_pointers(void);
    * Creates a linked list for PDIs
 * void print_local_pointers( struct local_pointers* locals);
    * Runs though a local pointers and prints its content
 void insert_popularity_local(struct local* head);
    * Runs through all locals and insert their popularity parameter
 * int count_local(struct local *head)
    * Count the number of locals on a local list
 * struct local** create_popularity_order(struct local* local_head, int size);
    * Main function that both creates and sorts local popularity array
 * struct local** add_pointers_locals(struct local *local_head, int size)
    * Add pointer to local to local array
 * void print_popularity_order(struct local** popularity_array,int size);
    * Print locals array
 * void bubble_sort_popularity_local(struct local** array,int n, int ascending);
    * Bubble sorts the array of locals by popularity
 * void print_local_and_pdi_pop(struct local** local_array_popularity, struct PDI** local_pdi_popularity, int local_size, int size_pdi);
    * Prints a list with both locals PDI's organized by popularity
 * void update_pdi_and_local_popularity(struct local** local_array_popularity,struct PDI** pdi_array_popularity,int local_nr, int pdi_nr, struct local* local_head, struct PDI* pdi_head);
    * Updates both pdi and local popularity arrays, only works post Initizlization
 
 
 
 #### *Main.c*
 | Functions here don't have a return value
 * void main();
    * Main Function
 * void show_main_menu();
    * prints the main menu, and by that I mean the first one that appears
 * void login(int max_tries, struct User* head);
   * Core Login system,  does  have return value
 * void user_interface_main(char *username, struct User\* head);
   * Post Login Interface
   
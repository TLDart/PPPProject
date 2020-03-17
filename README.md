# PPP Project

Small C based program, that uses linked lists, to plan field trips to different places and attraction points.

## Flow
1. When the program starts, and load data successfully the users is prompted for a login, which is, a simple matching password in the database
2. After a sucessful login the user enters the main menu, there he can:
  * Edit personal Info;
  * List the most popular places and Interest points;
  * Generates a custom trip 
  * Search the PDI database
  * Exit the program
3. If the user chooses to edit personal info:
  * Change Username
  * Change Password;
  * Change FullName;
  * Change Address;
  * Change Birthdate;
  * Change Phonenumber;
4. If the user chooses to list Interest Points;
  * List Alphabetically;
  * List by popularity;
5. If the user chooses to generate a Trip:
  * Generates a trip based on the user preferences;
6. If the user chooses to Search the Interest Point Database:
  * Manual Query for IP name;
7. When the program ends, all changes in the database are written back to the disk (txt file);

## Remarks
To Build a dataset for this project a custom script was used, it can be found [here](https://github.com/TLDart/DataGenerator).
## Known Bugs/Issues
* Besides some C usual weirdness there is nothing to report

## Colaborators
[AnDré Silva](https://github.com/DreSilva)

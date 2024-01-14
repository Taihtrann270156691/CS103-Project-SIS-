/*Programmer:  Taih Trann 270156691
* Description: This is CS103 Project
* School Information System
*/

#include "SystemFunction.h"

int main() {
	UserLogin userObj; //Userlogin's object
	std::string userName; //store user logged name
	bool admin = false; //to know if user logged in is admin

	manageSchoolFiles(); //Read & initialise system with school information
	printSystemWelcome(); //Print a welcome message with the chosen school
	
	Teacher teacherObj; //Teacher's object
	teacherObj.readTeacherFile();
	Student studentObj; //Student's object
	studentObj.readStudentFile();
	Parent parentObj; //Parent's object
	parentObj.readParentFile();
	ClassRoom classObj; //ClassRoom's object
	classObj.readClassFile();

	std::string choice;

	while (true) {
		bool admin = false;
		bool login = userObj.userLogin(admin, userName);
		if (!login)
			return 0; //terminate the system 

		std::cout << "Welcome " << userName << "!\n";
		bool whileTrue = false;
		while (login) {
			switch (mainMenu(admin)) {
				case 1:
					switch (userObj.UserMenu(admin)) {
						case 1:
							if (admin)
								userObj.addNewUser();
							break;

						case 2:
							if (admin)
								userObj.deleteUser();
							break;

						case 3: 
							userObj.editUserPassword(admin, userName);
							break;

						case 4:
							userObj.display();
							break;

						case -1:
								break;
					}
					break;
				case 2:
					if (admin)
						schoolMenu();
					break;

				case 3:
					teacherMenu(admin);
					break;

				case 4:
					parentMenu(admin);
					break;

				case 5:
					studentMenu(admin);
					break;
				case 6:
					classMenu(admin);
					break;
				case -1:
					std::cout << "You have logged out..." << std::endl;   
					login = false;
					std::cout << "Bye " << userName << "!\n";
					break;
			}
		}
	}

	return 0;
}
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
	//printSystemWelcome(); //Print a welcome message with the chosen school
	
	Teacher teacherObj; //Teacher's object
	teacherObj.readTeacherFile();
	Student studentObj; //Student's object
	studentObj.readStudentFile();
	Parent parentObj; //Parent's object
	parentObj.readParentFile();
	ClassRoom classObj; //ClassRoom's object
	classObj.readClassFile();

	std::string choice;
	bool login = false; 

	while (true) {
		mainLayout(choice);
		switch (std::stoi(choice)) {
			case 1:
				login = userObj.userLogin(admin, userName);
				if (!login)
					return 0; //terminate the system
				switch (mainMenu(admin)) {
					case 1:
						switch (userObj.UserMenu(admin)) {
							case 1:
								if (admin)
									userObj.addNewUser();
								// Wait for the user to press Enter
								std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
								break;

							case 2:
								if (admin)
									userObj.deleteUser();
								// Wait for the user to press Enter
								std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
								break;

							case 3:
								userObj.editUserPassword(admin, userName);
								// Wait for the user to press Enter
								std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
								break;

							case 4:
								userObj.display();
								// Wait for the user to press Enter
								std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
				break;
			case 2:
				aboutUs();
				// Wait for the user to press Enter
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				break;
			case 3:
				contactUs();
				// Wait for the user to press Enter
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				break;
			case -1:
				return 0;
		}
		
	}

	

	return 0;
}
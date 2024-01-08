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

	std::string choice;

	while (true) {
		bool admin = false;
		bool login = userObj.userLogin(admin, userName);
		if (!login)
			return 0; //terminate the system 

		std::cout << "Welcome " << userName << "!\n";
		bool whileTrue = false;
		while (login) {
			/*std::cout << "Please enter\n";
			std::cout << "1 - Manage User's menu\n";
			std::cout << "2 - Manage School's Menu\n";
			std::cout << "Or -1 to log out.\n";
			std::cout << "Please Enter: ";
			std::getline(std::cin, choice);
			auto valid = [=]()->bool {std::regex pattern(R"(\b[1]|[2]|-?[1]\b)");
									  return std::regex_match(choice, pattern); };
			short c = std::stoi(choice);*/
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
					std::cout << "parent's menu\n";
					break;

				case 5:
					std::cout << "studnet's menu\n";
					break;
				case -1:
					std::cout << "You have logged out..." << std::endl;   
					login = false;
					std::cout << "Bye " << userName << "!\n";
					break;
			}
		}
	}
		/*if (login) { //valid credential
			std::string choice;
			if (admin) {
				while (true) {
					std::cout << "Please enter\n";
					std::cout << "1 - Manage User's menu\n";
					std::cout << "2 - Manage School's Menu\n";
					std::cout << "Or -1 to log out.\n";
					std::cout << "Please Enter: ";
					std::getline(std::cin, choice);
					auto valid = [=]()->bool {std::regex pattern(R"(\b[1]|[2]|-?[1]\b)");
											  return std::regex_match(choice, pattern); };
					short c = std::stoi(choice);
					if (valid()) {
						switch (c) {
							case 1:
								whileTrue = true;
								while (whileTrue) {
									switch (userObj.adminMenu()) {
										case 1:
											userObj.addNewUser();
											std::cout << "a New user has been added to the file successfully." << std::endl;
											break;
										case 2:
											userObj.deleteUser();
											std::cout << "a user has been deleted from the file successfully." << std::endl;
											break;
										case 3:
											userObj.editUserPassword();
											break;
										case -1:
											whileTrue = false;
											break;
										}
								}
								break;

							case 2:
								schoolMenu();
								break;

							case -1:
								login = false;
								admin = false;
								break;
							}
					}
					else
						std::cout << "Invalid input! Please Enter a Valid Choice!" << std::endl;
				}
			}
		}
	} */
	

	// Wait for the user to press Enter
	//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return 0;
}
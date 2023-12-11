/*Programmer:  Taih Trann 270156691
* Description: This is CS103 Project
* School Information System
*/

#include "SystemFunction.h"

int main() {
	UserLogin userObj;
	std::cout << "Welcome to School Information System!" << std::endl;
	std::cout << "Please login." << std::endl;

	bool admin = false;
	bool login = userObj.userLogin(admin);
	bool whileTrue = false;
	if (login) {
		std::string choice;
		if (admin) {
			while (true) {
				std::cout << "Please enter\n";
				std::cout << "1 - add,  delete, edit user menu\n";
				std::cout << "2 - School Information System Menu\n";
				std::cout << "Or -1 to exit.\n";
				std::cout << "Please Enter: ";
				std::getline(std::cin, choice);
				auto valid = [=]()->bool {std::regex pattern(R"(\b[1]|[2]|-?[1]\b)");
				return std::regex_match(choice, pattern); };
				short c = std::stoi(choice);
				if (valid()) {
					switch (c)
					{
					case 1:
						whileTrue = true;
						while (whileTrue) {
							switch (userObj.adminMenu())
							{
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
						return 0;
					}
				}
				else
					std::cout << "Invalid input!" << std::endl;
			}
		}
	}

	// Wait for the user to press Enter
	//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return 0;
}
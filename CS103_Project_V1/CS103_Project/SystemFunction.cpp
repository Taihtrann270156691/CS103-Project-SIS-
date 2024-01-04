#include "SystemFunction.h"
#include "School.h"

//global variable
std::shared_ptr<std::map<short, School>> schoolMapPtr = std::make_shared<std::map<short, School>>();


/// <summary>
/// print main menu
/// </summary>
/// <param name="c"></param>
/// <returns></returns>
short mainMenu(bool& _admin) {
	std::string choice;
	while (true)
	{
		std::cout << "Please enter\n";
		if (_admin) {
			std::cout << "1 - Manage User's menu\n";
			std::cout << "2 - Manage School's Menu\n";
			std::cout << "3 - Manage Teacher's Menu\n";
			std::cout << "4 - Manage Parent's Menu\n";
			std::cout << "5 - Manage Student's Menu\n";
		}
		else {//non-admin cannot make change to school info
			std::cout << "1 - to change your password\n";
			std::cout << "3 - Manage Teacher's Menu\n";
			std::cout << "4 - Manage Parent's Menu\n";
			std::cout << "5 - Manage Student's Menu\n";
		}
		std::cout << "Or -1 to log out.\n";
		std::cout << "Please Enter: ";
		std::getline(std::cin, choice);

		//lambda function for valid choice
		auto valid = [=]()->bool {std::regex pattern(R"(\b[1]|[2]|-?[1]\b)");
		return std::regex_match(choice, pattern); };

		if (valid())
			break;
		else
			std::cout << "Invalid choice!" << std::endl;
	}

	return std::stoi(choice);
}

/// <summary>
/// Read school file, if the file does not exist, 
/// create new file and set up school name and details for the system.
/// </summary>
void manageSchoolFiles() {
	School schObj;
	UserLogin userObj;
	//std::shared_ptr<std::map<short, School>> schoolMapPtr = std::make_shared<std::map<short, School>>();
	std::string userName = "";
	schObj.readSchoolFile(schoolMapPtr);
	std::size_t size = schoolMapPtr->size();
	if (size == 0) {
		std::cout << "Welcome to School Information System!" << std::endl;
		std::cout << "Please take a minute to set up the system." << std::endl;
		std::cout << "Please login as an Administrator." << std::endl;
		bool admin = false;
		while (!admin) {
			
			if (userObj.userLogin(admin, userName) && admin) {
				schObj.addSchool(schObj.userInput_School(schoolMapPtr));
			}
			else {
				std::cout << "This user is not an Admin." << std::endl;
				std::cout << "Please login as an Administrator. " << std::endl;
			}
		}	
		std::cout << "System set up is complete! Please relogin again to continue using the system." << std::endl;
	}
}

void schoolMenu() {
	School schObj;
	//std::shared_ptr<std::map<short, School>> schoolMapPtr = std::make_shared<std::map<short, School>>();

	schObj.readSchoolFile(schoolMapPtr);

	std::string choice; //for user input choice
	//short key; //for map key
	bool whileTrue = false; //for while loop condition

	whileTrue = true;

	while (whileTrue) {
		switch (schoolChoice()) {
			case 1:
				schObj.editSchool(schoolMapPtr);
				break;
			case 2:
				//display School Info
				for (const auto& it : *schoolMapPtr) {
					std::cout << "key: " << it.first << std::endl;
					it.second.display();
				}
				break;
			case -1:
				whileTrue = false;
				break;
		}
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/// <summary>
/// print school menu
/// </summary>
/// <param name="c"></param>
/// <returns></returns>
short schoolChoice() {
	std::string choice;
	while (true)
	{
		std::cout << "Please enter:\n 1 - to make a change\n 2 to view School Information\n or -1 to go back.\nPlease Enter: " << std::endl;
		std::getline(std::cin, choice);

		//lambda function for valid choice
		auto valid = [choice]()->bool {std::regex pattern(R"(\b[1]|[2]|-?[1]\b)");
										return std::regex_match(choice, pattern); };
		if (valid())
			break;
		else
			std::cout << "Invalid choice! Please enter a valid choice!" << std::endl;
	}
	return std::stoi(choice);
}

void printSystemWelcome() {
	std::string name;
	for (const auto& it : *schoolMapPtr) {
		name = it.second.schoolName;
	}
	std::cout << "Welcome to Information System of " << name << std::endl;
}




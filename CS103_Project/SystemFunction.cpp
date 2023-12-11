#include "SystemFunction.h"
#include "School.h"

/// <summary>
/// print main menu
/// </summary>
/// <param name="c"></param>
/// <returns></returns>
short mainMenu(std::string& c) {
	while (true)
	{
		std::cout << "What menu would you like to access?\n";
		std::cout << "Enter 1 for School, 2 for Class, ";
		std::cout << "3 for Teachers, 4 for Parents, 5 for Student, or -1 to exit: " << std::endl;
		std::getline(std::cin, c);

		//lambda function for valid choice
		auto valid = [=]()->bool {std::regex pattern(R"(\b[1]|[2]|[3]|[4]|[5]|-?[1]\b)");
		return std::regex_match(c, pattern); };

		if (valid())
			break;
		else
			std::cout << "Invalid choice!" << std::endl;
	}

	return stoi(c);
}

void schoolMenu() {
	School schObj;
	std::shared_ptr<std::map<short, School>> schoolMapPtr = std::make_shared<std::map<short, School>>();

	schObj.readSchoolFile(schoolMapPtr);

	std::string choice; //for user input choice
	short key; //for map key
	bool whileTrue = false; //for while loop condition

	while (true)
	{
		switch (mainMenu(choice))
		{
		case 1:
			whileTrue = true;
			while (whileTrue)
			{
				switch (schoolChoice(choice))
				{
				case 1:
					schObj.addSchool(schObj.userInput_School(schoolMapPtr));
					std::cout << "School Data added successfully!" << std::endl;
					break;
				case 2:
					schObj.deleteSchool(schoolMapPtr);
					break;
				case 3:
					schObj.editSchool(schoolMapPtr);
					break;
				case 4:
					for (const auto& it : *schoolMapPtr)
					{
						std::cout << "key: " << it.first << std::endl;
						it.second.display();
					}
					break;
				case -1:
					whileTrue = false;
					break;
				}
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			break;
		case -1:
			return;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}

/// <summary>
/// print school menu
/// </summary>
/// <param name="c"></param>
/// <returns></returns>
short schoolChoice(std::string& c) {
	while (true)
	{
		std::cout << "Please enter 1 to add, 2 to delete, 3 to edit, 4 to view School Information, or -1 to go back: " << std::endl;
		std::getline(std::cin, c);

		//lambda function for valid choice
		auto valid = [=]()->bool {std::regex pattern(R"(\b[1]|[2]|[3]|[4]|-?[1]\b)");
		return std::regex_match(c, pattern); };
		if (valid())
			break;
		else
			std::cout << "Invalid choice!" << std::endl;
	}
	return std::stoi(c);
}
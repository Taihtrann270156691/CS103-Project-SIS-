#include "UserLogin.h"
std::string UserFile = "UserLogin.txt";

/// <summary>
/// prompting user name and password for login
/// </summary>
/// <param name="_admin"></param>
/// <returns></returns>
bool UserLogin::userLogin(bool& _admin, std::string& _name) {
	UserLogin userObj;
	bool login = false;
	short tryCount = 3;
	short key;
	readUserFile();  //read data and store them in mapUserPtr
	std::cout << "Please Login..." << std::endl;
	while (!login && tryCount > 0)
	{
		std::cout << "Enter user name: ";
		std::getline(std::cin, userObj.userName);
		std::cout << "Enter password: ";
		std::getline(std::cin, userObj.password);

		for (const auto& it : *myUserMap) {
			login = it.second == userObj; //check user and password credential
			if (login) {
				_admin = it.second.admin;
				break;
			}
		}
		--tryCount;
		if (tryCount == 0) {
			std::cout << "You have used all 3 attempted.\n";
			break;
		}
		if (login) {
			_name = userObj.userName;
			break;
		}
		else
			std::cout << "Invalid username or password.\nyou have " << tryCount << " more try!" << std::endl;
	}
	//auto itt = mapUserPtr->find(key);
	//return itt;

	return login;
}


short UserLogin::UserMenu(bool& _admin){
	std::string choice;

	if (_admin) {
		while (true) {
			std::cout << "Please enter\n";
			if (_admin) {
				std::cout << "1 - To add new user\n";
				std::cout << "2 - to delete a user\n";
			}

			std::cout << "3 - to change a user password\n";
			std::cout << "-1 to go back to main menu.\n";
			std::cout << "Please Enter: ";

			std::getline(std::cin, choice);
			auto valid = [=]()->bool {std::regex pattern(R"(\b[1]|[2]|[3]|-?[1]\b)");
			return std::regex_match(choice, pattern); };
			if (valid())
				break;
			else
				std::cout << "Invalid choice! Please enter a valid choice!" << std::endl;
		}
	}
	else
		return 3; //non-admin straight to update password

	return std::stoi(choice);
}

/// <summary>
/// to initialise an admin user at the start of programme
/// </summary>
void UserLogin::addAdmin() const {
	UserLogin userObj;
	userObj.userName = "admin";
	userObj.password = "123456";
	userObj.admin = 1;
	// Writing to a file
	std::ofstream outFile(UserFile); // Create or open a file for writing
	if (outFile.is_open()){ // Check if the file is open
		outFile << "1-" + userObj.userName + "-" + userObj.password + "-" << userObj.admin << std::endl; //create admin account
		(*myUserMap)[1] = userObj;
		outFile.close(); // Close the file
	}
	else
		std::cerr << "Unable to open " << UserFile << "the file for writing." << std::endl;
}

/// <summary>
/// Read UserLogin.txt and fetch all user logins details to map, create one if does not exist
/// </summary>
void UserLogin::readUserFile() {
	std::ifstream fileExist(UserFile);
	
	if (fileExist.is_open()) { //file exist
		std::string line;
		while (std::getline(fileExist, line)) { // Read each line
			splitLine(line);
		}
		fileExist.close(); // Close the file
		if (!(myUserMap->size() > 0)) //if UserLogin.txt file is empty
			addAdmin();
	}
	else { //create UserLogin.txt file with admin login credential
		addAdmin();
	}
}

/// <summary>
/// split raw data into a readable chunk of data
/// </summary>
/// <param name="line"></param>
void UserLogin::splitLine(const std::string& line) {
	std::istringstream str(line);
	std::string token;
	std::shared_ptr<std::string[]> userArray(new std::string[4], [](std::string* ptr) { delete[] ptr; });
	/*Array Reference : userArray[0] store keyvalue, schoolArray[1]-[3] store UserLogin Variable*/

	UserLogin userObj = UserLogin();

	int i = 0;
	while (std::getline(str, token, '-')) {
		userArray[i] = token;
		i++;
	}

	short key = std::stoi(userArray[0]);
	short admin = std::stoi(userArray[3]); // to know if user credential is admin or not
	userObj.userName = userArray[1];
	userObj.password = userArray[2];
	admin > 0 ? userObj.admin = true : userObj.admin = false;
	(*myUserMap)[key] = userObj;
}

/// <summary>
/// add new user login into UserLogin.txt
/// </summary>
void UserLogin::addNewUser(){
	UserLogin newUserObj;
	while (true) {
		std::cout << "Enter name: ";
		std::getline(std::cin, newUserObj.userName);
		auto validName = [=]()->bool {std::regex pattern("^[a-zA-Z]+[0-9]*$");
		return std::regex_match(newUserObj.userName, pattern); };
		bool isMatch = validName();
		bool dublicate = false;
		for (const auto& it : *myUserMap) { //check for dublicate user name
			if (it.second.userName == newUserObj.userName) {
				std::cout << "User name is already exist. Please enter different user name." << std::endl;
				dublicate = true;
				break;
			}
		}
		if (validName() && !dublicate) {
			break; //break while loop when input are correct and not already exist
		}
		else {
			std::cout << "Invalid input!" << std::endl;
		}
	}

	std::cout << "Enter password: ";
	std::getline(std::cin, newUserObj.password);

	while (true) {
		std::string choice;
		std::cout << "This will be an admin?" << std::endl;
		std::cout << "1 = Yes or 0 = No : ";
		std::getline(std::cin, choice);
		auto valid = [=]()->bool {std::regex pattern(R"(\b[1]|[0]\b)");
		return std::regex_match(choice, pattern); };
		if (valid()) {
			std::stoi(choice) ? newUserObj.admin = true : newUserObj.admin = false;
			break;
		}
		else
			std::cout << "Invalid input!" << std::endl;
	}

	// Open the file in append mode
	std::ofstream outFile(UserFile, std::ios::app);
	auto it = --myUserMap->end();
	short newKey = it->first + 1;
	(*myUserMap)[newKey] = newUserObj;
	if (!outFile) {
		std::cerr << "Error opening the file!" << std::endl;
	}
	else {
		// Add data to the end of the file
		outFile << newKey << "-" + newUserObj.userName << "-" << newUserObj.password << "-" << newUserObj.admin << std::endl;

		// Close the file
		outFile.close();

	}

	// Wait for the user to press Enter
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/// <summary>
/// delete a user login
/// </summary>
void UserLogin::deleteUser(){
	std::string key;
	bool validKey;
	std::cout << "Please provide key value to select user you want to delete." << std::endl;
	std::cout << "Key value must be positive integer.";
	do {
		std::cout << "Please enter key: ";
		std::getline(std::cin, key);
		//lambda function to check for positive number
		auto valid = [=]()->bool {std::regex pattern("^[1-9]\\d*$"); //regular expression for positive number
		return std::regex_match(key, pattern); };
		validKey = valid();
		if (!validKey)
			std::cout << "Invalid input!" << std::endl;
	} while (!validKey); //keep looping to get a valid input

	short finalKey = std::stoi(key); //finally a valid key

	if (finalKey == 1) {
		std::cout << "Access denied. Attempting to delete admin-admin is not allow." << std::endl;
		std::cout << "Only none-admin or admin-created user-admin are deleteable." << std::endl;
		return;
	}
	//check if element exist with provided key
	auto it = myUserMap->find(finalKey);
	if (it != myUserMap->end())
	{
		//delete element with provided key
		myUserMap->erase(finalKey);

		// Open the file in truncation mode
		std::ofstream file(UserFile, std::ios::trunc);

		// Check if the file is open
		if (file.is_open()) {
			// Close the file
			file.close();
			for ( auto it = myUserMap->begin(); it != myUserMap->end(); it++)
				updateUserFile(it);

			std::cout << "Selected user deleted successfully." << std::endl;
		}
		else
			std::cout << "Error opening the file." << std::endl;
	}
	else
		std::cout << "Error cannot find element with provided key." << std::endl;
}

/// <summary>
/// update UserLogin.txt
/// </summary>
/// <param name="_userIt"></param>
void UserLogin::updateUserFile(const std::map<short, UserLogin>::iterator& _userIt) {
	// Open the file in append mode
	std::ofstream outFile(UserFile, std::ios::app);

	if (!outFile) {
		std::cerr << "Error opening the file!" << std::endl;
	}
	else {
		// Add data to the end of the file
		outFile << _userIt->first << "-" << _userIt->second.userName
			<< "-" << _userIt->second.password << "-" << _userIt->second.admin << std::endl;

		// Close the file
		outFile.close();

		//std::cout << "A new user added to the file successfully." << std::endl;
	}
}

/// <summary>
/// update user's password
/// </summary>
void UserLogin::editUserPassword(bool& _admin, std::string& _name){
	std::string key;
	std::string newPassword;

	if (_admin) { //for administrator
		while (true) {
			std::cout << "Please provide key value to select a user OR -1 to go back to main menu." << std::endl;
			std::cout << "Please enter key: ";
			std::getline(std::cin, key);
			//lambda function to check for positive number
			auto valid = [=]()->bool {std::regex pattern("^[1-9]\\d*$"); //regular expression for positive number
									  return std::regex_match(key, pattern); };
			if (!valid())
				std::cout << "Invalid input! Please enter a valid key!" << std::endl;
			else
				break;
		}
		short finalKey = std::stoi(key);
		auto it = myUserMap->find(finalKey);
		if (it != myUserMap->end()) {
			
			std::cout << "Enter new password for - " << it->second.userName << std::endl;
			std::cout << "New password: ";
			std::getline(std::cin, newPassword);
			it->second.password = newPassword;

			// Open the file in truncation mode
			std::ofstream file(UserFile, std::ios::trunc);

			// Check if the file is open
			if (file.is_open()) {
				// Close the file
				file.close();

				//re-write edited element back to file
				for (auto it = myUserMap->begin(); it != myUserMap->end(); it++)
					updateUserFile(it);

				std::cout << "User Data updated successfully." << std::endl;
			}
			else
				std::cout << "Error opening UserLogin.txt." << std::endl;
		}
		else
			std::cout << "Error cannot find element with provided key.\n";
	} 
	else {
		short userKey;
		for (auto it = myUserMap->begin(); it != myUserMap->end(); it++) {
			if (it->second.userName == _name) {
				userKey = it->first;
				break;
			}
		}
		auto it = myUserMap->find(userKey);
		std::cout << "Hi" << _name << ", Please enter a new password:\n";
		std::getline(std::cin, newPassword);
		it->second.password = newPassword;

		std::ofstream file(UserFile, std::ios::trunc);

		// Check if the file is open
		if (file.is_open()) {
			// Close the file
			file.close();

			//re-write edited element back to file
			for (auto it = myUserMap->begin(); it != myUserMap->end(); it++)
				updateUserFile(it);

			std::cout << "User Data updated successfully." << std::endl;
		}
		else
			std::cout << "Error opening UserLogin.txt." << std::endl;
	}
	
}

void UserLogin::display() const {
	std::cout << userName << "-" << password << std::endl;
}
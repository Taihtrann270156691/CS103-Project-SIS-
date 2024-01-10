#pragma once
#include "SystemFunction.h"
class UserLogin
{
public:
	std::string userName;
	std::string password;
	bool admin;
	std::shared_ptr <std::map<short, UserLogin>> myUserMap = std::make_shared<std::map<short, UserLogin>>();

public:
	// Constructor to initialize the UserLogin object
	UserLogin() = default;
	UserLogin(const std::string& userName, const std::string& password, bool admin)
		: userName(userName), password(password), admin(admin) {}

	bool operator==(const UserLogin& other) const {
		return userName == other.userName && password == other.password;
	}

	bool userLogin(bool& _admin, std::string& _name);
	short UserMenu(bool& _admin);
	void addAdmin() const;
	void readUserFile();
	void splitLine(const std::string& line);
	void addNewUser();
	void deleteUser();
	void updateUserFile(const std::map<short, UserLogin>::iterator& _userIt);
	void editUserPassword(bool& _admin, std::string& _name);
	void display() const;
};

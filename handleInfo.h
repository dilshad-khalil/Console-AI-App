#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>

class userInfo {
public:
	std::string userName;
	std::string password;
	std::string confirmPassword;
	std::string loginState ="";
	void WriteUserData(std::string name, std::string password);
	
};

void userInfo::WriteUserData(std::string name, std::string password) {
	std::ofstream writeFile("userInfo.txt");
	if (writeFile.is_open()) {
		writeFile << name << ":" << password << std::endl;
		writeFile.close();
	}
	else {
		std::cerr << "Error opening file" << std::endl;
	}
};


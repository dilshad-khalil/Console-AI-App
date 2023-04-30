#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
#include "handleInfo.h"
#include "MainMenu.h"
#include "Animate.h"
Animate Anim;

userInfo user;
extern bool loggedIn = false;
class userAccount {
public:
	bool appExit = false;
	std::string user_name;
	std::string password;
	void Menu();
	void Register();
	void Login();
	void checkPasswordMatch();
	bool checkIfEmpty();
	void userData();
};



void userAccount::checkPasswordMatch() {
	std::cout << "Please Enter your password: ";
	getline(std::cin, user.password);
	std::cout << "Please confirm your password: ";
	getline(std::cin, user.confirmPassword);
	std::cout << std::endl;
	if (user.password == user.confirmPassword) {
		std::cout << "Registeration Done" << std::endl << std::endl;
		user.WriteUserData(user.userName , user.password);
		for (int i = 5; i >=1; i--) {
			std::cout.flush(); // flush the output buffer
			std::cout << " You will be redirected to main menu in : ";
			std::cout << "\033[34m";
			std::cout << i  << "s";
			std::cout << "\033[0m";
			Sleep(1000);
			std::cout << "\r"; // carriage return to move the cursor to the beginning of the line
		}
		loggedIn = true;
		exitApp = false;
	}
	else {
		std::cout << "\033[31m";
		std::cout << "Password doesn't match please re-enter your password" << std::endl;
		std::cout << "\033[0m";
		checkPasswordMatch();
	}
	user.userName = "";
	user.password = "";
}

bool userAccount::checkIfEmpty() {
	std::ifstream infile("userInfo.txt");
	infile.seekg(0, std::ios::end); // go to the end of the file
	if (infile.tellg() > 0) { // if the position is greater than 0, then the file is not empty
		return false;
	}
	else { // otherwise, the file is empty
		return true;
	}
}

void userAccount::userData() {
	if (user.userName == user_name && user.password == password) {
		for (int i = 3; i >= 1; i--) {
			std::cout.flush(); // flush the output buffer
			std::cout << "Logged in succesfully you will be redirected in  : ";
			std::cout << "\033[34m";
			std::cout << i << "s";
			std::cout << "\033[0m";
			Sleep(1000);
			std::cout << "\r"; // carriage return to move the cursor to the beginning of the line
		}
		system("cls");
		loggedIn = true;
		exitApp = false;
	}
	else {
		std::cout << "Wrong password or username please try again" << std::endl;
		Login();
	}
	system("cls");
}

void userAccount::Login() {

	std::ifstream inputFile("userInfo.txt");
	std::string line;
	if (inputFile.is_open()) {
		while (std::getline(inputFile, line)) {
			std::string::size_type pos = line.find(':');
			user_name = line.substr(0, pos);
			password = line.substr(pos + 1);
		}
		inputFile.close();
	}
	else {
		std::cout << "Error: could not open file." << std::endl;
	};
	std::cout << "\033[34m";
	std::cout << "Welcome to Login page" << std::endl;
	std::cout << "\033[0m";
	std::cout << "Please enter your uesrname: ";
	getline(std::cin, user.userName);
	std::cout << "Please enter your password: ";
	getline(std::cin, user.password);
	userData();
	user.userName = "";
	user.password = "";
}

void userAccount::Register(){

	if (checkIfEmpty()) {
		std::cout << "\033[34m";
		std::cout << "Welcome to register page" << std::endl;
		std::cout << "\033[0m";
		std::cout << "Please enter your uesrname: ";
		getline(std::cin, user.userName);
		checkPasswordMatch();
	}
	else {
		std::cout << "Alrady Registered please login instead" << std::endl;
		for (int i = 5; i >= 1; i--) {
			std::cout.flush(); // flush the output buffer
			std::cout << "You will be redirected to Login page in : ";
			std::cout << "\033[34m";
			std::cout << i << "s";
			std::cout << "\033[0m";
			Sleep(1000);
			std::cout << "\r"; // carriage return to move the cursor to the beginning of the line
		}
		system("cls");
		Login();
	}
}

void userAccount::Menu() {
	const std::string Options[3] = { "1:Register" , "2:Login"  , "3:Exit" };
	const int OptionsSize = sizeof(Options) / sizeof(Options[0]);
	int selectedOption = 0;

	while (!appExit) {
		system("cls");
		std::cout << "\033[0m";
		std::cout << "----Welcome to Console AI---- " << std::endl;
		std::cout << "\033[34m";
		std::cout << "Please select an option to continue Use [W,S] or [Arrow Down , Arrow Up]" << std::endl;
		std::cout << "\033[34m";
		std::cout << std::endl;

		for (int i = 0; i < OptionsSize; i++) {

			if (i == selectedOption) {
				std::cout << "\033[31m";
				std::cout << "=> ";
			}
			else {
				std::cout << "  ";
				std::cout << "\033[0m";
			}

			std::cout << Options[i] << std::endl;

		}

		//wait for the keyboard input
		char Key = _getch();

		//iterate to the next menu by getting the ascii code of the letter s or the down arrow key
		if (tolower(Key) == 115 || Key == 80) {
			selectedOption++;
		}
		//iterate to the previous menu by getting the ascii code of the letter w or the up arrow key
		if (tolower(Key) == 119 || Key == 72) {
			selectedOption--;
		}
		//reset the selected option to the first item when it's less than 0
		if (selectedOption < 0) {
			selectedOption = OptionsSize - 1;
		}
		else if (selectedOption >= OptionsSize) {
			//reset the selected option to the first item when it's less than 0
			selectedOption = 0;
		}

		if (Key == 13) {
			if (selectedOption == 0) {
				system("cls");
				appExit = true;
				Register();
				//exits the app and opens the about page
			}

			if (selectedOption == 1) {
				if (checkIfEmpty()) {
					system("cls");
					std::cout << "You don't have an account please register first" << std::endl;
					Register();
				}
				else {
					system("cls");
					appExit = true;
					Login();
				}
				
			}
			if (selectedOption == 2) {
				std::cout << std::endl;
				for (int i = 5; i >= 1; i--) {
					std::cout.flush();
					std::cout << "Exiting in: ";
					std::cout << i;
					std::cout << "\r";
					Sleep(1000);
				}
				ExitProcess(0);
			}
		}
	}
}
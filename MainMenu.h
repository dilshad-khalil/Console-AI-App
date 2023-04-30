#pragma once
#include <rapidjson/document.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <windows.h>
#include "Animate.h"
#include <future>
#include "ChatGPT_API.h"
#include "Dalle-2.h"

Animate Animation;
Data data;
DallE de;

//global variable that runs the app state
extern bool exitApp = false;
extern bool checkGPT = true;

class FetchData {
public:
	std::string user_name;
	FetchData() {
		std::ifstream inputFile("userInfo.txt");
		std::string line;
		if (inputFile.is_open()) {
			while (std::getline(inputFile, line)) {
				std::string::size_type pos = line.find(':');
				user_name = line.substr(0, pos);
			}
			inputFile.close();
		}
		else {
			std::cout << "Error: could not open file." << std::endl;
		};
		checkGPT = true;

		Animation.AnimateText("----Welcome to Console AI---- ", 30);
		std::cout << std::endl;
		data.API_DATA_FETCH("Hello There");
		std::string user_input;

		while (checkGPT!=false) {
			std::cout << "\033[33m";
			Animation.AnimateText((user_name + "/>").c_str(), 30);
			std::cout << "\033[0m";
			getline(std::cin, user_input);
			data.API_DATA_FETCH(user_input.c_str());
			std::cout << "\033[34m";
			AnimateText.AnimateText("Press [enter] to generate another response or [esc] to get back to the main menu", 20);
			std::cout << "\033[0m";
			std::cout << std::endl;

			int Key = _getch();

			if (Key == 27) {
				system("cls");
				checkGPT = false;
			}
			else if (Key == 13) {
				AnimateText.AnimateText("Let's continue", 20);
				std::cout << std::endl;
			};

		};
	}
};


class About {
public:
	About() {

		std::string About =
			"Introducing ConsoleAI - an AI-powered tool that allows you to generate highly realistic images\nand have conversations with an intelligent chatbot all in one place. With the combined power\nof GPT and DALL-E 2 APIs, ConsoleAI can quickly generate images that are detailed,\nspecific, and true to your vision. Plus, with the built-in chatbot powered by GPT,\nyou can have natural and engaging conversations with an AI that continues to learn\nand improve over time. Whether you're a designer, marketer, or just curious about the potential\nof AI, ConsoleAI has something for everyone.";

		Animation.AnimateText(About, 20);

		std::cout << std::endl << std::endl;
		std::cout << "Press [esc] to go back to the main menu" << std::endl;
		int Key = _getch();
		if (Key == 27) {
			system("cls");
			exitApp = false;
		};

	}

};

class MainMenu{
public:
	const std::string Options[4] = { "1:OpenAI ChatGPT" , "2:DALL-E 2" , "3:About" , "4:Exit" };
	const int OptionsSize = sizeof(Options) / sizeof(Options[0]);
	int selectedOption = 0;

	void iterateMenu();
};

void MainMenu::iterateMenu() {
	system("cls");
	std::cout << "\033[34m";
	std::cout << "Welcome to Console AI" << std::endl;
	std::cout << "\033[0m";
	std::cout << "Please select an option to continue Use [W,S] or [Arrow Down , Arrow Up]" << std::endl;
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
			exitApp = true;
			FetchData data;
	    }
		else if (selectedOption == 1) {
			system("cls");
			//exits the app and opens the about page
			de.handleProcess();
			exitApp = true;

		}
		else if (selectedOption == 2) {
			system("cls");
			//exits the app and opens the about page
			exitApp = true;
			About a;
		}else if (selectedOption == 3) {
			std::cout << std::endl;
			for (int i = 5; i >= 0; i--) {
				std::cout.flush();
				std::cout << "Terminating in: ";
				std::cout << i;
				std::cout << "\r";
				Sleep(1000);
			}
			std::cout << "\033[0m";
			ExitProcess(0);
		}

	}
}

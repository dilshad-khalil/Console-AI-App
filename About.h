#pragma once
#include <iostream>
#include <conio.h>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include "Animate.h"
Animate Animation;
class About {
public:
	About() {
		std::string About =
			"Introducing Console GPT - an AI-powered tool that allows you to generate highly realistic images\nand have conversations with an intelligent chatbot all in one place. With the combined power\nof GPT and DALL-E 2 APIs, Console GPT can quickly generate images that are detailed,\nspecific, and true to your vision. Plus, with the built-in chatbot powered by GPT,\nyou can have natural and engaging conversations with an AI that continues to learn\nand improve over time. Whether you're a designer, marketer, or just curious about the potential\nof AI, Console GPT has something for everyone.";
		Animation.AnimateText(About , 20);
		std::cout << std::endl << std::endl;
		std::cout << "\033[34m";
		std::cout << "Press [esc] to go back to the main menu" << std::endl;
		std::cout << "\033[0m";
		int Key = _getch();
		if (Key == 27) {
			system("cls");
		};

	}
};
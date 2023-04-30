#pragma once
#include <iostream>
#include <conio.h>
#include <string>
#include <windows.h>

class Animate {
public:
	void AnimateText(std::string text , int speed) {
		for (int i = 0; i < text.size(); i++) {
			std::cout << text[i];
			Sleep(speed);
		}
	}
};
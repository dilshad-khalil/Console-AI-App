#include <iostream>
#include <fstream>
#include "MainMenu.h"
#include "Account.h"
#include "handleInfo.h"
#include <opencv2/opencv.hpp>
#include <curl/curl.h>
#include "ImageData.h"
#include <string>
#include "MainMenu.h"
#include <windows.h>
#include <filesystem>
int main() {
	srand(time(NULL));
	userAccount user;
	MainMenu App;
	userInfo info;
	user.Menu();
	while (!exitApp || imageGeneration == false || checkGPT == false) {
		App.iterateMenu();
	}
	system("pause");
}
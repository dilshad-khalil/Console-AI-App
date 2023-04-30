#pragma once
#include <iostream>
#include "MainMenu.h"
#include <opencv2/opencv.hpp>
#include <curl/curl.h>
#include "Animate.h"
#include <string>
#include <windows.h>
#include <ShlObj.h> // Include ShlObj.h for SHGetFolderPathA
#pragma comment(lib, "Shell32.lib") // Link with Shell32.lib

Animate An;
extern bool imageGeneration = true;

// Callback function for libcurl to write image data to a buffer
static size_t write_callback(char* ptr, size_t size, size_t nmemb, void* userdata) {
	std::vector<uchar>* buffer = reinterpret_cast<std::vector<uchar>*>(userdata);
	size_t bytes = size * nmemb;
	buffer->insert(buffer->end(), ptr, ptr + bytes);
	return bytes;
}



std::string getRandomString() {
   std::string letters = "abcdefghijklmnopqrstuvwxyz";
   std::string randomString = "";

   for (int i = 0; i < 5; i++) {
       int randNum = rand() % letters.length() + 1;
       randomString += letters[randNum];
   }
   return randomString;
}

std::string getRandomInt() {
    int randNum = rand() % 1000 + 1;
    return std::to_string(randNum);
}

void showImage(std::string imageUrl) {
    // Set the image URL to download
    std::string url = imageUrl;

    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_ALL);

    // Create a libcurl easy handle for downloading the image
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize libcurl" << std::endl;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    // Set the libcurl write callback to capture the image data
    std::vector<uchar> buffer;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

    // Perform the download
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "Failed to download image: " << curl_easy_strerror(res) << std::endl;
    }
    // Clean up the libcurl easy handle
    curl_easy_cleanup(curl);
    // Decode the image data into a cv::Mat object
    cv::Mat image = cv::imdecode(buffer, cv::IMREAD_COLOR);
    if (image.empty()) {
        std::cerr << "Failed to decode image" << std::endl;
    }
    // Display the image in a window
    cv::imshow("Image", image);
    An.AnimateText("Fetching done ", 20);
    std::cout << std::endl;
    system("cls");
    cv::waitKey(0);
    cv::imwrite("./ConsoleAI/DALLE_IMAGES/" + getRandomInt() + ".jpg", image);
    An.AnimateText("Image Saved", 20);
    std::cout << std::endl;
    std::cout << "\033[34m";
    An.AnimateText("Press [enter] to generate another image or [esc] to get back to the main menu", 20);
    std::cout << std::endl;
    std::cout << "\033[0m";
    int Key = _getch();
    if (Key == 27) {
        system("cls");
        imageGeneration = false;
    }
    else {
        An.AnimateText("Let's continue", 20);
        std::cout << std::endl;

    }
    // Clean up libcurl
    curl_global_cleanup();
    //url = "";

}
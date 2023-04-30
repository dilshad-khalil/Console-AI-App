#pragma once
#define CURL_STATICLIB
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <iostream>
#include <string>
#include <Windows.h>
#include <curl/curl.h>
#include <conio.h>
#include "writeData.h"
#include "Animate.h"
#include "ImageData.h"
Animate AN;
class DallE {
public:
	std::string prompt;
	void handleProcess();
	void fetchData(std::string userPrompt);
	std::string FETCHED_DATA;
	void CHECK_FETCH(CURLcode result);
	void proccess_json();
	void getPrompt();
	rapidjson::Document Res;

};

void DallE::getPrompt() {
	prompt = "";
	getline(std::cin, prompt);
	if (prompt.empty()) {
		AN.AnimateText("Empty prompt please try again", 20);
		std::cout << std::endl;
		getPrompt();
	}
	else {
		AN.AnimateText("Fetching Please wait...", 20);
		std::cout << std::endl;
		fetchData(prompt);
	}
}

void DallE::handleProcess() {
	std::cout << "\033[34m";
	AN.AnimateText("Welcome to DALL E-2" , 20);
	std::cout << std::endl;
	std::cout << "\033[0m";
	AN.AnimateText("Please Note that every image you generate is saved into a floder called /DallE/" , 20);
	std::cout << std::endl;
	while (imageGeneration !=false) {
		AN.AnimateText("Please enter a prompt/> ", 20);
		getPrompt();
	}
}

void DallE::CHECK_FETCH(CURLcode result) {
	if (result == CURLE_OK) {
		std::cout << "\033[31m";
		AN.AnimateText("Hey the images are ready...", 20);
		std::cout << "\033[0m";
		proccess_json();
	}
	else {
		// Handle Curl errors
		std::cerr << "Curl error: " << curl_easy_strerror(result) << std::endl;
	}
}

void DallE::fetchData(std::string userPrompt) {
	FETCHED_DATA.clear();

	std::string promptContent = userPrompt;
	CURL* hnd = curl_easy_init();

	curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "POST");
	curl_easy_setopt(hnd, CURLOPT_URL, "https://openai80.p.rapidapi.com/images/generations");

	struct curl_slist* headers = NULL;
	headers = curl_slist_append(headers, "content-type: application/json");
	headers = curl_slist_append(headers, "X-RapidAPI-Key: 25cb8e9ae5msh86d80a2b1842102p10d2e0jsnc5f2eb6ec7c9");
	headers = curl_slist_append(headers, "X-RapidAPI-Host: openai80.p.rapidapi.com");
	curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);
	std::string jsonPayload = "{\r\n    \"prompt\": \"" + promptContent + "\",\r\n    \"n\": 1,\r\n    \"size\": \"512x512\"\r\n}";
	curl_easy_setopt(hnd, CURLOPT_POSTFIELDS,jsonPayload.c_str() );

	//write callback to a string
	curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(hnd, CURLOPT_WRITEDATA, &FETCHED_DATA);
	
	CURLcode ret = curl_easy_perform(hnd);

	//checks if the fetch is done
	CHECK_FETCH(ret);
	//cleaning up
	curl_easy_cleanup(hnd);
}

void DallE::proccess_json() {
	//std::cout << FETCHED_DATA << std::endl;
	Res.Parse(FETCHED_DATA.c_str());
	const rapidjson::Value& data = Res["data"];
	//std::cout << resp.GetString() << std::endl;
	if (Res.HasMember("data")) {
		const rapidjson::Value& resp = data[0]["url"];
		showImage(resp.GetString());
	}
	if (Res.HasMember("messages")) {
		std::cout << Res["messages"].GetString() << std::endl;
	}

}
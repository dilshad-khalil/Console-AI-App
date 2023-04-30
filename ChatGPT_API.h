#define CURL_STATICLIB
#pragma once
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <iostream>
#include <string>
#include <Windows.h>
#include <curl/curl.h>
#include <conio.h>
#include "Animate.h"
#include "writeData.h"
#include <fstream>
Animate AnimateText;


class Data {
public:
	std::string FETCHED_DATA;
	void API_DATA_FETCH(std::string user_message);
	void CHECK_FETCH(CURLcode result);
	void proccess_json();
    rapidjson::Document Res;
};

void Data::CHECK_FETCH(CURLcode result) {
    if (result == CURLE_OK) {
        std::cout << "\033[31m";
        AnimateText.AnimateText("Console Ai/>", 20);
        std::cout << "\033[0m";
        proccess_json();
    }
    else {
        // Handle Curl errors
        std::cerr << "Curl error: " << curl_easy_strerror(result) << std::endl;
    }
}

void Data::API_DATA_FETCH(std::string user_message) {
    std::string messageContent = user_message;
    CURL* hnd = curl_easy_init();

    curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "POST");
    curl_easy_setopt(hnd, CURLOPT_URL, "https://openai80.p.rapidapi.com/chat/completions");

    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "content-type: application/json");
    headers = curl_slist_append(headers, "X-RapidAPI-Key: 25cb8e9ae5msh86d80a2b1842102p10d2e0jsnc5f2eb6ec7c9");
    headers = curl_slist_append(headers, "X-RapidAPI-Host: openai80.p.rapidapi.com");
    curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);
    std::string jsonPayload = "{\r\n    \"model\": \"gpt-3.5-turbo\",\r\n    \"messages\": [\r\n        {\r\n            \"role\": \"user\",\r\n            \"content\": \"" + messageContent + "\"\r\n        }\r\n    ]\r\n}";
    curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jsonPayload.c_str());

    //write callback to a string
    curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(hnd, CURLOPT_WRITEDATA, &FETCHED_DATA);

    CURLcode ret = curl_easy_perform(hnd);

    //checks if the fetch is done
    CHECK_FETCH(ret);
    //cleaning up
    curl_easy_cleanup(hnd);

}

void Data::proccess_json() {
    std::ofstream gptResponse("./ConsoleAI/gptResponse/responses.txt", std::ios_base::app);
    
    Res.Parse(FETCHED_DATA.c_str());
    if (Res.HasMember("choices") && Res["choices"].IsArray()) {
        const rapidjson::Value& res = Res["choices"][0]["message"]["content"];
        AnimateText.AnimateText(res.GetString(), 30);
        std::cout << std::endl;
        FETCHED_DATA.clear();
        if (gptResponse.is_open()) {
            gptResponse << res.GetString() << std::endl;
            gptResponse << "***********************************************************" << std::endl;
        }
        else {
            std::cout << "Error Opening file Please make sure the folder exists and try again" << std::endl;
        }
    }
    if (!(Res.HasMember("choices") && Res["choices"].IsArray())) {
        const rapidjson::Value& error_message = Res["message"];
        AnimateText.AnimateText(error_message.GetString(), 30);
        std::cout << std::endl;
        FETCHED_DATA.clear();
    }
}


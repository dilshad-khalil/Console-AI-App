#pragma once
#include <iostream>
#include <string>
//to write the callback into a string
extern size_t WriteCallback(char* contents, size_t size, size_t nmemb, std::string* s)
{
    size_t newLength = size * nmemb;
    try
    {
        s->append(contents, newLength);
    }
    catch (std::bad_alloc& e)
    {
        // Handle memory allocation errors
        return 0;
    }
    return newLength;
}
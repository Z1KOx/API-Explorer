#include "api.h"
#include <curl/curl.h>
#include <nlohmann/json.hpp>

bool API::found = false;
bool API::requested = false;
std::string API::userApiLink = "";
std::string API::response = "";

size_t API::writeCallback(void* contents, size_t size, size_t nmemb, std::string* response)
{
    // Calculate total size of the received data
    size_t totalSize = size * nmemb;

    // Append the received data to the response string
    response->append((char*)contents, totalSize);
    return totalSize;
}

std::string API::getAPI()
{
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    // Initialize libcurl
    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, userApiLink.c_str());      // Set the URL to retrieve
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);  // Set the write callback function to handle the received data
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);        // Pass a pointer to the response string as the userdata parameter

        // Perform the request res will get the return code
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) 
            found = false;
        else 
        {
            // Store the response in the member variable
            response = readBuffer;
            found = true;
        }

        // Cleanup
        curl_easy_cleanup(curl);
    }

    return response;
}

#include "api.h"
#include <curl.h>

bool API::found = false;
bool API::requested = false;
std::string API::userApiLink = "";
std::string API::response = "";

size_t API::writeCallback(void* contents, size_t size, size_t nmemb, std::string* response)
{
    size_t totalSize = size * nmemb;
    response->append((char*)contents, totalSize);
    return totalSize;
}

std::string API::getAPI()
{
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, userApiLink.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) 
            found = false;
        else 
        {
            response = readBuffer;
            found = true;
        }

        curl_easy_cleanup(curl);
    }

    return response;
}

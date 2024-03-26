#ifndef API_H
#define API_H

#include <string>

class API {
public:
    static bool requested;
    static bool found;
    static std::string userApiLink;
    static std::string response;

    static size_t writeCallback(void* contents, size_t size, size_t nmemb, std::string* response);
    static std::string getAPI();
};

#endif // API_H

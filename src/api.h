#ifndef API_H
#define API_H

#include <string>

class API 
{
private:
	static bool m_foundAPI;
public:
	static bool m_requested;
	static std::string m_userApiLink;
	static std::string m_response;

	static size_t writeCallback(
		void* contents,
		size_t size,
		size_t nmemb,
		std::string* response) noexcept;

	static std::string getAPI() noexcept;
};

#endif // API_H

#include "downloader.h"
#include <fstream>
#include <memory>
#include <iostream>
#include <algorithm>

Downloader::Downloader(const Logger *log) : logger(log)
{
	curl = curl_easy_init();
}

Downloader::~Downloader()
{
    curl_easy_cleanup(curl);
}

bool Downloader::Load(const std::string_view& urlPath, const std::string_view& savePathFile)
{
	std::ofstream file = std::ofstream(savePathFile.data());

	curl_easy_setopt(curl, CURLOPT_URL, urlPath.data());
	curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/67.0.3396.62 Safari/537.36");
	curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8");
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
	curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2_0);
	curl_easy_setopt(curl, CURLOPT_CA_CACHE_TIMEOUT, 604800L);

	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, +[](void* ptr, std::size_t size, std::size_t nmemb, std::ofstream *stream) -> std::size_t
	{
		stream->write((char*)ptr, size*nmemb);
		return size*nmemb;
	});
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &file);
	auto res = curl_easy_perform(curl);
    logger->Log("Succesfull download");
	return res == CURLE_OK;
}
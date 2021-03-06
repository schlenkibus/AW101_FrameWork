#pragma once

#include <string>
#include <curl/curl.h>
#include <iostream>

static std::string readBuffer;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    readBuffer = std::string((char*)contents, realsize);
    return realsize;
}

class HTTPClient {
public:

    static std::string performRequest(std::string urlPlusPayload) {
        auto url = std::move(urlPlusPayload);
        auto curl = curl_easy_init();
        std::cout << url << std::endl;
        char buffer[500];
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_0);
        curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
        curl_easy_setopt(curl, CURLOPT_FORBID_REUSE, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        auto err = curl_easy_perform(curl);
        return readBuffer;
    }
};

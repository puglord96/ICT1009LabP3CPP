#include <iostream>
#include <fstream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

// for convenience
using json = nlohmann::json;


using namespace std;


static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main(void)
{
    CURL* curl;
    CURLcode res;
    string readBuffer;
    ofstream myfile;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.pushshift.io/reddit/search/comment/?q=kobe");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);


       // cout << readBuffer << endl;
        ofstream file("data.json");
        file << readBuffer;
        file.close();

    }

    std::ifstream jsonFile("data.json");
    nlohmann::json commands;
    jsonFile >> commands;
 
    nlohmann::json data = commands["data"];
    std::cout << "Number of items in Data: " << data.size() << std::endl;

    json test = data[1];

    for (auto it = test.begin(); it != test.end(); ++it)
    {
        std::cout << it.key() << ": " << it.value() << std::endl;
    }
    return 0;
}
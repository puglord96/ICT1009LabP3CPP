#include <iostream>
#include <iomanip>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <ctime>

#include "RedditPost.h"


//RedditPost redditposts[];

#define _CRT_SECURE_NO_WARNINGS



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
        //Curl is being used to get the html contents from the URL
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.pushshift.io/reddit/search/comment/?q=kobe%20bryant&size=50");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);


        //Contents extracted from curl is outputted into a JSON file
        ofstream file("data.json");
        file << readBuffer;
        file.close();

    }


    //Contents from json file is extracted and fed into the nholmann::json commands
    ifstream jsonFile("data.json");
    json commands;
    jsonFile >> commands;
 
    //data is the array which contains the content found in the json
    json data = commands["data"];


    // redditposts vector is used to store all the RedditPost objects generated
    vector<RedditPost> redditposts = {};
 

    //loop through the whole data array and extract all the relevant information to create the RedditPost objects
   for (int i = 0; i < data.size();i++) {

       time_t t = data[i]["created_utc"];



       string title = data[i]["body"];
       int likecount = data[i]["score"];
       string uname = data[i]["author"];
       string postdate = ctime(&t);
       string postsub = data[i]["subreddit"];
       string postlink = data[i]["permalink"];


       //Create RedditPost object
       RedditPost post(title, likecount, uname, postdate, postsub, postlink);

       //Insert object into vector
       redditposts.insert(redditposts.begin(), post);
    
       for (vector<RedditPost>::iterator r_ite = redditposts.begin(); r_ite != redditposts.end(); r_ite++) {
           cout << *r_ite << endl;
       }

      


      
    }


    return 0;
}
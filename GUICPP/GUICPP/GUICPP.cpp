#include "GUICPP.h"
#include "post.h"
#include "RedditPost.h"
#include "TwitterPost.h"

#include <qtablewidget.h>
#include <qtabwidget.h>
#include <QtWidgets/QApplication>

#include <time.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <ctime>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <locale>
#include <codecvt>
#include <fstream>
#include <regex>
#include <cctype>
#include <iostream>
#include <string>

#include <cpprest/http_client.h>
#include <cpprest/oauth1.h>
#include "json/json.h"

using namespace std;

//#include "twitter.cpp"

#define _CRT_SECURE_NO_WARNINGS



// for convenience
using json = nlohmann::json;
using namespace std;
using namespace utility;
using namespace web::http;


class twitterCrawler {
private:

    vector<TwitterPost> tweetList;

    //API keys for Twitter
    static constexpr auto
        consumerKey = U("uxP2xkp0iGQP7UKB70PuD4bNe"),
        consumerKeySecret = U("nZObs8qkpACDNCt8v9ZsikgXdU22aeU3ChfHZdG6B7FMDQheyc"),
        myOAuthAccessTokenKey = U("221371528-gyQixF6MxPB79o2FB66E0llBP6rG5UJ31G2EVHZN"),
        myOAuthAccessTokenKeySecret = U("rntSl0F6SDTcxu4JxbXa4gEwKfPXy7FrYLrWoatDwmvfF");

    //Crawler Configs
    client::http_client_config http_client_config;
    oauth1::experimental::oauth1_config oauth1_config{
        consumerKey,
        consumerKeySecret,
        U("https://api.twitter.com/oauth/request_token"),
        U("https://api.twitter.com/oauth/authorize"),
        U("https://api.twitter.com/oauth/access_token"),
        U(""),
        web::http::oauth1::experimental::oauth1_methods::hmac_sha1
    };

public:
    twitterCrawler();
    void crawl(string);
    string cleanseString(string, const string&, const string&);
    vector<TwitterPost> getTweets();
    void printTweets();
};

twitterCrawler::twitterCrawler() {
    //loads OAuthConfig to HTTP client
    http_client_config.set_oauth1(oauth1_config);
}

vector<TwitterPost> twitterCrawler::getTweets() {
    //returns list of tweets
    return tweetList;
}

string twitterCrawler::cleanseString(string str, const string& from, const string& to) {
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}

void twitterCrawler::crawl(string query) {
    wstring_convert<codecvt_utf8<wchar_t>, wchar_t> converter;

    //Builds query URL
    string qurl = "search/tweets.json?q=" + query + "&lang=en&result_type=mixed&count=30";
    string_t search_query(qurl.begin(), qurl.end());

    //Retrieves JSON from the api call
    client::http_client api{ U("https://api.twitter.com/1.1/"), http_client_config };
    auto root = api.request(methods::GET, search_query).get().extract_json().get();

    //Extracts from the returned JSON
    auto results = root.at(U("statuses"));

    for (int i = 0; i < results.size(); i++) {
        // Gets Username
        auto users = results[i][U("user")];
        string uname = converter.to_bytes(users[U("screen_name")].as_string());
        uname = cleanseString(uname, string(","), string(" "));
        uname = cleanseString(uname, string("\n"), string(" "));
        //cout << uname << endl;

        //Gets Date Posted of Tweet
        string t_datetime = converter.to_bytes(results[i][U("created_at")].as_string());
        //cout << t_datetime << endl;

        //Gets Metrics of Tweet
        int fv_count = results[i][U("favorite_count")].as_integer();
        int rt_count = results[i][U("retweet_count")].as_integer();
        //cout << fv_count << endl;
        //cout << rt_count << endl;

        //Gets Tweet Content
        string t_post = converter.to_bytes(results[i][U("text")].as_string());
        t_post = cleanseString(t_post, string(","), string(" "));
        t_post = cleanseString(t_post, string("\n"), string(" "));
        //cout << t_post << endl;

        //Saves tweet data as an object
        TwitterPost tweet(t_post, fv_count, uname, t_datetime, rt_count);

        //Adds Tweet Object to List
        tweetList.insert(tweetList.begin(), tweet);

        

    }
}

void twitterCrawler::printTweets() {
    //prints out all crawled tweets
    for (vector<TwitterPost>::iterator tweetList_iterator = tweetList.begin(); tweetList_iterator != tweetList.end(); tweetList_iterator++) {
        cout << *tweetList_iterator << endl;
    }
}

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

GUICPP::GUICPP(QWidget *parent)
	: QWidget(parent)
{
    CURL* curl;
    CURLcode res;
    string readBuffer, redditCurlURL;
    ofstream myfile;
    ui.setupUi(this);

    ui.redditTableWidget->setColumnCount(6);
    ui.redditTableWidget->setRowCount(50);
    ui.redditTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui.twittertableWidget->setColumnCount(5);
    ui.twittertableWidget->setRowCount(30);
    ui.twittertableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //Query vector contains substring of the query string of the Reddit Crawler API
    vector<string> query;
    query.push_back("?q=kobe%20bryant&size=50");
    query.push_back("?q=mambacita&size=50");
    query.push_back("?q=gianna%20bryant&size=50");

    // redditposts vector is used to store all the RedditPost objects generated
    vector<RedditPost> redditposts = {};

    for(auto&& querySub : query) {

        //URL of Reddit Crawler API
        redditCurlURL = "https://api.pushshift.io/reddit/search/comment/" + querySub;


        curl = curl_easy_init();
        if (curl) {
            //Curl is being used to get the html contents from the URL
            curl_easy_setopt(curl, CURLOPT_URL, redditCurlURL.c_str());
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



        vector<TwitterPost> tlist;

        //loop through the whole data array and extract all the relevant information to create the RedditPost objects
        for (int i = 0; i < data.size(); i++) {

            time_t t = data[i]["created_utc"];

            string title = data[i]["body"];
            int likecount = data[i]["score"];
            string uname = data[i]["author"];
            string postdate = ctime(&t);
            string postsub = data[i]["subreddit"];
            string postlink = data[i]["permalink"];

            //Reddit tableview
            QString qtitle = QString::fromStdString(title);
            QString qlikecount = QString::number(likecount);
            QString quname = QString::fromStdString(uname);
            QString qpostdate = QString::fromStdString(postdate);
            QString qpostsub = QString::fromStdString(postsub);
            QString qpostlink = QString::fromStdString(postlink);

            ui.redditTableWidget->setItem(i, 0, new QTableWidgetItem(qtitle));
            ui.redditTableWidget->setItem(i, 1, new QTableWidgetItem(qlikecount));
            ui.redditTableWidget->setItem(i, 2, new QTableWidgetItem(quname));
            ui.redditTableWidget->setItem(i, 3, new QTableWidgetItem(qpostdate));
            ui.redditTableWidget->setItem(i, 4, new QTableWidgetItem(qpostsub));
            ui.redditTableWidget->setItem(i, 5, new QTableWidgetItem(qpostlink));



            //Create RedditPost object
            RedditPost post(title, likecount, uname, postdate, postsub, postlink);

            //Insert object into vector
            redditposts.insert(redditposts.begin(), post);


            twitterCrawler t_crawl;

            t_crawl.crawl("kobe%20bryant");

            tlist = t_crawl.getTweets();


           
            t_crawl.printTweets();

            for (vector<TwitterPost>::iterator tweetlist_ptr = tlist.begin(); tweetlist_ptr < tlist.end(); tweetlist_ptr++) {
                cout << *tweetlist_ptr << endl;
            }

        }

        for (int i = 0; i  < tlist.size(); i++) {
            string t_post = tlist[i].getPostContent();
            int fv_count = tlist[i].getLikeCount();
            string uname1 = tlist[i].getUsername();
            string t_datetime = tlist[i].getPostDate();
            int rt_count = tlist[i].getRTCount();

            QString qt_post = QString::fromStdString(t_post);
            QString qfv_count = QString::number(fv_count);
            QString quname1 = QString::fromStdString(uname1);
            QString qt_datetime = QString::fromStdString(t_datetime);
            QString qrt_count = QString::number(rt_count);

            ui.twittertableWidget->setItem(i, 0, new QTableWidgetItem(qt_post));
            ui.twittertableWidget->setItem(i, 1, new QTableWidgetItem(qfv_count));
            ui.twittertableWidget->setItem(i, 2, new QTableWidgetItem(quname1));
            ui.twittertableWidget->setItem(i, 3, new QTableWidgetItem(qt_datetime));
            ui.twittertableWidget->setItem(i, 4, new QTableWidgetItem(qrt_count));
        }
        ui.redditTableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
        ui.twittertableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

    }



    for (vector<RedditPost>::iterator r_ite = redditposts.begin(); r_ite != redditposts.end(); r_ite++) {
        cout << *r_ite << endl;
    }

    cout << redditposts.size();

	
}

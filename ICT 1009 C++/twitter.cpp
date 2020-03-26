#pragma once

#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <locale>
#include <codecvt>
#include <fstream>
#include <regex>
#include <cctype>

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include "json/json.h"
#include "TwitterPost.h"

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
	string qurl = "search/tweets.json?q=" + query + "&lang=en&result_type=mixed&count=80";
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


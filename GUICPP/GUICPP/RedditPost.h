#pragma once

#include <iostream>

#include "Post.h"

using namespace std;

class RedditPost : public Post {
    friend ostream& operator<<(ostream&, const RedditPost&);
private:
    string p_subreddit;
    string p_link;

public:
    RedditPost(string, int, string, string, string, string);    // postContent, likeCount, username, postDate, subreddit, link, commentcount
    string getPostSubreddit();
    string getPostLink();
};


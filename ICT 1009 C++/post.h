#pragma once

#include <iostream>

using namespace std;

class Post
{
private:
    string postContent;
    int likeCount;
    string username;
    string postDate;

public:
    Post(string, int, string, string); // postContent, likeCount, username, postDate
    string getPostContent();
    int getLikeCount();
    string getUsername();
    string getPostDate();
};

class RedditPost : public Post {
private:
    string p_subreddit;
    string p_link;
    int p_commentcount;
    // list for comments?

public:
    RedditPost(string, int, string, string, string, string, int);    // postContent, likeCount, username, postDate, subreddit, link, commentcount
    string getPostSubreddit();
    int getPostCommentCount();
    string getPostLink();
};

class TwitterPost : public Post {
private:
    int RTCount;

public:
    TwitterPost(string, int, string, string, int); // postContent, likeCount, username, postDate, RTCount
    int getRTCount();
};
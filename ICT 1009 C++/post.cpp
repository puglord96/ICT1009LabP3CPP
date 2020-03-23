#pragma once

#ifndef POST_H
#define POST_H

#include "Post.h"

Post::Post(string title, int likecount, string uname, string postdate)
{
    postContent = title;
    likeCount = likecount;
    username = uname;
    postDate = postdate;
}

string Post::getPostContent()
{
    return postContent;
}

int Post::getLikeCount()
{
    return likeCount;
}

string Post::getUsername()
{
    return username;
}

string Post::getPostDate()
{
    return postDate;
}

#endif

#ifndef RPOST_H
#define RPOST_H

RedditPost::RedditPost(string title, int likecount, string uname, string postdate, string postsub, string postlink, int postcommentcount) : Post(title, likecount, uname, postdate) {
    p_subreddit = postsub;
    p_link = postlink;
    p_commentcount = postcommentcount;
}

string RedditPost::getPostSubreddit()
{
    return p_subreddit;
}

int RedditPost::getPostCommentCount()
{
    return p_commentcount;
}

string RedditPost::getPostLink()
{
    return p_link;
}

#endif

#ifndef TPOST_H
#define TPOST_H

TwitterPost::TwitterPost(string title, int favcount, string uname, string postdate, int rtcount) : Post(title, favcount, uname, postdate) {
    RTCount = rtcount;
}

int TwitterPost::getRTCount() {
    return RTCount;
}

#endif
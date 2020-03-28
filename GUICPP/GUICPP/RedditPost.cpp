#pragma once

#ifndef RPOST_H
#define RPOST_H

#include "RedditPost.h"

RedditPost::RedditPost(string title, int likecount, string uname, string postdate, string postsub, string postlink) : Post(title, likecount, uname, postdate) {
	p_subreddit = postsub;
	p_link = postlink;
}

string RedditPost::getPostSubreddit()
{
	return p_subreddit;
}

string RedditPost::getPostLink()
{
	return p_link;
}

ostream& operator<<(ostream& out, const RedditPost& rp)
{
	out << "Post: " << rp.postContent << endl;
	out << "Posted by: " << rp.username << endl;
	out << "Posted on: " << rp.postDate << endl;
	out << "Upvote Count: " << rp.likeCount << endl;
	out << "Posted to: " << rp.p_subreddit << endl;
	out << endl;
	return out;
}

#endif
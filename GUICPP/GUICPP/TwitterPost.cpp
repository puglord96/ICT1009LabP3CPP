#pragma once

#ifndef TPOST_H
#define TPOST_H

#include <iostream>
#include "TwitterPost.h"

TwitterPost::TwitterPost(string title, int favcount, string uname, string postdate, int rtcount) : Post(title, favcount, uname, postdate) {
	RTCount = rtcount;
}

int TwitterPost::getRTCount() {
	return RTCount;
}

ostream& operator<<(ostream& out, const TwitterPost& tp)
{
	out << "Tweet: " << tp.postContent << endl;
	out << "Tweeted by: " << tp.username << endl;
	out << "Tweeted on: " << tp.postDate << endl;
	out << "Favourite Count: " << tp.likeCount << endl;
	out << "Retweet Count: " << tp.RTCount << endl;
	out << endl;
	return out;
}

#endif

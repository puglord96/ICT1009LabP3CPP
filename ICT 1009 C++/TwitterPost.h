#pragma once

#include <iostream>

#include "Post.h"

using namespace std;

class TwitterPost : public Post {
private:
    int RTCount;

public:
    TwitterPost(string, int, string, string, int); // postContent, likeCount, username, postDate, RTCount
    int getRTCount();
};
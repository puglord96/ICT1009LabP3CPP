#pragma once

#ifndef TPOST_H
#define TPOST_H

#include "TwitterPost.h"

TwitterPost::TwitterPost(string title, int favcount, string uname, string postdate, int rtcount) : Post(title, favcount, uname, postdate) {
    RTCount = rtcount;
}

int TwitterPost::getRTCount() {
    return RTCount;
}

#endif
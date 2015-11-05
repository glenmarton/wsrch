#include "wsrch2BuildTime.h"

wsrch2BuildTime::wsrch2BuildTime()
: dateTime(__DATE__ " " __TIME__)
{
}

wsrch2BuildTime::~wsrch2BuildTime()
{
}

const char* wsrch2BuildTime::GetDateTime()
{
    return dateTime;
}


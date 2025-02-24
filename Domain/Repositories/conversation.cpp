#include "conversation.h"

string Conversation::dateConversion(const tm& date)
{
    unsigned int year = date.tm_year + 1900;
    unsigned short month = date.tm_mon + 1;
    unsigned short day = date.tm_mday;
    if (day < 1) day = 1;

    ostringstream dateStream;
    dateStream << setw(4) << setfill('0') << year << "-"
        << setw(2) << setfill('0') << month << "-"
        << setw(2) << setfill('0') << day;
    
    return dateStream.str();
}
tm Conversation::dateConversion(const string& date)
{
    tm tm = {};
    istringstream dateStream(date);
    dateStream >> get_time(&tm, "%Y-%m-%d");
    
    return tm;
}

string Conversation::statusConversion(const Status& status)
{
    INFO("AccountRepository -> method status—onversion (type::status): called;");

    switch (status)
    {
        case Status::active: { return "ACTIVE"; } break;
        case Status::frozen: { return "FROZEN"; } break;
        case Status::closed: { return "CLOSED"; } break;
        default: { return "FROZEN"; }
    }
}
Status Conversation::statusConversion(const string& status)
{
    INFO("AccountRepository -> method status—onversion (type::string): called;");

    if (status == "ACTIVE") { return Status::active; }
    else if (status == "FROZEN") { return Status::frozen; }
    else if (status == "CLOSED") { return Status::closed; }
    else { return Status::frozen; }
}
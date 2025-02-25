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

string Conversation::statusConversion(const AccountStatus& status)
{
    INFO("AccountRepository -> method status—onversion (type::status): called;");

    switch (status)
    {
        case AccountStatus::active: { return "ACTIVE"; } break;
        case AccountStatus::frozen: { return "FROZEN"; } break;
        case AccountStatus::closed: { return "CLOSED"; } break;
        default: { return "FROZEN"; }
    }
}
AccountStatus Conversation::statusConversion(const string& status)
{
    INFO("AccountRepository -> method status—onversion (type::string): called;");

    if (status == "ACTIVE") { return AccountStatus::active; }
    else if (status == "FROZEN") { return AccountStatus::frozen; }
    else if (status == "CLOSED") { return AccountStatus::closed; }
    else { return AccountStatus::frozen; }
}

string Conversation::statusConversion(const TransactionStatus& status, bool indi)
{
    INFO("AccountRepository -> method status—onversion (type::status): called;");

    switch (status)
    {
    case TransactionStatus::pending: { return "PENDING"; } break;
    case TransactionStatus::completed: { return "COMPLETED"; } break;
    case TransactionStatus::canceled: { return "CANCELED"; } break;
    default: { return "PENDING"; }
    }
}
TransactionStatus Conversation::statusConversion(const string& status, bool indi)
{
    INFO("AccountRepository -> method status—onversion (type::string): called;");

    if (status == "PENDING") { return TransactionStatus::pending; }
    else if (status == "COMPLETED") { return TransactionStatus::completed; }
    else if (status == "CANCELED") { return TransactionStatus::canceled; }
    else { return TransactionStatus::pending; }
}
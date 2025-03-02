#include "../../../Core/Libs/domainConfig.h"
#include "cardRepository.h"
#include "../conversation.h"

CardRepository::CardRepository() { CREATE_INFO("CardRepository <- Constructor: called;"); }

size_t CardRepository::_add(size_t& accountId, const string& cardNumber, const string& isBlocked, const string& isJarStr, const unsigned short& jarPercentage)
{
    INFO("CardRepository -> method add (value, isBlocked = type::string): called;");

    try
    {
        size_t newCardId = stoi(Queries::executeCommand(Queries::Cards::insertCard(accountId, cardNumber, isBlocked, isJarStr, jarPercentage)));

        INFO("CardRepository -> method add -> result: success;");
        return newCardId;
    }
    catch (const exception& e) { ERROR(string("CardRepository -> method add -> try/catch (exception): ") + e.what() + ";"); return -1; }
    catch (...) { ERROR("CardRepository -> method add -> try/catch (...): error!;"); return -1; }
}
size_t CardRepository::add(size_t& accountId, const string& cardNumber, const bool& isBlocked, const bool& isJar, const unsigned short& jarPercentage)
{
    INFO("CardRepository -> method add (value, isBlocked = type::bool): called;");

    return _add(accountId, cardNumber, isBlocked ? "t" : "f", isJar ? "t" : "f", jarPercentage);
}
size_t CardRepository::add(const Card* card)
{
    INFO("CardRepository -> method add (obj): called;");

    size_t accountId = card->accountId;
    return add(accountId, card->cardNumber, card->isBlocked, card->isJar, card->jarPercentage);
}

Card* CardRepository::get(size_t id)
{
    INFO("CardRepository -> method get: called;");

    try
    {
        string result = Queries::executeCommand(Queries::Cards::getCard(id));

        size_t pos = result.find('\n');
        if (pos != string::npos) { result = result.substr(pos + 1); }

        Card* card = new Card;
        istringstream iss(result);
        string token;

        getline(iss, token, '|'); card->cardId = stoi(token);
        getline(iss, token, '|'); card->accountId = stoi(token);
        getline(iss, token, '|'); card->cardNumber = token;
        getline(iss, token, '|'); card->expiryDate = Conversation::dateConversion(token);
        getline(iss, token, '|'); card->isBlocked = (token == "t");
        getline(iss, token, '|'); card->issueDate = Conversation::dateConversion(token);
        getline(iss, token, '|'); card->isJar = (token == "t");
        getline(iss, token, '|'); card->jarPercentage = stoi(token);

        INFO("CardRepository -> method get -> result: success;");
        return card;
    }
    catch (const exception& e) { ERROR(string("CardRepository -> method get -> try/catch (exception): ") + e.what() + ";"); return nullptr; }
    catch (...) { ERROR("CardRepository -> method get -> try/catch (...): error!;"); return nullptr; }
}

bool CardRepository::_update(const size_t& accountId, const string& expiryDateStr, const string& isBlockedStr, const string& isJarStr, const unsigned short& jarPercentage)
{
    INFO("CardRepository -> method update (value, dates = type::string, isBlocked = type::string, dates = type::string): called;");

    try
    {
        string result = Queries::executeCommand(Queries::Cards::updateCard(accountId, expiryDateStr, isBlockedStr, isJarStr, jarPercentage));

        INFO("CardRepository -> method update -> result: success;");
        return true;
    }
    catch (const exception& e) { ERROR(string("CardRepository -> method update -> try/catch (exception): ") + e.what() + ";"); return false; }
    catch (...) { ERROR("CardRepository -> method update -> try/catch (...): error!;"); return false; }
}
bool CardRepository::update(const size_t& accountId, const tm& expiryDate, const bool& isBlocked, const bool& isJar, const unsigned short& jarPercentage)
{
    INFO("CardRepository -> method update (value, isBlocked = type::bool, dates = type::tm): called;");

    return _update(accountId,  Conversation::dateConversion(expiryDate), isBlocked ? "t" : "f", isJar ? "t" : "f", jarPercentage);
}
bool CardRepository::update(const Card* card)
{
    INFO("CardRepository -> method update (obj): called;");

    return update(card->accountId, card->expiryDate, card->isBlocked, card->isJar, card->jarPercentage);
}

bool CardRepository::deleteClass(size_t id)
{
    INFO("CardRepository -> method deleteClass: called;");

    try
    {
        Queries::executeCommand(Queries::Cards::deleteCard(id));

        INFO("CardRepository -> method deleteClass -> result: success;");
        return true;
    }
    catch (const exception& e) {
        ERROR(string("CardRepository -> method deleteClass -> try/catch (exception): ") + e.what() + ";"); return false; }
    catch (...) { ERROR("CardRepository -> method deleteClass -> try/catch (...): error!;"); return false; }
}
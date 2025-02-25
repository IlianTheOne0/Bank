#include "../../../Core/Libs/domainConfig.h"
#include "cardRepository.h"
#include "../conversation.h"

CardRepository::CardRepository() { CREATE_INFO("CardRepository <- Constructor: called;"); }

size_t CardRepository::_add(size_t& accountId, const string& cardNumber, const bool& isBlocked)
{
    INFO("CardRepository -> method add (value, dates = type::string): called;");

    try
    {
        size_t newCardId = stoi(Queries::executeCommand(Queries::Cards::insertCard(accountId, cardNumber, isBlocked)));

        INFO("CardRepository -> method add -> result: success;");
        return newCardId;
    }
    catch (const exception& e) { ERROR(string("CardRepository -> method add -> try/catch (exception): ") + e.what() + ";"); return -1; }
    catch (...) { ERROR("CardRepository -> method add -> try/catch (...): error!;"); return -1; }
}
size_t CardRepository::add(size_t& accountId, const string& cardNumber, const bool& isBlocked)
{
    INFO("CardRepository -> method add (value, status = type::Status): called;");

    return _add(accountId, cardNumber, isBlocked);
}
size_t CardRepository::add(const Card* card)
{
    INFO("CardRepository -> method add (obj): called;");

    size_t accountId = card->accountId;
    return add(accountId, card->cardNumber, card->isBlocked);
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

        INFO("CardRepository -> method get -> result: success;");
        return card;
    }
    catch (const exception& e) { ERROR(string("CardRepository -> method get -> try/catch (exception): ") + e.what() + ";"); return nullptr; }
    catch (...) { ERROR("CardRepository -> method get -> try/catch (...): error!;"); return nullptr; }
}

bool CardRepository::_update(const size_t& accountId, const string& cardNumber, const string& expiryDateStr, const string& isBlockedStr, const string& issueDateStr)
{
    INFO("CardRepository -> method update (value, dates = type::string, clientRegistrationDate = type::string): called;");

    try
    {
        string result = Queries::executeCommand(Queries::Cards::updateCard(accountId, cardNumber, expiryDateStr, isBlockedStr, issueDateStr));

        INFO("CardRepository -> method update -> result: success;");
        return true;
    }
    catch (const exception& e) { ERROR(string("CardRepository -> method update -> try/catch (exception): ") + e.what() + ";"); return false; }
    catch (...) { ERROR("CardRepository -> method update -> try/catch (...): error!;"); return false; }
}
bool CardRepository::update(const size_t& accountId, const string& cardNumber, const tm& expiryDate, const bool& isBlocked, const tm& issueDate)
{
    INFO("CardRepository -> method update (value, dates = type::tm, status = type::Status): called;");

    return _update(accountId, cardNumber, Conversation::dateConversion(expiryDate), isBlocked ? "t" : "f", Conversation::dateConversion(issueDate));
}
bool CardRepository::update(const Card* card)
{
    INFO("CardRepository -> method update (obj): called;");

    return update(card->accountId, card->cardNumber, card->expiryDate, card->isBlocked, card->issueDate);
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
        ERROR(string("CardRepository -> method deleteClass -> try/catch (exception): ") + e.what() + ";"); return false;
    }
    catch (...) { ERROR("CardRepository -> method deleteClass -> try/catch (...): error!;"); return false; }
}
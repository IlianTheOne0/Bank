#include "../../../Core/Libs/domainConfig.h"
#include "accountRepository.h"
#include "../conversation.h"

AccountRepository::AccountRepository() { CREATE_INFO("AccountRepository <- Constructor: called;"); }

size_t AccountRepository::_add(size_t& clientId, const float& balance, const string& currency, const string& statusStr, const string& password, const string& salt, const string& adminStatusStr)
{
    INFO("AccountRepository -> method add (value, status = type::string): called;");

    try
    {
        size_t newAccountId = stoi(Queries::executeCommand(Queries::Accounts::insertAccount(clientId, balance, currency, statusStr, password, salt, adminStatusStr)));

        INFO("AccountRepository -> method add -> result: success;");
        return newAccountId;
    }
    catch (const exception& e) { ERROR(string("AccountRepository -> method add -> try/catch (exception): ") + e.what() + ";"); return -1; }
    catch (...) { ERROR("AccountRepository -> method add -> try/catch (...): error!;"); return -1; }
}
size_t AccountRepository::add(size_t& clientId, const float& balance, const string& currency, const AccountStatus& status, const string& password, const string& salt, const bool& adminStatus)
{
    INFO("AccountRepository -> method add (value, status = type::AccountStatus): called;");
    
    string adminStatusStr = ((adminStatus) ? "t" : "f");
    return _add(clientId, balance, currency, Conversation::statusConversion(status), password, salt, adminStatusStr);
}
//size_t AccountRepository::add(const Account* account, const string& salt)
//{
//    INFO("AccountRepository -> method add (obj): called;");
//
//    size_t clientId = account->getClientId();
//    return add(clientId, account->getBalance(), account->getCurrency(), account->getStatus(), account->getPassword(), salt, account->getAdminStatus());
//}

Account* AccountRepository::get(size_t id)
{
    INFO("AccountRepository -> method get: called;");

    try
    {
        string result = Queries::executeCommand(Queries::Accounts::getAccount(id));

        size_t pos = result.find('\n');
        if (pos != string::npos) { result = result.substr(pos + 1); }

        Account* account = new Account;
        istringstream iss(result);
        string token;

        getline(iss, token, '|'); account->setAccountId(stoi(token));
        getline(iss, token, '|'); account->setClientId(stoi(token));
        getline(iss, token, '|'); account->setBalance(stof(token));
        getline(iss, token, '|'); account->setCurrency(token);
        getline(iss, token, '|'); account->setOpenedDate(Conversation::dateConversion(token));
        getline(iss, token, '|'); account->setClosedDate(Conversation::dateConversion(token));
        getline(iss, token, '|'); account->setStatus(Conversation::statusConversion(token));

        INFO("AccountRepository -> method get -> result: success;");
        return account;
    }
    catch (const exception& e) { ERROR(string("AccountRepository -> method get -> try/catch (exception): ") + e.what() + ";"); return nullptr; }
    catch (...) { ERROR("AccountRepository -> method get -> try/catch (...): error!;"); return nullptr; }
}

bool AccountRepository::_update(const size_t& accountId, const float& balance, const string& currency, const string& openedDateStr, const string& closedDateStr, const string& status, const string& password, const string& adminStatusStr)
{
    INFO("AccountRepository -> method update (value, dates = type::string, clientRegistrationDate = type::string): called;");

    try
    {
        string result = Queries::executeCommand(Queries::Accounts::updateAccount(accountId, balance, currency, openedDateStr, closedDateStr, status, password, adminStatusStr));

        INFO("AccountRepository -> method update -> result: success;");
        return true;
    }
    catch (const exception& e) { ERROR(string("AccountRepository -> method update -> try/catch (exception): ") + e.what() + ";"); return false; }
    catch (...) { ERROR("AccountRepository -> method update -> try/catch (...): error!;"); return false; }
}
bool AccountRepository::update(const size_t& accountId, const float& balance, const string& currency, const tm& openedDate, const tm& closedDate, const AccountStatus& status, const string& password, const bool& adminStatus)
{
    INFO("AccountRepository -> method update (value, dates = type::tm, status = type::AccountStatus): called;");

    string adminStatusStr = ((adminStatus) ? "t" : "f");
    return _update(accountId, balance, currency, Conversation::dateConversion(openedDate), Conversation::dateConversion(closedDate), Conversation::statusConversion(status), password, adminStatusStr);
}
bool AccountRepository::update(const Account* account)
{
    INFO("AccountRepository -> method update (obj): called;");
    
    return update(account->getAccountId(), account->getBalance(), account->getCurrency(), account->getOpenedDate(), account->getClosedDate(), account->getStatus(), account->getPassword(), account->getAdminStatus());
}

bool AccountRepository::deleteClass(size_t id)
{
    INFO("AccountRepository -> method deleteClass: called;");

    try
    {
        Queries::executeCommand(Queries::Accounts::deleteAccount(id));

        INFO("AccountRepository -> method deleteClass -> result: success;");
        return true;
    }
    catch (const exception& e) { ERROR(string("AccountRepository -> method deleteClass -> try/catch (exception): ") + e.what() + ";"); return false; }
    catch (...) { ERROR("AccountRepository -> method deleteClass -> try/catch (...): error!;"); return false; }
}
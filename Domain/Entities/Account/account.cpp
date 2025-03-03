#include "account.h"

Account::Account(const size_t& accountId, const size_t& clientId, const float& balance, const string& currency, const tm& openedDate, const tm& closedDate, const string& password, bool adminStatus)
    : _accountId(accountId), _clientId(clientId), _balance(balance), _currency(currency), _openedDate(openedDate), _closedDate(closedDate), _password(password), _adminStatus(adminStatus)
{ CREATE_INFO("Account <- constructor (DB): called"); }
Account::Account(Account&& other) noexcept
    : _accountId(move(other._accountId)),
    _clientId(move(other._clientId)),
    _balance(move(other._balance)),
    _currency(move(other._currency)),
    _openedDate(move(other._openedDate)),
    _closedDate(move(other._closedDate)),
    _status(move(other._status)),
    _password(move(other._password)),
    _adminStatus(move(other._adminStatus))
{ CREATE_INFO("Account <- displacement constructor: called"); }
Account::~Account() { CREATE_INFO("Account <- destructor: called"); }

const size_t& Account::getAccountId() const { INFO("Account -> method getAccountId: called;"); return _accountId; }
const size_t& Account::getClientId() const { INFO("Account -> method getClientId: called;"); return _clientId; }
const float& Account::getBalance() const { INFO("Account -> method getBalance: called;"); return _balance; }
const string& Account::getCurrency() const { INFO("Account -> method getCurrency: called;"); return _currency; }
const tm& Account::getOpenedDate() const { INFO("Account -> method getOpenedDate: called;"); return _openedDate; }
const tm& Account::getClosedDate() const { INFO("Account -> method getClosedDate: called;"); return _closedDate; }
const AccountStatus& Account::getStatus() const { INFO("Account -> method getStatus: called;"); return _status; }
const string& Account::getPassword() const { INFO("Account -> method getPassword: called;"); return _password; }
const bool& Account::getAdminStatus() const { INFO("Account -> method getAdminStatus: called;"); return _adminStatus; }

void Account::setAccountId(const size_t& value) { INFO("Account -> method setAccountId: called;"); _accountId = value; }
void Account::setClientId(const size_t& value) { INFO("Account -> method setClientId: called;"); _clientId = value; }
void Account::setBalance(const float& value) { INFO("Account -> method setBalance: called;"); _balance = value; }
void Account::setCurrency(const string& value) { INFO("Account -> method setCurrency: called;"); _currency = value; }
void Account::setOpenedDate(const tm& value) { INFO("Account -> method setOpenedDate: called;"); _openedDate = value; }
void Account::setClosedDate(const tm& value) { INFO("Account -> method setClosedDate: called;"); _closedDate = value; }
void Account::setStatus(const AccountStatus& value) { INFO("Account -> method setStatus: called;"); _status = value; }
void Account::setPassword(const string& value) { INFO("Account -> method setPassword: called;"); _password = value; }
void Account::setAdminStatus(const bool& value) { INFO("Account -> method setAdminStatus: called;"); _adminStatus = value; }

/*
#include <iostream>
#include <sstream>
#include <cmath>

// Псевдофункция для выполнения SQL запроса (здесь просто выводим запрос)
bool executeQuery(const string& query)
{
    cout << "Executing query: " << query << endl;
    return true; // Предположим, что запрос всегда успешен
}

bool Bank::deposit(int accountId, double amount) 
{
    ostringstream query;
    query << "UPDATE accounts SET balance = balance + " << amount
          << " WHERE id = " << accountId << ";";
    return executeQuery(query.str());
}

bool Bank::withdraw(int accountId, double amount)
{
    std::ostringstream query;
    query << "UPDATE accounts SET balance = balance - " << amount
          << " WHERE id = " << accountId << " AND balance >= " << amount << ";";
    return executeQuery(query.str());
}

bool Bank::transfer(int fromAccountId, int toAccountId, double amount)
{
    // Начинаем транзакцию
    if (!executeQuery("BEGIN;"))
        return false;
    
    ostringstream query1;
    query1 << "UPDATE accounts SET balance = balance - " << amount
           << " WHERE id = " << fromAccountId << " AND balance >= " << amount << ";";
    if (!executeQuery(query1.str()))
    {
        executeQuery("ROLLBACK;");
        return false;
    }
    
    ostringstream query2;
    query2 << "UPDATE accounts SET balance = balance + " << amount
           << " WHERE id = " << toAccountId << ";";
    if (!executeQuery(query2.str()))
    {
        executeQuery("ROLLBACK;");
        return false;
    }
    
    return executeQuery("COMMIT;");
}

double Bank::calculateDeposit(double principal, double rate, int months)
{
    // Формула сложных процентов: A = P * (1 + r/12)^(months)
    return principal * pow((1 + rate / 12.0), months);
}
*/
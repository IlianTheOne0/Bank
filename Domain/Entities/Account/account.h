#ifndef TEMP_ACCOUNT_H
#define TEMP_ACCOUNT_H

#include "../../../Core/Libs/domainConfig.h"
#include "../Client/client.h"
#include "accountStatusEnum.h"

class Account
{
private:
    size_t _accountId;
    size_t _clientId;
    float _balance;
    string _currency;
    tm _openedDate;
    tm _closedDate;
    AccountStatus _status;
    string _password;
    bool _adminStatus;
public:
    Account() = default;
    Account(const size_t& accountId, const size_t& clientId, const float& balance, const string& currency, const tm& openedDate, const tm& closedDate, const string& password, bool adminStatus);
    Account(Account&& other) noexcept;
    ~Account();

    const size_t& getAccountId() const;
    const size_t& getClientId() const;
    const float& getBalance() const;
    const string& getCurrency() const;
    const tm& getOpenedDate() const;
    const tm& getClosedDate() const;
    const AccountStatus& getStatus() const;
    const string& getPassword() const;
    const bool& getAdminStatus() const;

    void setAccountId(const size_t& value);
    void setClientId(const size_t& value);
    void setBalance(const float& value);
    void setCurrency(const string& value);
    void setOpenedDate(const tm& value);
    void setClosedDate(const tm& value);
    void setStatus(const AccountStatus& value);
    void setPassword(const string& value);
    void setAdminStatus(const bool& value);
};

/*
class Bank
{
public:
    // прототип Регистрация клиента
    bool registerClient(const string& name, const string& email, const string& password);
    
    // прототип Пополнение счета
    bool deposit(int accountId, double amount);
    
    // прототип Снятие средств
    bool withdraw(int accountId, double amount);
    
    // прототип Перевод между счетами
    bool transfer(int fromAccountId, int toAccountId, double amount);
    
    // прототип Калькулятор депозитов: рассчитывает итоговую сумму с учетом сложных процентов
    double calculateDeposit(double principal, double rate, int months);
};
*/
#endif
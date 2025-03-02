#ifndef TEMP_ACCOUNT_H
#define TEMP_ACCOUNT_H

#include "../../../Core/Libs/domainConfig.h"
#include "accountStatusEnum.h"

struct Account
{
    size_t accountId;
    size_t clientId;
    float balance;
    string currency;
    tm openedDate;
    tm closedDate;
    AccountStatus status;
    string password;
    bool adminStatus;
    size_t getClientId() const;
};

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

#endif
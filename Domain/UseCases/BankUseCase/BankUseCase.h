#pragma once
#include <string>

class BankUseCase
{
public:
    // Пример регистрации клиента
    bool registerClient(const std::string& name, const std::string& email, const std::string& password);
    
    // Операции со счетом
    bool deposit(int accountId, double amount);
    bool withdraw(int accountId, double amount);
    bool transfer(int fromAccountId, int toAccountId, double amount);
    
    // Калькулятор депозитов с учетом сложных процентов
    double calculateDeposit(double principal, double rate, int months);
};

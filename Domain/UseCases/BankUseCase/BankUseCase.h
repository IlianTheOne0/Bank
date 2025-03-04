#pragma once
#include <string>

class BankUseCase
{
public:
    // Example of client registration
    bool registerClient(const std::string& name, const std::string& email, const std::string& password);
    
    // Account transactions
    bool deposit(int accountId, double amount);
    bool withdraw(int accountId, double amount);
    bool transfer(int fromAccountId, int toAccountId, double amount);
    
    // Deposit calculator with compound interest
    double calculateDeposit(double principal, double rate, int months);
};

#include "BankUseCase.h"

#include <iostream>
#include <sstream>
#include <cmath>

// Псевдофункция для выполнения SQL запроса – замени на свою реализацию
bool executeQuery(const std::string& query)
{
    std::cout << "Executing query: " << query << std::endl;
    return true;
}

bool BankUseCase::registerClient(const std::string& name, const std::string& email, const std::string& password) {
    std::ostringstream query;
    query << "INSERT INTO clients (name, email, password) VALUES ('"
          << name << "', '" << email << "', '" << password << "');";
    return executeQuery(query.str());
}

bool BankUseCase::deposit(int accountId, double amount)
{
    std::ostringstream query;
    query << "UPDATE accounts SET balance = balance + " << amount
          << " WHERE id = " << accountId << ";";
    return executeQuery(query.str());
}

bool BankUseCase::withdraw(int accountId, double amount)
{
    std::ostringstream query;
    query << "UPDATE accounts SET balance = balance - " << amount
          << " WHERE id = " << accountId << " AND balance >= " << amount << ";";
    return executeQuery(query.str());
}

bool BankUseCase::transfer(int fromAccountId, int toAccountId, double amount)
{
    // Начинаем транзакцию
    if (!executeQuery("BEGIN;"))
        return false;
    
    std::ostringstream query1;
    query1 << "UPDATE accounts SET balance = balance - " << amount
           << " WHERE id = " << fromAccountId << " AND balance >= " << amount << ";";
    if (!executeQuery(query1.str()))
    {
        executeQuery("ROLLBACK;");
        return false;
    }
    
    std::ostringstream query2;
    query2 << "UPDATE accounts SET balance = balance + " << amount
           << " WHERE id = " << toAccountId << ";";
    if (!executeQuery(query2.str()))
   {
        executeQuery("ROLLBACK;");
        return false;
    }
    
    return executeQuery("COMMIT;");
}

double BankUseCase::calculateDeposit(double principal, double rate, int months)
{
    // Формула: A = principal * (1 + (rate/(12*100)))^months
    return principal * pow(1 + rate / (12.0 * 100), months);
}

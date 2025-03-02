#include "account.h"

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
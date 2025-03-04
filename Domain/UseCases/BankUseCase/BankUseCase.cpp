#include "BankUseCase.h"

#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

// Pseudofunction to execute SQL query - replace with your implementation
bool executeQuery(const string& query)
{
    cout << "Executing query: " << query << endl;
    return true;
}

bool BankUseCase::registerClient(const string& name, const string& email, const string& password) {
    ostringstream query;
    query << "INSERT INTO clients (name, email, password) VALUES ('"
          << name << "', '" << email << "', '" << password << "');";
    return executeQuery(query.str());
}

bool BankUseCase::deposit(int accountId, double amount)
{
    ostringstream query;
    query << "UPDATE accounts SET balance = balance + " << amount
          << " WHERE id = " << accountId << ";";
    return executeQuery(query.str());
}

bool BankUseCase::withdraw(int accountId, double amount)
{
    ostringstream query;
    query << "UPDATE accounts SET balance = balance - " << amount
          << " WHERE id = " << accountId << " AND balance >= " << amount << ";";
    return executeQuery(query.str());
}

bool BankUseCase::transfer(int fromAccountId, int toAccountId, double amount)
{
    // Starting the transaction
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

double BankUseCase::calculateDeposit(double principal, double rate, int months)
{
    // Formula: A = principal * (1 + (rate/(12*100)))^months
    return principal * pow(1 + rate / (12.0 * 100), months);
}

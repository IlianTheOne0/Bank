#ifndef QUERIES_H
#define QUERIES_H

#include "../../Core/Libs/dataConfig.h"

namespace Queries
{
    extern const string defaultCommand;
    string executeCommand(const string& value);

    namespace Provider
    {
        extern const string deleteTablesData;
        extern const string connectAccountsTable;
        extern const string connectClientsTable;
        extern const string connectCardsTable;
        extern const string connectOperationsTable;
        extern const string connectTransactionsTable;
    }

    namespace Clients
    {
        string insertClient(const string& firstName, const string& lastName, const string& passportNumber, const string& phone, const string& email);
        string getClient(size_t id);
        string updateClient(size_t clientId, const string& firstName, const string& lastName, const string& passportNumber, const string& phone, const string& email, const string& registrationDate);
        string deleteClient(size_t id);
    }

    namespace Accounts
    {
        string insertAccount(size_t& clientId, const float& balance, const string& currency, const string& status);
        string getAccount(size_t id);
        string updateAccount(size_t accountId, const float& balance, const string& currency, const string& openedDate, const string& closedDate, const string& status);
        string deleteAccount(size_t id);
    }

    namespace Cards
    {
        string insertCard(size_t& accountId, const string& card_number, const bool& isBlocked);
        string getCard(size_t id);
        string updateCard(const size_t& accountId, const string& cardNumber, const string& expiryDateStr, const string& isBlockedStr, const string& issueDateStr);
        string deleteCard(size_t id);
    }

    namespace Transactions
    {
        string insertTransaction(const size_t& fromAccountId, const size_t& toAccountId, const float& amount, const size_t& operationType, const string& transactionDateStr, const string& description, const string& statusStr);
        string getTransaction(size_t id);
        string updateTransaction(size_t& transactionId, const size_t& fromAccountId, const size_t& toAccountId, const float& amount, const size_t& operationType, const string& transactionDateStr, const string& description, const string& statusStr);
        string deleteTransaction(size_t id);
    }

    namespace Operations
    {
        string insertOperation(const string& name, const string& isIncomeStr, const string& needsApprovalStr);
        string getOperation(size_t id);
        string updateOperation(size_t& operationId, const string& name, const string& isIncomeStr, const string& needsApprovalStr);
        string deleteOperation(size_t id);
    }
}

#endif
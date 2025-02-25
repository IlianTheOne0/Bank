#include "bank_db-Queries.h"

namespace Queries
{
    const string Queries::defaultCommand =
        "docker exec " + ConnectionConfig::containter + " psql --tuples-only --no-align -U " + ConnectionConfig::user + " -d " + ConnectionConfig::dbname + " -c ";

    string executeCommand(const string& value)
    {
        ostringstream commandStream;
        commandStream << Queries::defaultCommand << "\"" << value << "\"";
        string command = commandStream.str();
        LOG_OWN("[COMMAND] " + command + ";", Colors::LightPink);

        array<char, 128> buffer;
        string result;
        unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
        if (!pipe) { throw runtime_error("popen() failed!"); }

        steady_clock::time_point start = steady_clock::now();
        while (true)
        {
            if (steady_clock::now() - start > seconds(ConnectionConfig::queryTime)) { pclose(pipe.release()); throw runtime_error("Command execution timed out!"); }

            if (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) { result += buffer.data(); }
            else { break; }

            sleep_for(milliseconds(100));
        }

        return dataTrim(result);
    }

    namespace Provider
    {
        const string Queries::Provider::deleteTablesData =
            "SET search_path TO bank_system; "

            "DELETE FROM cards; "
            "DELETE FROM transactions; "
            "DELETE FROM accounts; "
            "DELETE FROM operation_types; "
            "DELETE FROM clients;";
    }

    namespace Clients
    {
        string insertClient(const string& firstName, const string& lastName, const string& passportNumber, const string& phone, const string& email)
        {
            ostringstream queryStream;
            queryStream
                << "INSERT INTO bank_system.clients (first_name, last_name, passport_number, phone, email) "
                << "VALUES ('" << firstName << "', '" << lastName << "', '" << passportNumber << "', '" << phone << "', '" << email << "') "
                << "RETURNING client_id"
                << ";";
            return queryStream.str();
        }

        string getClient(size_t id)
        {
            ostringstream queryStream;
            queryStream
                << "SELECT first_name, last_name, passport_number, phone, email, registration_date "
                << "FROM bank_system.clients "
                << "WHERE client_id = " << id
                << ";";
            return queryStream.str();
        }

        string updateClient(size_t clientId, const string& firstName, const string& lastName, const string& passportNumber, const string& phone, const string& email, const string& registrationDate)
        {
            ostringstream queryStream;
            queryStream
                << "UPDATE bank_system.clients SET "
                << "first_name = '" << firstName << "', "
                << "last_name = '" << lastName << "', "
                << "passport_number = '" << passportNumber << "', "
                << "phone = '" << phone << "', "
                << "email = '" << email << "', "
                << "registration_date = '" << registrationDate << "' "
                << "WHERE client_id = " << clientId
                << ";";
            return queryStream.str();
        }

        string deleteClient(size_t id)
        {
            ostringstream queryStream;
            queryStream
                << "DELETE FROM bank_system.clients WHERE client_id = " << id
                << ";";
            return queryStream.str();
        }
    }

    namespace Accounts
    {
        string insertAccount(size_t& clientId, const float& balance, const string& currency, const string& status)
        {
            ostringstream queryStream;
            queryStream
                << "INSERT INTO bank_system.accounts (client_id, balance, currency, status) "
                << "VALUES (" << clientId << ", " << balance << ", '" << currency << "', '" << status << "') "
                << "RETURNING account_id"
                << ";";
            return queryStream.str();
        }

        string getAccount(size_t id)
        {
            ostringstream queryStream;
            queryStream
                << "SELECT * FROM bank_system.accounts "
                << "WHERE account_id = " << id
                << ";";
            return queryStream.str();
        }

        string updateAccount(size_t accountId, const float& balance, const string& currency, const string& openedDate, const string& closedDate, const string& status)
        {
            ostringstream queryStream;
            queryStream
                << "UPDATE bank_system.accounts SET "
                << "balance = " << balance << ", "
                << "currency = '" << currency << "', "
                << "opened_date = '" << openedDate << "', "
                << "closed_date = '" << closedDate << "', "
                << "status = '" << status << "' "
                << "WHERE account_id = " << accountId
                << ";";
            return queryStream.str();
        }

        string deleteAccount(size_t id)
        {
            ostringstream queryStream;
            queryStream
                << "DELETE FROM bank_system.accounts "
                << "WHERE account_id = " << id
                << ";";
            return queryStream.str();
        }
    }

    namespace Cards
    {
        string insertCard(size_t& accountId, const string& card_number, const bool& isBlocked)
        {
            ostringstream queryStream;
            queryStream
                << "INSERT INTO bank_system.cards (account_id, card_number, is_blocked) "
                << "VALUES (" << accountId << ", '" << card_number << "', '" << isBlocked << "') "
                << "RETURNING card_id"
                << ";";
            return queryStream.str();
        }

        string getCard(size_t id)
        {
            ostringstream queryStream;
            queryStream
                << "SELECT * FROM bank_system.cards "
                << "WHERE card_id = " << id
                << ";";
            return queryStream.str();
        }

        string updateCard(const size_t& accountId, const string& cardNumber, const string& expiryDateStr, const string& isBlockedStr, const string& issueDateStr)
        {
            ostringstream queryStream;
            queryStream
                << "UPDATE bank_system.cards SET "
                << "card_number = '" << cardNumber << "', "
                << "expiry_date = '" << expiryDateStr << "', "
                << "is_blocked = '" << isBlockedStr << "', "
                << "issue_date = '" << issueDateStr << "' "
                << "WHERE account_id = " << accountId
                << ";";
            return queryStream.str();
        }

        string deleteCard(size_t id)
        {
            ostringstream queryStream;
            queryStream
                << "DELETE FROM bank_system.cards "
                << "WHERE account_id = " << id
                << ";";
            return queryStream.str();
        }
    }

    namespace Transactions
    {
        string insertTransaction(const size_t& fromAccountId, const size_t& toAccountId, const float& amount, const size_t& operationType, const string& transactionDateStr, const string& description, const string& statusStr)
        {
            ostringstream queryStream;
            queryStream
                << "INSERT INTO bank_system.transactions (from_account_id, to_account_id, amount, operation_type, transaction_date, description, status) "
                << "VALUES (" << fromAccountId << ", '" << toAccountId << "', '" << amount << "', '" << operationType << "', '" << transactionDateStr << "', '" << description << "', '" << statusStr << "') "
                << "RETURNING transaction_id"
                << ";";
            return queryStream.str();
        }

        string getTransaction(size_t id)
        {
            ostringstream queryStream;
            queryStream
                << "SELECT * FROM bank_system.transactions "
                << "WHERE transaction_id = " << id
                << ";";
            return queryStream.str();
        }

        string updateTransaction(size_t& transactionId, const size_t& fromAccountId, const size_t& toAccountId, const float& amount, const size_t& operationType, const string& transactionDateStr, const string& description, const string& statusStr)
        {
            ostringstream queryStream;
            queryStream
                << "UPDATE bank_system.transactions SET "
                << "from_account_id = '" << fromAccountId << "', "
                << "to_account_id = '" << toAccountId << "', "
                << "amount = '" << amount << "', "
                << "operation_type = '" << operationType << "', "
                << "transaction_date = '" << transactionDateStr << "', "
                << "description = '" << description << "', "
                << "status = '" << statusStr << "' "
                << "WHERE transaction_id = " << transactionId
                << ";";
            return queryStream.str();
        }

        string deleteTransaction(size_t id)
        {
            ostringstream queryStream;
            queryStream
                << "DELETE FROM bank_system.transactions "
                << "WHERE transaction_id = " << id
                << ";";
            return queryStream.str();
        }
    }

    namespace Operations
    {
        string insertOperation(const string& name, const string& isIncomeStr, const string& needsApprovalStr)
        {
            ostringstream queryStream;
            queryStream
                << "INSERT INTO bank_system.operation_types (name, is_income, needs_approval) "
                << "VALUES ('" << name << "', '" << isIncomeStr << "', '" << needsApprovalStr << "') "
                << "RETURNING operation_type_id"
                << ";";
            return queryStream.str();
        }

        string getOperation(size_t id)
        {
            ostringstream queryStream;
            queryStream
                << "SELECT * FROM bank_system.operation_types "
                << "WHERE operation_type_id = " << id
                << ";";
            return queryStream.str();
        }

        string updateOperation(size_t& operationId, const string& name, const string& isIncomeStr, const string& needsApprovalStr)
        {
            ostringstream queryStream;
            queryStream
                << "UPDATE bank_system.operation_types SET "
                << "name = '" << name << "', "
                << "is_income = '" << isIncomeStr << "', "
                << "needs_approval = '" << needsApprovalStr << "' "
                << "WHERE operation_type_id = " << operationId
                << ";";
            return queryStream.str();
        }

        string deleteOperation(size_t id)
        {
            ostringstream queryStream;
            queryStream
                << "DELETE FROM bank_system.operation_types "
                << "WHERE operation_type_id = " << id
                << ";";
            return queryStream.str();
        }
    }
}
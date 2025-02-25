#include "../../../Core/Libs/domainConfig.h"
#include "transactionRepository.h"
#include "../conversation.h"

TransactionRepository::TransactionRepository() { CREATE_INFO("TransactionRepository <- Constructor: called;"); }

size_t TransactionRepository::_add(const size_t& fromAccountId, const size_t& toAccountId, const float& amount, const size_t& operationType, const string& transactionDateStr, const string& description, const string& statusStr)
{
    INFO("TransactionRepository -> method add (value, status = type::string): called;");

    try
    {
        size_t newTransactionId = stoi(Queries::executeCommand(Queries::Transactions::insertTransaction(fromAccountId, toAccountId, amount, operationType, transactionDateStr, description, statusStr)));

        INFO("TransactionRepository -> method add -> result: success;");
        return newTransactionId;
    }
    catch (const exception& e) { ERROR(string("TransactionRepository -> method add -> try/catch (exception): ") + e.what() + ";"); return -1; }
    catch (...) { ERROR("TransactionRepository -> method add -> try/catch (...): error!;"); return -1; }
}
size_t TransactionRepository::add(const size_t& fromAccountId, const size_t& toAccountId, const float& amount, const size_t& operationType, const tm& transactionDate, const string& description, const TransactionStatus& status)
{
    INFO("TransactionRepository -> method add (value, status = type::Status): called;");
    
    return _add(fromAccountId, toAccountId, amount, operationType, Conversation::dateConversion(transactionDate), description, Conversation::statusConversion(status, true));
}
size_t TransactionRepository::add(const Transaction* transaction)
{
    INFO("TransactionRepository -> method add (obj): called;");

    return add(transaction->fromAccountId, transaction->toAccountId, transaction->amount, transaction->operationType, transaction->transactionDate, transaction->description, transaction->status);
}

Transaction* TransactionRepository::get(size_t id)
{
    INFO("TransactionRepository -> method get: called;");

    try
    {
        string result = Queries::executeCommand(Queries::Transactions::getTransaction(id));

        size_t pos = result.find('\n');
        if (pos != string::npos) { result = result.substr(pos + 1); }

        Transaction* transaction = new Transaction;
        istringstream iss(result);
        string token;

        getline(iss, token, '|'); transaction->transactionId = stoi(token);
        getline(iss, token, '|'); transaction->fromAccountId = stoi(token);
        getline(iss, token, '|'); transaction->toAccountId = stoi(token);
        getline(iss, token, '|'); transaction->amount = stof(token);
        getline(iss, token, '|'); transaction->operationType = stoi(token);
        getline(iss, token, '|'); transaction->transactionDate = Conversation::dateConversion(token);
        getline(iss, token, '|'); transaction->description = token;
        getline(iss, token, '|'); transaction->status = Conversation::statusConversion(token, true);
        getline(iss, token, '|'); string statusStr = token;

        INFO("TransactionRepository -> method get -> result: success;");
        return transaction;
    }
    catch (const exception& e) { ERROR(string("TransactionRepository -> method get -> try/catch (exception): ") + e.what() + ";"); return nullptr; }
    catch (...) { ERROR("TransactionRepository -> method get -> try/catch (...): error!;"); return nullptr; }
}

bool TransactionRepository::_update(size_t& transactionId, const size_t& fromAccountId, const size_t& toAccountId, const float& amount, const size_t& operationType, const string& transactionDateStr, const string& description, const string& statusStr)
{
    INFO("TransactionRepository -> method update (value, dates = type::string, clientRegistrationDate = type::string): called;");

    try
    {
        string result = Queries::executeCommand(Queries::Transactions::updateTransaction(transactionId, fromAccountId, toAccountId, amount, operationType, transactionDateStr, description, statusStr));

        INFO("TransactionRepository -> method update -> result: success;");
        return true;
    }
    catch (const exception& e) { ERROR(string("TransactionRepository -> method update -> try/catch (exception): ") + e.what() + ";"); return false; }
    catch (...) { ERROR("TransactionRepository -> method update -> try/catch (...): error!;"); return false; }
}
bool TransactionRepository::update(size_t& transactionId, const size_t& fromAccountId, const size_t& toAccountId, const float& amount, const size_t& operationType, const tm& transactionDate, const string& description, const TransactionStatus& status)
{
    INFO("TransactionRepository -> method update (value, dates = type::tm, status = type::Status): called;");

    return _update(transactionId, fromAccountId, toAccountId, amount, operationType, Conversation::dateConversion(transactionDate), description, Conversation::statusConversion(status, true));
}
bool TransactionRepository::update(const Transaction* transaction)
{
    INFO("TransactionRepository -> method update (obj): called;");
    
    size_t transactionId = transaction->transactionId;
    return update(transactionId, transaction->fromAccountId, transaction->toAccountId, transaction->amount, transaction->operationType, transaction->transactionDate, transaction->description, transaction->status);
}

bool TransactionRepository::deleteClass(size_t id)
{
    INFO("TransactionRepository -> method deleteClass: called;");

    try
    {
        Queries::executeCommand(Queries::Transactions::deleteTransaction(id));

        INFO("TransactionRepository -> method deleteClass -> result: success;");
        return true;
    }
    catch (const exception& e) { ERROR(string("TransactionRepository -> method deleteClass -> try/catch (exception): ") + e.what() + ";"); return false; }
    catch (...) { ERROR("TransactionRepository -> method deleteClass -> try/catch (...): error!;"); return false; }
}
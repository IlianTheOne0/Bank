#include "REP_accountsAbstraction.h"
#include <sstream>

#include "../../../Data/Queries/bank_db-Queries.h"

AAccountsRepository::AAccountsRepository(AConnectionProvider* provider)
	: _provider(provider)
{ CREATE_INFO("AAccountsRepository <- constructor: called;"); }
AAccountsRepository::~AAccountsRepository() { CREATE_INFO("AAccountsRepository <- destructor: called;"); }

int AAccountsRepository::createAccount(const Account* account)
{
    INFO("AAccountsRepository -> method createAccount: called;");

    try {
        connection* connection = _provider->getConnection();
        if (!connection->is_open()) {  ERROR("AAccountsRepository -> method createAccount -> connection: failed;");  return -1; }
    
        work txn(*connection);

        std::stringstream query;
        query << "INSERT INTO accounts (account_id, client_id, balance, currency, opened_date, closed_date, status) VALUES ("
            << "'" << account->accountId << "', "
            << "'" << account->clientId << "', "
            << "'" << account->balance << "', "
            << "'" << account->currency << "', "
            << "'" << account->openedDate << "', "
            << "'" << account->closedDate << "', "
            << "'" << account->status << "')";

        result result{ txn.exec(query.str()) };
        txn.commit();
        if (result.size() > 0) { return result[0][0].as<int>(); }

        INFO("AAccountsRepository -> method createAccount: success;");
        return 0;
    }
    catch (...) { ERROR("AAccountsRepository -> method createAccount: creating failed!"); return -1; }
    return -1;

}
Account* AAccountsRepository::getAllAccounts(size_t* counter)
{
    INFO("AAccountsRepository -> method getAllAccounts: called;");

    *counter = 0;
    Account* accountsArray{ nullptr };

    try
    {
        connection* connection = _provider->getConnection();
        if (!connection->is_open()) { ERROR("AAccountsRepository -> method getAllAccounts -> connection: failed;"); return nullptr; }

        work txn(*connection);
        result result = txn.exec(Queries::GET_ACCOUNTS_BY_CLIENT);

        *counter = result.size();
        if (*counter > 0)
        {
            accountsArray = new Account[*counter];
            for (size_t i = 0; i < *counter; ++i)
            {
                accountsArray[i].accountId = result[i]["account_id"].c_str();
                accountsArray[i].clientId = result[i]["client_id"].c_str();
                accountsArray[i].balance = result[i]["balance"].c_str();
                accountsArray[i].currency = result[i]["currency"].c_str();
                accountsArray[i].openedDate = result[i]["opened_date"].c_str();
                accountsArray[i].closedDate = result[i]["closed_date"].c_str();
                accountsArray[i].status = result[i]["status"].c_str();
            }
        }

        INFO("AAccountsRepository -> method getAllAccounts: success;");
    }
    catch (...)
    {
        ERROR("AAccountsRepository -> method getAllAccounts: getting failed!");

        if (accountsArray != nullptr) { delete[] accountsArray; accountsArray = nullptr; }
        *counter = 0;
    }

    return accountsArray;
}
#include <pqxx/pqxx>
#include "../../../Core/Libs/cfg/cfg.h"
#include "../../../Data/Queries/bank_db-Queries.h"
#include "../tests.h"
#include "../../../Domain/Repositories/accounts/REP_accountsAbstraction.h"

using pqxx::connection;
using pqxx::work;
using pqxx::result;
using pqxx::row;

void Test::accountsTask()
{
    INFO("Test -> static method accountsTask: called;");

    try
    {
        string con_string =
            "dbname=" + Config::dbname + " " +
            "user=" + Config::user + " " +
            "password=" + Config::password + " " +
            "host=" + Config::host + " " +
            "port=" + Config::port;
        connection con(con_string);

        if (con.is_open())
        {
            cout << "Opened database successfully: " << con.dbname() << endl;

            AConnectionProvider provider(con_string);
            AAccountsRepository accountsRepo(&provider);

            // Create new users
            Account account1 = { "1", "1", "1000.00", "USD", "2025-02-19", "", "ACTIVE" };
            Account account2 = { "2", "2", "2000.00", "USD", "2025-02-19", "", "ACTIVE" };
            Account account3 = { "3", "3", "3000.00", "USD", "2025-02-19", "", "ACTIVE" };

            accountsRepo.createAccount(&account1);
            accountsRepo.createAccount(&account2);
            accountsRepo.createAccount(&account3);

            // Retrieve all users
            size_t counter;
            Account* accounts = accountsRepo.getAllAccounts(&counter);

            // Print all users
            if (accounts != nullptr)
            {
                for (size_t i = 0; i < counter; ++i)
                {
                    cout << "Account ID: " << accounts[i].accountId << ", "
                        << "Client ID: " << accounts[i].clientId << ", "
                        << "Balance: " << accounts[i].balance << ", "
                        << "Currency: " << accounts[i].currency << ", "
                        << "Opened Date: " << accounts[i].openedDate << ", "
                        << "Closed Date: " << accounts[i].closedDate << ", "
                        << "Status: " << accounts[i].status << endl;
                }
                delete[] accounts;
            }
        }
        else
        {
            cout << "Can't open database" << endl;
        }
    }
    catch (const exception& e) { cout << "Exception: " << e.what() << endl; return; }
}

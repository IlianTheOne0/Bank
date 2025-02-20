#include <soci/soci.h>
#include <soci/postgresql/soci-postgresql.h>
#include <string>
#include <iostream>
#include <iomanip>

#include "../tests.h"
#include "../../../Data/Queries/bank_db-Queries.h"
#include "../../../Core/Libs/cfg/cfg.h"

using std::runtime_error;
using namespace::ConnectionConfig;

using std::string;
using std::to_string;

using soci::session;
using soci::postgresql;
using soci::indicator;
using soci::use;
using soci::into;
using soci::rowset;
using soci::row;
using soci::i_null;
using std::tm;
using std::put_time;

void getAccounts(session& sql, int accountId)
{
    rowset<row> result = (sql.prepare << Queries::GET_ACCOUNT_BY_ACCOUNTID, use(accountId));
    // The prefix 'f' means "fetched"
    for (auto it = result.begin(); it != result.end(); it++)
    {
        const row& r = *it;
        int f_clientId = r.get<int>(0); // WARNING: int to size_t must not be changed in ANY case! (BC size_t is an unsigned integer. In other words, it is not an int, but a signed data type)
        double f_balance = r.get<double>(1);
        string f_currency = r.get<string>(2);
        tm f_openedDate = r.get<tm>(3);
        indicator f_closedDateIndicator = r.get_indicator(4); tm f_closedDate; if (f_closedDateIndicator != i_null) { f_closedDate = r.get<tm>(4); }
        string f_status = r.get<string>(5);

        cout << "Account id: " << char(accountId) << ';' << endl;
        cout << "Cliend id: " << f_clientId << endl;
        cout << "Balance: " << f_balance << ' ' << f_currency << endl;
        cout << "Opened date: " << put_time(&f_openedDate, "%Y-%m-%d") << ';' << endl;
        if (f_closedDateIndicator != i_null) { cout << "Closed date: " << put_time(&f_closedDate, "%Y-%m-%d") << ';' << endl; }
        cout << "Status: " << f_status << ';' << endl;
    }
}
void getAccounts(session& sql)
{
    int accountId{ 52 }; // int('char'), so 50 = 2
    getAccounts(sql, accountId);
}
void createAccount(session& sql)
{
    int accountId; sql << "SELECT MAX(account_id) FROM accounts", into(accountId); accountId += 2;
    int clientId{ 200 };
    double balance{ 1000.7 };
    string currency = "USD";
    string status = "FROZEN";
    
    cout << "Inserting account with values: " << endl;
    cout << "ClientId: " << clientId << endl;
    cout << "Balance: " << balance << endl;
    cout << "Currency: " << currency << endl;
    cout << "Status: " << status << endl;

    sql << Queries::INSERT_ACCOUNT, use(clientId), use(balance), use(currency), use(status);
    system("docker exec - it postgres - local psql - U sa - d postgres - c \"INSERT INTO clients(client_id, first_name, last_name, passport_number, phone, email) VALUES(31, 'asd!', 'dsa!', 465360000, +380900123123, 'emailmailemail@gmail.com')\"");
    cout << endl << endl;  getAccounts(sql, accountId);
}

void Test::libTest()
{
    try
    {
        string connectionProperties{ "host=" + host + " port=" + port + " dbname=" + dbname + " user=" + user + " password=" + password };
        session sql(postgresql, connectionProperties); if (!sql.is_connected()) { throw runtime_error{ "The connection is not established. The database may not be running!" }; }
        sql << "SET search_path TO bank_system";
        
        getAccounts(sql);
        for (size_t i = 0; i < 50; i++) { cout << "="; } cout << endl;
        createAccount(sql);
    }
    catch (const std::exception& e) { std::cout << "Error: " << e.what() << endl; }
}

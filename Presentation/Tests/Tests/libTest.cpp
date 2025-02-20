#include <soci/soci.h>
#include <soci/postgresql/soci-postgresql.h>
#include <string>

#include "../tests.h"
#include "../../../Data/Queries/bank_db-Queries.h"
#include "../../../Core/Libs/cfg/cfg.h"

using std::string;
using namespace::ConnectionConfig;

using soci::session;
using soci::postgresql;
using soci::indicator;
using soci::use;
using soci::into;
using soci::rowset;
using soci::row;

void Test::libTest()
{
	try
	{
		string connectionProperties{ "host=" + host + " port=" + port + " dbname=" + dbname + " user=" + user + " password=" + password};
		session sql(postgresql, connectionProperties);

		size_t accountId, clientId{ 5 };
		double balance{ 5000.00 };
		string currency{ "UAH" }, openedDate{ "2025 - 02 - 20" };
		indicator closedDateInd{ soci::i_null };
		string status{ "ACTIVE" };

		sql << Queries::INSERT_ACCOUNT,
			use(accountId),
			use(clientId),
			use(balance),
			use(currency),
			use(openedDate),
			use(closedDateInd),
			use(status),
			into(accountId);

		cout << "Inserted new account with ID: " << accountId << endl;
		
		// =================  The prefix 'f_' means "fetched"  =================
		size_t f_accountId;
		double f_balance;
		string f_currency, f_openedDate, f_closedDateInd, f_status;

		rowset<row> result = (sql.prepare << Queries::GET_ACCOUNTS_BY_CLIENT, use(clientId));

		cout << "Client " << clientId << " Accounts:" << endl;
		for (auto& row : result)
		{
			f_accountId = row.get<size_t>(0);
			f_balance = row.get<double>(2);
			f_currency = row.get<string>(3);
			f_openedDate = row.get<string>(4);
			f_closedDateInd = row.get<string>(5);
			f_status = row.get<string>(6);

			cout << "  Account ID: " << f_accountId << endl
				<< "  Balance: " << f_balance << ' ' << f_currency << endl
				<< "  Opene date: " << f_openedDate << endl
				<< "  Closed date: " << f_closedDateInd << endl
				<< "  Status: " << f_status << endl;
		}
	}
	catch (const exception& e) { cout << "Error: " << e.what() << endl; }
}
#include <pqxx/pqxx>

#include "../../../Core/Libs/cfg/cfg.h"
#include "../../../Data/Queries/Queries-bank_db.h"
#include "../tests.h"

using pqxx::connection;
using pqxx::work;
using pqxx::result;
using pqxx::row;

void Test::libpqxxTest()
{
	INFO("Test -> static method libpqxxTest: called;");
	
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

			work txn{ con };
			result res{ txn.exec(Queries::GET_ALL_CLIENTS) };
			txn.commit();

			cout << "Columns: ";
			for (row::size_type i = 0; i < res.columns(); ++i) {
				cout << res.column_name(i);
				if (i < res.columns() - 1) cout << ", ";
			}
			cout << endl;

			for (const auto& row : res) {
				for (row::size_type i = 0; i < row.size(); ++i) {
					cout << row[i].c_str();
					if (i < row.size() - 1) cout << ", ";
				}
				cout << endl;
			}
		}
		else
		{
			cout << "Can't open database" << endl;
		}
	}
	catch (const exception& e) { cout << "Exception: " << e.what() << endl; return; }
}
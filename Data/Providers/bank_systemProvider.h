#ifndef BANK_SYSTEM_DB_PROVIDER_H
#define BANK_SYSTEM_DB_PROVIDER_H

#include "../../Core/Libs/dataConfig.h"
#include "../Queries/bank_db-Queries.h"

using namespace Queries;

class BankSystemDbProvider
{
public:
	static void connect()
	{
		/*
		executeCommand(Provider::connectAccountsTable);
		executeCommand(Provider::connectClientsTable);
		executeCommand(Provider::connectCardsTable);
		executeCommand(Provider::connectTransactionsTable);
		executeCommand(Provider::connectOperationsTable);
		*/
	}
	static void deleteTablesData() { executeCommand(Provider::deleteTablesData); }
};

#endif
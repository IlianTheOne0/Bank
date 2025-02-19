#ifndef DB_BANK_PROVIDER_CONNECTION_ABSTRACTION_H
#define DB_BANK_PROVIDER_CONNECTION_ABSTRACTION_H

#include "PROV_IConnection.h"

class AConnectionProvider
	: public IConnectionProvider
{
private:
	connection* _connection;
public:
	AConnectionProvider(const string& connectionInfo);
	virtual ~AConnectionProvider();

	connection* getConnection() override;
};

#endif
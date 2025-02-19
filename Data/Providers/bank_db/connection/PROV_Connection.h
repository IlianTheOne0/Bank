#ifndef DB_BANK_PROVIDER_CONNECTION_H
#define DB_BANK_PROVIDER_CONNECTION_H

#include "PROV_AConnection.h"

class ConnectionProvider
	: public AConnectionProvider
{
public:
	ConnectionProvider(const string& connectionInfo) : AConnectionProvider(connectionInfo) { CREATE_INFO("ConnectionProvider <- constructor: called;"); }
	~ConnectionProvider() override { CREATE_INFO("ConnectionProvider <- destructor: called;"); }
};

#endif
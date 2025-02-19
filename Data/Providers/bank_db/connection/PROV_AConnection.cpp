#include "PROV_AConnection.h"

AConnectionProvider::AConnectionProvider(const string& connectionInfo)
	: _connection(DEFAULT_EMPTY_CONNECTION)
{
	CREATE_INFO("AConnectionProvider <- constructor: called;");

	try
	{
		INFO("AConnectionProvider <- constructor <- connection: Trying to connect to the DB (" + connectionInfo + ");");

		_connection = new connection(connectionInfo);
		if (!_connection->is_open()) { ERROR("AConnectionProvider <- constructor <- connection: connection failed!"); throw exception(); }
	}
	catch (...) { if (_connection != nullptr) { delete _connection; _connection = DEFAULT_EMPTY_CONNECTION; } throw; }
}

AConnectionProvider::~AConnectionProvider()
{
	CREATE_INFO("AConnectionProvider <- destructor: called;");

	if (_connection != nullptr) { _connection->~connection(); delete _connection; _connection = DEFAULT_EMPTY_CONNECTION; }
}

connection* AConnectionProvider::getConnection() { INFO("AConnectionProvider -> method getConnection: called;"); return _connection; }
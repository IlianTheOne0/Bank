#ifndef BANK_SYSTEM_DB_PROVIDER_H
#define BANK_SYSTEM_DB_PROVIDER_H

#include "../../Core/Libs/dataConfig.h"

class IBankSystemDbProvider
{
public:
	virtual session& connect() = 0;
	virtual void disconnect(session& session) = 0;
};

class BankSystemDbProvider
	: public IBankSystemDbProvider
{
private:
	session* _session = nullptr;
public:
	BankSystemDbProvider() = delete;
	BankSystemDbProvider(const string& connectionProperties)
		: _session(new session(postgresql, connectionProperties))
	{ CREATE_INFO("BankSystemDbProvider <- Constructor: called;"); }
	virtual ~BankSystemDbProvider() { CREATE_INFO("BankSystemDbProvider <- Destrucotr: called;"); delete _session; }

	session& connect() override { INFO("BankSystemDbProvider -> method connect: called;"); return *_session; }
	void disconnect(session& session) override { INFO("BankSystemDbProvider -> method disconnect: called;"); _session->close(); }
};

#endif
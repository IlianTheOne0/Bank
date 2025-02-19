#ifndef DB_BANK_PROVIDER_CONNECTION_INTERFACE_H
#define DB_BANK_PROVIDER_CONNECTION_INTERFACE_H

#include "../../../../Core/Libs/dataConfig.h"

class IConnectionProvider
{
public:
	virtual connection* getConnection() = 0;
};

#endif
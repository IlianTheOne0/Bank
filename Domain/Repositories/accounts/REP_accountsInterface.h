#ifndef DB_BANK_REPOSITORY_ACCOUNTS_INTERFACE_H
#define DB_BANK_REPOSITORY_ACCOUNTS_INTERFACE_H

#include "../../Entities/Account/account.h"
#include "../../../Core/Libs/domainConfig.h"

class IAccountsRepository
{
public:
	virtual int createAccount(const Account* account) = 0;
	virtual Account* getAllAccounts(size_t* counter) = 0;
};

#endif
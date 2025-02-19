#ifndef DB_BANK_REPOSITORY_ACCOUNTS_ABSTRACTION_H
#define DB_BANK_REPOSITORY_ACCOUNTS_ABSTRACTION_H

#include "REP_accountsInterface.h"
#include "../../../Data/data.h"

class AAccountsRepository
	: public IAccountsRepository
{
private:
	AConnectionProvider* _provider;
public:
	AAccountsRepository(AConnectionProvider* provider);
	virtual ~AAccountsRepository();

	int createAccount(const Account* account) override;
	Account* getAllAccounts(size_t* counter) override;
};

#endif
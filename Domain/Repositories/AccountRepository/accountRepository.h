#ifndef ACCOUNT_REPOSITORY_ABSTRACTION_H
#define ACCOUNT_REPOSITORY_ABSTRACTION_H

#include "../../../Data/data.h"
#include "../../Entities/Account/account.h"
#include "../IRepository.h"

class AccountRepository
	: public IRepository<Account>
{
protected:
	virtual size_t _add(size_t& clientId, const float& balance, const string& currency, const string& statusStr);
	virtual bool _update(const size_t& accountId, const float& balance, const string& currency, const string& openedDateStr, const string& closedDateStr, const string& status);
public:
	AccountRepository();

	virtual size_t add(size_t& clientId, const float& balance, const string& currency, const AccountStatus& status);
	size_t add(const Account* account) override;
	Account* get(size_t id) override;
	virtual bool update(const size_t& accountId, const float& balance, const string& currency, const tm& openedDateStr, const tm& closedDateStr, const AccountStatus& status);
	bool update(const Account* class_) override;
	bool deleteClass(size_t id) override;
};

#endif
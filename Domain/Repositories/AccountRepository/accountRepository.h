#ifndef ACCOUNT_REPOSITORY_ABSTRACTION_H
#define ACCOUNT_REPOSITORY_ABSTRACTION_H

#include "../../../Data/data.h"
#include "../../Entities/Account/account.h"
#include "../IRepository.h"

class AccountRepository
	: public IRepository<Account>
{
protected:
	virtual size_t _add(size_t& clientId, const float& balance, const string& currency, const string& statusStr, const string& password, const string& salt, const string& adminStatusStr);
	virtual bool _update(const size_t& accountId, const float& balance, const string& currency, const string& openedDateStr, const string& closedDateStr, const string& status, const string& password, const string& adminStatusStr);
public:
	AccountRepository();

	size_t add(const Account* account) override { return 0; };
	virtual size_t add(size_t& clientId, const float& balance, const string& currency, const AccountStatus& status, const string& password, const string& salt, const bool& adminStatus);
	virtual size_t add(const Account* account, const string& salt);
	Account* get(size_t id) override;
	virtual bool update(const size_t& accountId, const float& balance, const string& currency, const tm& openedDateStr, const tm& closedDateStr, const AccountStatus& status, const string& password, const bool& adminStatusStr);
	bool update(const Account* class_) override;
	bool deleteClass(size_t id) override;
};

#endif
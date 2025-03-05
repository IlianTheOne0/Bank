#ifndef CREATEACCOUNT_USECASE_H
#define CREATEACCOUNT_USECASE_H

#include "../../../../Core/Libs/dataConfig.h"
#include "../../../../Domain/domain.h"

class AccountUseCase
{
public:
	static pair<string, string> encryptPassword(const string& password, const string& salt = "");
	static Account* createAccount(size_t& clientId, const string& currency, const string& password);
};

#endif
#ifndef CREATEACCOUNT_USECASE_H
#define CREATEACCOUNT_USECASE_H

#include "../../../Core/Libs/dataConfig.h"
#include "../../../Domain/domain.h"

class CreateAccountUseCase
{
private:
	static pair<string, string> encryptPassword_(const string& password);
public:
	static Account* createAccount(size_t& clientId, const string& currency, const string& password);
};

#endif
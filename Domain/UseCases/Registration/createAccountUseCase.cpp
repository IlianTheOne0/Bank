#include "createAccountUseCase.h"
#include "../../../Presentation/View/Items/LanguageSelection/languagesEnum.h"

pair<string, string> CreateAccountUseCase::encryptPassword_(const string& password)
{
	INFO("CreateAccountUseCase -> static method encryptPassword: called;");

	return pair<string, string>(password, password); // must be: (passport's hash, salt)
}

Account* CreateAccountUseCase::createAccount(size_t& clientId, const string& currency, const string& password)
{
	INFO("CreateAccountUseCase -> static method createAccount: called;");

	pair<string, string> encryptedPassword = encryptPassword_(password);

	AccountRepository accountRepo;
	return accountRepo.get(accountRepo.add(clientId, 0, currency, AccountStatus::active, encryptedPassword.first, encryptedPassword.second, false));
}
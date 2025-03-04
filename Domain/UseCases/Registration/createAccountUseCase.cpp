#include "createAccountUseCase.h"
#include "../../Core/Libs/presentationConfig.h"

pair<string, string> CreateAccountUseCase::encryptPassword_(const string& password) 
{
	INFO("CreateAccountUseCase -> static method encryptPassword: called;");

	// Generating a random salt (16 characters)
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distrib(33, 126); // Символы в ASCII

	string salt;
	for (int i = 0; i < 16; ++i) {
		salt += static_cast<char>(distrib(gen));
	}

	// Hash password + salt via hash (not crypto-resistant, but better than just password)
	hash<string> hasher;
	size_t hashed = hasher(password + salt);

	// Convert hash to string (hex)
	stringstream ss;
	ss << hex << hashed;
	string hashedPassword = ss.str();

	return {hashedPassword, salt};
}

Account* CreateAccountUseCase::createAccount(size_t& clientId, const string& currency, const string& password)
{
	INFO("CreateAccountUseCase -> static method createAccount: called;");

	pair<string, string> encryptedPassword = encryptPassword_(password);

	AccountRepository accountRepo;
	return accountRepo.get(accountRepo.add(clientId, 0, currency, AccountStatus::active, encryptedPassword.first, encryptedPassword.second, false));
}
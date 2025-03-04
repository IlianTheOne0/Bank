#include "createAccountUseCase.h"
#include "../../../Presentation/View/Items/LanguageSelection/languagesEnum.h"

#include <random>
#include <sstream>
//#include <iomanip>
	
pair<string, string> CreateAccountUseCase::encryptPassword_(const string& password) 
{
	INFO("CreateAccountUseCase -> static method encryptPassword: called;");

	// Генерация случайной соли (16 символов)
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(33, 126); // Символы в ASCII

	string salt;
	for (int i = 0; i < 16; ++i) {
		salt += static_cast<char>(distrib(gen));
	}

	// Хешируем пароль + соль через std::hash (не криптостойкий, но лучше, чем просто пароль)
	std::hash<string> hasher;
	size_t hashed = hasher(password + salt);

	// Конвертируем хеш в строку (hex)
	std::stringstream ss;
	ss << std::hex << hashed;
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
#include "../ClientUseCase/ClientUseCase.h"
#include "../../../../Core/Libs/presentationConfig.h"

pair<string, string> AccountUseCase::encryptPassword(const string& password, const string& salt)
{
    INFO("CreateAccountUseCase -> static method encryptPassword: called;");

    auto escapeString = [](const string& value)
        {
            string result;
            for (char ch : value) { if (ch == '\'') { result += "''"; } else { result += ch; } }
            return result;
        };

    string finalSalt = salt;
    if (finalSalt.empty()) {
        // Generating a random salt (16 characters)
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(33, 126); // ASCII characters

        for (int i = 0; i < 16; ++i) {
            finalSalt += static_cast<char>(distrib(gen));
        }
    }

    // Hash password + salt via hash (not crypto-resistant, but better than just password)
    hash<string> hasher;
    size_t hashed = hasher(password + finalSalt);

    // Convert hash to string (hex)
    stringstream ss;
    ss << hex << hashed;
    string hashedPassword = ss.str();

    return { escapeString(hashedPassword), escapeString(finalSalt) };
}

Account* AccountUseCase::createAccount(size_t& clientId, const string& currency, const string& password)
{
    INFO("CreateAccountUseCase -> static method createAccount: called;");

    pair<string, string> encryptedPassword = encryptPassword(password);

    AccountRepository accountRepo;
    size_t accountId = accountRepo.add(clientId, 0, currency, AccountStatus::active, encryptedPassword.first, encryptedPassword.second, false);
    return accountRepo.get(accountId);
}
#include "../../../Domain/Repositories/AccountRepository/accountRepository.h"
#include "../../../Domain/Repositories/ClientRepository/clientRepository.h"

#include "../tests.h"
#include "../randomGenerator.h"

#include <iostream>

void setupClient(BankSystemDbProvider& dbProvider) {
    ClientRepository clientRepo;
    Client client = { 0, "John", "Doe", to_string(generateRandomLongLong(100000, 999999)), "+380" + to_string(generateRandomLongLong(100000, 999999)), to_string(generateRandomLongLong(100000, 999999)) + "john.doe@example.com", {} };
    clientRepo.add(&client);
}

void testAddAccount(AccountRepository& accountRepo) {
    Account account = { 0, 1, 456.45f, "USD", {}, { 0, 0, 0, 1, 0, 121 }, AccountStatus::closed };
    int accountId = accountRepo.add(&account);

    if (accountId > 0) { std::cout << "AddAccount test passed." << std::endl; }
    else { std::cout << "AddAccount test failed." << std::endl; }
}

void testUpdateAccount(AccountRepository& accountRepo) {
    Account account = { 0, 1, 1000.0f, "USD", {}, { 0, 0, 0, 1, 0, 121 }, AccountStatus::closed };
    int accountId = accountRepo.add(&account);
    account.accountId = accountId;
    account.balance = 2000.0f;
    bool result = accountRepo.update(&account);

    if (result) { std::cout << "UpdateAccount test passed." << std::endl; }
    else { std::cout << "UpdateAccount test failed." << std::endl; }
}

void testDeleteAccount(AccountRepository& accountRepo) {
    Account account = { 0, 1, 1000.0f, "USD", {}, { 0, 0, 0, 1, 0, 121 }, AccountStatus::closed };
    int accountId = accountRepo.add(&account);
    bool result = accountRepo.deleteClass(accountId);

    if (result) { std::cout << "DeleteAccount test passed." << std::endl; }
    else { std::cout << "DeleteAccount test failed." << std::endl; }
}

void testGetAccount(AccountRepository& accountRepo) {
    Account account = { 0, 1, 1000.0f, "USD", {}, { 0, 0, 0, 1, 0, 121 }, AccountStatus::closed };
    int accountId = accountRepo.add(&account);
    Account* fetchedAccount = accountRepo.get(accountId);

    bool testPassed = true;

    if (fetchedAccount->balance != 1000.0f) {
        std::cout << "balance mismatch: expected 1000.0, got " << fetchedAccount->balance << std::endl;
        testPassed = false;
    }
    if (fetchedAccount->currency != "USD") {
        std::cout << "currency mismatch: expected USD, got " << fetchedAccount->currency << std::endl;
        testPassed = false;
    }

    if (testPassed) { std::cout << "GetAccount test passed." << std::endl; }
    else { std::cout << "GetAccount test failed." << std::endl; }

    delete fetchedAccount;
}

void Test::accountRepositoryTest()
{
    BankSystemDbProvider dbProvider;
    AccountRepository accountRepo;

    setupClient(dbProvider);

    testAddAccount(accountRepo);
    testUpdateAccount(accountRepo);
    testDeleteAccount(accountRepo);
    testGetAccount(accountRepo);

    //dbProvider.deleteTablesData();
}
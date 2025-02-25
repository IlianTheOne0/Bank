#include "../../../Domain/Repositories/TransactionRepository/transactionRepository.h"
#include "../../../Domain/Repositories/AccountRepository/accountRepository.h"
#include "../../../Domain/Repositories/ClientRepository/clientRepository.h"
#include "../../../Domain/Repositories/OperationRepository/operationRepository.h"

#include "../tests.h"
#include "../randomGenerator.h"

#include <iostream>

void setupClient(BankSystemDbProvider& dbProvider, size_t& clientId) {
    ClientRepository clientRepo;
    Client client = { 0, "John", "Doe", to_string(generateRandomLongLong(100000, 999999)), "+380" + to_string(generateRandomLongLong(100000, 999999)), to_string(generateRandomLongLong(100000, 999999)) + "john.doe@example.com", {} };
    clientId = clientRepo.add(&client);
}

void setupAccount(BankSystemDbProvider& dbProvider, size_t clientId, size_t& accountId) {
    AccountRepository accountRepo;
    Account account = { 0, clientId, 1000.0f, "USD", {}, { 0, 0, 0, 1, 0, 121 }, AccountStatus::closed };
    accountId = accountRepo.add(&account);
}

void setupOperation(BankSystemDbProvider& dbProvider, size_t& operationId) {
    OperationRepository operationRepo;
    Operation operation = { 0, "Test Operation", true, false };
    operationId = operationRepo.add(&operation);
}

void testAddTransaction(TransactionRepository& transactionRepo, size_t fromAccountId, size_t toAccountId, size_t operationId) {
    Transaction transaction = { 0, fromAccountId, toAccountId, 500.0f, operationId, {}, "Test transaction", TransactionStatus::pending };
    int transactionId = transactionRepo.add(&transaction);

    if (transactionId > 0) { std::cout << "AddTransaction test passed." << std::endl; }
    else { std::cout << "AddTransaction test failed." << std::endl; }
}

void testUpdateTransaction(TransactionRepository& transactionRepo, size_t fromAccountId, size_t toAccountId, size_t operationId) {
    Transaction transaction = { 0, fromAccountId, toAccountId, 500.0f, operationId, {}, "Test transaction", TransactionStatus::pending };
    int transactionId = transactionRepo.add(&transaction);
    transaction.transactionId = transactionId;
    transaction.amount = 1000.0f;
    bool result = transactionRepo.update(&transaction);

    if (result) { std::cout << "UpdateTransaction test passed." << std::endl; }
    else { std::cout << "UpdateTransaction test failed." << std::endl; }
}

void testDeleteTransaction(TransactionRepository& transactionRepo, size_t fromAccountId, size_t toAccountId, size_t operationId) {
    Transaction transaction = { 0, fromAccountId, toAccountId, 500.0f, operationId, {}, "Test transaction", TransactionStatus::pending };
    int transactionId = transactionRepo.add(&transaction);
    bool result = transactionRepo.deleteClass(transactionId);

    if (result) { std::cout << "DeleteTransaction test passed." << std::endl; }
    else { std::cout << "DeleteTransaction test failed." << std::endl; }
}

void testGetTransaction(TransactionRepository& transactionRepo, size_t fromAccountId, size_t toAccountId, size_t operationId) {
    Transaction transaction = { 0, fromAccountId, toAccountId, 500.0f, operationId, {}, "Test transaction", TransactionStatus::pending };
    int transactionId = transactionRepo.add(&transaction);
    Transaction* fetchedTransaction = transactionRepo.get(transactionId);

    bool testPassed = true;

    if (fetchedTransaction->amount != 500.0f) {
        std::cout << "amount mismatch: expected 500.0, got " << fetchedTransaction->amount << std::endl;
        testPassed = false;
    }
    if (fetchedTransaction->description != "Test transaction") {
        std::cout << "description mismatch: expected 'Test transaction', got " << fetchedTransaction->description << std::endl;
        testPassed = false;
    }

    if (testPassed) { std::cout << "GetTransaction test passed." << std::endl; }
    else { std::cout << "GetTransaction test failed." << std::endl; }

    delete fetchedTransaction;
}

void Test::transactionRepositoryTest()
{
    BankSystemDbProvider dbProvider;
    TransactionRepository transactionRepo;

    size_t clientId1, clientId2;
    setupClient(dbProvider, clientId1);
    setupClient(dbProvider, clientId2);

    size_t fromAccountId, toAccountId;
    setupAccount(dbProvider, clientId1, fromAccountId);
    setupAccount(dbProvider, clientId2, toAccountId);

    size_t operationId;
    setupOperation(dbProvider, operationId);

    testAddTransaction(transactionRepo, fromAccountId, toAccountId, operationId);
    testUpdateTransaction(transactionRepo, fromAccountId, toAccountId, operationId);
    testDeleteTransaction(transactionRepo, fromAccountId, toAccountId, operationId);
    testGetTransaction(transactionRepo, fromAccountId, toAccountId, operationId);

    //dbProvider.deleteTablesData();
}
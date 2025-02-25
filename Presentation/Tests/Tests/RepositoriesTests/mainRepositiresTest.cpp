#include "../../tests.h"
#include "../../../../Domain/Repositories/TransactionRepository/transactionRepository.h"
#include "../../../../Domain/Repositories/AccountRepository/accountRepository.h"
#include "../../../../Domain/Repositories/ClientRepository/clientRepository.h"
#include "../../../../Domain/Repositories/CardRepository/cardRepository.h"
#include "../../../../Domain/Repositories/OperationRepository/operationRepository.h"
#include "../randomGenerator.h"

#include <iostream>

void setupClientWithAccountsAndCards(BankSystemDbProvider& dbProvider, size_t& clientId, size_t& accountId1, size_t& accountId2, size_t& cardId1, size_t& cardId2) {
    ClientRepository clientRepo;
    AccountRepository accountRepo;
    CardRepository cardRepo;

    Client client = { 0, "John", "Doe", to_string(generateRandomLongLong(100000, 999999)), "+380" + to_string(generateRandomLongLong(100000, 999999)), to_string(generateRandomLongLong(100000, 999999)) + "john.doe@example.com", {} };
    clientId = clientRepo.add(&client);

    Account account1 = { 0, clientId, 1000.0f, "USD", {}, {}, AccountStatus::active };
    accountId1 = accountRepo.add(&account1);

    Account account2 = { 0, clientId, 2000.0f, "USD", {}, {}, AccountStatus::active };
    accountId2 = accountRepo.add(&account2);

    Card card1 = { 0, accountId1, to_string(generateRandomLongLong(100000, 999999)) + "4187060861", {}, false, {} };
    cardId1 = cardRepo.add(&card1);

    Card card2 = { 0, accountId2, to_string(generateRandomLongLong(100000, 999999)) + "4187060861", {}, true, {} };
    cardId2 = cardRepo.add(&card2);
}

void setupOperationMain(BankSystemDbProvider& dbProvider, size_t& operationId) {
    OperationRepository operationRepo;
    Operation operation = { 0, "Test Operation", true, false };
    operationId = operationRepo.add(&operation);
}

void testTransaction(TransactionRepository& transactionRepo, size_t fromAccountId, size_t toAccountId, size_t operationId) {
    Transaction transaction1 = { 0, fromAccountId, toAccountId, 500.0f, operationId, {}, "Test transaction 1", TransactionStatus::completed };
    int transactionId1 = transactionRepo.add(&transaction1);

    if (transactionId1 > 0) { std::cout << "Transaction 1 test passed." << std::endl; }
    else { std::cout << "Transaction 1 test failed." << std::endl; }

    Transaction transaction2 = { 0, fromAccountId, toAccountId, 300.0f, operationId, {}, "Test transaction 2", TransactionStatus::canceled };
    int transactionId2 = transactionRepo.add(&transaction2);

    if (transactionId2 > 0) { std::cout << "Transaction 2 test passed." << std::endl; }
    else { std::cout << "Transaction 2 test failed." << std::endl; }
}

void Test::mainRepositoriesTest()
{
    BankSystemDbProvider dbProvider;
    TransactionRepository transactionRepo;
    OperationRepository operationRepo;

    size_t clientId1, clientId2;
    size_t accountId1, accountId2, accountId3, accountId4;
    size_t cardId1, cardId2, cardId3, cardId4;

    setupClientWithAccountsAndCards(dbProvider, clientId1, accountId1, accountId2, cardId1, cardId2);
    setupClientWithAccountsAndCards(dbProvider, clientId2, accountId3, accountId4, cardId3, cardId4);

    size_t operationId;
    setupOperationMain(dbProvider, operationId);

    testTransaction(transactionRepo, accountId1, accountId3, operationId);
    testTransaction(transactionRepo, accountId2, accountId4, operationId);

    //dbProvider.deleteTablesData();
}
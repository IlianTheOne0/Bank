#include "../../tests.h"

#include "../../../../Domain/Repositories/CardRepository/cardRepository.h"
#include "../../../../Domain/Repositories/AccountRepository/accountRepository.h"
#include "../../../../Domain/Repositories/ClientRepository/clientRepository.h"

#include "../randomGenerator.h"

void setupClientAndAccount(BankSystemDbProvider& dbProvider, size_t& clientId, size_t& accountId) {
    ClientRepository clientRepo;
    AccountRepository accountRepo;

    Client client = { 0, "John", "Doe", to_string(generateRandomLongLong(100000, 999999)), "+380" + to_string(generateRandomLongLong(100000, 999999)), to_string(generateRandomLongLong(100000, 999999)) + "john.doe@example.com", {} };
    clientId = clientRepo.add(&client);

    string password = "securepassword";
    string salt = "randomsalt";
    bool adminStatus = false;

    Account account = { 0, clientId, 456.45f, "USD", {}, {}, AccountStatus::active, password, adminStatus };
    accountId = accountRepo.add(&account, salt);
}

void testAddCard(CardRepository& cardRepo, size_t accountId) {
    Card card = { 0, accountId, to_string(generateRandomLongLong(100000, 999999)) + "4187060861", {}, false, {}, false, 0 };
    int cardId = cardRepo.add(&card);

    if (cardId > 0) { cout << "AddCard test passed." << endl; }
    else { cout << "AddCard test failed." << endl; }
}

void testUpdateCard(CardRepository& cardRepo, size_t accountId) {
    Card card = { 0, accountId, to_string(generateRandomLongLong(100000, 999999)) + "4187060861", {}, false, {}, false, 0 };
    size_t cardId = cardRepo.add(&card);
    card.cardId = cardId;
    card.isBlocked = true;
    card.isJar = true;
    card.jarPercentage = 50;
    card.expiryDate = {}; // Set appropriate expiry date
    bool result = cardRepo.update(&card);

    if (result) { cout << "UpdateCard test passed." << endl; }
    else { cout << "UpdateCard test failed." << endl; }
}

void testDeleteCard(CardRepository& cardRepo, size_t accountId) {
    Card card = { 0, accountId, to_string(generateRandomLongLong(100000, 999999)) + "4187060861", {}, false, {}, false, 0 };
    size_t cardId = cardRepo.add(&card);
    bool result = cardRepo.deleteClass(cardId);

    if (result) { cout << "DeleteCard test passed." << endl; }
    else { cout << "DeleteCard test failed." << endl; }
}

void testGetCard(CardRepository& cardRepo, size_t accountId) {
    string cardIdRandom = to_string(generateRandomLongLong(100000, 999999)) + "4187060861";
    Card card = { 0, accountId, cardIdRandom, {}, false, {}, false, 0 };
    size_t cardId = cardRepo.add(&card);
    Card* fetchedCard = cardRepo.get(cardId);

    bool testPassed = true;

    if (fetchedCard->cardNumber != cardIdRandom) {
        cout << "cardNumber mismatch: expected " << cardIdRandom << ", got " << fetchedCard->cardNumber << endl;
        testPassed = false;
    }
    if (fetchedCard->isBlocked != false) {
        cout << "isBlocked mismatch: expected false, got " << fetchedCard->isBlocked << endl;
        testPassed = false;
    }
    if (fetchedCard->isJar != false) {
        cout << "isJar mismatch: expected false, got " << fetchedCard->isJar << endl;
        testPassed = false;
    }
    if (fetchedCard->jarPercentage != 0) {
        cout << "jarPercentage mismatch: expected 0, got " << fetchedCard->jarPercentage << endl;
        testPassed = false;
    }

    if (testPassed) { cout << "GetCard test passed." << endl; }
    else { cout << "GetCard test failed." << endl; }

    delete fetchedCard;
}

void Test::cardRepositoryTest()
{
    BankSystemDbProvider dbProvider;
    /* dbProvider.deleteTablesData();*/

    CardRepository cardRepo;
    size_t clientId, accountId;

    setupClientAndAccount(dbProvider, clientId, accountId);

    testAddCard(cardRepo, accountId);
    testUpdateCard(cardRepo, accountId);
    testDeleteCard(cardRepo, accountId);
    testGetCard(cardRepo, accountId);

    //dbProvider.deleteTablesData();
}

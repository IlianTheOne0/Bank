#include "../../../Domain/Repositories/CardRepository/cardRepository.h"
#include "../../../Domain/Repositories/AccountRepository/accountRepository.h"
#include "../../../Domain/Repositories/ClientRepository/clientRepository.h"

#include "../tests.h"
#include "../randomGenerator.h"

void setupClientAndAccount(BankSystemDbProvider& dbProvider, size_t& clientId, size_t& accountId) {
    ClientRepository clientRepo;
    AccountRepository accountRepo;

    Client client = { 0, "John", "Doe", to_string(generateRandomLongLong(100000, 999999)), "+380" + to_string(generateRandomLongLong(100000, 999999)), to_string(generateRandomLongLong(100000, 999999)) + "john.doe@example.com", {} };
    clientId = clientRepo.add(&client);

    Account account = { 0, clientId, 456.45f, "USD", {}, {}, Status::active };
    accountId = accountRepo.add(&account);
}

void testAddCard(CardRepository& cardRepo, size_t accountId) {
    Card card = { 0, accountId, to_string(generateRandomLongLong(100000, 999999)) + "4187060861", {}, false, {}};
    int cardId = cardRepo.add(&card);

    if (cardId > 0) { std::cout << "AddCard test passed." << std::endl; }
    else { std::cout << "AddCard test failed." << std::endl; }
}

void testUpdateCard(CardRepository& cardRepo, size_t accountId) {
    Card card = { 0, accountId, to_string(generateRandomLongLong(100000, 999999)) + "4187060861", {}, false, {} };
    size_t cardId = cardRepo.add(&card);
    card.cardId = cardId;
    card.isBlocked = true;
    Card card2 = { 0, accountId, to_string(generateRandomLongLong(100000, 999999)) + "4187060861", {}, true, {} };
    executeCommand("SELECT * FROM bank_system.cards WHERE card_number = '" + card2.cardNumber + "';");
    bool result = cardRepo.update(&card2);

    if (result) { std::cout << "UpdateCard test passed." << std::endl; }
    else { std::cout << "UpdateCard test failed." << std::endl; }
}

void testDeleteCard(CardRepository& cardRepo, size_t accountId) {
    Card card = { 0, accountId, to_string(generateRandomLongLong(100000, 999999)) + "4187060861", {}, false, {} };
    size_t cardId = cardRepo.add(&card);
    bool result = cardRepo.deleteClass(cardId);

    if (result) { std::cout << "DeleteCard test passed." << std::endl; }
    else { std::cout << "DeleteCard test failed." << std::endl; }
}

void testGetCard(CardRepository& cardRepo, size_t accountId) {
    string cardIdRandom = to_string(generateRandomLongLong(100000, 999999)) + "4187060861";
    Card card = { 0, accountId, cardIdRandom, {}, false, {} };
    size_t cardId = cardRepo.add(&card);
    Card* fetchedCard = cardRepo.get(cardId);

    bool testPassed = true;

    if (fetchedCard->cardNumber != cardIdRandom) {
        std::cout << "cardNumber mismatch: expected " << cardIdRandom << ", got " << fetchedCard->cardNumber << std::endl;
        testPassed = false;
    }
    if (fetchedCard->isBlocked != false) {
        std::cout << "isBlocked mismatch: expected false, got " << fetchedCard->isBlocked << std::endl;
        testPassed = false;
    }

    if (testPassed) { std::cout << "GetCard test passed." << std::endl; }
    else { std::cout << "GetCard test failed." << std::endl; }

    delete fetchedCard;
}

void Test::cardRepositoryTest()
{
    BankSystemDbProvider dbProvider;
    CardRepository cardRepo;
    size_t clientId, accountId;

    setupClientAndAccount(dbProvider, clientId, accountId);

    testAddCard(cardRepo, accountId);
    testUpdateCard(cardRepo, accountId);
    testDeleteCard(cardRepo, accountId);
    testGetCard(cardRepo, accountId);

    //dbProvider.deleteTablesData();
}

// docker exec -it postgres-local psql -U sa -d postgres -c "SELECT conname, condeferrable, convalidated, pg_get_constraintdef(oid) FROM pg_constraint WHERE conrelid = 'bank_system.cards'::regclass;"
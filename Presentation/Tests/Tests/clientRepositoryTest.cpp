#include "../../../Domain/Repositories/ClientRepository/ClientRepository.h"

#include "../tests.h"
#include "../randomGenerator.h"

#include <iostream>

void testAddClient(ClientRepository& clientRepo) {
    Client client = { 0, "John", "Doe", to_string(generateRandomLongLong(100000, 999999)), "+380" + to_string(generateRandomLongLong(100000, 999999)), to_string(generateRandomLongLong(100000, 999999)) + "john.doe@example.com", {} };
    int clientId = clientRepo.add(&client);

    if (clientId > 0) { cout << "AddClient test passed." << endl; }
    else { cout << "AddClient test failed." << endl; }
}

void testUpdateClient(ClientRepository& clientRepo) {
    Client client = { 0, "John", "Doe", to_string(generateRandomLongLong(100000, 999999)), "+380" + to_string(generateRandomLongLong(100000, 999999)), to_string(generateRandomLongLong(100000, 999999)) + "john.doe@example.com", {} };
    int clientId = clientRepo.add(&client);
    client.clientId = clientId;
    client.firstName = "Jane";
    bool result = clientRepo.update(&client);

    if (result) { cout << "UpdateClient test passed." << endl; }
    else { cout << "UpdateClient test failed." << endl; }
}

void testUpdateClientWithDate(ClientRepository& clientRepo) {
    Client client = { 0, "John", "Doe", to_string(generateRandomLongLong(100000, 999999)), "+380" + to_string(generateRandomLongLong(100000, 999999)), to_string(generateRandomLongLong(100000, 999999)) + "john.doe@example.com", {} };
    int clientId = clientRepo.add(&client);
    client.clientId = clientId;
    client.firstName = "Jane";
    client.registrationDate = { 0, 0, 0, 1, 0, 121 }; // 2021-01-01
    bool result = clientRepo.update(&client);

    if (result) { cout << "UpdateClientWithDate test passed." << endl; }
    else { cout << "UpdateClientWithDate test failed." << endl; }
}

void testDeleteClient(ClientRepository& clientRepo) {
    Client client = { 0, "John", "Doe", to_string(generateRandomLongLong(100000, 999999)), "+380" + to_string(generateRandomLongLong(100000, 999999)), to_string(generateRandomLongLong(1000000, 9999999)) + "john.doe@example.com", {} };
    int clientId = clientRepo.add(&client);
    bool result = clientRepo.deleteClass(clientId);

    if (result) { cout << "DeleteClient test passed." << endl; }
    else { cout << "DeleteClient test failed." << endl; }
}

void testGetClient(ClientRepository& clientRepo) {
    long long number = generateRandomLongLong(1000000, 9999999);
    Client client = { 0, "John", "Doe", to_string(number), "+380" + to_string(number), to_string(number) + "john.doe@example.com", {} };
    int clientId = clientRepo.add(&client);
    Client* fetchedClient = clientRepo.get(clientId);

    bool testPassed = true;

    if (fetchedClient->firstName != "John") {
        cout << "firstName mismatch: expected John, got " << fetchedClient->firstName << endl;
        testPassed = false;
    }
    if (fetchedClient->lastName != "Doe") {
        cout << "lastName mismatch: expected Doe, got " << fetchedClient->lastName << endl;
        testPassed = false;
    }
    if (fetchedClient->passportNumber != to_string(number)) {
        cout << "passportNumber mismatch: expected " << to_string(number) << ", got " << fetchedClient->passportNumber << endl;
        testPassed = false;
    }
    if (fetchedClient->phone != "+380" + to_string(number)) {
        cout << "phone mismatch: expected " << "+380" + to_string(number) << ", got " << fetchedClient->phone << endl;
        testPassed = false;
    }
    if (fetchedClient->email != to_string(number) + "john.doe@example.com") {
        cout << "email mismatch: expected " << to_string(number) + "john.doe@example.com" << ", got " << fetchedClient->email << endl;
        testPassed = false;
    }

    if (testPassed) { cout << "GetClient test passed." << endl; }
    else { cout << "GetClient test failed." << endl; }

    delete fetchedClient;
}

void Test::clientRepositoryTest()
{
    BankSystemDbProvider dbProvider;
    ClientRepository clientRepo;

    testAddClient(clientRepo);
    testUpdateClient(clientRepo);
    testUpdateClientWithDate(clientRepo);
    testDeleteClient(clientRepo);
    testGetClient(clientRepo);

    //dbProvider.deleteTablesData();
}
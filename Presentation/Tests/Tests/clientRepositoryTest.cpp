#include "../../../Domain/Entities/Client/client.h"
#include "../../../Domain/Repositories/ClientRepository/ClientRepository.h"

#include "../tests.h"

#include <random>

long long generateRandomLongLong(long long min, long long max) {
    std::random_device rd;
    std::mt19937_64 eng(rd());
    std::uniform_int_distribution<long long> distr(min, max);

    return distr(eng);
}

void testUpdateClient(ClientRepository& clientRepo) {
    Client client = { 0, "John", "Doe", to_string(generateRandomLongLong(100000, 999999)), to_string(generateRandomLongLong(100000, 999999)), to_string(generateRandomLongLong(100000, 999999)) + "john.doe@example.com", {} };
    int clientId = clientRepo.add(&client);
    client.clientId = clientId;
    client.firstName = "Jane";
    bool result = clientRepo.update(&client);
    
    if (result) { cout << "UpdateClient test passed." << endl; }
    else { cout << "UpdateClient test failed." << endl; }
}

void testDeleteClient(ClientRepository& clientRepo) {
    Client client = { 0, "John", "Doe", to_string(generateRandomLongLong(100000, 999999)), to_string(generateRandomLongLong(100000, 999999)), to_string(generateRandomLongLong(100000, 999999)) + "john.doe@example.com", {} };
    int clientId = clientRepo.add(&client);
    bool result = clientRepo.deleteClass(clientId);
    
    if (result) { cout << "DeleteClient test passed." << endl; }
    else { cout << "DeleteClient test failed." << endl; }
}

void testGetClient(ClientRepository& clientRepo) {
    long long number = generateRandomLongLong(100000, 999999);
    Client client = { 0, "John", "Doe", to_string(number), to_string(number) + "-" + to_string(number), to_string(number) + "john.doe@example.com", {} };
    int clientId = clientRepo.add(&client);
    Client fetchedClient = *clientRepo.get(clientId);

    bool testPassed = true;

    if (fetchedClient.clientId != clientId) {
        cout << "clientId mismatch: expected " << clientId << ", got " << fetchedClient.clientId << endl;
        testPassed = false;
    }
    if (fetchedClient.firstName != "John") {
        cout << "firstName mismatch: expected John, got " << fetchedClient.firstName << endl;
        testPassed = false;
    }
    if (fetchedClient.lastName != "Doe") {
        cout << "lastName mismatch: expected Doe, got " << fetchedClient.lastName << endl;
        testPassed = false;
    }
    if (fetchedClient.passportNumber != to_string(number)) {
        cout << "passportNumber mismatch: expected " << to_string(number) << ", got " << fetchedClient.passportNumber << endl;
        testPassed = false;
    }
    if (fetchedClient.phone != to_string(number) + "-" + to_string(number)) {
        cout << "phone mismatch: expected " << to_string(number) + "-" + to_string(number) << ", got " << fetchedClient.phone << endl;
        testPassed = false;
    }
    if (fetchedClient.email != to_string(number) + "john.doe@example.com") {
        cout << "email mismatch: expected " << to_string(number) + "john.doe@example.com" << ", got " << fetchedClient.email << endl;
        testPassed = false;
    }

    if (testPassed) {
        cout << "GetClient test passed." << endl;
    }
    else {
        cout << "GetClient test failed." << endl;
    }
}


void Test::clientRepositoryTest()
{
    string connectionProperties{ "host=" + host + " port=" + port + " dbname=" + dbname + " user=" + user + " password=" + password };
    BankSystemDbProvider dbProvider(connectionProperties);
    ClientRepository clientRepo(&dbProvider);

    testUpdateClient(clientRepo);
    testDeleteClient(clientRepo);
    testGetClient(clientRepo);
}
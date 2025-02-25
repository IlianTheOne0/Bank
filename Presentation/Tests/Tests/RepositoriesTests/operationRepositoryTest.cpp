#include "../../../../Domain/Repositories/OperationRepository/operationRepository.h"

#include "../../tests.h"
#include "../randomGenerator.h"

#include <iostream>

void testAddOperation(OperationRepository& operationRepo) {
    Operation operation = { 0, "Test Operation", true, false };
    int operationId = operationRepo.add(&operation);

    if (operationId > 0) { cout << "AddOperation test passed." << endl; }
    else { cout << "AddOperation test failed." << endl; }
}

void testUpdateOperation(OperationRepository& operationRepo) {
    Operation operation = { 0, "Test Operation", true, false };
    int operationId = operationRepo.add(&operation);
    operation.operationId = operationId;
    operation.name = "Updated Operation";
    bool result = operationRepo.update(&operation);

    if (result) { cout << "UpdateOperation test passed." << endl; }
    else { cout << "UpdateOperation test failed." << endl; }
}

void testDeleteOperation(OperationRepository& operationRepo) {
    Operation operation = { 0, "Test Operation", true, false };
    int operationId = operationRepo.add(&operation);
    bool result = operationRepo.deleteClass(operationId);

    if (result) { cout << "DeleteOperation test passed." << endl; }
    else { cout << "DeleteOperation test failed." << endl; }
}

void testGetOperation(OperationRepository& operationRepo) {
    Operation operation = { 0, "Test Operation", true, false };
    int operationId = operationRepo.add(&operation);
    Operation* fetchedOperation = operationRepo.get(operationId);

    bool testPassed = true;

    if (fetchedOperation->name != "Test Operation") {
        cout << "name mismatch: expected 'Test Operation', got " << fetchedOperation->name << endl;
        testPassed = false;
    }
    if (fetchedOperation->isIncome != true) {
        cout << "isIncome mismatch: expected true, got " << fetchedOperation->isIncome << endl;
        testPassed = false;
    }

    if (testPassed) { cout << "GetOperation test passed." << endl; }
    else { cout << "GetOperation test failed." << endl; }

    delete fetchedOperation;
}

void Test::operationRepositoryTest()
{
    BankSystemDbProvider dbProvider;
    OperationRepository operationRepo;

    testAddOperation(operationRepo);
    testUpdateOperation(operationRepo);
    testDeleteOperation(operationRepo);
    testGetOperation(operationRepo);

    //dbProvider.deleteTablesData();
}
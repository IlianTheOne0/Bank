#include "../../../Core/Libs/domainConfig.h"
#include "operationRepository.h"
#include "../conversation.h"

OperationRepository::OperationRepository() { CREATE_INFO("OperationRepository <- Constructor: called;"); }

size_t OperationRepository::_add(const string& name, const string& isIncomeStr, const string& needsApprovalStr)
{
    INFO("OperationRepository -> method add (value, booleans = type::string): called;");

    try
    {
        size_t newOperationId = stoi(Queries::executeCommand(Queries::Operations::insertOperation(name, isIncomeStr, needsApprovalStr)));

        INFO("OperationRepository -> method add -> result: success;");
        return newOperationId;
    }
    catch (const exception& e) { ERROR(string("OperationRepository -> method add -> try/catch (exception): ") + e.what() + ";"); return -1; }
    catch (...) { ERROR("OperationRepository -> method add -> try/catch (...): error!;"); return -1; }
}
size_t OperationRepository::add(const string& name, const bool& isIncome, const bool& needsApproval)
{
    INFO("OperationRepository -> method add (value, booleans = type::bool): called;");
    
    return _add(name, isIncome ? "t" : "f", needsApproval ? "t" : "f");
}
size_t OperationRepository::add(const Operation* operation)
{
    INFO("OperationRepository -> method add (obj): called;");

    return add(operation->name, operation->isIncome, operation->needsApproval);
}

Operation* OperationRepository::get(size_t id)
{
    INFO("OperationRepository -> method get: called;");

    try
    {
        string result = Queries::executeCommand(Queries::Operations::getOperation(id));

        size_t pos = result.find('\n');
        if (pos != string::npos) { result = result.substr(pos + 1); }

        Operation* operation = new Operation;
        istringstream iss(result);
        string token;

        getline(iss, token, '|'); operation->operationId = stoi(token);
        getline(iss, token, '|'); operation->name = token;
        getline(iss, token, '|'); operation->isIncome = (token == "t");
        getline(iss, token, '|'); operation->needsApproval = (token == "t");

        INFO("OperationRepository -> method get -> result: success;");
        return operation;
    }
    catch (const exception& e) { ERROR(string("OperationRepository -> method get -> try/catch (exception): ") + e.what() + ";"); return nullptr; }
    catch (...) { ERROR("OperationRepository -> method get -> try/catch (...): error!;"); return nullptr; }
}

bool OperationRepository::_update(size_t& operationId, const string& name, const string& isIncomeStr, const string& needsApprovalStr)
{
    INFO("OperationRepository -> method update (value, booleans = type::string): called;");

    try
    {
        string result = Queries::executeCommand(Queries::Operations::updateOperation(operationId, name, isIncomeStr, needsApprovalStr));

        INFO("OperationRepository -> method update -> result: success;");
        return true;
    }
    catch (const exception& e) { ERROR(string("OperationRepository -> method update -> try/catch (exception): ") + e.what() + ";"); return false; }
    catch (...) { ERROR("OperationRepository -> method update -> try/catch (...): error!;"); return false; }
}
bool OperationRepository::update(size_t& operationId, const string& name, const bool& isIncome, const bool& needsApproval)
{
    INFO("OperationRepository -> method update (value, booleans = type::bool): called;");

    return _update(operationId, name, isIncome ? "t" : "f", needsApproval ? "t" : "f");
}
bool OperationRepository::update(const Operation* operation)
{
    INFO("OperationRepository -> method update (obj): called;");
    
    size_t operationId = operation->operationId;
    return update(operationId, operation->name, operation->isIncome, operation->needsApproval);
}

bool OperationRepository::deleteClass(size_t id)
{
    INFO("OperationRepository -> method deleteClass: called;");

    try
    {
        Queries::executeCommand(Queries::Operations::deleteOperation(id));

        INFO("OperationRepository -> method deleteClass -> result: success;");
        return true;
    }
    catch (const exception& e) { ERROR(string("OperationRepository -> method deleteClass -> try/catch (exception): ") + e.what() + ";"); return false; }
    catch (...) { ERROR("OperationRepository -> method deleteClass -> try/catch (...): error!;"); return false; }
}
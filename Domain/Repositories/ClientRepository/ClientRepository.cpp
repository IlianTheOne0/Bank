#include "../../../Core/Libs/domainConfig.h"
#include "../conversation.h"
#include "ClientRepository.h"

ClientRepository::ClientRepository() { CREATE_INFO("ClientRepository <- Constructor: called;"); }

size_t ClientRepository::add(const string& firstName, const string& lastName, const string& passportNumber, const string& phone, const string& email)
{
    INFO("ClientRepository -> method add (value): called;");

    try
    {
        size_t newClientId = stoi(Queries::executeCommand(Queries::Clients::insertClient(firstName, lastName, passportNumber, phone, email)));

        INFO("ClientRepository -> method add -> result: success;");
        return newClientId;
    }
    catch (const exception& e) { ERROR(string("ClientRepository -> method add -> try/catch (exception): ") + e.what() + ";"); return -1; }
    catch (...) { ERROR("ClientRepository -> method add -> try/catch (...): error!;"); return -1; }
}
//size_t ClientRepository::add(const Client* client)
//{
//    INFO("ClientRepository -> method add (obj): called;");
//
//    return add(client->getFirstName(), client->getLastName(), client->getPassportNumber(), client->getPhone(), client->getEmail());
//}

Client* ClientRepository::get(size_t id)
{
    INFO("ClientRepository -> method get: called;");

    try
    {
        string result = Queries::executeCommand(Queries::Clients::getClient(id));

        size_t pos = result.find('\n');
        if (pos != string::npos) { result = result.substr(pos + 1); }

        Client* client = new Client;
        istringstream iss(result);
        string token;

        client->setClientId(id);
        getline(iss, token, '|'); client->setFirstName(token);
        getline(iss, token, '|'); client->setLastName(token);
        getline(iss, token, '|'); client->setPassportNumber(token);
        getline(iss, token, '|'); client->setPhone(token);
        getline(iss, token, '|'); client->setEmail(token);
        getline(iss, token, '|'); client->setRegistrationDate(Conversation::dateConversion(token));

        INFO("ClientRepository -> method get -> result: success;");
        return client;
    }
    catch (const exception& e) { ERROR(string("ClientRepository -> method get -> try/catch (exception): ") + e.what() + ";"); return nullptr; }
    catch (...) { ERROR("ClientRepository -> method get -> try/catch (...): error!;"); return nullptr; }
}

bool ClientRepository::update(const size_t& clientId, const string& firstName, const string& lastName, const string& passportNumber, const string& phone, const string& email, const string& clientRegistrationDateStr)
{
    INFO("ClientRepository -> method update (value, clientRegistrationDate = type::string): called;");

    try
    {
        string result = Queries::executeCommand(Queries::Clients::updateClient( clientId, firstName, lastName, passportNumber, phone, email, clientRegistrationDateStr));

        INFO("ClientRepository -> method update -> result: success;");
        return true;
    }
    catch (const exception& e) { ERROR(string("ClientRepository -> method update -> try/catch (exception): ") + e.what() + ";"); return false; }
    catch (...) { ERROR("ClientRepository -> method update -> try/catch (...): error!;"); return false; }
}
bool ClientRepository::update(const size_t& clientId, const string& firstName, const string& lastName, const string& passportNumber, const string& phone, const string& email, const tm& clientRegistrationDate)
{
    INFO("ClientRepository -> method update (value, clientRegistrationDate = type::tm): called;");

    return update(clientId, firstName, lastName, passportNumber, phone, email, Conversation::dateConversion(clientRegistrationDate));
}
bool ClientRepository::update(const Client* client)
{
    INFO("ClientRepository -> method update (obj): called;");
    
    return update(client->getClientId(), client->getFirstName(), client->getLastName(), client->getPassportNumber(), client->getPhone(), client->getEmail(), client->getRegistrationDate());
}

bool ClientRepository::deleteClass(size_t id)
{
    INFO("ClientRepository -> method deleteClass: called;");

    try
    {
        Queries::executeCommand(Queries::Clients::deleteClient(id));

        INFO("ClientRepository -> method deleteClass -> result: success;");
        return true;
    }
    catch (const exception& e) { ERROR(string("ClientRepository -> method deleteClass -> try/catch (exception): ") + e.what() + ";"); return false; }
    catch (...) { ERROR("ClientRepository -> method deleteClass -> try/catch (...): error!;"); return false; }
}

bool ClientRepository::checkByPassport(const string& passportNumber)
{
    INFO("ClientRepository -> method checkByPassport: called;");

    try
    {
        string result = Queries::executeCommand(Queries::Clients::checkByPassport(passportNumber));
        
        istringstream iss(result);
        string token;

        bool isExist;
        getline(iss, token, '|');
        if (!token.empty()) { INFO("ClientRepository -> method checkByPassport -> result: false;"); return false; }
        else { INFO("ClientRepository -> method checkByPassport -> result: true;"); return true; }
    }
    catch (const exception& e) { ERROR(string("ClientRepository -> method checkByPassport -> try/catch (exception): ") + e.what() + ";"); return false; }
    catch (...) { ERROR("ClientRepository -> method checkByPassport -> try/catch (...): error!;"); return false; }
}

bool ClientRepository::checkByPhone(const string& phoneNumber)
{
    INFO("ClientRepository -> method checkByPhone: called;");

    try
    {
        string result = Queries::executeCommand(Queries::Clients::checkByPhone(phoneNumber));

        istringstream iss(result);
        string token;

        bool isExist;
        getline(iss, token, '|');
        if (!token.empty()) { INFO("ClientRepository -> method checkByPhone -> result: false;"); return false; }
        else { INFO("ClientRepository -> method checkByPhone -> result: true;"); return true; }
    }
    catch (const exception& e) { ERROR(string("ClientRepository -> method checkByPhone -> try/catch (exception): ") + e.what() + ";"); return false; }
    catch (...) { ERROR("ClientRepository -> method checkByPhone -> try/catch (...): error!;"); return false; }
}

bool ClientRepository::checkByEmail(const string& email)
{
    INFO("ClientRepository -> method checkByPhone: called;");

    try
    {
        string result = Queries::executeCommand(Queries::Clients::checkByEmail(email));

        istringstream iss(result);
        string token;

        bool isExist;
        getline(iss, token, '|');
        if (!token.empty()) { INFO("ClientRepository -> method checkByEmail -> result: false;"); return false; }
        else { INFO("ClientRepository -> method checkByEmail -> result: true;"); return true; }
    }
    catch (const exception& e) { ERROR(string("ClientRepository -> method checkByEmail -> try/catch (exception): ") + e.what() + ";"); return false; }
    catch (...) { ERROR("ClientRepository -> method checkByEmail -> try/catch (...): error!;"); return false; }
}

size_t ClientRepository::getClientByEmail(const string& email)
{
    INFO("ClientRepository -> method getClientByEmail: called;");

    try
    {
        string result = Queries::executeCommand(Queries::Clients::getClientByEmail(email));

        size_t pos = result.find('\n');
        if (pos != string::npos) { result = result.substr(pos + 1); }

        istringstream iss(result);
        string token;
        size_t clientId;

        getline(iss, token, '|'); clientId = stoi(token);

        INFO("ClientRepository -> method getClientByEmail -> result: success;");
        return clientId;
    }
    catch (const exception& e) { ERROR(string("ClientRepository -> method getClientByEmail -> try/catch (exception): ") + e.what() + ";"); return -1; }
    catch (...) { ERROR("ClientRepository -> method getClientByEmail -> try/catch (...): error!;"); return -1; }
}

size_t ClientRepository::getClientByPhone(const string& phone)
{
    INFO("ClientRepository -> method getClientByPhone: called;");

    try
    {
        string result = Queries::executeCommand(Queries::Clients::getClientByPhone(phone));

        size_t pos = result.find('\n');
        if (pos != string::npos) { result = result.substr(pos + 1); }

        istringstream iss(result);
        string token;
        size_t clientId;

        getline(iss, token, '|'); clientId = stoi(token);

        INFO("ClientRepository -> method getClientByPhone -> result: success;");
        return clientId;
    }
    catch (const exception& e) { ERROR(string("ClientRepository -> method getClientByPhone -> try/catch (exception): ") + e.what() + ";"); return -1; }
    catch (...) { ERROR("ClientRepository -> method getClientByPhone -> try/catch (...): error!;"); return -1; }
}
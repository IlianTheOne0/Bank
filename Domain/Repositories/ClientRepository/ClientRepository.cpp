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
size_t ClientRepository::add(const Client* client)
{
    INFO("ClientRepository -> method add (obj): called;");

    return add(client->firstName, client->lastName, client->passportNumber, client->phone, client->email);
}

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

        getline(iss, token, '|'); client->firstName = token;
        getline(iss, token, '|'); client->lastName = token;
        getline(iss, token, '|'); client->passportNumber = token;
        getline(iss, token, '|'); client->phone = token;
        getline(iss, token, '|'); client->email = token;
        getline(iss, token, '|'); client->registrationDate = Conversation::dateConversion(token);

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
    
    return update(client->clientId, client->firstName, client->lastName, client->passportNumber, client->phone, client->email, client->registrationDate);
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
    catch (const exception& e) { ERROR(string("ClientRepository -> method deleteClass -> try/catch (exception): ") + e.what() + ";"); return false;
    }
    catch (...) { ERROR("ClientRepository -> method deleteClass -> try/catch (...): error!;"); return false; }
}
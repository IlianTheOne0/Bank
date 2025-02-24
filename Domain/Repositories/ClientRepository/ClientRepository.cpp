#include "../../../Core/Libs/domainConfig.h"
#include "ClientRepository.h"

ClientRepository::ClientRepository() { CREATE_INFO("ClientRepository <- Constructor: called;"); }

int ClientRepository::add(const Client* client)
{
    INFO("ClientRepository -> method add: called;");

    try
    {
        size_t newClientId = stoi(Queries::executeCommand(Queries::Clients::insertClient(client->firstName, client->lastName, client->passportNumber, client->phone, client->email)));

        INFO("ClientRepository -> method add -> result: success;");
        return newClientId;
    }
    catch (const exception& e) { ERROR(string("ClientRepository -> method add -> try/catch (exception): ") + e.what() + ";"); return -1; }
    catch (...) { ERROR("ClientRepository -> method add -> try/catch (...): error!;"); return -1;  }
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
        getline(iss, token, '|'); istringstream dateStream(token); dateStream >> get_time(&client->registrationDate, "%Y-%m-%d");

        INFO("ClientRepository -> method get -> result: success;");
        return client;
    }
    catch (const exception& e) { ERROR(string("ClientRepository -> method get -> try/catch (exception): ") + e.what() + ";"); return nullptr; }
    catch (...) { ERROR("ClientRepository -> method get -> try/catch (...): error!;"); return nullptr; }
}

bool ClientRepository::update(const Client* client)
{
    INFO("ClientRepository -> method update: called;");

    try
    {
        unsigned int year = client->registrationDate.tm_year + 1900;
        unsigned short month = client->registrationDate.tm_mon + 1;
        unsigned short day = client->registrationDate.tm_mday;
        if (day < 1) day = 1;

        ostringstream dateStream;
        dateStream << setw(4) << setfill('0') << year << "-"
            << setw(2) << setfill('0') << month << "-"
            << setw(2) << setfill('0') << day;
        string clientRegistrationDate = dateStream.str();

        string result = Queries::executeCommand(Queries::Clients::updateClient(
            client->clientId, client->firstName, client->lastName, client->passportNumber, client->phone, client->email, clientRegistrationDate
        ));

        INFO("ClientRepository -> method update -> result: success;");
        return true;
    }
    catch (const exception& e) { ERROR(string("ClientRepository -> method update -> try/catch (exception): ") + e.what() + ";"); return false; }
    catch (...) { ERROR("ClientRepository -> method update -> try/catch (...): error!;"); return false; }
}

bool ClientRepository::deleteClass(size_t id)
{
    INFO("ClientRepository -> method deleteClass: called;");

    try
    {
        Queries::executeCommand(Queries::Clients::deleteClient(id));
        ostringstream commandStream;

        INFO("ClientRepository -> method deleteClass -> result: success;");
        return true;
    }
    catch (const exception& e) { ERROR(string("ClientRepository -> method deleteClass -> try/catch (exception): ") + e.what() + ";"); return false;
    }
    catch (...) { ERROR("ClientRepository -> method deleteClass -> try/catch (...): error!;"); return false; }
}
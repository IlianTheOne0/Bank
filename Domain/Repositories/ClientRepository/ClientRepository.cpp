#include "ClientRepository.h"
#include <cstdlib>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iomanip>

#ifdef _WIN32
#define popen _popen
#define pclose _pclose
#endif

#define CREATE_INFO(msg)
#define INFO(msg)
#define ERROR(msg)

using namespace std;

static inline string trim(const string& s) {
    auto start = find_if_not(s.begin(), s.end(), [](int ch) { return isspace(ch); });
    auto end = find_if_not(s.rbegin(), s.rend(), [](int ch) { return isspace(ch); }).base();
    return (start < end ? string(start, end) : string());
}

ClientRepository::ClientRepository(BankSystemDbProvider* dbProvider)
    : _dbProvider(dbProvider)
{
    CREATE_INFO("ClientRepository <- Constructor: called;");
}

int ClientRepository::add(const Client* client)
{
    INFO("ClientRepository -> method add: called;");

    try
    {
        ostringstream commandStream;
        commandStream << "docker exec -i postgres-local psql -U sa -d postgres -t -c \""
            << "INSERT INTO clients (first_name, last_name, passport_number, phone, email) VALUES ('"
            << client->firstName << "', '"
            << client->lastName << "', '"
            << client->passportNumber << "', '"
            << client->phone << "', '"
            << client->email
            << "') RETURNING client_id;\"";
        string command = commandStream.str();

        array<char, 128> buffer;
        string result;
        unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
        if (!pipe) {
            throw runtime_error("popen() failed!");
        }
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            result += buffer.data();
        }
        result = trim(result);
        int newClientId = stoi(result);
        INFO("ClientRepository -> method add -> result: success;");
        return newClientId;
    }
    catch (const exception& e) {
        ERROR(string("ClientRepository -> method add -> try/catch (exception): ") + e.what() + ";");
        return -1;
    }
    catch (...) {
        ERROR("ClientRepository -> method add -> try/catch (...): error!;");
        return -1;
    }
}

Client* ClientRepository::get(int id)
{
    INFO("ClientRepository -> method get: called;");

    try
    {
        ostringstream commandStream;
        commandStream << "docker exec -i postgres-local psql -U sa -d postgres -t -c \"SELECT * FROM clients WHERE client_id = "
            << id << ";\"";
        string command = commandStream.str();

        array<char, 128> buffer;
        string result;
        unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
        if (!pipe) {
            throw runtime_error("popen() failed!");
        }
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            result += buffer.data();
        }
        result = trim(result);

        size_t pos = result.find('\n');
        if (pos != string::npos) {
            result = result.substr(pos + 1);
        }

        Client* client = new Client;
        istringstream iss(result);
        string token;

        getline(iss, token, '|');
        client->clientId = stoi(trim(token));

        getline(iss, token, '|');
        client->firstName = trim(token);

        getline(iss, token, '|');
        client->lastName = trim(token);

        getline(iss, token, '|');
        client->passportNumber = trim(token);

        getline(iss, token, '|');
        client->phone = trim(token);

        getline(iss, token, '|');
        client->email = trim(token);

        getline(iss, token, '|');
        istringstream dateStream(trim(token));
        dateStream >> get_time(&client->registrationDate, "%Y-%m-%d");

        INFO("ClientRepository -> method get -> result: success;");
        return client;
    }
    catch (const exception& e) {
        ERROR(string("ClientRepository -> method get -> try/catch (exception): ") + e.what() + ";");
        return nullptr;
    }
    catch (...) {
        ERROR("ClientRepository -> method get -> try/catch (...): error!;");
        return nullptr;
    }
}

bool ClientRepository::update(const Client* client)
{
    INFO("ClientRepository -> method update: called;");

    try
    {
        int year = client->registrationDate.tm_year + 1900;
        int month = client->registrationDate.tm_mon + 1;
        int day = client->registrationDate.tm_mday;
        if (day < 1) day = 1;

        ostringstream commandStream;
        commandStream << "docker exec -i postgres-local psql -U sa -d postgres -t -c \"UPDATE clients SET "
            << "first_name = '" << client->firstName << "', "
            << "last_name = '" << client->lastName << "', "
            << "passport_number = '" << client->passportNumber << "', "
            << "phone = '" << client->phone << "', "
            << "email = '" << client->email << "', "
            << "registration_date = '"
            << setw(4) << setfill('0') << year << "-"
            << setw(2) << setfill('0') << month << "-"
            << setw(2) << setfill('0') << day
            << "' WHERE client_id = " << client->clientId << ";\"";
        string command = commandStream.str();

        array<char, 128> buffer;
        string result;
        unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
        if (!pipe) {
            throw runtime_error("popen() failed!");
        }
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            result += buffer.data();
        }

        INFO("ClientRepository -> method update -> result: success;");
        return true;
    }
    catch (const exception& e) {
        ERROR(string("ClientRepository -> method update -> try/catch (exception): ") + e.what() + ";");
        return false;
    }
    catch (...) {
        ERROR("ClientRepository -> method update -> try/catch (...): error!;");
        return false;
    }
}

bool ClientRepository::deleteClass(int id)
{
    INFO("ClientRepository -> method deleteClass: called;");

    try
    {
        ostringstream commandStream;
        commandStream << "docker exec -i postgres-local psql -U sa -d postgres -t -c \"DELETE FROM clients WHERE client_id = "
            << id << ";\"";
        string command = commandStream.str();

        array<char, 128> buffer;
        string result;
        unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
        if (!pipe) {
            throw runtime_error("popen() failed!");
        }
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            result += buffer.data();
        }

        INFO("ClientRepository -> method deleteClass -> result: success;");
        return true;
    }
    catch (const exception& e) {
        ERROR(string("ClientRepository -> method deleteClass -> try/catch (exception): ") + e.what() + ";");
        return false;
    }
    catch (...) {
        ERROR("ClientRepository -> method deleteClass -> try/catch (...): error!;");
        return false;
    }
}
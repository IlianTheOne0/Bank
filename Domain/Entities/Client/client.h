#ifndef TEMP_CLIENT_H
#define TEMP_CLIENT_H

#include "../../../Core/Libs/domainConfig.h"

struct Client
{
	size_t clientId;
	string firstName;
	string lastName;
	string passportNumber;
	string phone;
	string email;
	tm registrationDate;
};

class Client
{
private:
	size_t accountId;
	size_t clientId;
	float balance;
	string currency;
	tm openedDate;
	tm closedDate;
	AccountStatus status;
	string email;
	string phone;
	int passportNumber;
	string lastName;
	string firstName;

public:
	Client(size_t accountId, size_t clientId, float balance, const string& currency, const tm& openedDate, const tm& closedDate, AccountStatus status)
		: accountId(accountId), clientId(clientId), balance(balance), currency(currency), openedDate(openedDate), closedDate(closedDate), status(status) {}
	// Геттеры
	size_t getAccountId() const { return accountId; }
	size_t getClientId() const { return clientId; }
	float getBalance() const { return balance; }
	const std::string& getCurrency() const { return currency; }
	const tm& getOpenedDate() const { return openedDate; }
	const tm& getClosedDate() const { return closedDate; }
	AccountStatus getStatus() const { return status; }
	const string& Client::getFirstName() const { return firstName; }
	const string& Client::getLastName() const { return lastName; }
	const string& Client::getPassportNumber() const { return passportNumber; }
	const string& Client::getPhone() const { return phone;}
	const string& Client::getEmail() const { return email; }
	
	// Сеттеры
	void setAccountId(size_t id) { accountId = id; }
	void setClientId(size_t id) { clientId = id; }
	void setBalance(float bal) { balance = bal; }
	void setCurrency(const std::string& curr) { currency = curr; }
	void setOpenedDate(const tm& date) { openedDate = date; }
	void setClosedDate(const tm& date) { closedDate = date; }
	void setStatus(AccountStatus stat) { status = stat; }
};

class Account
{
private:
	size_t accountId;
	size_t clientId;
	float balance;
	std::string currency;
	std::tm openedDate;
	std::tm closedDate;
	AccountStatus status;

public:
	// Геттеры
	size_t getAccountId() const { return accountId; }
	size_t getClientId() const { return clientId; }
	float getBalance() const { return balance; }
	std::string getCurrency() const { return currency; }
	std::tm getOpenedDate() const { return openedDate; }
	std::tm getClosedDate() const { return closedDate; }
	AccountStatus getStatus() const { return status; }

	// Сеттеры
	void setAccountId(size_t id) { accountId = id; }
	void setClientId(size_t id) { clientId = id; }
	void setBalance(float bal) { balance = bal; }
	void setCurrency(const std::string& curr) { currency = curr; }
	void setOpenedDate(const std::tm& date) { openedDate = date; }
	void setClosedDate(const std::tm& date) { closedDate = date; }
	void setStatus(AccountStatus stat) { status = stat; }
};

#endif
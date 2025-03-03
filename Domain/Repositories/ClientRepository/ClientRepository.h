#ifndef CLIENT_REPOSITORY_ABSTRACTION_H
#define CLIENT_REPOSITORY_ABSTRACTION_H

#include "../../../Data/data.h"
#include "../../Entities/Client/client.h"
#include "../IRepository.h"

class ClientRepository
	: public IRepository<Client>
{
public:
	ClientRepository();

	virtual size_t add(const string& firstName, const string& lastName, const string& passportNumber, const string& phone, const string& email);
	size_t add(const Client* class_) override { return 0; };
	Client* get(size_t id) override;
	virtual bool update(const size_t& clientId, const string& firstName, const string& lastName, const string& passportNumber, const string& phone, const string& email, const string& clientRegistrationDate);
	virtual bool update(const size_t& clientId, const string& firstName, const string& lastName, const string& passportNumber, const string& phone, const string& email, const tm& clientRegistrationDate);
	bool update(const Client* class_) override;
	bool deleteClass(size_t id) override;

	bool checkByPassport(const string& passportNumber);
	bool checkByPhone(const string& phoneNumber);
};

#endif
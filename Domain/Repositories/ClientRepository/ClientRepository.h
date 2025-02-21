#ifndef CLIENT_REPOSITORY_ABSTRACTION_H
#define CLIENT_REPOSITORY_ABSTRACTION_H

#include "../../../Data/data.h"
#include "../../Entities/Client/client.h"
#include "../IRepository.h"

class ClientRepository
	: public IRepository<Client>
{
private:
	IBankSystemDbProvider* _dbProvider = nullptr;
public:
	ClientRepository() = delete;
	ClientRepository(BankSystemDbProvider* dbProvider);

	int add(const Client* class_) override;
	Client* get(int id) override;
	bool update(const Client* class_) override;
	bool deleteClass(int id) override;
};

#endif
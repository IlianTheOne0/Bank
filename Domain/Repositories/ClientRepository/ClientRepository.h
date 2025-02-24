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

	int add(const Client* class_) override;
	Client* get(size_t id) override;
	bool update(const Client* class_) override;
	bool deleteClass(size_t id) override;
};

#endif
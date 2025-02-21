#ifndef TEMP_CLIENT_H
#define TEMP_CLIENT_H

#include "../../../Core/Libs/domainConfig.h"

struct Client
{
	int clientId;
	string firstName;
	string lastName;
	string passportNumber;
	string phone;
	string email;
	tm registrationDate;
};

#endif
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "../../../Core/Libs/domainConfig.h"

/*

		TEMPORARY SOLUTION

*/

struct Account
{
	string accountId;
	string clientId;
	string balance;
	string currency;
	string openedDate;
	string closedDate;
	string status;
};

#endif
#ifndef TEMP_CARD_H
#define TEMP_CARD_H

#include "../../../Core/Libs/domainConfig.h"

struct Card
{
	size_t cardId;
	size_t accountId;
	string cardNumber;
	tm expiryDate;
	bool isBlocked;
	tm issueDate;
};

#endif
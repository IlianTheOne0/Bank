#ifndef TEMP_TRANSACTION_H
#define TEMP_TRANSACTION_H

#include "../../../Core/Libs/domainConfig.h"
#include "transactionStatusEnum.h"

struct Transaction
{
	size_t transactionId;
	size_t fromAccountId;
	size_t toAccountId;
	float amount;
	size_t operationType;
	tm transactionDate;
	string description;
	TransactionStatus status;
};

#endif
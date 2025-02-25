#ifndef TEMP_OPERATION_H
#define TEMP_OPERATION_H

#include "../../../Core/Libs/domainConfig.h"

struct Operation
{
	size_t operationId;
	string name;
	bool isIncome;
	bool needsApproval;
};

#endif
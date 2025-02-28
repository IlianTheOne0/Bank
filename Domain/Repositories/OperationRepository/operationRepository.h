#ifndef OPERATION_REPOSITORY_ABSTRACTION_H
#define OPERATION_REPOSITORY_ABSTRACTION_H

#include "../../../Data/data.h"
#include "../../Entities/Operation/operation.h"
#include "../IRepository.h"

class OperationRepository
	: public IRepository<Operation>
{
protected:
	virtual size_t _add(const string& name, const string& isIncomeStr, const string& needsApprovalStr);
	virtual bool _update(size_t& operationId, const string& name, const string& isIncome, const string& needsApproval);
public:
	OperationRepository();

	virtual size_t add(const string& name, const bool& isIncome, const bool& needsApproval);
	size_t add(const Operation* operation) override;
	Operation* get(size_t id) override;
	virtual bool update(size_t& operationId, const string& name, const bool& isIncome, const bool& needsApproval);
	bool update(const Operation* class_) override;
	bool deleteClass(size_t id) override;
};

#endif
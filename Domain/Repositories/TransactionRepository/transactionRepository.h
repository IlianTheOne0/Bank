#ifndef TRANSACTION_REPOSITORY_ABSTRACTION_H
#define TRANSACTION_REPOSITORY_ABSTRACTION_H

#include "../../../Data/data.h"
#include "../../Entities/Transaction/transaction.h"
#include "../IRepository.h"

class TransactionRepository
	: public IRepository<Transaction>
{
protected:
	virtual size_t _add(const size_t& fromAccountId, const size_t& toAccountId, const float& amount, const size_t& operationType, const string& transactionDateStr, const string& description, const string& statusStr);
	virtual bool _update(size_t& transactionId, const size_t& fromAccountId, const size_t& toAccountId, const float& amount, const size_t& operationType, const string& transactionDateStr, const string& description, const string& statusStr);
public:
	TransactionRepository();

	virtual size_t add(const size_t& fromAccountId, const size_t& toAccountId, const float& amount, const size_t& operationType, const tm& transactionDate, const string& description, const TransactionStatus& status);
	size_t add(const Transaction* transaction) override;
	Transaction* get(size_t id) override;
	virtual bool update(size_t& transactionId, const size_t& fromAccountId, const size_t& toAccountId, const float& amount, const size_t& operationType, const tm& transactionDate, const string& description, const TransactionStatus& status);
	bool update(const Transaction* class_) override;
	bool deleteClass(size_t id) override;
};

#endif
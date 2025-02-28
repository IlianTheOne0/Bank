#ifndef CARD_REPOSITORY_ABSTRACTION_H
#define CARD_REPOSITORY_ABSTRACTION_H

#include "../../../Data/data.h"
#include "../../Entities/Card/card.h"
#include "../IRepository.h"

class CardRepository
	: public IRepository<Card>
{
protected:
	virtual size_t _add(size_t& accountId, const string& cardNumber, const string& isBlocked);
	virtual bool _update(const size_t& accountId, const string& expiryDateStr, const string& isBlockedStr);
public:
	CardRepository();

	virtual size_t add(size_t& accountId, const string& cardNumber, const bool& isBlocked);
	size_t add(const Card* account) override;
	Card* get(size_t id) override;
	virtual bool update(const size_t& accountId, const tm& expiryDate, const bool& isBlocked);
	bool update(const Card* class_) override;
	bool deleteClass(size_t id) override;
};

#endif
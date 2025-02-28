#ifndef REPOSITORY_INTERFACE_H
#define REPOSITORY_INTERFACE_H

template<typename TReturn>
class IRepository
{
public:
	virtual size_t add(const TReturn* class_) = 0;
	virtual TReturn* get(size_t id) = 0;
	virtual bool update(const TReturn* class_) = 0;
	virtual bool deleteClass(size_t id) = 0;
};

#endif
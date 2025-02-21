#ifndef REPOSITORY_INTERFACE_H
#define REPOSITORY_INTERFACE_H

template<typename TReturn>
class IRepository
{
public:
	virtual int add(const TReturn* class_) = 0;
	virtual TReturn* get(int id) = 0;
	virtual bool update(const TReturn* class_) = 0;
	virtual bool deleteClass(int id) = 0;
};

#endif
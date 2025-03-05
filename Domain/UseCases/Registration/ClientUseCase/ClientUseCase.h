#ifndef SIGNIN_USECASE_H
#define SIGNIN_USECASE_H

#include "../../../../Core/Libs/domainConfig.h"
#include "../../../../Domain/domain.h"

class ClientUseCase
{
public:
	static string checkPassport(const string& passportNumber);
	static string checkPhoneNumber(const string& phoneNumber);
	static string checkEmail(const string& email);

	static Client* signIn(const string& firstName, const string& lastName, const string& passportNumber, const string& phone, const string& email);
	static Client* logIn(const string& identifier, const string& password);
};

#endif
#ifndef SIGNIN_USECASE_H
#define SIGNIN_USECASE_H

#include "../../../Core/Libs/dataConfig.h"

class SignInUseCase
{
public:
	static string checkPassport(const string& passportNumber);
	static string checkPhoneNumber(const string& phoneNumber);
	static string checkEmail(const string& email);
};

#endif
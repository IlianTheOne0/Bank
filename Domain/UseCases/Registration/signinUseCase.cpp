#include "signinUseCase.h"
#include "../../../Presentation/View/Items/LanguageSelection/languagesEnum.h"

string SignInUseCase::checkPassport(const string& passportNumber)
{
	INFO("SignInUseCase -> static method checkPassport: called;");

	ClientRepository clientRepo;
	
	if (passportNumber.size() != 7) { return MESSAGE_SIGNIN_PASSPORT_LENGTH; }
	if (!clientRepo.checkByPassport(passportNumber)) { return MESSAGE_SINGIN_PASSPORT_EXIST; }

	return "true";
}

string SignInUseCase::checkPhoneNumber(const string& phoneNumber)
{
	INFO("SignInUseCase -> static method checkPhoneNumber: called;");

	ClientRepository clientRepo;

	if (
		phoneNumber[0] != '+' &&
		phoneNumber[1] != '3' &&
		phoneNumber[2] != '8' &&
		phoneNumber[3] != '0'
		)
	{ return MESSAGE_SIGNIN_PHONE_NOTWITH; }
	if (phoneNumber.size() != 13) { return MESSAGE_SIGNIN_PHONE_LENGTH; }
	//for (char ch : phoneNumber) { if (ch < '0' || ch > '9') { return MESSAGE_SIGNIN_PHONE_NOTNUMERIC; } }
	char ch = phoneNumber[2];
	for (unsigned short i = 2; i < 12; i++) { ch = phoneNumber[i]; if (ch < '0' || ch > '9') { return MESSAGE_SIGNIN_PHONE_NOTNUMERIC; } }
	if (!clientRepo.checkByPhone(phoneNumber)) { return MESSAGE_SINGIN_PHONE_EXIST; }

	return "true";
}

string SignInUseCase::checkEmail(const string& email)
{
	INFO("SignInUseCase -> static method checkEmail: called;");

	bool exists{ false };

	for (char ch : email) { if (ch == '@') { exists = true; break; } }

	return (exists ? "true" : MESSAGE_SIGNIN_EMAIL_INVALID);
}

Client* SignInUseCase::signIn(const string& firstName, const string& lastName, const string& passportNumber, const string& phone, const string& email)
{
	INFO("SignInUseCase -> static method signIn: called;");

	ClientRepository clientRepo;

	size_t clientId = clientRepo.add(firstName, lastName, passportNumber, phone, email);
	Client* client = clientRepo.get(clientId);
	return client;
}
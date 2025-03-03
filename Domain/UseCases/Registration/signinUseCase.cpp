#include "signinUseCase.h"
#include "../../../Domain/Repositories/ClientRepository/ClientRepository.h"
#include "../../../Presentation/View/Items/LanguageSelection/languagesEnum.h"

string checkPassport(const string& passportNumber)
{
	ClientRepository clientRepo;

	if (passportNumber.size() != 20) { return MESSAGE_SIGNIN_PASSPORT_LENGTH; }
	if (!clientRepo.checkByPassport(passportNumber)) { return MESSAGE_SINGIN_PASSPORT_EXIST; }

	return "true";
}

string SignInUseCase::checkPhoneNumber(const string& phoneNumber)
{
	ClientRepository clientRepo;

	if (
		phoneNumber[0] != '+' &&
		phoneNumber[1] != '3' &&
		phoneNumber[2] != '8' &&
		phoneNumber[3] != '0'
		)
	{ return MESSAGE_SIGNIN_PHONE_NOTWITH; }
	if (phoneNumber.size() != 15) { return MESSAGE_SIGNIN_PHONE_LENGTH; }
	for (char ch : phoneNumber) { if (ch < 0 || ch > 9) { return MESSAGE_SIGNIN_PHONE_NOTNUMERIC; } }
	if (!clientRepo.checkByPhone(phoneNumber)) { return MESSAGE_SINGIN_PHONE_EXIST; }

	return "true";
}

string checkEmail(const string& email)
{
	bool exists{ false };

	for (char ch : email) { if (ch == '@') { exists = true; break; } }

	return (exists ? "true" : MESSAGE_SIGNIN_EMAIL_INVALID);
}
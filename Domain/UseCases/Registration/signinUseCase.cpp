#include "SignInUseCase.h"
#include "../../Repositories/ClientRepository/ClientRepository.h"

#include "../../../Core/Libs/domainConfig.h"
#include "../../../Presentation/presentation.h"

string SignInUseCase::checkPassport(const string& passportNumber)
{
    INFO("SignInUseCase -> static method checkPassport: called;");

    if (passportNumber.length() == 7) { return "true"; }
    else { return MESSAGE_SIGNIN_PASSPORT_LENGTH; }
    
    ClientRepository clientRepo;
	if (clientRepo.checkByPassport(passportNumber)) { return "true"; }
	else { return MESSAGE_SINGIN_PASSPORT_EXIST; }
}

string SignInUseCase::checkPhoneNumber(const string& phoneNumber)
{
    INFO("SignInUseCase -> static method checkPhoneNumber: called;");

    if (
        phoneNumber[0] != '+' &&
        phoneNumber[1] != '3' &&
        phoneNumber[2] != '8' &&
        phoneNumber[3] != '0'
        )
    { return MESSAGE_SIGNIN_PHONE_NOTWITH; }
    if (phoneNumber.size() != 13) { return MESSAGE_SIGNIN_PHONE_LENGTH; }
    char ch;
    for (unsigned short i = 2; i < 12; i++) { ch = phoneNumber[i]; if (ch < '0' || ch > '9') { return MESSAGE_SIGNIN_PHONE_NOTNUMERIC; } }
    
    ClientRepository clientRepo;
    if (!clientRepo.checkByPhone(phoneNumber)) { return MESSAGE_SINGIN_PHONE_EXIST; }

    return "true";
}

string SignInUseCase::checkEmail(const string& email) {
    INFO("SignInUseCase -> static method checkEmail: called;");

    size_t atPos = email.find('@');
    size_t dotPos = email.find('.', atPos);

    if (atPos != string::npos && dotPos != string::npos && dotPos > atPos) { return "true"; }
    else { return MESSAGE_SIGNIN_EMAIL_INVALID; }

    ClientRepository clientRepo;
    if (!clientRepo.checkByEmail(email)) { return MESSAGE_SIGNIN_EMAIL_EXIST; }
}

Client* SignInUseCase::signIn(const string& firstName, const string& lastName, const string& passportNumber, const string& phone, const string& email) {
    ClientRepository clientRepo;

    if (checkPassport(passportNumber) == "true" &&
        checkPhoneNumber(phone) == "true" &&
        checkEmail(email) == "true") {

        size_t clientId = clientRepo.add(firstName, lastName, passportNumber, phone, email);
        Client* client = clientRepo.get(clientId);
        return client;
    }
    else { return nullptr; }
}

Client* SignInUseCase::login(const string& identifier, const string& password) {
    //BankUseCase bankUseCase;

    return nullptr;
}
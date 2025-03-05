#include "ClientUseCase.h"
#include "../AccountUseCase/accountUseCase.h"
#include "../../../Repositories/ClientRepository/ClientRepository.h"

#include "../../../../Core/Libs/domainConfig.h"
#include "../../../../Presentation/presentation.h"

string ClientUseCase::checkPassport(const string& passportNumber)
{
    INFO("SignInUseCase -> static method checkPassport: called;");

    if (passportNumber.length() == 7) { return "true"; }
    else { return MESSAGE_SIGNIN_PASSPORT_LENGTH; }
    
    ClientRepository clientRepo;
	if (clientRepo.checkByPassport(passportNumber)) { return "true"; }
	else { return MESSAGE_SINGIN_PASSPORT_EXIST; }
}

string ClientUseCase::checkPhoneNumber(const string& phoneNumber)
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

string ClientUseCase::checkEmail(const string& email)
{
    INFO("SignInUseCase -> static method checkEmail: called;");

    size_t atPos = email.find('@');
    size_t dotPos = email.find('.', atPos);

    if (atPos == string::npos || dotPos == string::npos || dotPos < atPos + 2 || dotPos == email.length() - 1 || email.find("..") != string::npos) { return MESSAGE_SIGNIN_EMAIL_INVALID; }


    ClientRepository clientRepo;
    if (!clientRepo.checkByEmail(email)) { return MESSAGE_SIGNIN_EMAIL_EXIST; }
    return "true";
}

Client* ClientUseCase::signIn(const string& firstName, const string& lastName, const string& passportNumber, const string& phone, const string& email)
{
    ClientRepository clientRepo;

    if (checkPassport(passportNumber) == "true" &&
        checkPhoneNumber(phone) == "true" &&
        checkEmail(email) == "true")
    {

        size_t clientId = clientRepo.add(firstName, lastName, passportNumber, phone, email);
        Client* client = clientRepo.get(clientId);
        return client;
    }
    else { return nullptr; }
}

Client* ClientUseCase::logIn(const string& identifier, const string& password)
{
    ClientRepository clientRepo;
    AccountRepository accountRepo;
    Client* client = nullptr;

    if (checkEmail(identifier) == "true") { client = clientRepo.get(clientRepo.getClientByEmail(identifier)); }
    else { client = clientRepo.get(clientRepo.getClientByPhone(identifier)); }
    
    Account* account = accountRepo.get(client->getClientId());
    if (AccountUseCase::encryptPassword(password, accountRepo.getSaltByClientId(client->getClientId())).first == account->getPassword()) { return client; }
    else { return nullptr; }
}
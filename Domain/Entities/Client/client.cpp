#include "client.h"

Client::Client(const size_t& clientId, const string& firstName, const string& lastName, const string& passportNumber, const string& phone, const string& email, const tm& registrationDate)
	: _clientId(clientId), _firstName(firstName), _lastName(lastName), _passportNumber(passportNumber), _phone(phone), _email(email)
{ CREATE_INFO("Client <- constructor: called"); _registrationDate = registrationDate; }
Client::Client(const Client&& other) noexcept
	: _clientId(move(other._clientId)),
	_firstName(move(other._firstName)),
	_lastName(move(other._lastName)),
	_passportNumber(move(other._passportNumber)),
	_phone(move(other._phone)),
	_email(move(other._email)),
	_registrationDate(move(other._registrationDate))
{ CREATE_INFO("Client <- displacement constructor: called"); }
Client::~Client() { CREATE_INFO("Client <- destructor: called"); }

const size_t& Client::getClientId() const { INFO("Client -> method getClientId: called;"); return _clientId; }
const string& Client::getFirstName() const { INFO("Client -> method getFirstName: called;"); return _firstName; }
const string& Client::getLastName() const { INFO("Client -> method getLastName: called;"); return _lastName; }
const string& Client::getPassportNumber() const { INFO("Client -> method getPassportNumber: called;"); return _passportNumber; }
const string& Client::getPhone() const { INFO("Client -> method getPhone: called;"); return _phone; }
const string& Client::getEmail() const { INFO("Client -> method getEmail: called;"); return _email; }
const tm& Client::getRegistrationDate() const { INFO("Client -> method getRegistrationDate: called;"); return _registrationDate; }

void Client::setClientId(const size_t& value) { INFO("Client -> method setClientId: called;"); _clientId = value; }
void Client::setFirstName(const string& value) { INFO("Client -> method setFirstName: called;"); _firstName = value; }
void Client::setLastName(const string& value) { INFO("Client -> method setLastName: called;"); _lastName = value; }
void Client::setPassportNumber(const string& value) { INFO("Client -> method setPassportNumber: called;"); _passportNumber = value; }
void Client::setPhone(const string& value) { INFO("Client -> method setPhone: called;"); _phone = value; }
void Client::setEmail(const string& value) { INFO("Client -> method setEmail: called;"); _email = value; }
void Client::setRegistrationDate(const tm& value) { INFO("Client -> method setRegistrationDate: called;"); _registrationDate = value; }
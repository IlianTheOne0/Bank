#ifndef CLIENT_H
#define CLIENT_H

#include "../../../Core/Libs/domainConfig.h"

class Client
{
private:
	size_t _clientId;
	string _firstName;
	string _lastName;
	string _passportNumber;
	string _phone;
	string _email;
	tm _registrationDate;
public:
	Client() = default;
	Client(const size_t& clientId, const string& firstName, const string& lastName, const string& passportNumber, const string& phone, const string& email, const tm& registrationDate);
	Client(const Client&& other) noexcept;
	~Client();

	/*Client(const string& firstName, const string& lastName,
			   const string& passportNumber, const string& phone, 
			   const string& email) 
			: _firstName(firstName), _lastName(lastName),
			  _passportNumber(passportNumber), _phone(phone), _email(email)
	{
		// Генерируем _clientId (например, случайно или по времени)
		_clientId = static_cast<size_t>(time(nullptr)); // Простой пример, замени на реальный генератор
		// Устанавливаем текущую дату регистрации
		time_t now = time(nullptr);
		_registrationDate = *localtime(&now);
	}*/
	
	const size_t& getClientId() const;
	const string& getFirstName() const;
	const string& getLastName() const;
	const string& getPassportNumber() const;
	const string& getPhone() const;
	const string& getEmail() const;
	const tm& getRegistrationDate() const;

	void setClientId(const size_t& value);
	void setFirstName(const string& value);
	void setLastName(const string& value);
	void setPassportNumber(const string& value);
	void setPhone(const string& value);
	void setEmail(const string& value);
	void setRegistrationDate(const tm& value);
};

#endif
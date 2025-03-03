#ifndef LANGUAGES_ENUM_H
#define LANGUAGES_ENUM_H

enum Languages
{
	English,
	Ukrainian
};

#define MESSAGE_SELECT "select please"
#define MESSAGE_INSERTDATA "insert data please"
#define MESSAGE_OPTION "option"
#define MESSAGE_INVALIDOPTION "invalid option"

#define MESSAGE_LANGUAGESELECTION "select the language"
#define MESSAGE_LANGUAGESELECTION_ACTION "languages list"

#define MESSAGE_REGISTRATION "registration and login manu"
#define MESSAGE_REGISTRATIONACTION "log in and sign in (list to-do)"

#define MESSAGE_SIGNIN "signin"
#define MESSAGE_SIGNIN_NAME "signin name"
#define MESSAGE_SIGNIN_LASTNAME "signin last name"
#define MESSAGE_SIGNIN_PASSPORTNUMBER "signin passport number"
#define MESSAGE_SIGNIN_PASSPORT_LENGTH "signin passport length error"
#define MESSAGE_SINGIN_PASSPORT_EXIST "signin passport already exist"
#define MESSAGE_SIGNIN_PHONE "signin phone number"
#define MESSAGE_SIGNIN_PHONE_NOTWITH "signin starting not with +380"
#define MESSAGE_SIGNIN_PHONE_LENGTH "signin phone length error"
#define MESSAGE_SIGNIN_PHONE_NOTNUMERIC "signin not numeric"
#define MESSAGE_SINGIN_PHONE_EXIST "signin phone already exist"
#define MESSAGE_SIGNIN_EMAIL "signin email"
#define MESSAGE_SIGNIN_EMAIL_INVALID "signin email invalid"

#define MESSAGE_LOGIN "login"

// ENGLISH
#define MESSAGE_ENGLISH_DEFAULT_SELECT "Select please"
#define MESSAGE_ENGLISH_DEFAULT_INSERTDATA "Insert data please"
#define MESSAGE_ENGLISH_DEFAULT_OPTION "Option: "
#define MESSAGE_ENGLISH_DEFAULT_INVALIDOPTION "Invalid option!"

#define MESSAGE_ENGLISH_LANGUAGESELECTION "SELECT THE LANGUAGE"
#define MESSAGE_ENGLISH_LANGUAGESELECTION_ACTION "1. English\n2. Ukrainian"

#define MESSAGE_ENGLISH_DEFAULT_REGISTRATION_ACTION "1. Sign in\n2. Log in\n3. Exit the program"

#define MESSAGE_ENGLISH_SIGNIN "SIGNIN"
#define MESSAGE_ENGLISH_SIGNIN_NAME "Your name: "
#define MESSAGE_ENGLISH_SIGNIN_LASTNAME "Your last name: "
#define MESSAGE_ENGLISH_SIGNIN_PASSPORTNUMBER "Your passport number: "
#define MESSAGE_ENGLISH_SIGNIN_PASSPORT_LENGTH "Insufficient number of characters (must be 20)!"
#define MESSAGE_ENGLISH_SINGIN_PASSPORT_EXIST "This passport number already exists in the database!"
#define MESSAGE_ENGLISH_SIGNIN_PHONE "Your phone number: "
#define MESSAGE_ENGLISH_SIGNIN_PHONE_NOTWITH "The phone number does not start with \"+380\"!"
#define MESSAGE_ENGLISH_SIGNIN_PHONE_LENGTH "Insufficient number of characters (must be 15)!"
#define MESSAGE_ENGLISH_SIGNIN_PHONE_NOTNUMERIC "The phone number must consist of digits!"
#define MESSAGE_ENGLISH_SINGIN_PHONE_EXIST "This number already exists in the database!"
#define MESSAGE_ENGLISH_SIGNIN_EMAIL "Your email: "
#define MESSAGE_ENGLISH_SIGNIN_EMAIL_INVALID "The mail is incorrect!"

#define MESSAGE_ENGLISH_LOGIN "LOGIN"

// UKRAINIAN
#define MESSAGE_UKRAINIAN_DEFAULT_SELECT "Будь ласка, оберiть"
#define MESSAGE_UKRAINIAN_DEFAULT_INSERTDATA "Будь ласка, введiть данi"
#define MESSAGE_UKRAINIAN_DEFAULT_OPTION "Вибiр: "
#define MESSAGE_UKRAINIAN_DEFAULT_INVALIDOPTION "Не правильний вибiр!"

#define MESSAGE_UKRAINIAN_LANGUAGESELECTION "ОБЕРIТЬ МОВУ"
#define MESSAGE_UKRAINIAN_LANGUAGESELECTION_ACTION "1. Ангiйська\n2. Українська"

#define MESSAGE_UKRAINIAN_DEFAULT_REGISTRATION_ACTION "1. Зареєструватися\n2. Увiйти\n3. Вийти з програми"

#define MESSAGE_UKRAINIAN_SIGNIN "ЗАРЕЄСТРУВАТИСЯ"
#define MESSAGE_UKRAINIAN_SIGNIN_NAME "Ваше iм'я: "
#define MESSAGE_UKRAINIAN_SIGNIN_LASTNAME "Ваше прiзвище: "
#define MESSAGE_UKRAINIAN_SIGNIN_PASSPORTNUMBER "Номер Вашого паспорта: "
#define MESSAGE_UKRAINIAN_SIGNIN_PASSPORT_LENGTH "Неправильна довжина номера (повинно бути 20)!"
#define MESSAGE_UKRAINIAN_SINGIN_PASSPORT_EXIST "Цей номер паспорта вже iснує в базi даних!"
#define MESSAGE_UKRAINIAN_SIGNIN_PHONE "Ваш номер телефона: "
#define MESSAGE_UKRAINIAN_SIGNIN_PHONE_NOTWITH "Ваш номер телефона починається не з \"+380\"!"
#define MESSAGE_UKRAINIAN_SIGNIN_PHONE_LENGTH "Неправильна довжина номера (повинно бути 15)!"
#define MESSAGE_UKRAINIAN_SINGIN_PHONE_EXIST "Цей номер вже iснує в базi даних!"
#define MESSAGE_UKRAINIAN_SIGNIN_PHONE_NOTNUMERIC "Номер повинен складатися із цифр!"
#define MESSAGE_UKRAINIAN_SIGNIN_EMAIL "Ваша пошта: "
#define MESSAGE_UKRAINIAN_SIGNIN_EMAIL_INVALID "Пошта не правильна!"

#define MESSAGE_UKRAINIAN_LOGIN "УВIЙТИ"

// ERRORS
#define LANGUAGE_ERROR "Language error!"
#define TRANSLATION_ERROR "Translation error!"

#endif
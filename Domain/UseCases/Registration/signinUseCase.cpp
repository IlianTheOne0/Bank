#include "SignInUseCase.h"
#include "../BankUseCase/BankUseCase.h"
#include <string>

// Статический метод для проверки номера паспорта
std::string SignInUseCase::checkPassport(const std::string& passportNumber) {
    // Пример: валидный, если длина равна 9 символам
    if (passportNumber.length() == 9) {
        return "true";
    } else {
        return "Неверный номер паспорта";
    }
}

// Статический метод для проверки номера телефона
std::string SignInUseCase::checkPhoneNumber(const std::string& phoneNumber) {
    // Пример: валидный, если начинается с '+' и длиннее 1 символа
    if (!phoneNumber.empty() && phoneNumber[0] == '+' && phoneNumber.length() > 1) {
        return "true";
    } else {
        return "Неверный номер телефона";
    }
}

// Статический метод для проверки email
std::string SignInUseCase::checkEmail(const std::string& email) {
    // Пример: валидный, если содержит '@', за которым следует '.'
    size_t atPos = email.find('@');
    size_t dotPos = email.find('.', atPos);
    if (atPos != std::string::npos && dotPos != std::string::npos && dotPos > atPos) {
        return "true";
    } else {
        return "Неверный email";
    }
}

// Статический метод для регистрации клиента
Client* SignInUseCase::signIn(const std::string& firstName, const std::string& lastName, 
                              const std::string& passportNumber, const std::string& phone, 
                              const std::string& email) {
    // Проверяем все входные данные перед созданием клиента
    if (checkPassport(passportNumber) == "true" &&
        checkPhoneNumber(phone) == "true" &&
        checkEmail(email) == "true") {
        // Предполагаем, что у Client есть конструктор, соответствующий этим параметрам
        return new Client(firstName, lastName, passportNumber, phone, email);
    } else {
        return nullptr;
    }
}

// Нестатический метод для логина (уже реализован)
Client* SignInUseCase::login(const std::string& identifier, const std::string& password) {
    BankUseCase bankUseCase;

    return nullptr; // Заглушка; замени на реальную реализацию, если нужно
}
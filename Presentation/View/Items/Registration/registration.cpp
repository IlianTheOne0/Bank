#include "../../view.h"
#include "../../../../Domain/domain.h"

unsigned short View::Registration_()
{
	INFO("View -> method Registration: called;");

	do
	{
		clear;
		printWithColor(MESSAGE_REGISTRATION, Colors::LightWhite);
		printWithColor(MESSAGE_SELECT, Colors::Yellow); cout << endl;
		
		print(MESSAGE_REGISTRATIONACTION); cout << endl;

		unsigned short option;
		printWithColor(MESSAGE_OPTION, Colors::LightYellow, false);
		cin >> option;

		if (option < 1 || option > 3) { INFO("View -> method Registration -> loop: invalid option!;"); printWithColor(MESSAGE_INVALIDOPTION, Colors::LightRed, true, true); continue; }
		switch (option)
		{
			case 1: { INFO("View -> method Registration -> selected option: sign in;"); return 1; } break;
			case 2: { INFO("View -> method Registration -> selected option: log in;"); return 2; } break;
			case 3: { INFO("View -> method Registration -> selected option: exit;"); return 0; } break;
		}
		break;
	} while (true);

	return 0;
}

Client* View::Signin_()
{
	INFO("View -> method Sigin: called;");
	
	string firstName;
	string lastName;
	string passportNumber;
	string phone;
	string email;

	auto printStartMessage = []()
		{
			clear;
			printWithColor(MESSAGE_SIGNIN, Colors::LightWhite);
			printWithColor(MESSAGE_INSERTDATA, Colors::Yellow); cout << endl;
		};

	do { printStartMessage(); print(MESSAGE_SIGNIN_NAME, false); cin >> firstName; if (firstName.empty()) { INFO("View -> method Signin -> loop (name): invalid option!;"); printWithColor(MESSAGE_INVALIDOPTION, Colors::LightRed, true, true); continue; } break; } while (true);
	do { printStartMessage(); print(MESSAGE_SIGNIN_LASTNAME, false); cin >> lastName; if (lastName.empty()) { INFO("View -> method Signin -> loop (last name): invalid option!;"); printWithColor(MESSAGE_INVALIDOPTION, Colors::LightRed, true, true); continue; } break; } while (true);
	do
	{
		printStartMessage();

		print(MESSAGE_SIGNIN_PASSPORTNUMBER, false);
		cin >> passportNumber;

		if (passportNumber.empty())
		{
			INFO("View -> method Signin -> loop (phone): invalid option!;");
			printWithColor(MESSAGE_INVALIDOPTION, Colors::LightRed, true, true);
			continue;
		}
		string checkPassport = ClientUseCase::checkPassport(passportNumber);
		if (checkPassport != "true")
		{
			INFO("View -> method Signin -> loop (phone): invalid option!;");
			printWithColor(checkPassport, Colors::LightRed, true, true);
			continue;
		}
		break;
	} while (true);
	do
	{
		printStartMessage();
		print(MESSAGE_SIGNIN_PHONE, false);
		cin >> phone;
		
		if (phone.empty())
		{
			INFO("View -> method Signin -> loop (phone): invalid option!;");
			printWithColor(MESSAGE_INVALIDOPTION, Colors::LightRed, true, true);
			continue;
		}
		string checkPhone = ClientUseCase::checkPhoneNumber(phone);
		if (checkPhone != "true")
		{
			INFO("View -> method Signin -> loop (phone): invalid option!;");
			printWithColor(checkPhone, Colors::LightRed, true, true);
			continue;
		}
		break;
	} while (true);
	do
	{
		printStartMessage();

		print(MESSAGE_SIGNIN_EMAIL, false);
		cin >> email;

		if (email.empty())
		{
			INFO("View -> method Signin -> loop (phone): invalid option!;");
			printWithColor(MESSAGE_INVALIDOPTION, Colors::LightRed, true, true);
			continue;
		}
		string checkEmail = ClientUseCase::checkEmail(email);
		if (checkEmail != "true")
		{
			INFO("View -> method Signin -> loop (phone): invalid option!;");
			printWithColor(checkEmail, Colors::LightRed, true, true);
			continue;
		}
		break;
	} while (true);

	clear;
	return ClientUseCase::signIn(firstName, lastName, passportNumber, phone, email);
}

Client* View::Login_()
{
    INFO("View -> method Login: called;");

    string identifier;
    string password;

	ClientUseCase signInUseCase;
	
    auto printStartMessage = []()
    {
        clear;
        printWithColor(MESSAGE_LOGIN, Colors::LightWhite);
        printWithColor(MESSAGE_INSERTDATA, Colors::Yellow); cout << endl;
    };
	
    do
    {
        printStartMessage();
        print(MESSAGE_LOGIN_LOGIN, false);
        cin >> identifier;
        if (identifier.empty())
        {
            INFO("View -> method Login -> loop (identifier): invalid option!;");
            printWithColor(MESSAGE_INVALIDOPTION, Colors::LightRed, true, true);
            continue;
        }

        if (identifier.find('@') != string::npos)
        {
            string checkEmail = ClientUseCase::checkEmail(identifier);
            if (checkEmail != "true")
            {
                INFO("View -> method Login -> loop (email): invalid option!;");
                printWithColor(checkEmail, Colors::LightRed, true, true);
                continue;
            }
        }
        else
        {
            string checkPhone = ClientUseCase::checkPhoneNumber(identifier);
            if (checkPhone != "true")
            {
                INFO("View -> method Login -> loop (phone): invalid option!;");
                printWithColor(checkPhone, Colors::LightRed, true, true);
                continue;
            }
        }
        break;
    } while (true);

	Client* client = nullptr;
	do
	{
		do
		{
			printStartMessage();
			print(MESSAGE_LOGIN_PASSWORD, false);
			cin >> password;
			if (password.empty())
			{
				INFO("View -> method Login -> loop (password): invalid option!;");
				printWithColor(MESSAGE_INVALIDOPTION, Colors::LightRed, true, true);
				continue;
			}

			break;
		} while (true);

		client = signInUseCase.logIn(identifier, password);
		if (client == nullptr)
		{
			INFO("View -> method Login -> loop (password): invalid option!;");
			printWithColor(MESSAGE_INVALIDOPTION, Colors::LightRed, true, true);
			continue;
		}
		break;
	} while (true);

    return client;
}
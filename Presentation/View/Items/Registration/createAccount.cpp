#include "../../view.h"
#include "../../../../Domain/domain.h"

Account* View::createAccount_(const Client* client)
{
	INFO("View -> method createAccount: called;");

	size_t clientId = client->getClientId();
	string currency = "UAH";
	string password;

	auto printStartMessage = []()
		{
			clear;
			printWithColor(MESSAGE_CREATEACCOUNT, Colors::LightWhite);
			printWithColor(MESSAGE_INSERTDATA, Colors::Yellow); cout << endl;
		};

	do { printStartMessage(); print(MESSAGE_CREATEACCOUNT_CURRENCY, false); cin >> currency; if (currency.empty()) { INFO("View -> method createAccount -> loop (currency): invalid option!;"); printWithColor(MESSAGE_INVALIDOPTION, Colors::LightRed, true, true); continue; } break; } while (true);
	do { printStartMessage(); print(MESSAGE_CREATEACCOUNT_PASSWORD, false); cin >> password; if (password.empty()) { INFO("View -> method createAccount -> loop (password): invalid option!;"); printWithColor(MESSAGE_INVALIDOPTION, Colors::LightRed, true, true); continue; } break; } while (true);

	clear;
	
	return CreateAccountUseCase::createAccount(clientId, currency, password);
}
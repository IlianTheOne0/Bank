#include "../view.h"
#include "../../../Domain/domain.h"

unsigned short View::Menu_(Client* client)
{
	AccountRepository accountRepo;

	if (accountRepo.checkByClientId(client->getClientId())) { return 1; }
	cout << "Hello wordl!" << endl;

	printWithColor(MESSAGE_MENU, Colors::LightWhite);
	printWithColor(MESSAGE_SELECT, Colors::Yellow); cout << endl;
}
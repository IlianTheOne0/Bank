#include "../view.h"

void View::startTheProgram()
{
	LanguageSelection_();
	Client* client = nullptr;

	do
	{
		unsigned short registrationResult = Registration_();
		if (registrationResult == 0) { break; }
		switch (registrationResult)
		{
			case 1: { client = Signin_(); } break;
			//case 2: { Login; } break;
		}

		cout << client->getClientId() << endl << client->getPassportNumber() << endl << client->getPhone() << endl;
		//Menu();
		break;
	} while (true);
};
#include "../view.h"

void View::Loop()
{
	LanguageSelection_();

	Client* client = nullptr;
	Account* account = nullptr;
	unsigned short result;
	
	do
	{
		result = Registration_();
		if (result == 0) { break; }
		switch (result)
		{
			case 1: { client = Signin_(); } break;
			case 2: { client = Login_(); } break;
		}
		result = Menu_(client);
		if (result == 0) { break; }
		switch (result)
		{
			case 1: { account = createAccount_(client); Menu_(client); } break;
		}
		
		break;
	} while (true);
};
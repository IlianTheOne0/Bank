#include "../view.h"

void Signin();
void Login();

unsigned short View::Registration_()
{
	INFO("View -> method Registration: called;");

	do
	{
		clear;
		printWithColor_(MESSAGE_DEFAULT_REGISTRATION, Colors::LightWhite);
		printWithColor_(MESSAGE_DEFAULT_DEFAULT_SELECT, Colors::Yellow); cout << endl;
		
		print_(MESSAGE_DEFAULT_REGISTRATION_FORSELECTING); cout << endl;

		unsigned short option;
		printWithColor_(MESSAGE_DEFAULT_DEFAULT_OPTION, Colors::LightYellow, false);
		cin >> option;

		if (option < 0 || option > 3) { INFO("View -> method Registration -> loop: invalid option!;"); printWithColor_(MESSAGE_DEFAULT_DEFAULT_INVALIDOPTION, Colors::LightRed, true, true); continue; }
		switch (option)
		{
			case 1: { INFO("View -> method Registration -> selected option: sign in;");  Signin(); } break;
			case 2: { INFO("View -> method Registration -> selected option: log in;"); Login(); } break;
			case 3: { INFO("View -> method Registration -> selected option: exit;"); return 0; } break;
		}
		break;
	} while (true);

	return 0;
}

void Signin()
{
	INFO("method Sigin: called;");

	do
	{
		pause;
		break;
	} while (true);
}

void Login()
{
	INFO("method Login: called;");

	do
	{
		pause;
		break;
	} while (true);
}
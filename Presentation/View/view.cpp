#include "view.h"

Languages selectedLanguage;

void clear_() { if (!Logger::getState()) { system("cls"); } }
void pause_() { system("pause"); }

void print(const string& message, const bool& isEnd, const bool& isPause)
{
	setlocale(LC_ALL, "ukrainian");
	auto printMessage = [isEnd, isPause](string message) { cout << message; if (isEnd) { cout << endl; } if (isPause) { pause; } };
	auto printMessageWithColor = [isEnd, isPause](const string& message, const Colors& color)
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


			SetConsoleTextAttribute(hConsole, color);
			cout << message;
			SetConsoleTextAttribute(hConsole, Colors::DefaultColor);
			if (isEnd) { cout << endl; } if (isPause) { pause; }
		};

	switch (selectedLanguage)
	{
		case Languages::English:
		{
			if (message == MESSAGE_SELECT) { printMessage(MESSAGE_ENGLISH_DEFAULT_SELECT); }
			else if (message == MESSAGE_OPTION) { printMessage(MESSAGE_ENGLISH_DEFAULT_OPTION); }
			else if (message == MESSAGE_INSERTDATA) { printMessage(MESSAGE_ENGLISH_DEFAULT_INSERTDATA); }
			else if (message == MESSAGE_INVALIDOPTION) { printMessage(MESSAGE_ENGLISH_DEFAULT_INVALIDOPTION); }

			else if (message == MESSAGE_LANGUAGESELECTION) { printMessage(MESSAGE_ENGLISH_LANGUAGESELECTION); }
			else if (message == MESSAGE_LANGUAGESELECTION_ACTION) { printMessage(MESSAGE_ENGLISH_LANGUAGESELECTION_ACTION); }

			else if (message == MESSAGE_REGISTRATION) { printMessage(string(MESSAGE_ENGLISH_SIGNIN) + " / " + MESSAGE_ENGLISH_LOGIN); }
			else if (message == MESSAGE_REGISTRATIONACTION) { printMessage(MESSAGE_ENGLISH_DEFAULT_REGISTRATION_ACTION); }

			else if (message == MESSAGE_SIGNIN) { printMessage(MESSAGE_ENGLISH_SIGNIN); }
			else if (message == MESSAGE_SIGNIN_NAME) { printMessage(MESSAGE_ENGLISH_SIGNIN_NAME); }
			else if (message == MESSAGE_SIGNIN_LASTNAME) { printMessage(MESSAGE_ENGLISH_SIGNIN_LASTNAME); }
			else if (message == MESSAGE_SIGNIN_PASSPORTNUMBER) { printMessage(MESSAGE_ENGLISH_SIGNIN_PASSPORTNUMBER); }
			else if (message == MESSAGE_SIGNIN_PHONE) { printMessage(MESSAGE_ENGLISH_SIGNIN_PHONE); }
			else if (message == MESSAGE_SIGNIN_EMAIL) { printMessage(MESSAGE_ENGLISH_SIGNIN_EMAIL); }

			else if (message == MESSAGE_LOGIN) { printMessage(MESSAGE_ENGLISH_LOGIN); }
			else { printMessageWithColor("Error: " + string(TRANSLATION_ERROR), Colors::LightRed); }
		} break;
		
		case Languages::Ukrainian:
		{
			if (message == MESSAGE_SELECT) { printMessage(MESSAGE_UKRAINIAN_DEFAULT_SELECT); }
			else if (message == MESSAGE_OPTION) { printMessage(MESSAGE_UKRAINIAN_DEFAULT_OPTION); }
			else if (message == MESSAGE_INSERTDATA) { printMessage(MESSAGE_UKRAINIAN_DEFAULT_INSERTDATA); }
			else if (message == MESSAGE_INVALIDOPTION) { printMessage(MESSAGE_UKRAINIAN_DEFAULT_INVALIDOPTION); }

			else if (message == MESSAGE_LANGUAGESELECTION) { printMessage(MESSAGE_UKRAINIAN_LANGUAGESELECTION); }
			else if (message == MESSAGE_LANGUAGESELECTION_ACTION) { printMessage(MESSAGE_UKRAINIAN_LANGUAGESELECTION_ACTION); }

			else if (message == MESSAGE_REGISTRATION) { printMessage(string(MESSAGE_UKRAINIAN_SIGNIN) + " / " + MESSAGE_UKRAINIAN_LOGIN); }
			else if (message == MESSAGE_REGISTRATIONACTION) { printMessage(MESSAGE_UKRAINIAN_DEFAULT_REGISTRATION_ACTION); }

			else if (message == MESSAGE_SIGNIN) { printMessage(MESSAGE_UKRAINIAN_SIGNIN); }
			else if (message == MESSAGE_SIGNIN_NAME) { printMessage(MESSAGE_UKRAINIAN_SIGNIN_NAME); }
			else if (message == MESSAGE_SIGNIN_LASTNAME) { printMessage(MESSAGE_UKRAINIAN_SIGNIN_LASTNAME); }
			else if (message == MESSAGE_SIGNIN_PASSPORTNUMBER) { printMessage(MESSAGE_UKRAINIAN_SIGNIN_PASSPORTNUMBER); }
			else if (message == MESSAGE_SIGNIN_PHONE) { printMessage(MESSAGE_UKRAINIAN_SIGNIN_PHONE); }
			else if (message == MESSAGE_SIGNIN_EMAIL) { printMessage(MESSAGE_UKRAINIAN_SIGNIN_EMAIL); }

			else if (message == MESSAGE_LOGIN) { printMessage(MESSAGE_UKRAINIAN_LOGIN); }
			else { printMessageWithColor("Error: " + string(TRANSLATION_ERROR), Colors::LightRed); }
		} break;
		
		default: { printMessageWithColor("Error: " + string(LANGUAGE_ERROR), Colors::LightRed); }
	}
}

void printWithColor(const string& message, const Colors& color, const bool& isEnd, const bool& isPause)
{

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, color);
	print(message, isEnd, isPause);
	SetConsoleTextAttribute(hConsole, Colors::DefaultColor);
}
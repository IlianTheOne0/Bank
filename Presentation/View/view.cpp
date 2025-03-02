#include "view.h"

Languages selectedLanguage = Languages::Ukrainian;

void View::clear_() { if (!Logger::getState()) { system("cls"); } }
void View::pause_() { system("pause"); }

void View::print_(const string& message, const bool& isEnd, const bool& isPause)
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
			if (message == MESSAGE_DEFAULT_DEFAULT_SELECT) { printMessage(MESSAGE_ENGLISH_DEFAULT_SELECT); }
			else if (message == MESSAGE_DEFAULT_DEFAULT_OPTION) { printMessage(MESSAGE_ENGLISH_DEFAULT_OPTION); }
			else if (message == MESSAGE_DEFAULT_DEFAULT_INVALIDOPTION) { printMessage(MESSAGE_ENGLISH_DEFAULT_INVALIDOPTION); }
			else if (message == MESSAGE_DEFAULT_LANGUAGESELECTION) { printMessage(MESSAGE_ENGLISH_LANGUAGESELECTION); }
			else if (message == MESSAGE_DEFAULT_LANGUAGESELECTION_FORSELECTING) { printMessage(MESSAGE_ENGLISH_LANGUAGESELECTION_FORSELECTING); }
			else if (message == MESSAGE_DEFAULT_REGISTRATION) { printMessage(string(MESSAGE_ENGLISH_REGISTRATION_SIGNIN) + " / " + MESSAGE_ENGLISH_REGISTRATION_LOGIN); }
			else if (message == MESSAGE_DEFAULT_REGISTRATION_FORSELECTING) { printMessage(MESSAGE_ENGLISH_DEFAULT_REGISTRATION_FORSELECTING); }
			else { printMessageWithColor("Error: " + string(TRANSLATION_ERROR), Colors::LightRed); }
		} break;
		
		case Languages::Ukrainian:
		{
			if (message == MESSAGE_DEFAULT_DEFAULT_SELECT) { printMessage(MESSAGE_UKRAINIAN_DEFAULT_SELECT); }
			else if (message == MESSAGE_DEFAULT_DEFAULT_OPTION) { printMessage(MESSAGE_UKRAINIAN_DEFAULT_OPTION); }
			else if (message == MESSAGE_DEFAULT_DEFAULT_INVALIDOPTION) { printMessage(MESSAGE_UKRAINIAN_DEFAULT_INVALIDOPTION); }
			else if (message == MESSAGE_DEFAULT_LANGUAGESELECTION) { printMessage(MESSAGE_UKRAINIAN_LANGUAGESELECTION); }
			else if (message == MESSAGE_DEFAULT_LANGUAGESELECTION_FORSELECTING) { printMessage(MESSAGE_UKRAINIAN_LANGUAGESELECTION_FORSELECTING); }
			else if (message == MESSAGE_DEFAULT_REGISTRATION) { printMessage(string(MESSAGE_UKRAINIAN_REGISTRATION_SIGNIN) + " / " + MESSAGE_UKRAINIAN_REGISTRATION_LOGIN); }
			else if (message == MESSAGE_DEFAULT_REGISTRATION_FORSELECTING) { printMessage(MESSAGE_UKRAINIAN_DEFAULT_REGISTRATION_FORSELECTING); }
			else { printMessageWithColor("Error: " + string(TRANSLATION_ERROR), Colors::LightRed); }
		} break;
		
		default: { printMessageWithColor("Error: " + string(LANGUAGE_ERROR), Colors::LightRed); }
	}
}

void View::printWithColor_(const string& message, const Colors& color, const bool& isEnd, const bool& isPause)
{

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, color);
	print_(message, isEnd, isPause);
	SetConsoleTextAttribute(hConsole, Colors::DefaultColor);
}
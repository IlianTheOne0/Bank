#include "../../view.h"

void View::LanguageSelection_()
{
	INFO("View -> method LanguageSelection: called;");

	do
	{
		clear;
		printWithColor(MESSAGE_LANGUAGESELECTION, Colors::LightWhite); cout << endl;

		print(MESSAGE_LANGUAGESELECTION_ACTION); cout << endl;

		unsigned short option;
		printWithColor(MESSAGE_OPTION, Colors::LightYellow, false);
		cin >> option;

		if (option < 1 || option > 2) { INFO("View -> method LanguageSelection -> loop: invalid option!;"); printWithColor(MESSAGE_INVALIDOPTION, Colors::LightRed, true, true); continue; }
		switch (option)
		{
			case 1: { INFO("View -> method LanguageSelection -> selected language: english;"); selectedLanguage = Languages::English; } break;
			case 2: { INFO("View -> method LanguageSelection -> selected language: ukrainian;"); selectedLanguage = Languages::Ukrainian; } break;
			default: { INFO("View -> method LanguageSelection -> selected language (Default): english;"); selectedLanguage = Languages::English; } break;
		}
		break;
	} while (true);
}
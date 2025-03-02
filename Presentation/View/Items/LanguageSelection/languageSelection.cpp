#include "../../view.h"
#include <limits>

void View::LanguageSelection_()
{
	INFO("View -> method LanguageSelection: called;");

	do
	{
		clear;
		printWithColor_(MESSAGE_DEFAULT_LANGUAGESELECTION, Colors::LightWhite); cout << endl;

		print_(MESSAGE_DEFAULT_LANGUAGESELECTION_FORSELECTING); cout << endl;

		unsigned short option;
		printWithColor_(MESSAGE_DEFAULT_DEFAULT_OPTION, Colors::LightYellow, false);
		cin >> option;

		if (option < 0 || option > 2) { INFO("View -> method LanguageSelection -> loop: invalid option!;"); printWithColor_(MESSAGE_DEFAULT_DEFAULT_INVALIDOPTION, Colors::LightRed, true, true); continue; }
		switch (option)
		{
			case 1: { INFO("View -> method LanguageSelection -> selected language: english;"); selectedLanguage = Languages::English; } break;
			case 2: { INFO("View -> method LanguageSelection -> selected language: ukrainian;"); selectedLanguage = Languages::Ukrainian; } break;
			default: { INFO("View -> method LanguageSelection -> selected language (Default): english;"); selectedLanguage = Languages::English; } break;
		}
		break;
	} while (true);
}
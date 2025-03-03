#include "../view.h"

void View::startTheProgram()
{
	LanguageSelection_();

	do
	{
		unsigned short registrationResult = Registration_();
		if (registrationResult == 0) { break; }
	} while (true);
};
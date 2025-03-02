#ifndef VIEW_H
#define VIEW_H

#include "../../Core/Libs/presentationConfig.h"
#include "Items/LanguageSelection/languagesEnum.h"

extern Languages selectedLanguage;

#define clear View::clear_()
#define pause View::pause_()

class View
{
private:
	static void print_(const string& message, const bool& isEnd = true, const bool& isPause = false);
	static void printWithColor_(const string& message, const Colors& color = Colors::DefaultColor, const bool& isEnd = true, const bool& isPause = false);

	static void LanguageSelection_();
	static unsigned short Registration_();
public:
	static void clear_();
	static void pause_();

	static void startTheProgram();
};

#endif
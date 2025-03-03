#ifndef VIEW_H
#define VIEW_H

#include "../../Core/Libs/presentationConfig.h"
#include "Items/LanguageSelection/languagesEnum.h"
#include "../../Domain/Entities/Client/client.h"

extern Languages selectedLanguage;

#define clear clear_()
#define pause pause_()

void clear_();
void pause_();
void print(const string& message, const bool& isEnd = true, const bool& isPause = false);
void printWithColor(const string& message, const Colors& color = Colors::DefaultColor, const bool& isEnd = true, const bool& isPause = false);

class View
{
private:
	static void LanguageSelection_();
	static unsigned short Registration_();
	static Client* Signin_();
public:

	static void startTheProgram();
};

#endif
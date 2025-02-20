#ifndef TEST_H
#define TEST_H

#include "../../Core/Libs/presentationConfig.h"
#include "../View/view.h"

class Test
{
private:
	static const unsigned short testCounter;
public:
	static void libTest();

	static void startTest()
	{
		switch (testCounter)
		{
			case 0: { libTest(); } break;
			default: { View::Intro(); }
		}
	}
};

#endif
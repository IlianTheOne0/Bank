#ifndef TEST_H
#define TEST_H

#include "../../Core/Libs/presentationConfig.h"
#include "../View/view.h"

class Test
{
private:
	static const unsigned short testCounter;
public:
	static void clientRepositoryTest();
	static void accountRepositoryTest();
	static void cardRepositoryTest();

	static void startTest()
	{
		switch (testCounter)
		{
			case 0: { clientRepositoryTest(); } break;
			case 1: { accountRepositoryTest(); } break;
			case 2: { cardRepositoryTest(); } break;
			default: { View::Intro(); }
		}
	}
};

#endif
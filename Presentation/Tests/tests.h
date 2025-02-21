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
	static void clientRepositoryTest();

	static void startTest()
	{
		switch (testCounter)
		{
			case 0: { libTest(); } break;
			case 1: { clientRepositoryTest(); } break;
			default: { View::Intro(); }
		}
	}
};

#endif
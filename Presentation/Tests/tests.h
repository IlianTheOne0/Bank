#ifndef TEST_H
#define TEST_H

#include "../../Core/Libs/presentationConfig.h"
#include "../View/view.h"

class Test
{
private:
	static const unsigned short testCounter;
public:
	static void libpqxxTest();

	static void startTest()
	{
		switch (testCounter)
		{
			case 0: { libpqxxTest(); } break;
			default: { View::Intro(); }
		}
	}
};

#endif
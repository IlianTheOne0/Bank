#ifndef TEST_H
#define TEST_H

#include "../../Core/Libs/presentationConfig.h"
#include "../View/view.h"

class Test
{
public:
	//static void clientRepositoryTest();
	//static void accountRepositoryTest();
	static void cardRepositoryTest();
	//static void operationRepositoryTest();
	//static void transactionRepositoryTest();
	//static void mainRepositoriesTest();

	static void startTest()
	{
		switch (testCounter)
		{
			//case 0: { clientRepositoryTest(); } break;
			//case 1: { accountRepositoryTest(); } break;
			case 2: { cardRepositoryTest(); } break;
			//case 3: { operationRepositoryTest(); } break;
			//case 4: { transactionRepositoryTest(); } break;
			//case 5: { mainRepositoriesTest(); } break;
			default: { View::Intro(); }
		}
	}
};

#endif
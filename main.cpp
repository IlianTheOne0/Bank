#include "Core/Libs/cfg/cfg.h"
#include "Presentation/presentation.h"

int main()
{
	INFO("The program is started");

	(Logger::getState()) ? Test::startTest() : View::startTheProgram();

	INFO("The program is closed");

	return 0;
}
#include "cfg.h"

namespace ConnectionConfig {
	const string containter = "postgres-local";
	const string user = "sa";
	const string dbname = "postgres";
	const unsigned short queryTime = 5;
}

#include "../../Logger/logger.h"
bool Logger::_isEnabled = true;

#include "../../../Presentation/Tests/tests.h"
const unsigned short Test::testCounter = 5;
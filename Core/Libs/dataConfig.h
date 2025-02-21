#ifndef DATA_CONFIG_H
#define DATA_CONFIG_H

#include "mainLib.h"

#include <soci/soci.h>
#include <soci/postgresql/soci-postgresql.h>
#include <string>

using soci::session;
using soci::postgresql;

using std::string;
using std::to_string;

#define DEFAULT_EMPTY_CONNECTION 0

#endif
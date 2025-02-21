#ifndef DOMAIN_CONFIG_H
#define DOMAIN_CONFIG_H

#include "mainLib.h"

#include <string>
#include <soci/soci.h>
#include <soci/postgresql/soci-postgresql.h>

using std::string;
using std::tm;

using soci::session;
using soci::use;
using soci::into;
using soci::soci_error;

#endif
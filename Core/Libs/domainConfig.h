#ifndef DOMAIN_CONFIG_H
#define DOMAIN_CONFIG_H

#include "mainLib.h"
#include "../../Data/data.h"

#include <string>
#include <exception>
#include <iomanip>
#include <algorithm>

using std::string;
using std::tm;
using std::exception;
using std::istringstream;
using std::get_time;
using std::setw;
using std::setfill;
using std::find_if_not;

static inline string domainTrim(const string& s) {
    auto start = find_if_not(s.begin(), s.end(), [](int ch) { return isspace(ch); });
    auto end = find_if_not(s.rbegin(), s.rend(), [](int ch) { return isspace(ch); }).base();
    return (start < end ? string(start, end) : string());
}

#endif
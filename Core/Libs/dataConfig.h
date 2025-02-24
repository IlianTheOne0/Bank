#ifndef DATA_CONFIG_H
#define DATA_CONFIG_H

#include "mainLib.h"
#include "cfg/cfg.h"

#include <string>
#include <sstream>
#include <array>
#include <exception>
#include <chrono>
#include <thread>
#include <algorithm>

using std::string;
using std::to_string;

using std::ostringstream;
using std::array;
using std::unique_ptr;
using std::chrono::steady_clock;
using std::chrono::seconds;
using std::chrono::milliseconds;
using std::this_thread::sleep_for;
using std::find_if_not;

using std::runtime_error;

#ifdef _WIN32
#define popen _popen
#define pclose _pclose
#endif

static inline string dataTrim(const string& s) {
    auto start = find_if_not(s.begin(), s.end(), [](int ch) { return isspace(ch); });
    auto end = find_if_not(s.rbegin(), s.rend(), [](int ch) { return isspace(ch); }).base();
    return (start < end ? string(start, end) : string());
}

#endif
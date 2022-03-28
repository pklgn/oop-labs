#pragma once
#include <set>
#include <string>
#include <sstream>

std::string Trim(const std::string& str);

std::string RemoveExtraBlanks(const std::string& string);

std::set<std::string> SplitString(const std::string& string, char delimeter);
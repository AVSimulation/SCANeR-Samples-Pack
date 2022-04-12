#pragma once

#include "stk/STK.h"

#include <string>
#include <vector>

namespace stk {

STK_API std::string ToLower(const std::string& str);
STK_API std::string ToUpper(const std::string& str);

STK_API double StringToDouble( const std::string& str );
STK_API std::string DoubleToString( double value );

STK_API std::vector<std::string> SplitString(const std::string &str, char delim);

STK_API void Trim(std::string &s);
}
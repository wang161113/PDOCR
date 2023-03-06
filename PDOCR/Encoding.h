#pragma once
#include <string>

std::string UnicodeToUTF8(const std::wstring & wstr);
std::wstring UTF8ToUnicode(const std::string & str);
std::string UnicodeToANSI(const std::wstring & wstr);
std::wstring ANSIToUnicode(const std::string & str);
std::string UTF8ToANSI(const std::string & str);
std::string ANSIToUTF8(const std::string & str);
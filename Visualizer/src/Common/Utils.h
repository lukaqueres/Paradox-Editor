#pragma once
#include <string>

class StringUtils
{
public:
	static std::wstring ToWide(const std::string& narrow);
	static std::string ToNarrow(const std::wstring& wide);
};
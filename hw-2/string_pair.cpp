#pragma once
#include <string>

struct StringPair
{
    std::string left;
    std::string right;

    StringPair(const std::string &str, const std::string &delimiter)
    {
        size_t pos = 0;
        if ((pos = str.find(delimiter)) != std::string::npos)
        {
            left = str.substr(0, pos);
            right = str.substr(pos + 1, str.size());
        }
    }
};
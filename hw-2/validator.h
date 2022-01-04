#pragma once
#include <stdexcept>
#include <vector>
#include <algorithm>
#include "string_pair.cpp"

class Validator
{
private:
    const std::string WHITESPACE = " \n\r\t\f\v";

    std::string ltrim(const std::string &s);
    std::string rtrim(const std::string &s);
    std::string trim(const std::string &str);

    std::vector<StringPair> removeWhiteSpaces(std::vector<StringPair> &relations);
    void checkForRemainingSpaces(std::vector<StringPair> &relations);
    std::vector<StringPair> createRelations(const std::string &str);

public:
    std::vector<StringPair> validateRelations(const std::string &data);
};
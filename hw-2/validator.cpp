#include "validator.h"

std::string Validator::ltrim(const std::string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string Validator::rtrim(const std::string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string Validator::trim(const std::string &str)
{
    return rtrim(ltrim(str));
}

std::vector<StringPair> Validator::removeWhiteSpaces(std::vector<StringPair> &relations)
{
    for (int i = 0; i < relations.size(); i++)
    {
        relations[i].left = trim(relations[i].left);
        relations[i].right = trim(relations[i].right);
    }

    return relations;
}

void Validator::checkForRemainingSpaces(std::vector<StringPair> &relations)
{
    for (int i = 0; i < relations.size(); i++)
    {
        if (relations[i].left.find(" ") != std::string::npos || relations[i].left.find(" ") != std::string::npos)
        {
            throw std::invalid_argument("No spaces in name allowed");
        }
    }
}

std::vector<StringPair> Validator::createRelations(const std::string &str)
{
    if (str.find("-") == std::string::npos)
    {
        throw std::invalid_argument("Invalid data1");
    }

    std::string strCopy = str;
    std::vector<StringPair> relations;
    std::string delimiter = "\n";

    int pos = 0;
    std::string token;
    while ((pos = strCopy.find(delimiter)) != std::string::npos)
    {

        token = strCopy.substr(0, pos);
        relations.push_back(StringPair(token, "-"));
        strCopy.erase(0, pos + delimiter.length());
    }

    removeWhiteSpaces(relations);
    checkForRemainingSpaces(relations);

    return relations;
}

std::vector<StringPair> Validator::validateRelations(const std::string &data)
{
    std::vector<StringPair> relations;
    if (!data.size())
    {
        return relations;
    }

    std::string cpy = data;
    if (cpy[cpy.size() - 1] != '\n')
    {
        cpy.append("\n");
    }
    relations = createRelations(cpy);

    return relations;
}

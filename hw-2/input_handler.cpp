#include <string>
#include <vector>
#include <fstream>
#include "interface.h"

std::vector<Hierarchy *> hierarchies;
std::vector<bool> status;

void ifExists(const std::string name)
{
    for (int i = 0; i < hierarchies.size(); i++)
    {
        if (hierarchies[i]->getName() == name)
        {
            delete hierarchies[i];
            hierarchies.erase(hierarchies.begin() + i);
            return;
        }
    }
    return;
}

int getHierarchy(const std::string name)
{
    int idx = 0;
    for (; idx < hierarchies.size(); idx++)
    {
        if (hierarchies[idx]->getName() == name)
        {
            break;
        }

        if (idx + 1 == hierarchies.size())
        {
            return -1;
        }
    }
    return idx;
}

uint32_t hash(const std::string &s)
{
    uint32_t hash = 5381;
    for (const auto &c : s)
        hash = ((hash << 5) + hash) + (unsigned char)c;
    return hash;
}

std::string removeWhiteSpaces(const std::string &input)
{
    string nstr = "";

    for (int i = 0; i < input.length();)
    {
        if (input[i] == ' ')
        {
            if (i == 0 || i == input.length() - 1)
            {
                i++;
                continue;
            }
            while (input[i + 1] == ' ')
            {
                i++;
            }
        }
        nstr += input[i++];
    }
    nstr += " ";

    return nstr;
}

std::vector<std::string> getArguments(const std::string &input)
{
    std::string copy = removeWhiteSpaces(input);

    std::vector<std::string> arguments;
    std::string delimiter = " ";

    int pos = 0;
    std::string token;
    while ((pos = copy.find(delimiter)) != std::string::npos)
    {
        token = copy.substr(0, pos);
        arguments.push_back(token);
        copy.erase(0, pos + delimiter.length());
    }

    return arguments;
}

void help(std::vector<std::string> &arguments)
{
    if (arguments.size() > 1)
    {
        std::cout << "Too many arguments, 'help' does't require any.\n";
        return;
    }

    std::cout << "load hierarchy_name file_name - creates a new hierarchy based on the data in the file. (If no file is passed program will read data from standard input)\n";
    std::cout << "save hierarchy_name file_name - saves the specified hierarchy in the given file, if no file is passed the hierarchy is displayed on standard output\n";
    std::cout << "find hierarchy_name employee_name - checks whether the employee is present in the specified hierarchy\n";
    std::cout << "num_subordinates hierarchy_name employee_name - displays the number of direct subordinates of the employee in the specified hierarchy\n";
    std::cout << "manager hierarchy_name employee_name - displays the name of the head of the employee in the specified hierarchy\n";
    std::cout << "num_employees hierarchy_name - displays the number of employees in the specified hierarchy\n";
    std::cout << "overloaded hierarchy_name - displays the number of employees in the specified hierarchy for which the number of subordinates (direct or not) is greater than 20\n";
    std::cout << "join hierarchy_name_1 hierarchy_name_2 hierarchy_name_result - merges 2 hierarchies in a new one with the specified name\n";
    std::cout << "fire hierarchy_name employee_name - removes employee from specified hierarchy\n";
    std::cout << "hire hierarchy_name employee_name manager - appoints the employee in the specified hierarchy as subordinate to the submitted manager\n";
    std::cout << "salary hierarchy_name employee_name - displays the salary of the employee in the specified hierarchy\n";
    std::cout << "incorporate hierarchy_name - incorporates the specified hierarchy\n";
    std::cout << "modernize hierarchy_name - modernizes the specified hierarchy\n";
    std::cout << "exit - ends program. Prompts user to save all new or changed hierarchies in file\n";
}

void load(std::vector<std::string> &arguments)
{
    if (arguments.size() > 3 || arguments.size() == 1)
    {
        std::cout << "Invalid number of arguments. Type 'help' for more information.\n";
        return;
    }

    // make new from user input
    if (arguments.size() == 2)
    {   
        std::cout << "Enter your relations and type 'stop' on a new line when you are done.\n";
        std::string relations;
        std::string line;
        while (std::getline(std::cin, line))
        {
            if(line == "stop")
            {
                break;
            }
            relations += line + "\n";
        }

        ifExists(arguments[1]);

        Hierarchy *newHierarchy = new Hierarchy(relations);
        newHierarchy->setName(arguments[1]);

        hierarchies.push_back(newHierarchy);
        status.push_back(0);
    }
    else
    {
        // read one from file
        std::ifstream fin(arguments[2].data());
        if (fin.is_open())
        {
            std::string relations;
            std::string temp;
            while (std::getline(fin, temp))
            {
                relations += temp;
                relations += "\n";
            }

            ifExists(arguments[1]);

            Hierarchy *newHierarchy = new Hierarchy(relations);
            newHierarchy->setName(arguments[1]);

            hierarchies.push_back(newHierarchy);
            status.push_back(0);
            fin.close();
        }
        else
        {
            std::cout << "File not found. Try again.\n";
            return;
        }
    }
    std::cout << arguments[1] << " loaded successfully!\n";
    
    return;
}

void save(std::vector<std::string> &arguments)
{
    if (arguments.size() > 3 || arguments.size() == 1)
    {
        std::cout << "Invalid number of arguments. Type 'help' for more information.\n";
        return;
    }

    // find the hierarchy
    int idx = getHierarchy(arguments[1]);
    if (idx == -1)
    {
        std::cout << "No such hierarchy has been found\n";
        return;
    }

    // display
    if (arguments.size() == 2)
    {
        std::cout << hierarchies[idx]->print();
    }
    // save to file
    else
    {
        std::ofstream fout(arguments[2].data());
        if (fout.is_open())
        {
            fout << hierarchies[idx]->print();
            status[idx] = 1;
            fout.close();
        }
        else
        {
            std::cout << "File not found. Try again.\n";
            return;
        }

        std::cout << arguments[1] << " saved.\n";
    }
}

void find(std::vector<std::string> &arguments)
{
    if (arguments.size() != 3)
    {
        std::cout << "Invalid number of arguments. Type 'help' for more information.\n";
        return;
    }

    int idx = getHierarchy(arguments[1]);
    if (idx == -1)
    {
        std::cout << "No such hierarchy has been found\n";
        return;
    }

    if (hierarchies[idx]->find(arguments[2]))
    {
        std::cout << arguments[2] << " is employed in " << arguments[1] << ".\n";
        return;
    }

    std::cout << arguments[2] << " is not employed in " << arguments[1] << ".\n";
}

void num_subordinates(std::vector<std::string> &arguments)
{
    if (arguments.size() != 3)
    {
        std::cout << "Invalid number of arguments. Type 'help' for more information.\n";
        return;
    }

    int idx = getHierarchy(arguments[1]);
    if (idx == -1)
    {
        std::cout << "No such hierarchy has been found\n";
        return;
    }

    int subordinates = hierarchies[idx]->num_subordinates(arguments[2]);
    if (subordinates == -1)
    {
        std::cout << arguments[2] << " is not in " << arguments[1] << ".\n";
        return;
    }

    std::cout << arguments[2] << " has " << subordinates << " subordinates.\n";
}

void manager(std::vector<std::string> &arguments)
{
    if (arguments.size() != 3)
    {
        std::cout << "Invalid number of arguments. Type 'help' for more information.\n";
        return;
    }

    int idx = getHierarchy(arguments[1]);
    if (idx == -1)
    {
        std::cout << "No such hierarchy has been found\n";
        return;
    }

    std::string manager = hierarchies[idx]->manager(arguments[2]);

    if (manager == "")
    {
        std::cout << "Uspeshnia has no manager.\n";
        return;
    }

    std::cout << "The manager of " << arguments[2] << " is " << manager << ".\n";
}

void num_employees(std::vector<std::string> &arguments)
{
    if (arguments.size() != 2)
    {
        std::cout << "Invalid number of arguments. Type 'help' for more information.\n";
        return;
    }

    int idx = getHierarchy(arguments[1]);
    if (idx == -1)
    {
        std::cout << arguments[1] << " is an unknown office!\n";
        return;
    }

    std::cout << "There are " << hierarchies[idx]->num_employees() << " employees in " << arguments[1] << ".\n";
}

void overloaded(std::vector<std::string> &arguments)
{
    if (arguments.size() != 2)
    {
        std::cout << "Invalid number of arguments. Type 'help' for more information.\n";
        return;
    }

    int idx = getHierarchy(arguments[1]);
    if (idx == -1)
    {
        std::cout << arguments[1] << " is an unknown office!\n";
        return;
    }

    int overloadedEmployees = hierarchies[idx]->num_overloaded();
    if (overloadedEmployees == 0)
    {
        std::cout << "No overloaded employees in " << arguments[1] << ".\n";
        return;
    }
    std::cout << overloadedEmployees << "employees are overloaded in" << arguments[1] << ".\n";
}

void join(std::vector<std::string> &arguments)
{
    if (arguments.size() != 4)
    {
        std::cout << "Invalid number of arguments. Type 'help' for more information.\n";
        return;
    }

    int idxL = getHierarchy(arguments[1]);
    int idxR = getHierarchy(arguments[2]);
    if (idxL == -1 || idxR == -1)
    {
        std::cout << "Unknown office was passed! Try again.\n";
        return;
    }

    ifExists(arguments[3]);

    Hierarchy *newHierarchy = new Hierarchy(hierarchies[idxL]->join(*hierarchies[idxR]));
    newHierarchy->setName(arguments[3]);

    hierarchies.push_back(newHierarchy);
    status.push_back(0);
    std::cout << arguments[3] << " created!\n";
}

void fire(std::vector<std::string> &arguments)
{
    if (arguments.size() != 3)
    {
        std::cout << "Invalid number of arguments. Type 'help' for more information.\n";
        return;
    }

    int idx = getHierarchy(arguments[1]);
    if (idx == -1)
    {
        std::cout << arguments[1] << " is an unknown office!\n";
        return;
    }

    bool fired = hierarchies[idx]->fire(arguments[2]);

    if (fired)
    {
        std::cout << arguments[2] << " was fired.\n";
        status[idx] = 0;
        return;
    }

    std::cout << arguments[2] << " is not part of this office.\n";
}

void hire(std::vector<std::string> &arguments)
{
    if (arguments.size() != 4)
    {
        std::cout << "Invalid number of arguments. Type 'help' for more information.\n";
        return;
    }

    int idx = getHierarchy(arguments[1]);
    if (idx == -1)
    {
        std::cout << arguments[1] << " is an unknown office!\n";
        return;
    }

    bool hired = hierarchies[idx]->hire(arguments[2], arguments[3]);

    if (hired)
    {
        std::cout << arguments[2] << " was hired.\n";
        status[idx] = 0;
        return;
    }
    std::cout << "There is no employee called " << arguments[3] << ".\n";
}

void salary(std::vector<std::string> &arguments)
{
    if (arguments.size() != 3)
    {
        std::cout << "Invalid number of arguments. Type 'help' for more information.\n";
        return;
    }

    int idx = getHierarchy(arguments[1]);
    if (idx == -1)
    {
        std::cout << arguments[1] << " is an unknown office!\n";
        return;
    }

    unsigned long salary = hierarchies[idx]->getSalary(arguments[2]);

    if (salary == -1)
    {
        std::cout << arguments[2] << " is not part of this office.\n";
        return;
    }

    std::cout << "The salary is " << salary << " BGN.\n";
}

void incorporate(std::vector<std::string> &arguments)
{
    if (arguments.size() != 2)
    {
        std::cout << "Invalid number of arguments. Type 'help' for more information.\n";
        return;
    }

    int idx = getHierarchy(arguments[1]);
    if (idx == -1)
    {
        std::cout << arguments[1] << " is an unknown office!\n";
        return;
    }

    hierarchies[idx]->incorporate();
    std::cout << arguments[1] << " incorporated.\n";
}

void modernize(std::vector<std::string> &arguments)
{
    if (arguments.size() != 2)
    {
        std::cout << "Invalid number of arguments. Type 'help' for more information.\n";
        return;
    }

    int idx = getHierarchy(arguments[1]);
    if (idx == -1)
    {
        std::cout << arguments[1] << " is an unknown office!\n";
        return;
    }

    hierarchies[idx]->modernize();
    std::cout << arguments[1] << " modernized.\n";
}

void exit(std::vector<std::string> &arguments)
{
    if (arguments.size() != 1)
    {
        std::cout << "Invalid number of arguments. Type 'help' for more information.\n";
        return;
    }

    for (int i = 0; i < hierarchies.size(); i++)
    {
        if (status[i] == 0)
        {
            std::string input;
            std::cout << hierarchies[i]->getName() << " is modified but not saved.\n";
            std::cout << "Enter file name to save: ";
            std::cin >> input;

            std::ofstream fout(input.data());
            if (fout.is_open())
            {
                fout << hierarchies[i]->print();
                fout.close();
            }

            std::cout << hierarchies[i]->getName() << " saved!\n";
        }
    }

    std::cout << "Goodbye!\n";
}

#include <iostream>
#include <fstream>
#include "interface.h"
#include "input_handler.cpp"

int main()
{
    string input;
    std::vector<string> arguments;

    while (input != "exit" && !std::cin.eof())
    {   
        
        std::getline(std::cin, input);
        arguments = getArguments(input);

        switch (hash(arguments[0]))
        {
        // help
        case 2090324718:
            help(arguments);
            break;
        // load
        case 2090478981:
            load(arguments);
            break;
        // save
        case 2090715988:
            save(arguments);
            break;
        // find
        case 2090257254:
            find(arguments);
            break;
        // num_subordinates
        case 2375170919:
            num_subordinates(arguments);
            break;
        // manager
        case 3029163104:
            manager(arguments);
            break;
        // num_employees
        case 1846855239:
            num_employees(arguments);
            break;
        // overloaded
        case 688101674:
            overloaded(arguments);
            break;
        // join
        case 2090407381:
            join(arguments);
            break;
        // fire
        case 2090257387:
            fire(arguments);
            break;
        // hire
        case 2090329261:
            hire(arguments);
            break;
        // salary
        case 456684209:
            salary(arguments);
            break;
        // incorporate
        case 745480235:
            incorporate(arguments);
            break;
        // modernize
        case 21611122:
            modernize(arguments);
            break;
        // exit
        case 2090237503:
            exit(arguments);
            break;
        default:
            std::cout << "No function found.\n";
            break;
        }
            

    }
    
    
}
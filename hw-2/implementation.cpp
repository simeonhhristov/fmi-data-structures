#include "interface.h"

Hierarchy::Hierarchy(Hierarchy &&r) noexcept
{
    std::swap(name, r.name);
    std::swap(numOfEmployees, r.numOfEmployees);
    std::swap(employees, r.employees);
}

Hierarchy::Hierarchy(const Hierarchy &r)
{
    this->name = r.name;
    this->numOfEmployees = r.numOfEmployees;
    this->employees = new Tree<string>(*r.employees);
}

Hierarchy::Hierarchy(const string &data)
{
    Validator validator;
    std::vector<StringPair> relations = validator.validateRelations(data);

    if (!relations.size())
    {
        employees = nullptr;
        return;
    }
    employees = new Tree<string>(relations[0].left);
    numOfEmployees++;

    for (size_t i = 0; i < relations.size(); i++)
    {
        if (!insertAfter(relations[i].left, relations[i].right, employees))
        {
            throw std::invalid_argument("Employee must first be presented as employer");
        }
        numOfEmployees++;
    }
    sortAscending(employees);
}

Hierarchy::~Hierarchy() noexcept
{
    delete employees;
}

string Hierarchy::print() const
{
    string result = "";
    std::queue<Tree<string> *> fringe;
    fringe.push(employees);

    while (!fringe.empty() && fringe.front())
    {
        Tree<string> *curr = fringe.front();
        fringe.pop();
        for (int i = 0; i < curr->children.size(); i++)
        {
            fringe.push(curr->children[i]);
            result += curr->value + "-" + curr->children[i]->value + "\n";
        }
    }
    return result;
}

int Hierarchy::longest_chain() const
{
    if (employees)
    {
        return employees->longestPathLen(employees);
    }
    return 0;
}

bool Hierarchy::find(const string &name) const
{
    if (employees)
    {
        return findNode(name, employees);
    }
    return 0;
}

int Hierarchy::num_employees() const
{
    return numOfEmployees;
}

int Hierarchy::num_overloaded(int level) const
{
    if (employees)
    {
        return overloadedCount(employees, level);
    }
    return 0;
}

string Hierarchy::manager(const string &name) const
{
    Tree<string> *employee = findNode(name, employees);
    if (employee->parent)
    {
        return employee->parent->value;
    }
    return "";
}

int Hierarchy::num_subordinates(const string &name) const
{
    Tree<string> *employee = findNode(name, employees);
    if (employee)
    {
        return employee->children.size();
    }
    return -1;
}

unsigned long Hierarchy::getSalary(const string &who) const
{
    Tree<string> *employee = findNode(who, employees);
    if (employee)
    {
        // after some refactoring the formula looks like this
        return 50 * (9 * num_subordinates(who) + nodesCount(employee) - 1);
    }
    return -1;
}

bool Hierarchy::fire(const string &who)
{
    if (who != "Uspeshnia" && pop(who, employees))
    {
        numOfEmployees--;
        return 1;
    }
    return 0;
}

bool Hierarchy::hire(const string &who, const string &boss)
{
    if (findNode(who, employees))
    {
        fire(who);
    }

    if (insertAfter(boss, who, employees))
    {
        numOfEmployees++;
        return 1;
    }
    return 0;
}

void Hierarchy::incorporate()
{
    std::stack<Tree<string> *> teams;
    std::queue<Tree<string> *> fringe;
    fringe.push(employees);
    while (!fringe.empty() && fringe.front())
    {
        Tree<string> *curr = fringe.front();
        fringe.pop();
        if (curr->children.size() >= 2)
        {
            teams.push(curr);
        }
        for (int i = 0; i < curr->children.size(); i++)
        {
            fringe.push(curr->children[i]);
        }
    }

    while (!teams.empty() && teams.top())
    {
        Tree<string> *curr = teams.top();
        teams.pop();
        Tree<string> *toPromote = curr->children[0];
        int idx = 0;

        for (int i = 0; i < curr->children.size(); i++)
        {
            if (getSalary(toPromote->value) < getSalary(curr->children[i]->value))
            {
                toPromote = curr->children[i];
                idx = i;
            }
        }

        curr->children.erase(curr->children.begin() + idx);
        for (int i = curr->children.size() - 1; i >= 0; i--)
        {
            curr->children[i]->parent = toPromote;
            toPromote->children.push_back(curr->children[i]);
            curr->children.pop_back();
        }
        curr->children.push_back(toPromote);
    }

    sortAscending(employees);
    level(employees);
}

void Hierarchy::modernize()
{
    std::vector<Tree<string> *> oddNodes = getOddLeveled(employees);
    for (int i = oddNodes.size() - 1; i >= 0; i--)
    {
        Tree<string> *curr = oddNodes[i];
        Tree<string> *currBoss = curr->parent;

        for (int j = 0; j < currBoss->children.size(); j++)
        {
            if (currBoss->children[j] == curr)
            {
                currBoss->children.erase(currBoss->children.begin() + j);
                break;
            }
        }

        for (int j = curr->children.size() - 1; j >= 0; j--)
        {
            curr->children[j]->parent = currBoss;
            currBoss->children.push_back(curr->children[j]);
            curr->children.pop_back();
        }
        delete curr;
        numOfEmployees--;
    }
    sortAscending(employees);
    level(employees);
}

Hierarchy Hierarchy::join(const Hierarchy &right) const
{
    Hierarchy newHierarchy;

    Tree<string> *temp1 = new Tree<string>(*employees);
    Tree<string> *temp2 = new Tree<string>(*right.employees);

    delete newHierarchy.employees;

    newHierarchy.employees = merge(temp1, temp2);

    sortAscending(newHierarchy.employees);
    newHierarchy.numOfEmployees = nodesCount(newHierarchy.employees);

    delete temp1;
    delete temp2;

    return newHierarchy;
}

void Hierarchy::setName(const string &name)
{
    this->name = name;
}

string Hierarchy::getName()
{
    return this->name;
}
#pragma once
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <stdexcept>
#include "validator.h"
#include "tree.cpp"
#include "string_pair.cpp"

using std::string;

class Hierarchy
{
public:
    Hierarchy(Hierarchy &&r) noexcept;
    Hierarchy() = default;
    Hierarchy(const Hierarchy &r);
    Hierarchy(const string &data);
    ~Hierarchy() noexcept;
    void operator=(const Hierarchy &) = delete;

    string print() const;

    int longest_chain() const;
    bool find(const string &name) const;
    int num_employees() const;
    int num_overloaded(int level = 20) const;

    string manager(const string &name) const;
    int num_subordinates(const string &name) const;
    unsigned long getSalary(const string &who) const;

    bool fire(const string &who);
    bool hire(const string &who, const string &boss);

    void incorporate();
    void modernize();

    Hierarchy join(const Hierarchy &right) const;

    void setName(const string &name);
    string getName();

private:
    string name = "";
    int numOfEmployees = 0;
    Tree<string> *employees = nullptr;
};
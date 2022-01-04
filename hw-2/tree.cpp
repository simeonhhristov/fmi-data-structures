#pragma once
#include <iostream>
#include <vector>
#include <queue>

template <class T>
struct Tree
{
private:
    T value;
    int level;
    Tree *parent = nullptr;
    std::vector<Tree *> children;

    friend class Hierarchy;

public:
    Tree() = default;
    Tree(const T &_value, int _level = 0) : value(_value), parent(nullptr), level(_level) {}
    Tree(const Tree<T> &other)
    {
        this->value = other.value;
        this->level = other.level;
        for (int i = 0; i < other.children.size(); i++)
        {
            this->children.push_back(new Tree(*other.children[i]));
            this->children[i]->parent = this;
        }
    }
    ~Tree()
    {
        for (int i = 0; i < children.size(); i++)
        {
            delete this->children[i];
        }
        this->children.clear();
    }

    Tree<T> &operator=(const Tree<T> &other)
    {
        if (this != &other)
        {
            Tree<T> cpy = other;
            std::swap(this->value, cpy.value);
            std::swap(this->level, cpy.level);
            std::swap(this->parent, cpy.parent);
            std::swap(this->children, cpy.children);
        }
        return *this;
    }

    void print()
    {
        std::queue<Tree *> fringe;
        fringe.push(this);
        while (!fringe.empty())
        {
            Tree<T> *curr = fringe.front();
            fringe.pop();
            for (int i = 0; i < curr->children.size(); i++)
            {
                fringe.push(curr->children[i]);
                std::cout << curr->value << "-" << curr->children[i]->value << "\n";
            }
        }
    }

    int longestPathLen(Tree<T> *tree) const
    {
        if (!tree)
        {
            return -1;
        }

        int maxLen = 0;

        for (int i = 0; i < tree->children.size(); i++)
        {
            int currLen = longestPathLen(tree->children[i]);
            if (maxLen < currLen)
            {
                maxLen = currLen;
            }
        }
        return maxLen + 1;
    }

    std::queue<Tree<T> *> BFS()
    {
        std::queue<Tree<T> *> fringe;
        std::queue<Tree<T> *> result;
        Tree<T> *cpy = new Tree<T>(*this);

        fringe.push(cpy);

        while (!fringe.empty() && fringe.front())
        {
            Tree<T> *curr = fringe.front();
            fringe.pop();
            for (int i = 0; i < curr->children.size(); i++)
            {
                fringe.push(curr->children[i]);
            }
            result.push(curr);
        }
        return result;
    }

    template <class Y>
    friend void level(Tree<Y> *tree);

    template <class Y>
    friend std::vector<Tree<Y> *> getOddLeveled(Tree<Y> *tree, bool isOdd);

    template <class Y>
    friend int Partition(std::vector<Tree<Y> *> &v, int start, int end);

    template <class Y>
    friend void sortAscending(Tree<Y> *node);

    template <class Y>
    friend bool insertAfter(const Y &parent, const Y &value, Tree<Y> *node);

    template <class Y>
    friend Tree<Y> *findNode(const Y &value, Tree<Y> *tree);

    template <class Y>
    friend int nodesCount(Tree<Y> *tree);

    template <class Y>
    friend int overloadedCount(Tree<Y> *tree, int level);

    template <class Y>
    friend bool pop(const Y &value, Tree<Y> *tree);

    template <class Y>
    friend Tree<Y> *merge(Tree<Y> *left, Tree<Y> *right);
};

template <class T>
void level(Tree<T> *tree)
{
    std::queue<Tree<T> *> fringe;
    fringe.push(tree);
    while (!fringe.empty() && fringe.front())
    {
        Tree<T> *curr = fringe.front();
        fringe.pop();
        if (curr->parent)
        {
            curr->level = curr->parent->level + 1;
        }
        for (int i = 0; i < curr->children.size(); i++)
        {
            fringe.push(curr->children[i]);
        }
    }
}

template <class T>
std::vector<Tree<T> *> getOddLeveled(Tree<T> *tree, bool isOdd = false)
{
    std::vector<Tree<T> *> oddNodes;
    std::queue<Tree<T> *> fringe;
    fringe.push(tree);
    while (!fringe.empty() && fringe.front())
    {
        Tree<T> *curr = fringe.front();
        fringe.pop();

        for (int i = 0; i < curr->children.size(); i++)
        {
            fringe.push(curr->children[i]);
        }

        if (curr->level % 2 == 1 && curr->children.size())
        {
            oddNodes.push_back(curr);
        }
    }
    return oddNodes;
}

template <class T>
int Partition(std::vector<Tree<T> *> &v, int start, int end)
{
    int pivot = end;
    int j = start;
    for (int i = start; i < end; ++i)
    {
        if (v[i]->value < v[pivot]->value)
        {
            std::swap(v[i], v[j]);
            ++j;
        }
    }
    std::swap(v[j], v[pivot]);
    return j;
}

template <class T>
void Quicksort(std::vector<Tree<T> *> &v, int start, int end)
{

    if (start < end)
    {
        int p = Partition(v, start, end);
        Quicksort(v, start, p - 1);
        Quicksort(v, p + 1, end);
    }
}

template <class T>
void sortAscending(Tree<T> *node)
{
    if (!node)
    {
        return;
    }

    for (int i = 0; i < node->children.size(); i++)
    {
        Quicksort(node->children, 0, node->children.size() - 1);
        sortAscending(node->children[i]);
    }
}

template <class T>
bool insertAfter(const T &parent, const T &value, Tree<T> *node)
{
    Tree<T> *vertex = findNode(parent, node);
    if (vertex)
    {
        Tree<T> *newNode = new Tree<T>(value, (vertex->level + 1));
        newNode->parent = vertex;
        vertex->children.push_back(newNode);

        sortAscending(node);
        return 1;
    }
    return 0;
}

template <class T>
Tree<T> *findNode(const T &value, Tree<T> *tree)
{
    std::queue<Tree<T> *> fringe;
    fringe.push(tree);
    while (!fringe.empty() && fringe.front())
    {
        Tree<T> *curr = fringe.front();
        fringe.pop();

        if (curr->value == value)
        {
            return curr;
        }
        for (int i = 0; i < curr->children.size(); i++)
        {
            fringe.push(curr->children[i]);
        }
    }
    return nullptr;
}

template <class T>
int nodesCount(Tree<T> *tree)
{
    if (!tree)
    {
        return 0;
    }

    int count = 1;
    for (int i = 0; i < tree->children.size(); i++)
    {
        count += nodesCount(tree->children[i]);
    }

    return count;
}

template <class T>
int overloadedCount(Tree<T> *tree, int level)
{
    int count = 0 + (nodesCount(tree) - 1 > level);

    for (size_t i = 0; i < tree->children.size(); i++)
    {
        count += overloadedCount(tree->children[i], level);
    }

    return count;
}

template <class T>
bool pop(const T &value, Tree<T> *tree)
{
    Tree<T> *nodeToPop = findNode(value, tree);

    if (nodeToPop)
    {
        Tree<T> *parent = nodeToPop->parent;
        for (int i = nodeToPop->children.size() - 1; i >= 0; i--)
        {
            nodeToPop->children[i]->parent = parent;
            parent->children.push_back(nodeToPop->children[i]);
            nodeToPop->children.pop_back();
        }

        for (int i = 0; i < parent->children.size(); i++)
        {
            if (nodeToPop == parent->children[i])
            {
                parent->children.erase(parent->children.begin() + i);
                break;
            }
        }
        sortAscending(parent);
        level(parent);
        delete nodeToPop;

        return 1;
    }
    return 0;
}

template <class T>
Tree<T> *merge(Tree<T> *left, Tree<T> *right)
{
    Tree<T> *newTree = new Tree<T>(*left);
    std::queue<Tree<T> *> rightTree = right->BFS();
    Tree<T> *toDelete = rightTree.front();

    while (!rightTree.empty())
    {
        Tree<T> *current = rightTree.front();
        rightTree.pop();

        Tree<T> *leftRepresentative = findNode(current->value, newTree);

        // skip, it's root
        if (leftRepresentative && !leftRepresentative->parent)
        {
            continue;
        }

        // Not in left tree
        if (!leftRepresentative)
        {
            Tree<T> *leftParent = findNode(current->parent->value, newTree);
            insertAfter(leftParent->value, current->value, newTree);
        }
        // already exists in left tree
        else
        {
            // left level is higher
            if (leftRepresentative->level < current->level)
            {
                continue;
            }
            // right level is higher
            else if (leftRepresentative->level > current->level)
            {
                Tree<T> *newParent = findNode(current->parent->value, newTree);
                for (int i = 0; i < leftRepresentative->parent->children.size(); i++)
                {
                    if (leftRepresentative->parent->children[i]->value == current->value)
                    {
                        leftRepresentative->parent->children.erase(leftRepresentative->parent->children.begin() + i);
                    }
                }
                leftRepresentative->parent = newParent;
                newParent->children.push_back(leftRepresentative);
                level(newParent);
            }
            // equal levels
            else
            {
                if (leftRepresentative->parent->value <= current->parent->value)
                {
                    continue;
                }
                else
                {
                    Tree<T> *newParent = findNode(current->parent->value, newTree);
                    for (int i = 0; i < leftRepresentative->parent->children.size(); i++)
                    {
                        if (leftRepresentative->parent->children[i]->value == current->value)
                        {
                            leftRepresentative->parent->children.erase(leftRepresentative->parent->children.begin() + i);
                        }
                    }
                    leftRepresentative->parent = newParent;
                    newParent->children.push_back(leftRepresentative);
                    level(newParent);
                }
            }
        }
    }
    delete toDelete;

    sortAscending(newTree);
    return newTree;
}
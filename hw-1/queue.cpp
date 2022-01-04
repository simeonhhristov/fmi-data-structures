#pragma once
#include <cassert>

template <class T>
class queue
{
private:
    T *data = new T[4];
    int last = 0;
    int first = 0;
    int capacity = 4;

    void resize()
    {
        T *newData = new T[capacity * 2];
        try
        {
            for (int i = 0; i < capacity * 2; i++)
            {
                newData[i] = this->data[i];
            }
        }
        catch (...)
        {
            delete[] newData;
            throw;
        }

        std::swap(this->data, newData);
        delete[] newData;

        this->last -= this->first;
        this->first = 0;
        this->capacity *= 2;
    }

public:
    queue() = default;

    queue(const queue<T> &other)
    {
        this->data = new T[other.capacity];
        for (int i = 0; i < other.last; i++)
        {
            this->data[i] = other.data[i];
        }

        this->first = other.first;
        this->last = other.last;
        this->capacity = other.capacity;
    }

    queue<T> &operator=(const queue<T> &other)
    {
        queue<T> copy = other;
        std::swap(this->data, copy.data);
        std::swap(this->first, copy.first);
        std::swap(this->last, copy.last);
        std::swap(this->capacity, copy.capacity);

        return *this;
    }

    ~queue()
    {
        delete[] this->data;
    }

    const T &peek() const
    {
        if(!isEmpty())
        {
        return this->data[first];
        }
        throw std::underflow_error("Empty queue");
    }
    const T &peekBack() const
    {
        if (!isEmpty())
        {
        return this->data[last - 1];
        }
        throw std::underflow_error("Empty queue");
    }

    void enqueue(const T &element)
    {
        if (last == capacity)
        {
            this->resize();
        }
        this->data[last++] = element;
    }
    T dequeue()
    {
        if (!isEmpty())
        {
            const T &element = data[first];
            first++;
            return element;
        }
        throw std::underflow_error("Empty queue");
    }
    int size() const
    {
        return this->last - this->first;
    }
    bool isEmpty() const
    {
        return this->size() == 0;
    }
};
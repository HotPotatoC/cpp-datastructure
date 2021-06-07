#pragma once

#ifndef __STACK_HPP__
#define __STACK_HPP__

#include <iostream>
#include <vector>

template <class T>
class Stack
{
private:
    using element_type = T;
    std::vector<element_type> items_;

public:
    Stack() = default;
    Stack(std::vector<element_type> v) : items_(v) {}
    ~Stack() = default;

    void push(const element_type &&element) { this->items_.insert(this->items_.begin(), std::move(element)); }
    void pop() { this->items_.erase(this->items_.begin()); }

    element_type top() const { return this->items_.front(); }
    element_type bottom() const { return this->items_.back(); }

    unsigned int size() const { return this->items_.size(); }

    friend std::ostream &operator<<(std::ostream &out, const Stack<element_type> &s)
    {
        out << "Top: " << s.top() << '\n';
        out << "Bottom: " << s.bottom() << '\n';
        out << "[ ";
        for (auto &&i : s.items_)
        {
            out << i << ", ";
        }
        out << "]";

        return out;
    }
};

#endif
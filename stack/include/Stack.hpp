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
    std::vector<element_type> elements_;

public:
    Stack() = default;
    Stack(std::vector<element_type> v) : elements_(v) {}
    ~Stack() = default;

    /**
     * @brief Add an element into the stack
     */
    void push(const element_type &&element) { this->elements_.insert(this->elements_.begin(), std::move(element)); }

    /**
     * @brief Removes the top element of the stack
     */
    void pop() { this->elements_.erase(this->elements_.begin()); }

    /**
     * @brief Return top element of the stack
     */
    element_type top() const { return this->elements_.front(); }

    /**
     * @brief Return bottom element of the stack
     */
    element_type bottom() const { return this->elements_.back(); }

    /**
     * @brief Return the size of the stack
     */
    unsigned int size() { return this->elements_.size(); }

    /**
     * @brief Return the const size of the stack
     */
    const unsigned int size() const { return this->elements_.size(); }

    friend std::ostream &operator<<(std::ostream &out, const Stack<element_type> &s)
    {
        out << "Top: " << s.top() << '\n';
        out << "Bottom: " << s.bottom() << '\n';
        out << "[ ";
        for (auto &&i : s.elements_)
        {
            out << i << ", ";
        }
        out << "]";

        return out;
    }
};

#endif
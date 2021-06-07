#pragma once

#ifndef __QUEUE_HPP__
#define __QUEUE_HPP__

#include <iostream>
#include <vector>
#include <memory>

/**
 *  @brief A simple queue implementation using std::vector.
 *
 *  @ingroup sequences
 *
 *  @tparam T  Type of element.
*/
template <class T>
class Queue
{
private:
    using element_type = T;
    std::vector<element_type> elements_;

public:
    Queue() = default;
    Queue(std::vector<element_type> v)
        : elements(v){};

    ~Queue() = default;

    /**
     *  @brief Enqueue the element
     *  @param  element  Data to be added.
     */
    void enqueue(const element_type &&element) { elements_.push_back(element); }

    /**
     *  @brief Dequeue the element
     */
    void dequeue() { elements_.erase(elements_.begin()); }

    /**
     *  @brief Return all elements in the queue
     */
    std::vector<element_type> items() const { return elements; }

    /**
     * @brief Return the element at front of the queue
     */
    element_type front() const { return elements_.front(); }

    /**
     * @brief Return the element at back of the queue
     */
    element_type rear() const { return elements_.back(); }

    /**
     * @brief Returns true if the queue is empty, false otherwise
     */
    bool is_empty() const { return elements_.empty(); }

    /**
     * @brief Returns the current size of the queue
     */
    unsigned int size() const { return elements_.size(); }

    friend std::ostream &operator<<(std::ostream &out, const Queue<element_type> &q)
    {
        for (auto &&item : q.items())
        {
            out << item << " ";
        }

        return out;
    }

    friend std::ostream &operator<<(std::ostream &out, const std::unique_ptr<Queue<element_type>> &q)
    {
        for (auto &&item : q->items())
        {
            out << item << " ";
        }

        return out;
    }
};

#endif
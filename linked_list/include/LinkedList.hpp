#pragma once

#ifndef __LINKED_LIST_HPP__
#define __LINKED_LIST_HPP__

#include <atomic>
#include <memory>

/**
 *  @brief A key-value pair linked-list node
 *
 *  @ingroup sequences
 *
 *  @tparam T  Type of element
*/
template <class T>
struct Node
{
    using element_type = T;

    element_type value;
    std::unique_ptr<Node> next;

    explicit Node(const element_type &v)
        : value(v), next(nullptr){};
    ~Node() = default;
};

/**
 *  @brief A simple linked list implementation.
 *
 *  @ingroup sequences
 *
 *  @tparam T  Type of element
*/
template <class T>
class LinkedList
{
private:
    using element_type = T;

    std::unique_ptr<Node<T>> head_;
    std::atomic<int> n_size_;

public:
    LinkedList()
        : head_(nullptr), n_size_(0){};
    ~LinkedList() = default;

    /**
     * @brief Appends an item into the list
     * @param  data  Data to be added.
     */
    void append(const element_type &data)
    {
        auto _new_node = std::make_unique<Node<element_type>>(data);
        if (this->head_ == nullptr)
        {
            this->head_ = std::move(_new_node);
            ++this->n_size_;
            return;
        }

        _new_node->next = std::move(this->head_);
        this->head_ = std::move(_new_node);
        ++this->n_size_;
    }

    /**
     * @brief Removes a node inside the list with the matching value
     */
    template <class _eraseT = element_type>
    void erase(const _eraseT &data)
    {
        if (this->head_ == nullptr)
        {
            return;
        }

        if (this->head_->value == data)
        {
            this->head_ = std::move(this->head_->next);
            --this->n_size_;
            return;
        }

        Node<element_type> *tmp_head = this->head_.get();
        while (tmp_head->next.get() != nullptr)
        {
            if (tmp_head->next->value == data)
            {
                tmp_head->next = std::move(tmp_head->next->next);

                --this->n_size_;
                return;
            }
            tmp_head = tmp_head->next.get();
        }
    }

    /**
     * @brief Removes the head of the list and replace it with the next node
     */
    void pop()
    {
        if (this->head_ == nullptr)
        {
            return;
        }

        this->head_ = std::move(this->head_->next);
        --this->n_size_;
    }

    /**
     * @brief Reverses the list
     */
    void reverse()
    {
        if (this->head_ == nullptr)
        {
            return;
        }

        LinkedList<element_type> tmp;
        Node<element_type> *curr = this->head_.get();

        while (curr) {
            tmp.append(curr->value);
            curr = curr->next.get();
        }

        this->clean();
        this->head_ = std::move(tmp.head_);
    }

    void clean()
    {
        while (this->head_)
        {
            this->head_ = std::move(this->head_->next);
        }
    }

    /**
     * @brief Return the size of the list
     */
    unsigned int size() { return this->n_size_; }

    /**
     * @brief Return the const size of the list
     */
    const unsigned int size() const { return this->n_size_; }

    friend std::ostream &operator<<(std::ostream &out, const LinkedList<element_type> &ll)
    {
        Node<element_type> *tmp_head = ll.head_.get();
        out << "Head: " << tmp_head->value << '\n';
        out << "Size: " << ll.n_size_ << '\n';
        while (tmp_head)
        {
            out << "[ " << tmp_head->value << " ] ";
            tmp_head = tmp_head->next.get();
            if (tmp_head != nullptr)
            {
                out << "-> ";
            }
        }

        return out;
    }
};
#endif
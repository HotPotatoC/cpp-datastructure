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
        // Initialize a new node
        auto _new_node = std::make_unique<Node<element_type>>(data);

        // if the current head is null, assign the new node
        // into the head of the list
        if (this->head_ == nullptr)
        {
            this->head_ = std::move(_new_node);

            // increase the size
            ++this->n_size_;
            return;
        }

        // replace the next link of the new node with the current head
        _new_node->next = std::move(this->head_);

        // replace the head with the new node
        this->head_ = std::move(_new_node);

        // increase the size
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

        // if the head matches with the value delete it and replace
        // it with the next node without looping to maintain O(1)
        if (this->head_->value == data)
        {
            this->head_ = std::move(this->head_->next);
            --this->n_size_;
            return;
        }

        // Loop through the list
        Node<element_type> *tmp_head = this->head_.get();
        while (tmp_head->next.get() != nullptr)
        {
            // if the next link of the current node have the matching value replace it
            if (tmp_head->next->value == data)
            {
                // replace it with the next node
                tmp_head->next = std::move(tmp_head->next->next);

                // decrease the size
                --this->n_size_;
                return;
            }

            // go to the next node
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

        // replace the current head with the next node
        this->head_ = std::move(this->head_->next);

        // decrease the size
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

        // Create a temporary linked list to create the reversed list
        LinkedList<element_type> tmp;

        // Pointer to the head of the list for iterating purposes
        Node<element_type> *curr = this->head_.get();

        while (curr)
        {
            // append the current value into the temporary linked list
            tmp.append(curr->value);

            // go to the next node
            curr = curr->next.get();
        }

        // clear the list
        this->clean();

        // set the list
        this->head_ = std::move(tmp.head_);
    }

    /**
     * @brief Clears the list
     */
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
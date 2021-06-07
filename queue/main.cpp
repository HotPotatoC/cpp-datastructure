#include <iostream>
#include <vector>
#include <memory>

#include "Queue.hpp"

int main()
{
    Queue<int> int_q;

    int_q.enqueue(1);
    int_q.enqueue(5);
    int_q.enqueue(2);
    int_q.enqueue(6);
    std::cout << int_q << std::endl;

    int_q.dequeue();
    int_q.enqueue(2);
    int_q.enqueue(2);
    std::cout << int_q << std::endl;

    Queue<int> q(std::vector<int>{1, 5, 4, 3});

    std::cout << q << std::endl;
    std::cout << "front: " << q.front() << std::endl;
    std::cout << "rear: " << q.rear() << std::endl;
    std::cout << "size: " << q.size() << std::endl;

    return EXIT_SUCCESS;
}
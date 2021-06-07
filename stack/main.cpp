#include <iostream>

#include "Stack.hpp"

int main() {
    Stack<int> stack;

    stack.push(5);
    stack.push(4);
    stack.push(6);
    stack.push(9);

    std::cout << stack << '\n';

    stack.pop();
    stack.pop();
    stack.push(12);
    stack.push(8);
    std::cout << stack << '\n';
}
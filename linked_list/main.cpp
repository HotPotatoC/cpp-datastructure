#include <iostream>
#include <string>

#include "LinkedList.hpp"

struct Person
{
    std::string name;
    unsigned short age;

    explicit Person(const std::string &name, const unsigned short &age)
        : name(name), age(age) {}

    friend std::ostream &operator<<(std::ostream &out, const Person &s)
    {
        out << "{ \"name\": \"" << s.name << "\", \"age\": " << s.age << " }";
        return out;
    }

    // Compare by name
    inline bool operator==(const std::string &n) { return name == n; }
    // Compare struct with std::tie
    inline bool operator==(const Person &s) { return std::tie(name, age) == std::tie(s.name, s.age); }
};

int main()
{
    LinkedList<Person> ll;

    ll.append(Person("Juan", 18));
    ll.append(Person("Vadikus", 18));
    ll.append(Person("Wesker", 18));
    ll.append(Person("John", 18));
    ll.append(Person("George", 18));

    std::cout << ll << '\n';

    ll.erase(Person("Vadikus", 18));
    ll.erase<std::string>("Wesker");
    std::cout << ll << '\n';

    ll.reverse();
    std::cout << ll << '\n';
}
#include <iostream>
#include <numeric>
#include "single_linked_list.h"


int main() {

    utec::single_linked_list<double> sll = {10.5, 20.3, 30.2, 40.1, 50.4};
    std::cout << sll;

    sll.pop_front();
    std::cout << sll;

    utec::single_linked_list<int> sll2;
    sll2.push_front(10);
    sll2.push_front(20);
    sll2.push_front(30);
    sll2.push_front(40);
    sll2.push_front(50);
    std::cout << sll2;

    utec::single_linked_list<int> sll3 = {10, 20, 30, 40, 50};
    for (auto it = std::begin(sll3); it != std::end(sll3); ++it)
         std::cout << *it << " ";

    utec::single_linked_list<int> sll4 = {10, 20, 30, 40, 50};
    auto sll5 = sll4;
    for (auto& item: sll4)
        item *=10;
    std::cout << sll4 << std::endl;
    std::cout << sll5 << std::endl;


    utec::single_linked_list<int> sll6 = {10, 20, 30, 40, 50};
    auto sll7 = sll6;
    for (auto& item: sll7)
        item *=10;
    std::cout << sll6 << std::endl;
    std::cout << sll7 << std::endl;

    utec::single_linked_list<int> sll8 = {10, 20, 30, 40, 50};
    auto total = std::accumulate(std::begin(sll8), std::end(sll8), 0);
    std::cout << total;
}

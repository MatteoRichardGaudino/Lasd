
//#include "zlasdtest/test.hpp"

#include "zmytest/test.hpp"

/* ************************************************************************** */

#include <iostream>

/* ************************************************************************** */

int main() {
    std::cout << "Lasd Libraries 2020" << std::endl;
    //lasdtest(); // To call in the menu of your library test!
    //launchMenu();

    lasd::List<int> l;
    l.InsertAtFront(5);
    l.InsertAtFront(4);
    l.InsertAtFront(3);
    l.InsertAtFront(2);
    l.InsertAtFront(1);
    l.InsertAtFront(0);

    printMappable(l, true);
    lasd::List<int> l2 = std::move(l);
    printMappable(l, true);
    printMappable(l2, true);
    l2[0] = 99;
    printMappable(l, true);
    printMappable(l2, true);
    return 0;
}

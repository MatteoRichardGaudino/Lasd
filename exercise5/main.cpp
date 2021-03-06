#include "zlasdtest/test.hpp"
//#include "zmytest/test.hpp"
//#include "binarytree/binarytree.hpp"
/* ************************************************************************** */
#include "bst/bst.hpp"
#include <iostream>
#include <random>

using namespace std;
using namespace lasd;

default_random_engine gen(random_device{}());
/* ************************************************************************** */

int main() {
  std::cout << "Lasd Libraries 2020" << std::endl;
  //lasdtest(); // To call in the menu of your library test!
  //launchMenu();
    Vector<int> vec(30);
    for(unsigned int i=0; i<vec.Size(); i++){
        vec[i] = i;
    }

    vec.MapPreOrder([](int& i, void*){
        cout<< i << " ";
    }, nullptr);
    cout<<endl;
    vec.Shuffle();
    vec.Shuffle();
    vec.Shuffle();
    vec.Shuffle();


    vec.MapPreOrder([](int& i, void*){
        cout<< i << " ";
    }, nullptr);
    cout<<endl;
    cout<< "Is sorted: "<<vec.IsSorted()<<endl;

    vec.QuickSort();
    vec.MapPreOrder([](int& i, void*){
        cout<< i << " ";
    }, nullptr);
    cout<<endl;
    cout<< "Is sorted: "<<vec.IsSorted()<<endl;

    return 0;
}

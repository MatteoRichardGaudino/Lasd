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
    Vector<int> vec(5);
//    for(unsigned int i=0; i<vec.Size(); i++){
//        vec[i] = i;
//    }
    vec[0] = 2;
    vec[1] = 1;
    vec[2] = 4;
    vec[3] = 3;
    vec[4] = 5;
    cout<< "Pvot [0]: " << vec[0] << endl;
    unsigned long j = vec.Partition(0, vec.Size()-1);
    cout<< "J is " << j << " A[j] is " << vec[j] << endl;

    vec.MapPreOrder([](int& i, void*){
        cout<< i << " ";
    }, nullptr);
//    cout<<endl;
////    vec.Shuffle();
//
//
//    vec.MapPreOrder([](int& i, void*){
//        cout<< i << " ";
//    }, nullptr);
//    cout<<endl;
//    cout<< "Is sorted: "<<vec.IsSorted()<<endl;
//
//    vec.HeapSort();
//    vec.MapPreOrder([](int& i, void*){
//        cout<< i << " ";
//    }, nullptr);
//    cout<<endl;
//    cout<< "Is sorted: "<<vec.IsSorted()<<endl;

    return 0;
}

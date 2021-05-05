
#include "zlasdtest/test.hpp"

#include "zmytest/test.hpp"

/* ************************************************************************** */

#include <iostream>
#include "binarytree/binarytree.hpp"
#include "binarytree/vec/binarytreevec.hpp"
#include "binarytree/lnk/binarytreelnk.hpp"

/* ************************************************************************** */
using namespace std;
bool bteq(BinaryTree<int>& a, BinaryTree<int>& b){
    return a==b;
}

unsigned long siz(BinaryTree<int>& a){
    return a.Size();
}

int main() {
  std::cout << "Lasd Libraries 2020" << std::endl;
  //lasdtest(); // To call in the menu of your library test!
  return 0;
}

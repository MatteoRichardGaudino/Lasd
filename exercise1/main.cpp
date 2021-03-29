
#include "zlasdtest/test.hpp"

#include "zmytest/test.hpp"

#include "vector/vector.hpp"

/* ************************************************************************** */

#include <iostream>

using namespace lasd;

/* ************************************************************************** */

int main() {
  std::cout << "Lasd Libraries 2020" << std::endl;
  //lasdtest(); // To call in the menu of your library test!

  Vector<int> v();

  v.Resize(2);
  std::cout<<v[0];



  return 0;
}

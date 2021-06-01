
#include "zlasdtest/test.hpp"

#include "zmytest/test.hpp"

/* ************************************************************************** */

#include <iostream>
#include "matrix/csr/matrixcsr.hpp"

using namespace std;
using namespace lasd;

/* ************************************************************************** */

void printMx(const Matrix<int>& m){
    for (int i = 0; i < m.RowNumber(); ++i) {
        for (int j = 0; j < m.ColumnNumber(); ++j) {
            if (m.ExistsCell(i, j))
                cout<< m(i, j) << " ";
            else
                cout<< 0 << " ";
        }
        cout<< endl;
    }
}

int main() {
  std::cout << "Lasd Libraries 2020" << std::endl;
  lasdtest(); // To call in the menu of your library test!
  MatrixCSR<int> m(5,4);

//  m.RowResize(1);
//  m.ColumnResize(1);
////  m.Clear();
//  m.RowResize(5);
//  m.ColumnResize(4);

  m(0,1) = 1;
  m(1, 0) = 2;
    m(2,1) = 3;
    m(0,3) = 4;

  m(2, 2) = 5;
  m(3, 0) = 2;

  m(4,1) = 6;
  m(4,3) = 7;

//    MatrixCSR<int> cop(m);
    printMx(m);

  m.ColumnResize(5);

  m(1,4) = 8;
  m(3,4) = 9;
    cout<<endl;
    printMx(m);


    cout<<endl;
    MatrixCSR<int> cop = m;
    cout<< cop.RowNumber() << " aa " << cop.ColumnNumber() << endl;
    printMx(cop);

    cout<< cop.RowNumber() << " " << cop.ColumnNumber()<< endl;
    cout<< cop(1, 3) << "<- 1, 4";



//  for (int i = 0; i < 5; ++i) {
//    m(i, i) = i;
//  }
//  m(1, 0) = 666;
//  m.ColumnResize(0);
//  printMx(m);
  cout<< "fineee";
  return 0;
}

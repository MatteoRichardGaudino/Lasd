
#ifndef MATRIXVEC_HPP
#define MATRIXVEC_HPP

/* ************************************************************************** */

#include "../matrix.hpp"

#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class MatrixVec : virtual public Matrix<Data>, virtual private Vector<Data>{ // Must extend Matrix<Data>

private:

  // ...

protected:

  using Matrix<Data>::row;
  using Matrix<Data>::column;
  using Vector<Data>::Resize;

public:

  // Default constructor
  MatrixVec() = default;

  /* ************************************************************************ */

  // Specific constructors
  MatrixVec(unsigned long, unsigned long); // A matrix of some specified dimension

  /* ************************************************************************ */

  // Copy constructor
  MatrixVec(const Matrix<Data>&);

  // Move constructor
  MatrixVec(Matrix<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~MatrixVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  MatrixVec& operator=(const MatrixVec<Data>&);

  // Move assignment
  MatrixVec& operator=(MatrixVec<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const MatrixVec<Data>&) const noexcept;
  bool operator!=(const MatrixVec<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Matrix)

  void RowResize(unsigned long) override; // Override Matrix member
  void ColumnResize(unsigned long) override; // Override Matrix member

  bool ExistsCell(unsigned long, unsigned long) const noexcept override; // Override Matrix member (should not throw exceptions)

  Data& operator()(unsigned long, unsigned long) override; // Override Matrix member (mutable access to the element; throw out_of_range when out of range)
  const Data& operator()(unsigned long, unsigned long) const override; // Override Matrix member (immutable access to the element; throw out_of_range when out of range and length_error when not present)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override; // Override Container member

  /* ************************************************************************ */

  // Specific member functions (inherited from MappableContainer)

  using Vector<Data>::MapPreOrder;
  using Vector<Data>::MapPostOrder;
  //using typename MappableContainer<Data>::MapFunctor;
  //void MapPreOrder(const MapFunctor, void*) override; // Override MappableContainer member
  //void MapPostOrder(const MapFunctor, void*) override; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from FoldableContainer)

  using Vector<Data>::FoldPreOrder;
  using Vector<Data>::FoldPostOrder;
//  using typename FoldableContainer<Data>::FoldFunctor;
//  void FoldPreOrder(const FoldFunctor, const void*, void*) const override; // Override FoldableContainer member
//  void FoldPostOrder(const FoldFunctor, const void*, void*) const override; // Override FoldableContainer member

};

/* ************************************************************************** */

}

#include "matrixvec.cpp"

#endif

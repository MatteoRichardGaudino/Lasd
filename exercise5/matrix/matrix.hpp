
#ifndef MATRIX_HPP
#define MATRIX_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Matrix: virtual public MappableContainer<Data>,
              virtual public FoldableContainer<Data>{ // Must extend MappableContainer<Data> and FoldableContainer<Data>

private:

  // ...

protected:

  unsigned long row = 0;
  unsigned long column = 0;

public:

  // Destructor
  virtual ~Matrix() = default;

  /* ************************************************************************ */

  // Copy assignment
  Matrix& operator=(const Matrix<Data>&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  Matrix& operator=(Matrix<Data>&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Matrix<Data>&) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const Matrix<Data>&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual unsigned long RowNumber() const noexcept{ return row; }; // (concrete function should not throw exceptions)
  virtual unsigned long ColumnNumber() const noexcept { return column; }; // (concrete function should not throw exceptions)

  virtual void RowResize(unsigned long) = 0;
  virtual void ColumnResize(unsigned long ) = 0;

  virtual bool ExistsCell(unsigned long, unsigned long) const noexcept = 0; // (concrete function should not throw exceptions)

  virtual Data& operator()(unsigned long, unsigned long) = 0; // Mutable access to the element (concrete function should throw exceptions only when out of range)
  virtual const Data& operator()(unsigned long, unsigned long) const = 0; // Immutable access to the element (concrete function should throw exceptions when not present)

};

/* ************************************************************************** */

}

#include "matrix.cpp"

#endif

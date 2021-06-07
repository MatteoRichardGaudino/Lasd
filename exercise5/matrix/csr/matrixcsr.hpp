
#ifndef MATRIXCSR_HPP
#define MATRIXCSR_HPP

/* ************************************************************************** */

#include "../matrix.hpp"
#include "../../list/list.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class MatrixCSR: virtual public Matrix<Data>,
                 virtual protected List<std::pair<Data, unsigned long>>{ // Must extend Matrix<Data>

private:

  // ...

protected:

  typedef std::pair<Data, unsigned long> pair;
  using Matrix<Data>::row;
  using Matrix<Data>::column;
  using typename List<pair>::Node;
  using List<pair>::head;
  using List<pair>::size;
  Vector<Node**> R;

  void forEachElementInRow(unsigned long i, std::function<void(void)> fun) const;
public:

  // Default constructor
  MatrixCSR();

  /* ************************************************************************ */

  // Specific constructors
  MatrixCSR(unsigned long, unsigned long); // A matrix of some specified dimension

  /* ************************************************************************ */

  // Copy constructor
  MatrixCSR(const MatrixCSR<Data>&);

  // Move constructor
  MatrixCSR(MatrixCSR<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~MatrixCSR() = default;

  /* ************************************************************************ */

  // Copy assignment
  MatrixCSR& operator=(const MatrixCSR<Data>&);

  // Move assignment
  MatrixCSR& operator=(MatrixCSR<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const MatrixCSR<Data>&) const noexcept;
  bool operator!=(const MatrixCSR<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Matrix)

  void RowResize(unsigned long) override; // Override Matrix member
  void ColumnResize(unsigned long) override; // Override Matrix member

  bool ExistsCell(unsigned long, unsigned long) const noexcept override; // Override Matrix member (should not throw exceptions)

  Data& operator()(unsigned long, unsigned long); // Override Matrix member (mutable access to the element; throw out_of_range when out of range)
  const Data& operator()(unsigned long, unsigned long) const; // Override Matrix member (immutable access to the element; throw out_of_range when out of range and length_error when not present)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override; // Override Container member

  /* ************************************************************************ */

  // Specific member functions (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFunctor;
  void MapPreOrder(const MapFunctor, void*) override; // Override MappableContainer member
  void MapPostOrder(const MapFunctor, void*) override; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from FoldableContainer)

  using typename FoldableContainer<Data>::FoldFunctor;
  void FoldPreOrder(const FoldFunctor, const void*, void*) const override; // Override FoldableContainer member
  void FoldPostOrder(const FoldFunctor, const void*, void*) const override; // Override FoldableContainer member

  using Matrix<Data>::Exists;
};

/* ************************************************************************** */

}

#include "matrixcsr.cpp"

#endif

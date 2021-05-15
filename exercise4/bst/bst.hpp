
#ifndef BST_HPP
#define BST_HPP

/* ************************************************************************** */

#include "../binarytree/lnk/binarytreelnk.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BST : virtual public BinaryTreeLnk<Data> { // Must extend BinaryTreeLnk<Data>

private:

  // ...

protected:

  using BinaryTreeLnk<Data>::size;

  // ...

public:

  // Default constructor
  BST() = default;

  /* ************************************************************************ */

  // Specific constructors
  BST(const LinearContainer<Data>&); // A bst obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  BST(const BST<Data>&);

  // Move constructor
  BST(BST<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BST() = default;

  /* ************************************************************************ */

  // Copy assignment
  BST<Data>& operator=(const BST<Data>&);

  // Move assignment
  BST<Data>& operator=(BST<Data>&&) noexcept;

  /* ************************************************************************ */

    // Comparison operators
    bool operator==(const BST<Data>&) const noexcept;
    bool operator!=(const BST<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  void Insert(const Data&); // Copy of the value
  void Insert(Data&&); // Move of the value
  void Remove(const Data&);

  Data& Min() const; // (concrete function must throw std::length_error when empty)
  Data& MinNRemove(); // (concrete function must throw std::length_error when empty)
  void RemoveMin(); // (concrete function must throw std::length_error when empty)

  Data& Max() const; // (concrete function must throw std::length_error when empty)
  Data& MaxNRemove(); // (concrete function must throw std::length_error when empty)
  Data& RemoveMax(); // (concrete function must throw std::length_error when empty)

  Data& Predecessor(const Data&) const; // (concrete function must throw std::length_error when empty)
  Data& PredecessorNRemove(const Data&); // (concrete function must throw std::length_error when empty)
  void RemovePredecessor(const Data&); // (concrete function must throw std::length_error when empty)

  Data& Successor(const Data&) const; // (concrete function must throw std::length_error when empty)
  Data& SuccessorNRemove(const Data&); // (concrete function must throw std::length_error when empty)
  Data& RemoveSuccessor(const Data&); // (concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  bool Exists(argument) const noexcept override; // Override TestableContainer member

protected:

  // Auxiliary member functions

  // type DataNDelete(argument) specifiers;

  // type Detach(argument) specifiers;

  // type DetachMin(argument) specifiers;
  // type DetachMax(argument) specifiers;

  // type SkipOnLeft(argument) specifiers;
  // type SkipOnRight(argument) specifiers;

  // type FindPointerToMin(argument) specifiers;
  // type FindPointerToMax(argument) specifiers;

  // type FindPointerTo(argument) specifiers;

  // type FindPointerToPredecessor(argument) specifiers;
  // type FindPointerToSuccessor(argument) specifiers;

};

/* ************************************************************************** */

}

#include "bst.cpp"

#endif

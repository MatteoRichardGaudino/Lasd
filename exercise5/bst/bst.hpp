
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
  using typename BinaryTreeLnk<Data>::NodeLnk;
  using BinaryTreeLnk<Data>::root;

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

  const Data& Min() const; // (concrete function must throw std::length_error when empty)
  Data MinNRemove(); // (concrete function must throw std::length_error when empty)
  void RemoveMin(); // (concrete function must throw std::length_error when empty)

  const Data& Max() const; // (concrete function must throw std::length_error when empty)
  Data MaxNRemove(); // (concrete function must throw std::length_error when empty)
  void RemoveMax(); // (concrete function must throw std::length_error when empty)

  const Data& Predecessor(const Data&) const; // (concrete function must throw std::length_error when empty or not found)
  Data PredecessorNRemove(const Data&); // (concrete function must throw std::length_error when empty)
  void RemovePredecessor(const Data&); // (concrete function must throw std::length_error when empty)

  const Data& Successor(const Data&) const; // (concrete function must throw std::length_error when empty)
  Data SuccessorNRemove(const Data&); // (concrete function must throw std::length_error when empty)
  void RemoveSuccessor(const Data&); // (concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  bool Exists(const Data&) const noexcept override; // Override TestableContainer member
  using BinaryTreeLnk<Data>::Empty;

protected:

  // Auxiliary member functions

  NodeLnk* Detach(NodeLnk**);

  NodeLnk* DetachMin(NodeLnk**);
  NodeLnk* DetachMax(NodeLnk**);

  NodeLnk** FindPointerToMin(NodeLnk**) const;
  NodeLnk** FindPointerToMax(NodeLnk**) const;

  NodeLnk** FindPointerTo(NodeLnk**, const Data&) const;

  NodeLnk** FindPointerToPredecessor(NodeLnk**, const Data&) const;
  NodeLnk** FindPointerToSuccessor(NodeLnk**, const Data&) const;

};

/* ************************************************************************** */

}

#include "bst.cpp"

#endif

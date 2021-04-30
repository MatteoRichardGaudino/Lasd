
#ifndef BINARYTREEVEC_HPP
#define BINARYTREEVEC_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeVec : virtual public BinaryTree<Data>{ // Must extend BinaryTree<Data>

private:

  // ...

protected:
  // ...

struct NodeVec : virtual public BinaryTree<Data>::Node { // Must extend Node

  private:

    // ...

  protected:
    unsigned long index;
    Data element;

    // ...

  public:

    Data& Element() noexcept; // Mutable access to the element (concrete function should not throw exceptions)
    const Data& Element() const noexcept; // Immutable access to the element (concrete function should not throw exceptions)

    bool HasLeftChild() const noexcept; // (concrete function should not throw exceptions)
    bool HasRightChild() const noexcept; // (concrete function should not throw exceptions)

    NodeVec& LeftChild() const; // (concrete function must throw std::out_of_range when not existent)
    NodeVec& RightChild() const;

  };

Vector<NodeVec> elements;

public:

  // Default constructor
  BinaryTreeVec() = default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeVec(const LinearContainer<Data>&); // A binary tree obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeVec(const BinaryTreeVec<Data>&);

  // Move constructor
  BinaryTreeVec(BinaryTreeVec<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BinaryTreeVec();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeVec& operator=(const BinaryTreeVec<Data>&);

  // Move assignment
  BinaryTreeVec& operator=(BinaryTreeVec<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTreeVec<Data>&) const noexcept;
  bool operator!=(const BinaryTreeVec<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  NodeVec& Root() const override; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override; // Override Container member

  using typename MappableContainer<Data>::MapFunctor;
  void MapBreadth(const MapFunctor, void*) override; // Override BreadthMappableContainer member

  using typename FoldableContainer<Data>::FoldFunctor;
  void FoldBreadth(const FoldFunctor, const void*, void*) const override; // Override BreadthFoldableContainer member


};

/* ************************************************************************** */

}

#include "binarytreevec.cpp"

#endif

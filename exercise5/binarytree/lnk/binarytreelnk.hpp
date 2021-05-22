
#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"
/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeLnk : virtual public BinaryTree<Data> { // Must extend BinaryTree<Data>

private:

  // ...

protected:

  using BinaryTree<Data>::size;
  using typename BinaryTree<Data>::Node;

  // ...

  struct NodeLnk : Node { // Must extend Node

  private:

    // ...

  protected:
    friend class BinaryTreeLnk<Data>;
    void AuxCopyNode(NodeLnk*, const Node&);
  public:
    Data element;
    NodeLnk* right = nullptr;
    NodeLnk* left = nullptr;

    NodeLnk() = default;
    ~NodeLnk() = default;
    NodeLnk(const Data& e);
    NodeLnk(Data&& e);
    NodeLnk(const NodeLnk&);


    Data& Element() noexcept override; // Mutable access to the element (concrete function should not throw exceptions)
    const Data& Element() const noexcept override; // Immutable access to the element (concrete function should not throw exceptions)

    bool HasLeftChild() const noexcept override; // (concrete function should not throw exceptions)
    bool HasRightChild() const noexcept override; // (concrete function should not throw exceptions)

    NodeLnk& LeftChild() const override; // (concrete function must throw std::out_of_range when not existent)
    NodeLnk& RightChild() const override; // (concrete function must throw std::out_of_range when not existent)
  };

  NodeLnk* root = nullptr;
public:

  // Default constructor
  BinaryTreeLnk() = default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeLnk(const LinearContainer<Data>&); // A binary tree obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeLnk(const BinaryTreeLnk<Data>&);

  // Move constructor
  BinaryTreeLnk(BinaryTreeLnk<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTreeLnk();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeLnk& operator=(const BinaryTreeLnk<Data>&);

  // Move assignment
  BinaryTreeLnk& operator=(BinaryTreeLnk<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTreeLnk<Data>&) const noexcept;
  bool operator!=(const BinaryTreeLnk<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  NodeLnk& Root() const override; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override; // Override Container member
  using BinaryTree<Data>::Empty;
protected:
    void PostOrderClear(NodeLnk*);
    void FromLinearContainer(const LinearContainer<Data>&, NodeLnk*, unsigned long);
};

/* ************************************************************************** */
}

#include "binarytreelnk.cpp"

#endif

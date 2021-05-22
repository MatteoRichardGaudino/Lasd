
#ifndef STACKLST_HPP
#define STACKLST_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackLst : virtual protected List<Data>, virtual public Stack<Data>{ // Must extend Stack<Data> and List<Data>

private:

  // ...

protected:

  using List<Data>::size;

  // ...

public:

  // Default constructor
  StackLst() = default;

  /* ************************************************************************ */

  // Specific constructor
  StackLst(const LinearContainer<Data>& lc) : List<Data>(lc){}; // A stack obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  StackLst(const StackLst<Data>& sl) : List<Data>(sl){};

  // Move constructor
  StackLst(StackLst<Data>&& sl) noexcept : List<Data>(std::move(sl)){};

  /* ************************************************************************ */

  // Destructor
  ~StackLst();

  /* ************************************************************************ */

  // Copy assignment
  StackLst& operator=(const StackLst<Data>&);

  // Move assignment
  StackLst& operator=(StackLst&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const StackLst&) const noexcept;
  bool operator!=(const StackLst&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)

  void Push(const Data&) override; // Override Stack member (copy of the value)
  void Push(Data&&) override; // Override Stack member (move of the value)
  Data& Top() const override; // Override Stack member (must throw std::length_error when empty)
  void Pop() override; // Override Stack member (must throw std::length_error when empty)
  Data TopNPop() override; // Override Stack member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override; // Override Container member

};

/* ************************************************************************** */

}

#include "stacklst.cpp"

#endif

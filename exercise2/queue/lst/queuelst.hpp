
#ifndef QUEUELST_HPP
#define QUEUELST_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class QueueLst : public virtual Queue<Data>, protected virtual List<Data>{ // Must extend Queue<Data> and List<Data>

private:

  // ...

protected:

  using List<Data>::size;

  // ...

public:

  // Default constructor
  QueueLst() = default;

  /* ************************************************************************ */

  // Specific constructor
  QueueLst(const LinearContainer<Data>& lc) : List<Data>(lc){}; // A queue obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  QueueLst(const QueueLst<Data>& ql) : List<Data>(ql){};

  // Move constructor
  QueueLst(QueueLst<Data>&& ql) noexcept : List<Data>(std::move(ql)){};

  /* ************************************************************************ */

  // Destructor
  ~QueueLst() = default;

  /* ************************************************************************ */

  // Copy assignment
  QueueLst& operator=(const QueueLst<Data>&);

  // Move assignment
  QueueLst& operator=(QueueLst<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const QueueLst<Data>&) const noexcept;
  bool operator!=(const QueueLst<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Queue)

  void Enqueue(const Data&) override; // Override Queue member (copy of the value)
  void Enqueue(Data&&) override; // Override Queue member (move of the value)
  Data& Head() const override; // Override Queue member (must throw std::length_error when empty)
  void Dequeue() override; // Override Queue member (must throw std::length_error when empty)
  Data HeadNDequeue() override; // Override Queue member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override; // Override Container member

};

/* ************************************************************************** */

}

#include "queuelst.cpp"

#endif

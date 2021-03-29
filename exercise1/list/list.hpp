
#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class List: virtual public LinearContainer<Data>,
            virtual public MappableContainer<Data>,
            virtual public FoldableContainer<Data>{ // Must extend LinearContainer<Data>, MappableContainer<Data>, and FoldableContainer<Data>

private:

  // ...

protected:

  using LinearContainer<Data>::size;

  struct Node{

    // Data
    // ...
    Data data;
    Node* next;

    /* ********************************************************************** */

    // Specific constructors
    // ...
    Node() = default;

    Node(const Data& d){
        data = d;
        next = nullptr;
    }

    Node(Data&& d) noexcept {
        std::swap(data, d);
        next = nullptr;
    }

    /* ********************************************************************** */

    // Copy constructor
    // ...
    Node(const Node& node){
        data = node.data;
        next = node.next;
    }

    // Move constructor
    // ...
    Node(Node&& node){
        std::swap(data, node.data);
        std::swap(next, node.next);
    }

    /* ********************************************************************** */

    // Destructor
    // ...
    virtual ~Node() = default;

    /* ********************************************************************** */

    // Comparison operators
    // ...

    bool operator==(const Node& node) const noexcept{
        return (this->data == node.data) && (this->next == node.next);
    }
    bool operator!=(const Node& node) const noexcept{
        return !(*this == node);
    }

    /* ********************************************************************** */

    // Specific member functions

    // ...

  };

  Node* head = nullptr;

  // ...

public:

  // Default constructor
  List() = default;

  /* ************************************************************************ */

  // Specific constructor
  List(const LinearContainer<Data>&); // A list obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  List(const List<Data>&);

  // Move constructor
  List(List<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~List();

  /* ************************************************************************ */

  // Copy assignment
  List& operator=(const List<Data>&);

  // Move assignment
  List& operator=(List<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(List<Data>&) const noexcept;
  bool operator!=(List<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  void InsertAtFront(const Data&); // Copy of the value
  void InsertAtFront(Data&&); // Move of the value
  void RemoveFromFront(); // (must throw std::length_error when empty)
  Data& FrontNRemove(); // (must throw std::length_error when empty)

  void InsertAtBack(const Data&); // Copy of the value
  void InsertAtBack(Data&&); // Move of the value

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override; // Override Container member

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  Data& Front() const override; // Override LinearContainer member (must throw std::length_error when empty)
  Data& Back() const override; // Override LinearContainer member (must throw std::length_error when empty)

  Data& operator[](const unsigned long) const noexcept override; // Override LinearContainer member (must throw std::out_of_range when out of range)

  /* ************************************************************************ */

  // Specific member functions (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFunctor;

  void MapPreOrder(const MapFunctor, void *) override; // Override MappableContainer member
  void MapPostOrder(const MapFunctor, void *) override; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from FoldableContainer)

  using typename FoldableContainer<Data>::FoldFunctor;

  void FoldPreOrder(const FoldFunctor, const void*, void*) const override; // Override FoldableContainer member
  void FoldPostOrder(const FoldFunctor, const void*, void*) const override; // Override FoldableContainer member

protected:

  // Auxiliary member functions (for MappableContainer)

  // type MapPreOrder(arguments) specifiers; // Accessory function executing from one point of the list onwards
  // type MapPostOrder(arguments) specifiers; // Accessory function executing from one point of the list onwards

  /* ************************************************************************ */

  // Auxiliary member functions (for FoldableContainer)

  // type FoldPreOrder(arguments) specifiers; // Accessory function executing from one point of the list onwards
  // type FoldPostOrder(arguments) specifiers; // Accessory function executing from one point of the list onwards

};

/* ************************************************************************** */

}

#include "list.cpp"

#endif

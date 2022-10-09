
#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class List : virtual public LinearContainer<Data>,
             virtual public PreOrderMappableContainer<Data>,
             virtual public PostOrderMappableContainer<Data>,
             virtual public PreOrderFoldableContainer<Data>,
             virtual public PostOrderFoldableContainer<Data> { // Must extend LinearContainer<Data>,
                                                               //  PreOrderMappableContainer<Data>,
                                                               //  PostOrderMappableContainer<Data>,
                                                               //  PreOrderFoldableContainer<Data>,
                                                               //  PostOrderFoldableContainer<Data>


private:

protected:

  using LinearContainer<Data>::size;

  struct Node
  {

    // Data

    Data element {};
    struct Node* next = nullptr;

    /* ********************************************************************** */
    // Default constructor - CHANGED
    Node() = default ;


    // Specific constructor (copy) - CHANGED
    Node(const Data& var) {
        element = var;
        next = nullptr ;
    }

    /*// Specific constructor (move) - CHANGED
    Node(Data&& var) {
        std::swap(element, var);
        next = nullptr ;
    }*/
    /* ********************************************************************** */

    // Copy constructor
    Node(const Node& oldNode) {
      element = oldNode.element;
      next = oldNode.next ;

    }

    // Move constructor
    Node(Node&& oldNode) noexcept {
        std::swap(element, oldNode.element);
        std::swap(next, oldNode.next);
    }

    /* ********************************************************************** */

    // Destructor - CHANGED
    virtual ~Node() = default ;

    /* ********************************************************************** */

    // Comparison operators
    bool operator==(const Node& par) const noexcept {
        if ( (par.element) == element ){
          return true ;
        }
        else
        {
          return false ;
        }
    }

    bool operator!=(const Node& par) const noexcept {
        if ( (par.element) != element ){
          return true ;
        }
        else
        {
          return false ;
        }
    }

    /* ********************************************************************** */

    // Specific member functions

    void InsertIntoNode (const Data& var) noexcept {
        element = var ;
    }

  };


  struct Node* head = nullptr ;
  struct Node* tail = nullptr ;

public:

  // Default constructor
  List();

  /* ************************************************************************ */

  // Specific constructor

  // A list obtained from a LinearContainer
  List(const LinearContainer<Data>&);

  /* ************************************************************************ */

  // Copy constructor
  List(const List&);

  // Move constructor
  List(List&&) noexcept ;

  /* ************************************************************************ */

  // Destructor
  virtual ~List() ;

  /* ************************************************************************ */

  // Copy assignment
  List& operator=(const List&);

  // Move assignment
  List& operator=(List&&) noexcept ;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const List&) const noexcept ;
  inline bool operator!=(const List&) const noexcept ;

  /* ************************************************************************ */

  // Specific member functions

  void InsertAtFront(const Data&) ; // Copy of the value
  void InsertAtFront(Data&&) noexcept ; // Move of the value
  void RemoveFromFront() ; // (must throw std::length_error when empty)
  Data FrontNRemove(); // (must throw std::length_error when empty)

  void InsertAtBack(const Data&) ; // Copy of the value
  void InsertAtBack(Data&&) noexcept ; // Move of the value

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override; // Override Container member

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  Data& Front() const override; // Override LinearContainer member (must throw std::length_error when empty)
  Data& Back() const override; // Override LinearContainer member (must throw std::length_error when empty)

  Data& operator[](const ulong) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)

  /* ************************************************************************ */

  // Specific member functions (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFunctor;

  void Map(const MapFunctor, void*) override; // Override MappableContainer member - CHANGED

  /* ************************************************************************ */

  // Specific member functions (inherited from PreOrderMappableContainer)

  void MapPreOrder(const MapFunctor, void*) override; // Override PreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from PostOrderMappableContainer)

  void MapPostOrder(const MapFunctor, void*) override; // Override PostOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from FoldableContainer)

  using typename FoldableContainer<Data>::FoldFunctor;

  void Fold(const FoldFunctor, const void*, void*) const override; // Override FoldableContainer member - CHANGED

  /* ************************************************************************ */

  // Specific member functions (inherited from PreOrderFoldableContainer)

  void FoldPreOrder(const FoldFunctor, const void*, void*) const override; // Override FoldableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from PostOrderFoldableContainer)

  void FoldPostOrder(const FoldFunctor, const void*, void*) const override; // Override FoldableContainer member

protected:

  // Auxiliary member functions (for PreOrderMappableContainer & PostOrderMappableContainer)

  void MapPreOrder(const MapFunctor, void*, Node*) ; // Accessory function executing from one point of the list onwards
  void MapPostOrder(const MapFunctor, void*, Node*) ; // Accessory function executing from one point of the list onwards

  /* ************************************************************************ */

  // Auxiliary member functions (for PreOrderFoldableContainer & PostOrderFoldableContainer)

  void FoldPreOrder(const FoldFunctor, const void*, void*, Node*) const; // Accessory function executing from one point of the list onwards
  void FoldPostOrder(const FoldFunctor, const void*, void*, Node*) const; // Accessory function executing from one point of the list onwards

};

/* ************************************************************************** */

}

#include "list.cpp"

#endif

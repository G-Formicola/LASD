
#ifndef BST_HPP
#define BST_HPP

/* ************************************************************************** */

#include "../binarytree/lnk/binarytreelnk.hpp"
#include "../binarytree/binarytree.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BST : virtual public BinaryTreeLnk<Data>, virtual public DictionaryContainer<Data> { // Must extend BinaryTreeLnk<Data>

private:

protected:

  using typename BinaryTreeLnk<Data>::NodeLnk;
  using BinaryTreeLnk<Data>::root;
  using BinaryTreeLnk<Data>::size;

public:

  // Default constructor
  BST() = default;

  /* ************************************************************************ */

  // Specific constructors
  BST(const LinearContainer<Data>&) ; // A bst obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  BST(const BST&) ;

  // Move constructor
  BST(BST&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BST() = default;

  /* ************************************************************************ */

  // Copy assignment
  BST& operator=(const BST&) ;

  // Move assignment
  BST& operator=(BST&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BST&) const noexcept;
  inline bool operator!=(const BST& bsT) const noexcept{
    return (!(*this==bsT));
  }

  /* ************************************************************************ */

  // Specific member functions

  const Data& Min() const ; // (concrete function must throw std::length_error when empty)
  Data MinNRemove() ; // (concrete function must throw std::length_error when empty)
  void RemoveMin() ; // (concrete function must throw std::length_error when empty)

  const Data& Max() const; // (concrete function must throw std::length_error when empty)
  Data MaxNRemove() ; // (concrete function must throw std::length_error when empty)
  void RemoveMax() ; // (concrete function must throw std::length_error when empty)

  const Data& Predecessor(const Data&) const; // (concrete function must throw std::length_error when not found)
  Data PredecessorNRemove(const Data&) ; // (concrete function must throw std::length_error when not found)
  void RemovePredecessor(const Data&) ; // (concrete function must throw std::length_error when not found)

  const Data& Successor(const Data&) const; // (concrete function must throw std::length_error when not found)
  Data SuccessorNRemove(const Data&) ; // (concrete function must throw std::length_error when not found)
  void RemoveSuccessor(const Data&) ; // (concrete function must throw std::length_error when not found)

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data&) override; // Override DictionaryContainer member (Copy of the value)
  bool Insert(Data&&) noexcept override; // Override DictionaryContainer member (Move of the value)
  bool Remove(const Data&) noexcept override; // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  bool Exists(const Data&) const noexcept override; // Override TestableContainer member


protected:

  // Auxiliary member functions

  Data DataNDelete(NodeLnk*) noexcept ;

  NodeLnk* Detach(NodeLnk**) noexcept ;

  NodeLnk* DetachMin(NodeLnk**) noexcept ;
  NodeLnk* DetachMax(NodeLnk**) noexcept ;

  /*
  void Skip2Left() noexcept;
  void Skip2Right() noexcept;
  */

  NodeLnk* const * FindPointerToMin(NodeLnk* const * ) const noexcept ; // Both mutable & unmutable versions
  NodeLnk** FindPointerToMin(NodeLnk** ) noexcept ; // Both mutable & unmutable versions
  NodeLnk* const * FindPointerToMax(NodeLnk* const * ) const noexcept; // Both mutable & unmutable versions
  NodeLnk** FindPointerToMax(NodeLnk** ) noexcept; // Both mutable & unmutable versions

  NodeLnk* const * FindPointerTo(NodeLnk* const *, const Data&) const noexcept; // Both mutable & unmutable versions
  NodeLnk** FindPointerTo(NodeLnk**, const Data&) noexcept; // Both mutable & unmutable versions

  NodeLnk* const *  FindPointerToPredecessor(NodeLnk* const * , const Data&) const noexcept; // Both mutable & unmutable versions
  NodeLnk**  FindPointerToPredecessor(NodeLnk** , const Data&) noexcept; // Both mutable & unmutable versions
  NodeLnk* const * FindPointerToSuccessor(NodeLnk* const * , const Data&) const noexcept; // Both mutable & unmutable versions
  NodeLnk** FindPointerToSuccessor(NodeLnk** , const Data&) noexcept; // Both mutable & unmutable versions

};

/* ************************************************************************** */

}

#include "bst.cpp"

#endif


#ifndef BINARYTREEVEC_HPP
#define BINARYTREEVEC_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeVec : virtual public BinaryTree<Data> {
                      // Must extend BinaryTree<Data>

private:

  // ...

protected:

  using BinaryTree<Data>::size;

  // ...

  struct NodeVec : public BinaryTree<Data>::Node { // Must extend Node

  private:

    // ...

  protected:

    using BinaryTree<Data>::Node::element;
    ulong index {};
    lasd::Vector<struct NodeVec*>* handleNodesVector = nullptr ;


  public:

    friend class BinaryTreeVec<Data>;

    /* ********************************************************************** */
    //Specific constructor
    NodeVec(const Data& elem, const ulong ind, lasd::Vector<struct NodeVec*>* handle){
      element = elem ;
      index = ind ;
      handleNodesVector = handle;
    }

    // Destructor
    virtual ~NodeVec() = default;
    /* ********************************************************************** */

    /*
    Non utilizzate
    // Copy assignment
    NodeVec& operator=(const Node&) ; // Copy assignment of abstract types should not be possible.

    // Move assignment
    Node& operator=(Node&&) noexcept ; // Move assignment of abstract types should not be possible.
    */

    /* ********************************************************************** */

    // (concrete function should not throw exceptions)
    bool HasLeftChild() const noexcept {
      ulong sx = (2*index)+1 ;
      if ( (*handleNodesVector).Size() <= sx ){
        return false ;
      }
      else
      {
        if ( (*handleNodesVector)[sx] != nullptr )
          return true ;
        else
          return false ;
      }
    }

    // (concrete function should not throw exceptions)
    bool HasRightChild() const noexcept {
      ulong dx = 2*(index+1) ;
      if ( (*handleNodesVector).Size() <= dx ){
        return false ;
      }
      else
      {
        if ( (*handleNodesVector)[dx] != nullptr )
          return true ;
        else
          return false ;
      }
    }

    // (concrete function must throw std::out_of_range when not existent)
    NodeVec& LeftChild() const {

      if (HasLeftChild())
      {
        ulong sx = (2*index)+1 ;
        return (*(*handleNodesVector)[sx]);
      }
      else
      {
        throw std::out_of_range("Access to a non-existent node !");
      }

    }

    // (concrete function must throw std::out_of_range when not existent)
    NodeVec& RightChild() const {

      if (HasRightChild())
      {
        ulong dx = 2*(index+1);
        return (*(*handleNodesVector)[dx]);
      }
      else
      {
        throw std::out_of_range("Access to a non-existent node !");
      }
    }


  };

  lasd::Vector<struct NodeVec*> nodesVector;

public:

  // Default constructor
  BinaryTreeVec() = default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeVec(const LinearContainer<Data>&) ; // A binary tree obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeVec(const BinaryTreeVec&) ;

  // Move constructor
  BinaryTreeVec(BinaryTreeVec&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTreeVec() ;

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeVec& operator=(const BinaryTreeVec&) ;

  // Move assignment
  BinaryTreeVec& operator=(BinaryTreeVec&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  //bool operator==(const BinaryTreeVec&) const noexcept;
  //bool operator!=(const BinaryTreeVec&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  NodeVec& Root() const override; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override; // Override Container member

  /* ************************************************************************ */

  // Specific member functions (inherited from BreadthMappableContainer)

  using typename MappableContainer<Data>::MapFunctor;

  void MapBreadth(const MapFunctor, void*) override; // Override BreadthMappableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from BreadthFoldableContainer)

  using typename FoldableContainer<Data>::FoldFunctor;

  void FoldBreadth(const FoldFunctor, const void*, void*) const override; // Override BreadthFoldableContainer member

};

/* ************************************************************************** */

}

#include "binarytreevec.cpp"

#endif

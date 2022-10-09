
#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeLnk : virtual public BinaryTree<Data>{
                      // Must extend BinaryTree<Data>

private:

protected:

  using BinaryTree<Data>::size;


  struct NodeLnk : public BinaryTree<Data>::Node { // Must extend Node

  private:

  protected:

    /*using BinaryTree<Data>::Node::element;
    struct NodeLnk* sx = nullptr;
    struct NodeLnk* dx = nullptr;*/


  public:

    friend class BinaryTreeLnk<Data>;
    //friend class lasd::BST<Data>; not working
    using BinaryTree<Data>::Node::element;
    struct NodeLnk* sx = nullptr;
    struct NodeLnk* dx = nullptr;

    /* ********************************************************************** */

    NodeLnk() = default ;

    // Specific constructor
    NodeLnk(const Data& elem){
      element = elem ;
    }

    // Specific constructor
    NodeLnk(Data&& elem){
      element = std::move(elem) ;
    }

    // Destructor
    virtual ~NodeLnk() {
      if (sx != nullptr) delete sx ;
      if (dx != nullptr) delete dx ;
    }

    /* ********************************************************************** */


    // Copy assignment
    // Copy assignment of abstract types should not be possible.
    NodeLnk& operator=(const NodeLnk& node){
        element = node.element ;
        if (node.sx != nullptr){
          sx = new NodeLnk();
          *sx = *node.sx ;
        }
        else
        {
          sx = nullptr ;
        }
        if (node.dx != nullptr){
          dx = new NodeLnk();
          *dx = *node.dx ;
        }
        else
        {
          dx = nullptr ;
        }
        return *this;
    }

    // Move assignment
    // Move assignment of abstract types should not be possible.
    NodeLnk& operator=(NodeLnk&& node) noexcept {
        element = std::move(node.element);
        if (node.sx != nullptr){
          sx = new NodeLnk();
          *sx = std::move(*node.sx) ;
        }
        else
        {
          sx = nullptr ;
        }
        if (node.dx != nullptr){
          dx = new NodeLnk();
          *dx = std::move(*node.dx) ;
        }
        else
        {
          dx = nullptr ;
        }
        return *this;
    }


    /* ********************************************************************** */


    // (function should not throw exceptions)
    bool HasLeftChild() const noexcept {
      return (sx!=nullptr);
    }

    // (function should not throw exceptions)
    bool HasRightChild() const noexcept {
      return (dx!=nullptr);
    }

    // (function must throw std::out_of_range when not existent)
    NodeLnk& LeftChild() const {
      if (HasLeftChild())
        return *sx ;
      else
        throw std::out_of_range("Access to a non-existent node !");
    }

    // (function must throw std::out_of_range when not existent)
    NodeLnk& RightChild() const {
      if (HasRightChild())
        return *dx ;
      else
        throw std::out_of_range("Access to a non-existent node !");
    }

  };

  struct NodeLnk* root = nullptr;

public:

  // Default constructor
  BinaryTreeLnk() = default;

  /* ************************************************************************ */

  //++
  // Specific constructors
  // A binary tree obtained from a LinearContainer
  BinaryTreeLnk(const LinearContainer<Data>&) ;

  /* ************************************************************************ */

  //++
  // Copy constructor
  BinaryTreeLnk(const BinaryTreeLnk&) ;

  //
  // Move constructor
  BinaryTreeLnk(BinaryTreeLnk&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTreeLnk() ;

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeLnk& operator=(const BinaryTreeLnk&) ;

  // Move assignment
  BinaryTreeLnk& operator=(BinaryTreeLnk&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTreeLnk&) const noexcept ;
  inline bool operator!=(const BinaryTreeLnk& bt) const noexcept {
    return (!(*this==bt));
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  NodeLnk& Root() const override; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override; // Override Container member

protected:

  // Auxiliary member functions
  NodeLnk* BuildBT(const NodeLnk*) ; // From a binarytree

  NodeLnk* BuildBT(NodeLnk*, const LinearContainer<Data>&, const ulong); // From a LinearContainer

};

/* ************************************************************************** */

}

#include "binarytreelnk.cpp"

#endif

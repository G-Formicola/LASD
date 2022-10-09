
#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

/* ************************************************************************** */

#include <random>

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Hash {

public:

  ulong operator()(const Data&) const noexcept; // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class HashTable : virtual public DictionaryContainer<Data>,
                  virtual public MappableContainer<Data>,
                  virtual public FoldableContainer<Data>{
                  // Must extend DictionaryContainer<Data>,
                  //             MappableContainer<Data>,
                  //             FoldableContainer<Data>

private:

  // ...

protected:

  using DictionaryContainer<Data>::size;
  Hash<Data> encodingHash {} ;
  ulong sizeOfTable ; // Primo oppure una potenza di un primo (M)
  unsigned long long a  ; // Random da 1 a Prime-1
  unsigned long long b ; // Random da 0 a Prime-1
  const unsigned long long prime = 4295032837 ; // Numero primo (P) maggiore di 2^32, cioè la cardinalità N dell'insieme delle chiavi ulong restituite da hashkey. Ed N sarà maggiore di sizeOfTable (M)

public:

  //Constructor
  HashTable() ;

  // Destructor
  virtual ~HashTable() = default;

  /* ************************************************************************ */

  // Copy assignment
  HashTable& operator=(const HashTable&) = delete ; // Copy assignment of abstract types should not be possible.

  // Move assignment
  HashTable& operator=(HashTable&&) noexcept = delete ; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTable&) const noexcept = delete; // Comparison of abstract binary tree is possible.
  bool operator!=(const HashTable&) const noexcept = delete; // Comparison of abstract binary tree is possible.

  /* ************************************************************************ */

  // Specific member function

  virtual void Resize(const ulong) = 0 ; // Resize the hashtable to a given size

protected:

  //Copy Constructor
  HashTable(const HashTable&) ;
  //Move Constructor
  HashTable(HashTable&&) noexcept ;

  // Auxiliary member functions
  // Funzione di trasformazione del dato in chiave e della chiave in indice
  inline ulong HashKey(const Data& dat) const noexcept{
    return HashKey(encodingHash(dat));
  }

  // Funzione di indirizzamento della chiave nella tabella : ((a*k + b) % p )% m
  inline ulong HashKey(const ulong k) const noexcept{
    unsigned long long result = ( ((a*k) + b) % prime ) % sizeOfTable ;
    return static_cast<ulong>(result) ;
  }



};

/* ************************************************************************** */

}

#include "hashtable.cpp"

#endif

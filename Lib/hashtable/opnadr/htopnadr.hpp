
#ifndef HTOPNADR_HPP
#define HTOPNADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HashTableOpnAdr : virtual public HashTable<Data> { // Must extend HashTable<Data>

private:

  // ...

protected:

  using HashTable<Data>::size;
  using HashTable<Data>::sizeOfTable;
  using HashTable<Data>::encodingHash;
  using HashTable<Data>::HashKey;
  using HashTable<Data>::a;
  using HashTable<Data>::b;
  using HashTable<Data>::prime;

  unsigned long long a2 ; // Random da 1 a Prime-1
  unsigned long long b2 ; // Random da 0 a Prime-1

  lasd::Vector<unsigned short>* flagVector = nullptr ;
  lasd::Vector<Data>* table = nullptr ;



public:

  // Default constructor
  HashTableOpnAdr() ;

  /* ************************************************************************ */

  // Specific constructors
  HashTableOpnAdr(const ulong) ; // A hash table of a given size
  HashTableOpnAdr(const LinearContainer<Data>&) ; // A hash table obtained from a LinearContainer
  HashTableOpnAdr(const ulong, const LinearContainer<Data>&) ; // A hash table of a given size obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  HashTableOpnAdr(const HashTableOpnAdr&) ;

  // Move constructor
  HashTableOpnAdr(HashTableOpnAdr&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~HashTableOpnAdr() ;

  /* ************************************************************************ */

  // Copy assignment
  HashTableOpnAdr& operator=(const HashTableOpnAdr&) ;

  // Move assignment
  HashTableOpnAdr& operator=(HashTableOpnAdr&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTableOpnAdr&) const noexcept;
  inline bool operator!=(const HashTableOpnAdr& hashT) const noexcept{
    return (!(*this==hashT));
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from HashTable)

  void Resize(const ulong) override; // Resize the hashtable to a given size

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data&) override; // Override DictionaryContainer member (Copy of the value)
  bool Insert(Data&&) noexcept override; // Override DictionaryContainer member (Move of the value)
  bool Remove(const Data&) noexcept override; // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  bool Exists(const Data&) const noexcept override; // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFunctor;

  void Map(const MapFunctor, void*) override; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from FoldableContainer)

  using typename FoldableContainer<Data>::FoldFunctor;

  void Fold(const FoldFunctor, const void*, void*) const override; // Override FoldableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override; // Override Container member

protected:

  // Auxiliary member functions

  ulong HashKey(const Data&, const ulong) const noexcept ;
  ulong HashKey2(const Data&) const noexcept ;
  ulong Find(const Data&, bool*) const noexcept;
  bool Remove(const Data&, const ulong) noexcept ;
  ulong ComputeTheRealSize(const ulong) const noexcept ;
  void InitA2andB2() noexcept ;

};

/* ************************************************************************** */

}

#include "htopnadr.cpp"

#endif

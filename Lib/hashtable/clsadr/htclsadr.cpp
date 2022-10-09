
namespace lasd {

/* ************************************************************************** */

// Default constructor
template<typename Data>
HashTableClsAdr<Data>::HashTableClsAdr() : HashTable<Data>::HashTable() {
  table = new Vector<BST<Data>>(sizeOfTable);
}

/* ************************************************************************** */


// Specific constructors
// A hash table of a given size
template<typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const ulong userSize) : HashTable<Data>::HashTable() {
  sizeOfTable = userSize;
  table = new Vector<BST<Data>>(sizeOfTable);
}

// A hash table obtained from a LinearContainer
template<typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const LinearContainer<Data>& cont) : HashTable<Data>::HashTable() {
  table = new Vector<BST<Data>>(sizeOfTable);
  DictionaryContainer<Data>::Insert(cont);
}

// A hash table of a given size obtained from a LinearContainer
template<typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const ulong userSize, const LinearContainer<Data>& cont) : HashTable<Data>::HashTable() {
  sizeOfTable = userSize;
  table = new Vector<BST<Data>>(sizeOfTable);
  DictionaryContainer<Data>::Insert(cont);
}

/* ************************************************************************ */

// Copy constructor
template<typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const HashTableClsAdr<Data>& hashT) : HashTable<Data>::HashTable(hashT) {
  table = new Vector<BST<Data>>(*(hashT.table));
}

// Move constructor
template<typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(HashTableClsAdr<Data>&& hashT) noexcept : HashTable<Data>::HashTable(hashT) {
  std::swap(table,hashT.table);
}

/* ************************************************************************ */

// Destructor
template<typename Data>
HashTableClsAdr<Data>::~HashTableClsAdr(){
  if (table != nullptr)
    delete table ;
}

/* ************************************************************************ */

// Copy assignment
template<typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(const HashTableClsAdr<Data>& hashT) {
  HashTableClsAdr<Data>* tmpHT = new HashTableClsAdr<Data>(hashT);
  std::swap(*this,*tmpHT);
  delete tmpHT;
  return *this;
}

// Move assignment
template<typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(HashTableClsAdr<Data>&& hashT) noexcept{
  std::swap(size, hashT.size);
  std::swap(encodingHash, hashT.encodingHash);
  std::swap(sizeOfTable,hashT.sizeOfTable);
  std::swap(a, hashT.a);
  std::swap(b, hashT.b);
  std::swap(table,hashT.table);
  return *this;
}

/* ************************************************************************ */

// Comparison operators
template<typename Data>
bool HashTableClsAdr<Data>::operator==(const HashTableClsAdr<Data>& hashT) const noexcept {
  if (size != hashT.size){
    return false ;
  }
  else
  {
    if (size == 0){
      return true ;
    }
    else
    {
      for (ulong i=0 ; i<sizeOfTable ; i++){
        BTInOrderIterator<Data> tmpIter((*table)[i]);
        while(!tmpIter.Terminated()){
          if (!hashT.Exists(*tmpIter)){
            return false ;
          }
          ++tmpIter;
        }
      }
      return true ;
    }
  }
}


/* ************************************************************************ */

// Specific member functions (inherited from HashTable)
// Resize the hashtable to a given size
template<typename Data>
void HashTableClsAdr<Data>::Resize(const ulong newSizeOfTable) {
  HashTableClsAdr<Data>* tmpHT = new HashTableClsAdr<Data>(newSizeOfTable);
  for (ulong i=0 ; i<sizeOfTable ; i++){
    BTBreadthIterator<Data> tmpIter((*table)[i]);
    while(!tmpIter.Terminated()){
      tmpHT->Insert(*tmpIter);
      ++tmpIter;
    }
  }
  std::swap(*this,*tmpHT);
  delete tmpHT;
}

/* ************************************************************************ */

// Specific member functions (inherited from DictionaryContainer)
// Override DictionaryContainer member (Copy of the value)
template<typename Data>
bool HashTableClsAdr<Data>::Insert(const Data& dat) {
  ulong slot = HashKey(dat);
  bool result = ( (*table)[slot].Insert(dat) );
  if ( result == true ){
    size = size + 1;
    return true ;
  }
  else
  {
    return false ;
  }
}

// Override DictionaryContainer member (Move of the value)
template<typename Data>
bool HashTableClsAdr<Data>::Insert(Data&& dat) noexcept {
  ulong slot = HashKey(dat);
  bool result = ( (*table)[slot].Insert(std::move(dat)) );
  if ( result == true ){
    size = size + 1;
    return true ;
  }
  else
  {
    return false ;
  }
}

// Override DictionaryContainer member
template<typename Data>
bool HashTableClsAdr<Data>::Remove(const Data& dat) noexcept {
  ulong slot = HashKey(dat);
  bool result = ( (*table)[slot].Remove(dat) );
  if ( result == true ){
    size = size - 1;
    return true ;
  }
  else
  {
    return false ;
  }
}

/* ************************************************************************ */

// Specific member functions (inherited from TestableContainer)
// Override TestableContainer member

template<typename Data>
bool HashTableClsAdr<Data>::Exists(const Data& dat) const noexcept {
  ulong slot = HashKey(dat);
  return ( (*table)[slot].Exists(dat) );
}

/* ************************************************************************ */

// Specific member functions (inherited from MappableContainer)
// Override MappableContainer member

template<typename Data>
void HashTableClsAdr<Data>::Map(const MapFunctor fun, void* par) {
  if(size>0 && table != nullptr)
  {
    for ( ulong i=0 ; i<sizeOfTable ; i++){
      (*table)[i].Map(fun, par);
    }
  }
}
/* ************************************************************************ */

// Specific member functions (inherited from FoldableContainer)
// Override FoldableContainer member

template<typename Data>
void HashTableClsAdr<Data>::Fold(const FoldFunctor fun, const void* par1, void* par2) const {
  if(size>0 && table != nullptr)
  {
    for ( ulong i=0 ; i<sizeOfTable ; i++){
      (*table)[i].Fold(fun, par1, par2);
    }
  }
}

/* ************************************************************************ */

// Specific member functions (inherited from Container)
// Override Container member
template<typename Data>
void HashTableClsAdr<Data>::Clear() {
  HashTableClsAdr<Data>* tmpHT = new HashTableClsAdr<Data>();
  std::swap(*this,*tmpHT);
  delete tmpHT;
}


/* ************************************************************************ */


}

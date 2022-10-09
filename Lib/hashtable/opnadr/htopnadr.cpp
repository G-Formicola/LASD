
namespace lasd {

/* ************************************************************************** */

// Default constructor
template<typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr() : HashTable<Data>::HashTable() {
  InitA2andB2();
  flagVector = new Vector<unsigned short>(sizeOfTable);
  table = new Vector<Data>(sizeOfTable);
}

/* ************************************************************************** */


// Specific constructors
// A hash table of a given size
template<typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const ulong userSize) : HashTable<Data>::HashTable() {
  InitA2andB2();
  sizeOfTable = ComputeTheRealSize(userSize); // Da fixare
  flagVector = new Vector<unsigned short>(sizeOfTable);
  table = new Vector<Data>(sizeOfTable);
}

// A hash table obtained from a LinearContainer
template<typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const LinearContainer<Data>& cont) : HashTable<Data>::HashTable() {
  InitA2andB2();
  flagVector = new Vector<unsigned short>(sizeOfTable);
  table = new Vector<Data>(sizeOfTable);
  DictionaryContainer<Data>::Insert(cont);
}

// A hash table of a given size obtained from a LinearContainer
template<typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const ulong userSize, const LinearContainer<Data>& cont) : HashTable<Data>::HashTable() {
  InitA2andB2();
  sizeOfTable = ComputeTheRealSize(userSize); // Da fixare
  flagVector = new Vector<unsigned short>(sizeOfTable);
  table = new Vector<Data>(sizeOfTable);
  DictionaryContainer<Data>::Insert(cont);
}

/* ************************************************************************ */

// Copy constructor
template<typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const HashTableOpnAdr<Data>& hashT) : HashTable<Data>::HashTable(hashT) {
  flagVector = new Vector<unsigned short>(*(hashT.flagVector));
  table = new Vector<Data>(*(hashT.table));
  a2 = hashT.a2 ;
  b2 = hashT.b2 ;
}

// Move constructor
template<typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(HashTableOpnAdr<Data>&& hashT) noexcept : HashTable<Data>::HashTable(hashT) {
  std::swap(flagVector,hashT.flagVector);
  std::swap(table,hashT.table);
  std::swap(a2,hashT.a2);
  std::swap(b2,hashT.b2);
}

/* ************************************************************************ */

// Destructor
template<typename Data>
HashTableOpnAdr<Data>::~HashTableOpnAdr(){
  if (table != nullptr)
    delete table ;
  if (flagVector != nullptr)
    delete flagVector ;
}

/* ************************************************************************ */

// Copy assignment
template<typename Data>
HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(const HashTableOpnAdr<Data>& hashT) {
  HashTableOpnAdr<Data>* tmpHT = new HashTableOpnAdr<Data>(hashT);
  std::swap(*this,*tmpHT);
  delete tmpHT;
  return *this;
}

// Move assignment
template<typename Data>
HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(HashTableOpnAdr<Data>&& hashT) noexcept{
  std::swap(size, hashT.size);
  std::swap(encodingHash, hashT.encodingHash);
  std::swap(sizeOfTable,hashT.sizeOfTable);
  std::swap(a, hashT.a);
  std::swap(b, hashT.b);
  std::swap(flagVector,hashT.flagVector);
  std::swap(table,hashT.table);
  std::swap(a2,hashT.a2);
  std::swap(b2,hashT.b2);
  return *this;
}

/* ************************************************************************ */

// Comparison operators
template<typename Data>
bool HashTableOpnAdr<Data>::operator==(const HashTableOpnAdr<Data>& hashT) const noexcept {
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
        if ((*flagVector)[i]==1){
          if ( ! hashT.Exists((*table)[i]) ) {
            return false ;
          }
        }
      }
      return true ;
    }
  }
}


/* ************************************************************************ */

// Specific member functions (inherited from HashTable)
// Resize the hashtable to a given size
// Max size allowed : 2^31
// The new size will be truncated (in case of being major than 2^31) to the max allowed.
template<typename Data>
void HashTableOpnAdr<Data>::Resize(const ulong newSizeOfTable) {
  ulong newRealSizeOfTable ;
  if (newSizeOfTable < size)
    newRealSizeOfTable = ComputeTheRealSize(size*2) ;
  else
    newRealSizeOfTable = ComputeTheRealSize(newSizeOfTable);
  HashTableOpnAdr<Data>* tmpHT = new HashTableOpnAdr<Data>(newRealSizeOfTable);
  for (ulong i=0 ; i<sizeOfTable ; i++){
      if ((*flagVector)[i] == 1){
        tmpHT->Insert((*table)[i]);
      }
  }
  std::swap(*this,*tmpHT);
  delete tmpHT;
}

/* ************************************************************************ */

// Specific member functions (inherited from DictionaryContainer)
// Override DictionaryContainer member (Copy of the value)
template<typename Data>
bool HashTableOpnAdr<Data>::Insert(const Data& dat) {
  if (size*2 >= sizeOfTable && sizeOfTable<2147483648){
    Resize(sizeOfTable*2);
  }
  bool result ;
  ulong index = 0 ;
  ulong slot = HashKey(dat, index);
  while (index < sizeOfTable && (*flagVector)[slot]== 1  && (*table)[slot]!= dat){
    index = index + 1 ;
    slot = HashKey(dat, index);
  }
  if (index >= sizeOfTable)
  {
    result = false ;
  }
  else
  {
    if ((*flagVector)[slot]!= 1){
      (*table)[slot] = dat ;
      size = size + 1 ;
      if ( (*flagVector)[slot]== 2 ){
         result = !(Remove(dat,index+1));
      }
      (*flagVector)[slot] = 1 ;

    }else{
      result = false ;
    }
  }
  return result ;

}

// Override DictionaryContainer member (Move of the value)
template<typename Data>
bool HashTableOpnAdr<Data>::Insert(Data&& dat) noexcept {
  if (size*2 >= sizeOfTable && sizeOfTable<2147483648){
    Resize(sizeOfTable*2);
  }
  bool result ;
  ulong index = 0 ;
  ulong slot = HashKey(dat, index);
  while (index < sizeOfTable && (*flagVector)[slot]== 1  && (*table)[slot]!= dat){
    index = index + 1 ;
    slot = HashKey(dat, index);
  }
  if (index >= sizeOfTable)
  {
    result = false ;
  }
  else
  {
    if ((*flagVector)[slot]!=1){
      (*table)[slot] = std::move(dat) ;
      size = size + 1 ;
      if ((*flagVector)[slot]==2){
         result = !(Remove(dat,index+1));
      }
      (*flagVector)[slot] = 1 ;
    }else{
      result = false ;
    }
  }
  return result ;
}

// Override DictionaryContainer member
template<typename Data>
bool HashTableOpnAdr<Data>::Remove(const Data& dat) noexcept {
  return Remove(dat,0);
}

/* ************************************************************************ */

// Specific member functions (inherited from TestableContainer)
// Override TestableContainer member

template<typename Data>
bool HashTableOpnAdr<Data>::Exists(const Data& dat) const noexcept {
  bool result ;
  Find(dat, &result);
  return result;
}

/* ************************************************************************ */
// Specific member functions (inherited from MappableContainer)
// Override MappableContainer member

template<typename Data>
void HashTableOpnAdr<Data>::Map(const MapFunctor fun, void* par) {
  if(size>0 && table != nullptr)
  {
    for ( ulong i=0 ; i<sizeOfTable ; i++){
        if ((*flagVector)[i] == 1){
          fun((*table)[i], par);
        }
    }
  }
}
/* ************************************************************************ */

// Specific member functions (inherited from FoldableContainer)
// Override FoldableContainer member

template<typename Data>
void HashTableOpnAdr<Data>::Fold(const FoldFunctor fun, const void* par1, void* par2) const {
  if(size>0 && table != nullptr)
  {
    for ( ulong i=0 ; i<sizeOfTable ; i++){
        if ((*flagVector)[i] == 1){
          fun((*table)[i], par1, par2);
        }
    }
  }
}

/* ************************************************************************ */

// Specific member functions (inherited from Container)
// Override Container member
template<typename Data>
void HashTableOpnAdr<Data>::Clear() {
  HashTableOpnAdr<Data>* tmpHT = new HashTableOpnAdr<Data>(sizeOfTable);
  std::swap(*this,*tmpHT);
  delete tmpHT;
}

/* ************************************************************************ */


// Auxiliary member functions

template<typename Data>
ulong HashTableOpnAdr<Data>::HashKey(const Data& dat, const ulong i) const noexcept {
  ulong h1 = HashKey(dat);
  ulong h2 = HashKey2(dat);
  return ( h1 + (i * h2) ) % sizeOfTable ;
}

template<typename Data>
ulong HashTableOpnAdr<Data>::HashKey2(const Data& dat) const noexcept {
  ulong k = encodingHash(dat) ;
  unsigned long long result = (( ( ((a2*k) + b2) % prime ) % sizeOfTable ) * 2 )-1 ;
  return static_cast<ulong>(result) ;
}



// Fissata la chiave, trovare la locazione dov'è presente il dato (se c'è)
template<typename Data>
ulong HashTableOpnAdr<Data>::Find(const Data& dat, bool* result) const noexcept {
  ulong index = 0 ;
  ulong slot = HashKey(dat, index);
  while (index < sizeOfTable && (*flagVector)[slot]!= 0  && (*table)[slot]!= dat){
    index = index + 1 ;
    slot = HashKey(dat, index);
  }
  if (index >= sizeOfTable)
  {
    *result = false ;
  }
  else
  {
    if ((*flagVector)[slot]==0){
      *result = false ;
    }else{
      if ((*flagVector)[slot]==1){
        *result = true ;
      }
      else
      {
        *result = false ;
      }
    }
  }
  return slot ;
}


template<typename Data>
bool HashTableOpnAdr<Data>::Remove(const Data& dat, const ulong startPoint) noexcept {
  ulong index = startPoint ;
  ulong slot = HashKey(dat, index);
  while (index < sizeOfTable && (*flagVector)[slot]!= 0 && (*table)[slot]!= dat){
    index = index + 1 ;
    slot = HashKey(dat, index);
  }
  if (index >= sizeOfTable){
    return false ;
  }
  else
  {
    if ( (*flagVector)[slot] == 0 )
    {
      return false ;
    }
    else
    {
      if ((*flagVector)[slot] == 2){
        return false ;
      }
      else
      {
        (*flagVector)[slot] = 2 ;
        size = size - 1 ;
        return true ;
      }
    }
  }

}

template<typename Data>
ulong HashTableOpnAdr<Data>::ComputeTheRealSize(const ulong sizeOfChoice) const noexcept {

  ulong extInf = 1024 ;
  ulong extSup = 2147483648 ;
  if (sizeOfChoice > extInf){
    ulong result = static_cast<ulong>( ceil( log2(sizeOfChoice) ) );
    result = pow(2,result);
    if (result <= extSup )
      return result ;
    else
      return extSup ;
  }
  else
  {
    return extInf ;
  }
}


template<typename Data>
void HashTableOpnAdr<Data>::InitA2andB2() noexcept {
  std::default_random_engine genx(std::random_device{}());
  std::uniform_int_distribution<long long> distA2(1, prime-1);
  std::uniform_int_distribution<long long> distB2(0, prime-1);
  a2 =  distA2(genx) ;
  b2 =  distB2(genx) ;
}

/* ************************************************************************** */

}

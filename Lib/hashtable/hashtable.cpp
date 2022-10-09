
namespace lasd {

#include <string>

/* ************************************************************************** */

template<>
class Hash<int>{

public:

  ulong operator()(const int& dat) const noexcept {
    return (dat*dat);
  }

};

template<>
class Hash<double>{

public:

  ulong operator()(const double& dat) const noexcept {
    ulong intPart = floor(dat);
    ulong fracPart = pow(2,24) * (dat - intPart);
    return (intPart*fracPart);
  }

};

template<>
class Hash<std::string>{

public:

  ulong operator()(const std::string& dat) const noexcept {
    ulong hash = 5381 ;
    for(ulong i=0 ; i<<dat.length(); ++i){
      hash = (hash << 5) + dat[i] ;
    }
    return hash ;
  }

};

template <typename Data>
HashTable<Data>::HashTable(){
  std::default_random_engine genx(std::random_device{}());
  std::uniform_int_distribution<long long> distA(1, prime-1);
  std::uniform_int_distribution<long long> distB(0, prime-1);
  a =  distA(genx) ;
  b =  distB(genx) ;
  sizeOfTable =  pow(2,10) ;
}

// Copy constructor
template<typename Data>
HashTable<Data>::HashTable(const HashTable<Data>& hashT) {
  size = hashT.size ;
  encodingHash = hashT.encodingHash ;
  sizeOfTable = hashT.sizeOfTable ;
  a = hashT.a ;
  b = hashT.b ;
}

// Move constructor
template<typename Data>
HashTable<Data>::HashTable(HashTable<Data>&& hashT) noexcept {
  std::swap(size, hashT.size);
  std::swap(encodingHash, hashT.encodingHash);
  std::swap(sizeOfTable,hashT.sizeOfTable);
  std::swap(a, hashT.a);
  std::swap(b, hashT.b);
}

// ...

/* ************************************************************************** */

}

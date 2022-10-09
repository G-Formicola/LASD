
namespace lasd {

/* ************************************************************************** */


template<typename Data>
void auxFoldExists(const Data& dat, const void* val, void* exists){
  if ( (*((Data*) val)) == dat ){
    (*((bool*) exists)) = true ;
  }
}

template <typename Data>
bool FoldableContainer<Data>::Exists(const Data& x) const noexcept {
  bool exist = false ;
  Fold(&auxFoldExists<Data>, &x, &exist );
  return exist ;
}

template <typename Data>
void DictionaryContainer<Data>::Insert(const LinearContainer<Data>& cont) {
  ulong limit = cont.Size();
  for(ulong i = 0 ; i<limit ; i++){
    Insert(cont[i]);
  }
}

template <typename Data>
void DictionaryContainer<Data>::Insert(LinearContainer<Data>&& cont) noexcept {
  ulong limit = cont.Size();
  for(ulong i = 0 ; i<limit ; i++){
    Insert(std::move(cont[i]));
  }
}

template <typename Data>
void DictionaryContainer<Data>::Remove(const LinearContainer<Data>& cont) noexcept {
  ulong limit = cont.Size();
  for(ulong i = 0 ; i<limit ; i++){
    Remove(cont[i]);
  }
}


template <typename Data>
void PreOrderMappableContainer<Data>::Map(const MapFunctor fun, void* par) {
  MapPreOrder(fun, par);
}

template <typename Data>
void PreOrderFoldableContainer<Data>::Fold(const FoldFunctor fun, const void* par1, void* par2) const {
  FoldPreOrder(fun, par1, par2);
}

template <typename Data>
void PostOrderMappableContainer<Data>::Map(const MapFunctor fun, void* par) {
  MapPostOrder(fun, par);
}

template <typename Data>
void PostOrderFoldableContainer<Data>::Fold(const FoldFunctor fun, const void* par1, void* par2) const {
  FoldPostOrder(fun, par1, par2);
}

template <typename Data>
void InOrderMappableContainer<Data>::Map(const MapFunctor fun, void* par) {
  MapInOrder(fun, par);
}

template <typename Data>
void InOrderFoldableContainer<Data>::Fold(const FoldFunctor fun, const void* par1, void* par2) const {
  FoldInOrder(fun, par1, par2);
}

template <typename Data>
void BreadthMappableContainer<Data>::Map(const MapFunctor fun, void* par) {
  MapBreadth(fun, par);
}

template <typename Data>
void BreadthFoldableContainer<Data>::Fold(const FoldFunctor fun, const void* par1, void* par2) const {
  FoldBreadth(fun, par1, par2);
}

/* ************************************************************************** */

}

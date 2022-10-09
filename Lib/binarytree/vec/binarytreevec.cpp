
namespace lasd {

/* ************************************************************************ */

// Specific constructors
// A binary tree obtained from a LinearContainer
template<typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const LinearContainer<Data>& cont) {
  size = cont.Size();
  nodesVector.Resize(size);
  for (ulong i=0 ; i<size ; i++){
    nodesVector[i] = new BinaryTreeVec<Data>::NodeVec(cont[i],i,&nodesVector);
  }
}

/* ************************************************************************ */

// Copy constructor
template<typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data>& bt) {
  size = bt.size ;
  nodesVector.Resize(size);
  for (ulong i=0 ; i<size ; i++){
    if (bt.nodesVector[i] != nullptr){
      struct BinaryTreeVec<Data>::NodeVec* tmp = bt.nodesVector[i];
      nodesVector[i] = new BinaryTreeVec<Data>::NodeVec(tmp->element,tmp->index,tmp->handleNodesVector);
    }else
    {
      nodesVector[i] = nullptr ;
    }
  }
}

// Move constructor
template<typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data>&& bt) noexcept {
  //nodesVector = std::move(bt.nodesVector);
  //size = std::move(bt.size);
  std::swap(nodesVector, bt.nodesVector);
  std::swap(size, bt.size);
}

/* ************************************************************************ */

// Destructor
template<typename Data>
BinaryTreeVec<Data>::~BinaryTreeVec() {
  Clear();
}

/* ************************************************************************ */

// Copy assignment
template<typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(const BinaryTreeVec<Data>& bt) {
  BinaryTreeVec<Data>* tmpBT = new BinaryTreeVec<Data>(bt);
  std::swap(*this,*tmpBT);
  delete tmpBT;
  return *this;
}

// Move assignment
template<typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(BinaryTreeVec<Data>&& bt) noexcept {
  //nodesVector = std::move(bt.nodesVector);
  //size = std::move(bt.size);
  std::swap(nodesVector, bt.nodesVector);
  std::swap(size, bt.size);
  return *this;
}

/* ************************************************************************ */
/*
// Comparison operators
template<typename Data>
bool BinaryTreeVec<Data>::operator==(const BinaryTreeVec<Data>& bt) const noexcept {
  if ( size != bt.Size() ){
    return false ;
  }
  else
  {
    if (size == 0){
      return true ;
    }
    else
    {
      return Root() == bt.Root();
    }
  }
}

template<typename Data>
bool BinaryTreeVec<Data>::operator!=(const BinaryTreeVec<Data>& bt) const noexcept {
  return !(*this==bt) ;
}
*/
/* ************************************************************************ */

// Specific member functions (inherited from BinaryTree)
// Override BinaryTree member (throw std::length_error when empty)

template<typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() const {
  if (size>0)
    return *(nodesVector[0]);
  else
    throw std::length_error("This BinaryTreeVec is empty !");
}

/* ************************************************************************ */

// Specific member functions (inherited from Container)
// Override Container member

template<typename Data>
void BinaryTreeVec<Data>::Clear() {
  if(size>0){
    for (ulong i = 0 ; i<size ; i++){
      delete nodesVector[i];
    }

    nodesVector.Clear();
    size = 0;
  }
}
/* ************************************************************************ */

// Specific member functions (inherited from BreadthMappableContainer)
// Override BreadthMappableContainer member
template<typename Data>
void BinaryTreeVec<Data>::MapBreadth(const MapFunctor fun, void* par) {
  for (ulong i = 0; i < size; i++) {
    if (nodesVector[i]!=nullptr)
      fun(nodesVector[i]->Element(),par);
  }
}

/* ************************************************************************ */

// Specific member functions (inherited from BreadthFoldableContainer)
// Override BreadthFoldableContainer member
template<typename Data>
void BinaryTreeVec<Data>::FoldBreadth(const FoldFunctor fun, const void* par1, void* par2) const {
  for (ulong i = 0; i < size; i++) {
    if (nodesVector[i]!=nullptr)
      fun(nodesVector[i]->Element(),par1,par2);
  }
}

/* ************************************************************************** */

}

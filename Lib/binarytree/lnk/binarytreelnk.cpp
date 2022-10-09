
namespace lasd {

/* ************************************************************************** */

// Specific constructors
// A binary tree obtained from a LinearContainer
template<typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const LinearContainer<Data>& cont) {
  size = cont.Size();
  if (size>0){
    root = BuildBT(root,cont,0);
  }
  else
  {
    root = nullptr ;
  }

}

/* ************************************************************************ */

// Copy constructor
template<typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk<Data>& bt) {
  size = bt.Size();
  if (size>0){
      root = BuildBT(bt.root);
  }
  else
  {
      root = nullptr;
  }
}

// Move constructor
template<typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk<Data>&& bt) noexcept {
  std::swap(root, bt.root);
  std::swap(size,bt.size);
}

/* ************************************************************************ */

// Destructor
template<typename Data>
BinaryTreeLnk<Data>::~BinaryTreeLnk() {
  Clear();
}

/* ************************************************************************ */

// Copy assignment
template<typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk<Data>& bt) {
  BinaryTreeLnk<Data>* tmpBT = new BinaryTreeLnk<Data>(bt);
  std::swap(*this,*tmpBT);
  delete tmpBT;
  return *this;
}

// Move assignment
template<typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(BinaryTreeLnk<Data>&& bt) noexcept {
  std::swap(root, bt.root);
  std::swap(size, bt.size);
  return *this;
}

/* ************************************************************************ */

// Comparison operators
template<typename Data>
bool BinaryTreeLnk<Data>::operator==(const BinaryTreeLnk<Data>& bt) const noexcept {
  /*if ( size != bt.Size() ){
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
  }*/
  return BinaryTree<Data>::operator==(bt);
}


/* ************************************************************************ */

// Specific member functions (inherited from BinaryTree)
// Override BinaryTree member (throw std::length_error when empty)

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::Root() const {
  if (root != nullptr){
    return (*(root)) ;
  }
  else
  {
    throw std::length_error("This BinaryTreeLnk is empty !");
  }
}
/* ************************************************************************ */

// Specific member functions (inherited from Container)
// Override Container member

template<typename Data>
void BinaryTreeLnk<Data>::Clear() {
  if(size > 0){
    delete root ;
    root = nullptr ;
    size = 0 ;
  }
}

/* ************************************************************************** */

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* BinaryTreeLnk<Data>::BuildBT(const NodeLnk* current){
  if ( current != nullptr ){

    NodeLnk* tmp = new NodeLnk(current->Element());

    if (current->HasLeftChild()){
      tmp->sx = BuildBT(current->sx);
    }

    if (current->HasRightChild()){
      tmp->dx = BuildBT(current->dx);
    }

    return tmp;

  }
  else
  {
    return nullptr;
  }

}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* BinaryTreeLnk<Data>::BuildBT(NodeLnk* current, const LinearContainer<Data>& cont, const ulong startpoint){

  if ( startpoint < cont.Size() )
  {
    current = new NodeLnk(cont[startpoint]);
    current->sx = BuildBT(current->sx,cont,((startpoint*2)+1));
    current->dx = BuildBT(current->dx,cont,((startpoint+1)*2));
  }

  return current ;

}


}


namespace lasd {

/* ************************************************************************** */

// Specific constructors
// A bst obtained from a LinearContainer
template<typename Data>
BST<Data>::BST(const LinearContainer<Data>& con) {
  if (con.Size()>0){
    for (ulong i=0 ; i<con.Size() ; i++){
      Insert(con[i]);
    }
  }
  else
  {
    root = nullptr ;
    size = 0 ;
  }
}
/* ************************************************************************ */

// Copy constructor
template<typename Data>
BST<Data>::BST(const BST<Data>& bst) : BinaryTreeLnk<Data>::BinaryTreeLnk(bst) {
}

// Move constructor
template<typename Data>
BST<Data>::BST(BST<Data>&& bst) noexcept : BinaryTreeLnk<Data>::BinaryTreeLnk(std::move(bst)) {
}

/* ************************************************************************ */

// Copy assignment
template<typename Data>
BST<Data>& BST<Data>::operator=(const BST<Data>& bst) {
  BinaryTreeLnk<Data>::operator=(bst);
  return *this;
}

// Move assignment
template<typename Data>
BST<Data>& BST<Data>::operator=(BST<Data>&& bst) noexcept {
  BinaryTreeLnk<Data>::operator=(std::move(bst));
  return *this;
}

/* ************************************************************************ */






// Comparison operators
template<typename Data>
bool BST<Data>::operator==(const BST<Data>& bst) const noexcept{
  if (size != bst.Size()) return false ;
  if (size == 0){
    return true ;
  }else{
    BTInOrderIterator<Data> iter1 (*this) ;
    BTInOrderIterator<Data> iter2 (bst);
    bool result = true ;
    while (!iter1.Terminated() && !iter2.Terminated() && result==true){
      if ( *iter1 != *iter2){
        result = false ;
      }
      ++iter1 ;
      ++iter2 ;
    }

    // Ridondante dal momento che controllo già la size
    if ( result == true && ( !iter1.Terminated() || !iter2.Terminated() ) ){
        result = false ;
    }

    return result ;
  }
}










/* ************************************************************************ */

// Specific member functions

// (concrete function must throw std::length_error when empty)
template<typename Data>
const Data& BST<Data>::Min() const {
  if (size==0){
    throw std::length_error("This binary search tree is empty !");
  }
  else
  {
    NodeLnk* const * tmp = FindPointerToMin(&root) ;
    return (*tmp)->Element();
  }
}

// (concrete function must throw std::length_error when empty)
template<typename Data>
Data BST<Data>::MinNRemove() {
  if (size == 0){
    throw std::length_error("This binary search tree is empty !");
  }
  else
  {
    Data ret = DataNDelete(DetachMin(&root));
    size = size - 1 ;
    if (size == 0) root = nullptr ;
    return ret;
  }
}

// (concrete function must throw std::length_error when empty)
template<typename Data>
void BST<Data>::RemoveMin() {
  if (size == 0){
    throw std::length_error("This binary search tree is empty !");
  }
  else
  {
    NodeLnk* tmp = DetachMin(&root) ;
    delete tmp;
    size = size - 1 ;
    if (size == 0) root = nullptr ;
  }
}

// (concrete function must throw std::length_error when empty)
template<typename Data>
const Data& BST<Data>::Max() const {
  if (size==0){
    throw std::length_error("This binary search tree is empty !");
  }
  else
  {
    NodeLnk* const * tmp = FindPointerToMax(&root) ;
    return (*tmp)->Element();
  }
}

// (concrete function must throw std::length_error when empty)
template<typename Data>
Data BST<Data>::MaxNRemove() {
  if (size == 0){
    throw std::length_error("This binary search tree is empty !");
  }
  else
  {
    Data ret = DataNDelete(DetachMax(&root));
    size = size - 1 ;
    if (size == 0) root = nullptr ;
    return ret;
  }
}

// (concrete function must throw std::length_error when empty)
template<typename Data>
void BST<Data>::RemoveMax() {
  if (size == 0){
    throw std::length_error("This binary search tree is empty !");
  }
  else
  {
    NodeLnk* tmp = DetachMax(&root) ;
    delete tmp;
    size = size - 1 ;
    if (size == 0) root = nullptr ;
  }
}


// (concrete function must throw std::length_error when not found)
template<typename Data>
const Data& BST<Data>::Predecessor(const Data& dat) const{
  NodeLnk* const * predec = FindPointerToPredecessor(&root,dat);
  if (predec!=nullptr && (*predec)!=nullptr){
    return (*predec)->Element();
  }
  else
  {
    throw std::length_error("Predecessor not found !");
  }
}
// (concrete function must throw std::length_error when not found)
template<typename Data>
Data BST<Data>::PredecessorNRemove(const Data& dat) {
  NodeLnk** predec = FindPointerToPredecessor(&root,dat);
  if ( predec!=nullptr && (*predec)!=nullptr){
    Data result = DataNDelete(Detach(predec));
    size = size - 1 ;
    if (size == 0) root = nullptr ;
    return result ;
  }
  else
  {
    throw std::length_error("Predecessor not found !");
  }
}
// (concrete function must throw std::length_error when not found)
template<typename Data>
void BST<Data>::RemovePredecessor(const Data& dat) {
  NodeLnk** predec = FindPointerToPredecessor(&root,dat);
  if (predec!=nullptr && (*predec)!=nullptr){
    delete Detach(predec);
    size = size - 1 ;
    if (size == 0) root = nullptr ;
  }
  else
  {
    throw std::length_error("Predecessor not found !");
  }
}

 // (concrete function must throw std::length_error when not found)
template<typename Data>
const Data& BST<Data>::Successor(const Data& dat) const{
  NodeLnk* const * succ = FindPointerToSuccessor(&root,dat);
  if (succ!=nullptr && (*succ)!=nullptr){
    return (*succ)->Element();
  }
  else
  {
    throw std::length_error("Successor not found !");
  }
}
// (concrete function must throw std::length_error when not found)
template<typename Data>
Data BST<Data>::SuccessorNRemove(const Data& dat) {
  NodeLnk** succ = FindPointerToSuccessor(&root,dat);
  if (succ!=nullptr && (*succ)!=nullptr){
    Data result = DataNDelete(Detach(succ));
    size = size - 1 ;
    if (size == 0) root = nullptr ;
    return result ;
  }
  else
  {
    throw std::length_error("Successor not found !");
  }
}
// (concrete function must throw std::length_error when not found)
template<typename Data>
void BST<Data>::RemoveSuccessor(const Data& dat) {
  NodeLnk** succ = FindPointerToSuccessor(&root,dat);
  if (succ!=nullptr && (*succ)!=nullptr){
    delete Detach(succ);
    size = size - 1 ;
    if (size == 0) root = nullptr ;
  }
  else
  {
    throw std::length_error("Successor not found !");
  }
}







/* ************************************************************************ */

// Specific member functions (inherited from DictionaryContainer)
// Override DictionaryContainer member (Copy of the value)

template<typename Data>
bool BST<Data>::Insert(const Data& dat) {
  NodeLnk** whereToInsert = FindPointerTo(&root,dat);
  if (whereToInsert!=nullptr)
  {
      if (*whereToInsert == nullptr)
      {
        *whereToInsert = new NodeLnk(dat);
        size = size + 1 ;
        return true ;
      }
      else
      {
        return false ;
      }
  }
  else
  {
    return false ;
  }
}

// Override DictionaryContainer member (Move of the value)

template<typename Data>
bool BST<Data>::Insert(Data&& dat) noexcept {
  NodeLnk** whereToInsert = FindPointerTo(&root,dat);
  if (whereToInsert!=nullptr)
  {
        if (*whereToInsert == nullptr)
        {
          *whereToInsert = new NodeLnk(std::move(dat));
          size = size + 1 ;
          return true ;
        }
        else
        {
          return false ;
        }
  }
  else
  {
    return false ;
  }

}

// Override DictionaryContainer member

template<typename Data>
bool BST<Data>::Remove(const Data& dat) noexcept {
  NodeLnk** whereToDelete = FindPointerTo(&root,dat);
  if (whereToDelete == nullptr || *whereToDelete == nullptr)
  {
    return false ;
  }
  else
  {

    NodeLnk* nodeToDelete = Detach(whereToDelete);
    if (nodeToDelete!=nullptr){
      delete nodeToDelete;
      size = size - 1 ;
      if (size == 0) root = nullptr ;
      return true ;
    }
    else{
      return false;
    }

  }
}

/* ************************************************************************ */

// Specific member functions (inherited from TestableContainer)
// Override TestableContainer member

template<typename Data>
bool BST<Data>::Exists(const Data& dat) const noexcept {
  NodeLnk* const * whereToInsert = FindPointerTo(&root,dat);
  if (whereToInsert==nullptr || *whereToInsert == nullptr)
  {
    return false ;
  }
  else
  {
    return true ;
  }
}


/* ************************************************************************** */

// Auxiliary member functions

template<typename Data>
Data BST<Data>::DataNDelete(NodeLnk* nodeToDelete) noexcept {
  Data ret {};
  if (nodeToDelete!=nullptr)
  {
      ret = nodeToDelete->Element();
      delete nodeToDelete;
  }
  return ret ;
}


template<typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Detach(NodeLnk** node) noexcept {

  NodeLnk* nodeDetached = nullptr;
  if (node != nullptr)
  {
      nodeDetached = *node;
      if (*node != nullptr)
      {
            if ( (*node)->IsLeaf() )
            {
              *node = nullptr ;
            }
            else
            {
                    if ((*node)->HasLeftChild() && !((*node)->HasRightChild()))
                    {
                      *node = &(nodeDetached->LeftChild());
                      nodeDetached->sx = nullptr ;
                    }
                    else if ((*node)->HasRightChild() && !((*node)->HasLeftChild()))
                    {
                      *node = &(nodeDetached->RightChild());
                      nodeDetached->dx = nullptr ;
                    }
                    else
                    {
                      nodeDetached = DetachMin((&(*node)->dx));
                      (*node)->element = std::move(nodeDetached->element);
                    }
            }
      }

  }
  return nodeDetached ;
}


template<typename Data>
typename BST<Data>::NodeLnk* BST<Data>::DetachMin(NodeLnk** startNode) noexcept {

  NodeLnk** min = FindPointerToMin(startNode);
  NodeLnk* nodeToDetach = nullptr;
  if (min!=nullptr)
  {
      nodeToDetach = (*min);
      if (nodeToDetach!=nullptr)
      {
        if ((*min)->HasRightChild()){
          *min = &((*min)->RightChild());
           nodeToDetach->dx = nullptr ;
        }
        else
        {
          *min = nullptr ;
        }
      }
  }
  return nodeToDetach ;
}

template<typename Data>
typename BST<Data>::NodeLnk* BST<Data>::DetachMax(NodeLnk** startNode) noexcept {

  NodeLnk** max = FindPointerToMax(startNode);
  NodeLnk* nodeToDetach = nullptr;
  if (max!=nullptr)
  {
      nodeToDetach = (*max);
      if (nodeToDetach!=nullptr)
      {
          if ((*max)->HasLeftChild()){
            *max = &((*max)->LeftChild());
            nodeToDetach->sx = nullptr ;
          }
          else
          {
            *max = nullptr ;
          }
      }
  }
  return nodeToDetach ;
}


// unmutable version
template<typename Data>
typename BST<Data>::NodeLnk* const * BST<Data>::FindPointerToMin(NodeLnk* const * startNode) const noexcept {

  NodeLnk* curr = nullptr;
  NodeLnk* const * minimo = startNode ;
  if (minimo != nullptr && *minimo != nullptr )
  {
      curr = *minimo ;
      while (curr->HasLeftChild()){
        minimo = &(curr->sx);
        curr = &(curr->LeftChild());
      }
  }
  return minimo ;
}

// mutable version
template<typename Data>
typename BST<Data>::NodeLnk** BST<Data>::FindPointerToMin(NodeLnk** startNode) noexcept {

  NodeLnk* curr = nullptr;
  NodeLnk** minimo = startNode ;
  if (minimo != nullptr && *minimo != nullptr )
  {
      curr = *minimo ;
      while (curr->HasLeftChild()){
        minimo = &(curr->sx);
        curr = &(curr->LeftChild());
      }
  }
  return minimo ;
}



// unmutable version
template<typename Data>
typename BST<Data>::NodeLnk* const * BST<Data>::FindPointerToMax(NodeLnk* const * startNode ) const noexcept {

  NodeLnk* curr = nullptr;
  NodeLnk* const * massimo = startNode ;
  if (massimo != nullptr && *massimo != nullptr )
  {
      curr = *massimo ;
      while (curr->HasRightChild()){
        massimo = &(curr->dx);
        curr = &(curr->RightChild());
      }
  }
  return massimo  ;
}

// mutable version
template<typename Data>
typename BST<Data>::NodeLnk** BST<Data>::FindPointerToMax(NodeLnk** startNode ) noexcept {

  NodeLnk* curr = nullptr;
  NodeLnk** massimo = startNode;
  if (massimo != nullptr && *massimo != nullptr )
  {
      curr = *massimo ;
      while (curr->HasRightChild()){
        massimo = &(curr->dx);
        curr = &(curr->RightChild());
      }
  }
  return massimo  ;
}

// unmutable version
template<typename Data>
typename BST<Data>::NodeLnk* const * BST<Data>::FindPointerTo(NodeLnk* const * startNode, const Data& dat) const noexcept{

  NodeLnk* const * result = startNode;
  NodeLnk* curr = nullptr ;
  if (startNode != nullptr && *startNode != nullptr )
  {
        curr = *result ;
        while ( curr!= nullptr ){
                if(curr->Element()==dat)
                {
                    return result ;
                }

                if(curr->Element()>dat){
                  result = &(curr->sx);
                  curr = curr->sx ;
                }
                else
                {
                  result = &(curr->dx);
                  curr = curr->dx ;
                }
          }
  }
  return result ;
}

// mutable version
template<typename Data>
typename BST<Data>::NodeLnk** BST<Data>::FindPointerTo(NodeLnk** startNode, const Data& dat) noexcept{

  NodeLnk** result = startNode;
  NodeLnk* curr = nullptr ;
  if (startNode != nullptr && *startNode != nullptr )
  {
        curr = *result ;
        while ( curr!= nullptr ){
              if(curr->Element()==dat)
              {
                  return result ;
              }

              if(curr->Element()>dat){
                result = &(curr->sx);
                curr = curr->sx ;
              }
              else
              {
                result = &(curr->dx);
                curr = curr->dx ;
              }
        }
  }
  return result ;
}


// unmutable version
template<typename Data>
typename BST<Data>::NodeLnk* const * BST<Data>::FindPointerToPredecessor(NodeLnk* const * startNode, const Data& dat) const noexcept {

   NodeLnk* const * result = nullptr;
   NodeLnk* const * curr = startNode ;
   bool stima = false ;
   if (startNode != nullptr && *startNode != nullptr )
   {
        while ( (*curr)!= nullptr ){
                 if((*curr)->Element()<dat)
                 {
                     result = curr ;
                     stima = true ;
                     curr = &((*curr)->dx) ;
                 }
                 else
                 {
                   curr = &((*curr)->sx) ;
                   if ( stima == false ){
                     result = curr ;
                   }
                 }
          }
   }
   return result ;

}

// mutable version
template<typename Data>
typename BST<Data>::NodeLnk** BST<Data>::FindPointerToPredecessor(NodeLnk** startNode , const Data& dat) noexcept {

   NodeLnk* * result = nullptr;
   NodeLnk* * curr = startNode ;
   bool stima = false ;
   if (startNode != nullptr && *startNode != nullptr )
   {
        while ( (*curr)!= nullptr ){
                 if((*curr)->Element()<dat)
                 {
                     result = curr ;
                     stima = true ;
                     curr = &((*curr)->dx) ;
                 }
                 else
                 {
                   curr = &((*curr)->sx) ;
                   if ( stima == false ){
                     result = curr ;
                   }
                 }
          }
   }
   return result ;

}

// unmutable version
template<typename Data>
typename BST<Data>::NodeLnk* const * BST<Data>::FindPointerToSuccessor(NodeLnk* const * startNode , const Data& dat) const noexcept {

  NodeLnk* const * result = nullptr;
  NodeLnk* const * curr = startNode ;
  bool stima = false ;
  if (startNode != nullptr && *startNode != nullptr )
  {
       while ( (*curr)!= nullptr ){
                if((*curr)->Element()>dat)
                {
                    result = curr ;
                    stima = true ;
                    curr = &((*curr)->sx) ;
                }
                else
                {
                  curr = &((*curr)->dx) ;
                  if ( stima == false ){
                    result = curr ;
                  }
                }
         }
  }
  return result ;

}


// mutable version
template<typename Data>
typename BST<Data>::NodeLnk** BST<Data>::FindPointerToSuccessor(NodeLnk* * startNode, const Data& dat) noexcept {

  NodeLnk* * result = nullptr;
  NodeLnk* * curr = startNode ;
  bool stima = false ;
  if (startNode != nullptr && *startNode != nullptr )
  {
       while ( (*curr)!= nullptr ){
                if((*curr)->Element()>dat)
                {
                    result = curr ;
                    stima = true ;
                    curr = &((*curr)->sx) ;
                }
                else
                {
                  curr = &((*curr)->dx) ;
                  if ( stima == false ){
                    result = curr ;
                  }
                }
         }
  }
  return result ;

}


}

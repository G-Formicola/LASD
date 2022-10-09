
#include "../queue/lst/queuelst.hpp"

#include "../stack/lst/stacklst.hpp"

namespace lasd {

  // BINARYTREE IMPLEMENTATION
  /* ************************************************************************ */

  // Comparison operators
  // Comparison of abstract binary tree is possible.
  template<typename Data>
  bool BinaryTree<Data>::operator==(const BinaryTree<Data>& bt) const noexcept {
    if ( size != bt.Size() ) return false ;
    if ( size > 0 ) return (Root()==bt.Root());

    // Se entrambe le size sono zero, trivially true.
    return true;
  }

/* ************************************************************************** */

// Specific member functions (inherited from MappableContainer)
// Override MappableContainer member
template<typename Data>
void BinaryTree<Data>::Map(const MapFunctor fun, void* par) {
  PreOrderMappableContainer<Data>::Map(fun,par);
}

/* ************************************************************************ */

// Specific member functions (inherited from FoldableContainer)
// Override FoldableContainer member
template<typename Data>
void BinaryTree<Data>::Fold(const FoldFunctor fun, const void* par1, void* par2) const {
  PreOrderFoldableContainer<Data>::Fold(fun,par1,par2);
}

/* ************************************************************************ */

// Specific member functions (inherited from PreOrderMappableContainer)
 // Override PreOrderMappableContainer member
template<typename Data>
void BinaryTree<Data>::MapPreOrder(const MapFunctor fun, void* par){
  if (size>0) MapPreOrder(fun, par, Root());
}

/* ************************************************************************ */

// Auxiliary member functions (for PreOrderMappableContainer)
// Accessory function executing from one node of the tree
template<typename Data>
void BinaryTree<Data>::MapPreOrder(const MapFunctor fun, void* par, Node& node) {

  fun(node.Element(),par);

  if (node.HasLeftChild()) MapPreOrder(fun, par, node.LeftChild());

  if (node.HasRightChild()) MapPreOrder(fun, par, node.RightChild());

}


/* ************************************************************************ */

// Specific member functions (inherited from PreOrderFoldableContainer)
// Override PreOrderFoldableContainer member
template<typename Data>
void BinaryTree<Data>::FoldPreOrder(const FoldFunctor fun, const void* par1, void* par2) const {
  if (size>0) FoldPreOrder(fun,par1,par2,Root());
}

/* ************************************************************************ */

// Auxiliary member functions (for PreOrderFoldableContainer)
// Accessory function executing from one node of the tree
template<typename Data>
void BinaryTree<Data>::FoldPreOrder(const FoldFunctor fun, const void* par1, void* par2, Node& node) const {

  fun(node.Element(),par1,par2);

  if (node.HasLeftChild()) FoldPreOrder(fun,par1,par2,node.LeftChild());

  if (node.HasRightChild()) FoldPreOrder(fun,par1,par2,node.RightChild());

}

/* ************************************************************************ */

// Specific member functions (inherited from PostOrderMappableContainer)
// Override PostOrderMappableContainer member
template<typename Data>
void BinaryTree<Data>::MapPostOrder(const MapFunctor fun, void* par) {
  if (size>0) MapPostOrder(fun,par,Root());
}

/* ************************************************************************ */

// Auxiliary member functions (for PostOrderMappableContainer)
// Accessory function executing from one node of the tree
template<typename Data>
void BinaryTree<Data>::MapPostOrder(const MapFunctor fun, void* par, Node& node) {

  if (node.HasLeftChild()) MapPostOrder(fun, par, node.LeftChild());

  if (node.HasRightChild()) MapPostOrder(fun, par, node.RightChild());

  fun(node.Element(),par);
}

/* ************************************************************************ */

// Specific member functions (inherited from PostOrderFoldableContainer)
// Override PostOrderFoldableContainer member
template<typename Data>
void BinaryTree<Data>::FoldPostOrder(const FoldFunctor fun, const void* par1, void* par2) const {

  if (size>0) FoldPostOrder(fun,par1,par2,Root());

}

/* ************************************************************************** */


// Auxiliary member functions (for PostOrderFoldableContainer)
// Accessory function executing from one node of the tree
template<typename Data>
void BinaryTree<Data>::FoldPostOrder(const FoldFunctor fun, const void* par1, void* par2, Node& node) const {



    if (node.HasLeftChild()) FoldPostOrder(fun,par1,par2,node.LeftChild());

    if (node.HasRightChild()) FoldPostOrder(fun,par1,par2,node.RightChild());

    fun(node.Element(),par1,par2);

}

/* ************************************************************************ */

// Specific member functions (inherited from InOrderMappableContainer)
// Override InOrderMappableContainer member
template<typename Data>
void BinaryTree<Data>::MapInOrder(const MapFunctor fun, void* par) {

  if (size>0) MapInOrder(fun,par,Root());

}

/* ************************************************************************ */

// Auxiliary member functions (for InOrderMappableContainer)
// Accessory function executing from one node of the tree
template<typename Data>
void BinaryTree<Data>::MapInOrder(const MapFunctor fun, void* par, Node& node) {

  if (node.HasLeftChild()) MapInOrder(fun, par, node.LeftChild());

  fun(node.Element(),par);

  if (node.HasRightChild()) MapInOrder(fun, par, node.RightChild());

}

/* ************************************************************************ */

// Specific member functions (inherited from InOrderFoldableContainer)
// Override InOrderFoldableContainer member
template<typename Data>
void BinaryTree<Data>::FoldInOrder(const FoldFunctor fun, const void* par1, void* par2) const {
  if (size>0) FoldInOrder(fun,par1,par2,Root());
}

/* ************************************************************************ */

// Auxiliary member functions (for InOrderFoldableContainer)
// Accessory function executing from one node of the tree
template<typename Data>
void BinaryTree<Data>::FoldInOrder(const FoldFunctor fun, const void* par1, void* par2, Node& node) const {

  if (node.HasLeftChild()) FoldInOrder(fun,par1,par2,node.LeftChild());

  fun(node.Element(),par1,par2);

  if (node.HasRightChild()) FoldInOrder(fun,par1,par2,node.RightChild());

}

/* ************************************************************************ */

// Specific member functions (inherited from BreadthMappableContainer)
// Override BreadthMappableContainer member
template<typename Data>
void BinaryTree<Data>::MapBreadth(const MapFunctor fun, void* par) {

  if (size>0) {

    QueueLst<struct Node*> queue ;

    struct Node* current = &(Root());

    if (current->HasLeftChild()) queue.Enqueue(&(current->LeftChild()));
    if (current->HasRightChild()) queue.Enqueue(&(current->RightChild()));

    fun(current->Element(),par);

    while (queue.Size()>0) {

      current = queue.HeadNDequeue();

      if (current->HasLeftChild()) queue.Enqueue(&(current->LeftChild()));
      if (current->HasRightChild()) queue.Enqueue(&(current->RightChild()));

      fun(current->Element(),par);

    }
  }

}

/* ************************************************************************ */

// Specific member functions (inherited from BreadthFoldableContainer)
// Override BreadthFoldableContainer member
template<typename Data>
void BinaryTree<Data>::FoldBreadth(const FoldFunctor fun, const void* par1, void* par2) const {

  if (size>0) {

    QueueLst<struct Node*> queue ;

    struct Node* current = &(Root());

    if (current->HasLeftChild()) queue.Enqueue(&(current->LeftChild()));
    if (current->HasRightChild()) queue.Enqueue(&(current->RightChild()));

    fun(current->Element(),par1,par2);

    while (queue.Size()>0) {

      current = queue.HeadNDequeue();

      if (current->HasLeftChild()) queue.Enqueue(&(current->LeftChild()));
      if (current->HasRightChild()) queue.Enqueue(&(current->RightChild()));

      fun(current->Element(),par1,par2);

    }
  }
}

/* ***********************BTPREORDER IMPLEMENTATION************************ */
/* ************************************************************************ */


// Specific constructors
// An iterator over a given binary tree
template<typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data>& bt) {
  if (bt.Size()>0){
    current = &(bt.Root());
    startpoint = &(bt.Root());

    if (current->HasRightChild()) stack.Push(&(current->RightChild()));
    if (current->HasLeftChild()) stack.Push(&(current->LeftChild()));
  }
}

/* ************************************************************************ */

// Copy constructor
template<typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator<Data>& preIT ) {
  current = preIT.current ;
  stack = preIT.stack ;
  startpoint = preIT.startpoint ;
}

// Move constructor
template<typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator<Data>&& preIT) noexcept {
  std::swap(current,preIT.current);
  std::swap(stack,preIT.stack);
  std::swap(startpoint,preIT.startpoint);
}

/* ************************************************************************ */

// Copy assignment
template<typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator<Data>& preIT ) {
  current = preIT.current;
  stack = preIT.stack;
  startpoint = preIT.startpoint;
  return *this;
}

// Move assignment
template<typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(BTPreOrderIterator<Data>&& preIT ) noexcept {
  current = std::move(preIT.current);
  stack = std::move(preIT.stack);
  startpoint = std::move(preIT.startpoint);
  return *this;
}

/* ************************************************************************ */

// Comparison operators
template<typename Data>
bool BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator<Data>& preIT) const noexcept {
  if ( stack == preIT.stack && (current) == (preIT.current) && startpoint == preIT.startpoint  )
  {
    return true ;
  }
  else
  {
    return false ;
  }
}

template<typename Data>
bool BTPreOrderIterator<Data>::operator!=(const BTPreOrderIterator<Data>& preIT) const noexcept {
  return (!(*this==preIT));
}

/* ************************************************************************ */

// Specific member functions (inherited from Iterator)

// (throw std::out_of_range when terminated)
template<typename Data>
Data& BTPreOrderIterator<Data>::operator*() const {
  if (Terminated())
    throw std::out_of_range("Iterator terminated !");
  else
    return ( (*current).Element() ) ;
}

// (should not throw exceptions)
template<typename Data>
bool BTPreOrderIterator<Data>::Terminated() const noexcept {
  if (stack.Size()==0 && current == nullptr)
    return true ;
  else
    return false ;
}

/* ************************************************************************ */

// Specific member functions (inherited from ForwardIterator)

// (throw std::out_of_range when terminated)
template<typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator++() {
  if (Terminated()){
    throw std::out_of_range("Iterator terminated !");
  }
  else
  {
    if (!stack.Empty()){
      current = stack.TopNPop();
    }
    else
    {
      current = nullptr ;
    }

    if (current != nullptr ){
        if (current->HasRightChild()) stack.Push(&(current->RightChild()));
        if (current->HasLeftChild()) stack.Push(&(current->LeftChild()));
    }

  }

  return *this;

}

/* ************************************************************************ */

// Specific member functions (inherited from ResettableIterator)

// (should not throw exceptions)
template<typename Data>
void BTPreOrderIterator<Data>::Reset() noexcept {

  if (startpoint!=nullptr){
      stack.Clear();
      current = startpoint;
      if (current->HasRightChild()) stack.Push(&(current->RightChild()));
      if (current->HasLeftChild()) stack.Push(&(current->LeftChild()));
  }
}

/* ***********************BTPOSTORDER IMPLEMENTATION************************ */
/* ************************************************************************ */


// Specific constructors
// An iterator over a given binary tree
template<typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data>& bt) {
  if (bt.Size()>0){

    current = &(bt.Root());
    startpoint = &(bt.Root());

    while ( current->HasLeftChild() || current->HasRightChild() ){

      stack.Push(current);

      if ( current->HasLeftChild() )
        current = &(current->LeftChild());
      else
        current = &(current->RightChild());

    }
  }

}

/* ************************************************************************ */

// Copy constructor
template<typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BTPostOrderIterator<Data>& postIT ) {
  current = postIT.current ;
  stack = postIT.stack ;
  startpoint = postIT.startpoint ;
}

// Move constructor
template<typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(BTPostOrderIterator<Data>&& postIT) noexcept {
  std::swap(current,postIT.current);
  std::swap(stack,postIT.stack);
  std::swap(startpoint,postIT.startpoint);
}

/* ************************************************************************ */

// Copy assignment
template<typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator<Data>& postIT ) {
  current = postIT.current;
  stack = postIT.stack;
  startpoint = postIT.startpoint;
  return *this;
}

// Move assignment
template<typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(BTPostOrderIterator<Data>&& postIT ) noexcept {
  current = std::move(postIT.current);
  stack = std::move(postIT.stack);
  startpoint = std::move(postIT.startpoint);
  return *this;
}

/* ************************************************************************ */

// Comparison operators
template<typename Data>
bool BTPostOrderIterator<Data>::operator==(const BTPostOrderIterator<Data>& postIT) const noexcept {
  if ( stack == postIT.stack && (current) == (postIT.current) && startpoint == postIT.startpoint  )
  {
    return true ;
  }
  else
  {
    return false ;
  }
}

template<typename Data>
bool BTPostOrderIterator<Data>::operator!=(const BTPostOrderIterator<Data>& postIT) const noexcept {
  return (!(*this==postIT));
}

/* ************************************************************************ */

// Specific member functions (inherited from Iterator)

// (throw std::out_of_range when terminated)
template<typename Data>
Data& BTPostOrderIterator<Data>::operator*() const {
  if (Terminated() )
    throw std::out_of_range("Iterator terminated !");
  else
    return ( (*current).Element() ) ;
}

// (should not throw exceptions)
template<typename Data>
bool BTPostOrderIterator<Data>::Terminated() const noexcept {
  if (stack.Size()==0 && current == nullptr)
    return true ;
  else
    return false ;
}

/* ************************************************************************ */

// Specific member functions (inherited from ForwardIterator)

// (throw std::out_of_range when terminated)
template<typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator++() {
  if (Terminated()){
    throw std::out_of_range("Iterator terminated !");
  }
  else
  {
        if (stack.Empty())
        {
          current = nullptr ;
        }
        else
        {
                if (stack.Top()->HasRightChild())
                {
                        if ( &(stack.Top()->RightChild()) != current )
                        {
                              current = &(stack.Top()->RightChild());

                              while ( current->HasLeftChild() || current->HasRightChild() ){

                                  stack.Push(current);

                                  if ( current->HasLeftChild() ){
                                    current = &(current->LeftChild());
                                  }else{
                                    current = &(current->RightChild());
                                  }
                                }
                        }
                        else
                        {
                                current = stack.TopNPop();
                        }
                }
                else
                {
                        current = stack.TopNPop();
                }
        }

  }

  return *this;
}

/* ************************************************************************ */

// Specific member functions (inherited from ResettableIterator)

// (should not throw exceptions)
template<typename Data>
void BTPostOrderIterator<Data>::Reset() noexcept {

  if (startpoint!=nullptr){
    stack.Clear();

    current = startpoint;

    while ( current->HasLeftChild() || current->HasRightChild() ){

        stack.Push(current);

        if ( current->HasLeftChild() )
          current = &(current->LeftChild());
        else
          current = &(current->RightChild());

    }
  }

}

/* ***********************BTINORDER IMPLEMENTATION************************ */
/* ************************************************************************ */


// Specific constructors
// An iterator over a given binary tree
template<typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data>& bt) {
  if (bt.Size()>0){

    current = &(bt.Root());
    startpoint = &(bt.Root());

    while ( current->HasLeftChild() ){

      stack.Push(current);
      current = &(current->LeftChild());

    }
  }

}

/* ************************************************************************ */

// Copy constructor
template<typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BTInOrderIterator<Data>& inIT ) {
  current = inIT.current ;
  stack = inIT.stack ;
  startpoint = inIT.startpoint ;
}

// Move constructor
template<typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(BTInOrderIterator<Data>&& inIT) noexcept {
  std::swap(current, inIT.current);
  std::swap(stack, inIT.stack);
  std::swap(startpoint,inIT.startpoint);
}

/* ************************************************************************ */

// Copy assignment
template<typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(const BTInOrderIterator<Data>& inIT ) {
  current = inIT.current;
  stack = inIT.stack;
  startpoint = inIT.startpoint;
  return *this;
}

// Move assignment
template<typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(BTInOrderIterator<Data>&& inIT ) noexcept {
  current = std::move(inIT.current);
  stack = std::move(inIT.stack);
  startpoint = std::move(inIT.startpoint);
  return *this;
}

/* ************************************************************************ */

// Comparison operators
template<typename Data>
bool BTInOrderIterator<Data>::operator==(const BTInOrderIterator<Data>& inIT) const noexcept {
  if ( stack == inIT.stack && (current) == (inIT.current) && startpoint == inIT.startpoint  )
  {
    return true ;
  }
  else
  {
    return false ;
  }
}

template<typename Data>
bool BTInOrderIterator<Data>::operator!=(const BTInOrderIterator<Data>& inIT) const noexcept {
  return (!(*this==inIT));
}

/* ************************************************************************ */

// Specific member functions (inherited from Iterator)

// (throw std::out_of_range when terminated)
template<typename Data>
Data& BTInOrderIterator<Data>::operator*() const {
  if (Terminated())
    throw std::out_of_range("Iterator terminated !");
  else
    return ( (*current).Element() ) ;
}

// (should not throw exceptions)
template<typename Data>
bool BTInOrderIterator<Data>::Terminated() const noexcept {
  if (stack.Size()==0 && current == nullptr)
    return true ;
  else
    return false ;
}

/* ************************************************************************ */

// Specific member functions (inherited from ForwardIterator)

// (throw std::out_of_range when terminated)
template<typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator++() {
  if (Terminated()){
    throw std::out_of_range("Iterator terminated !");
  }
  else
  {
    if(current->IsLeaf())
    {
        if(stack.Empty()){
          current = nullptr;
        }else{
          current = stack.TopNPop();
        }
    }
    else
    {
      if(current->HasRightChild())
      {
        current = &current->RightChild();

        while(current->HasLeftChild())
        {
          stack.Push(current);
          current = &current->LeftChild();
        }
      }
      else
      {
        if(stack.Empty())
        {
          current = nullptr;
        }
        else
        {
          current = stack.TopNPop();
        }
      }
    }
  }

  return *this;
}

/* ************************************************************************ */

// Specific member functions (inherited from ResettableIterator)

// (should not throw exceptions)
template<typename Data>
void BTInOrderIterator<Data>::Reset() noexcept {


  if (startpoint!=nullptr){
      stack.Clear();

      current = startpoint;

      while ( current->HasLeftChild() ){

        stack.Push(current);
        current = &(current->LeftChild());

      }
  }
}

/* ***********************BTBREADTH IMPLEMENTATION************************ */
/* ************************************************************************ */


// Specific constructors
// An iterator over a given binary tree
template<typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BinaryTree<Data>& bt) {
  if (bt.Size()>0){

    current = &(bt.Root());
    startpoint = &(bt.Root());

    if (current->HasLeftChild()) queue.Enqueue(&(current->LeftChild()));
    if (current->HasRightChild()) queue.Enqueue(&(current->RightChild()));
  }

}

/* ************************************************************************ */

// Copy constructor
template<typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BTBreadthIterator<Data>& brIT ) {
  current = brIT.current ;
  queue = brIT.queue ;
  startpoint = brIT.startpoint ;
}

// Move constructor
template<typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(BTBreadthIterator<Data>&& brIT) noexcept {
  std::swap(current,brIT.current);
  std::swap(queue,brIT.queue);
  std::swap(startpoint,brIT.startpoint);
}

/* ************************************************************************ */

// Copy assignment
template<typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(const BTBreadthIterator<Data>& brIT ) {
  current = brIT.current;
  queue = brIT.queue;
  startpoint = brIT.startpoint;
  return *this;
}

// Move assignment
template<typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(BTBreadthIterator<Data>&& brIT ) noexcept {
  current = std::move(brIT.current);
  queue = std::move(brIT.queue);
  startpoint = std::move(brIT.startpoint);
  return *this;
}

/* ************************************************************************ */

// Comparison operators
template<typename Data>
bool BTBreadthIterator<Data>::operator==(const BTBreadthIterator<Data>& brIT) const noexcept {
  if ( queue == brIT.queue && (current) == (brIT.current) && startpoint == brIT.startpoint  )
  {
    return true ;
  }
  else
  {
    return false ;
  }
}

template<typename Data>
bool BTBreadthIterator<Data>::operator!=(const BTBreadthIterator<Data>& brIT) const noexcept {
  return (!(*this==brIT));
}

/* ************************************************************************ */

// Specific member functions (inherited from Iterator)

// (throw std::out_of_range when terminated)
template<typename Data>
Data& BTBreadthIterator<Data>::operator*() const {
  if (Terminated())
    throw std::out_of_range("Iterator terminated !");
  else
    return ( (*current).Element() ) ;
}

// (should not throw exceptions)
template<typename Data>
bool BTBreadthIterator<Data>::Terminated() const noexcept {
  if (queue.Size()==0 && current == nullptr)
    return true ;
  else
    return false ;
}

/* ************************************************************************ */

// Specific member functions (inherited from ForwardIterator)

// (throw std::out_of_range when terminated)
template<typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator++() {
  if (Terminated())
  {
    throw std::out_of_range("Iterator terminated !");
  }
  else
  {
    if (!queue.Empty())
    {
      current = queue.HeadNDequeue() ;
    }
    else
    {
      current = nullptr ;
    }

    if (current != nullptr){
      if (current->HasLeftChild()) queue.Enqueue(&(current->LeftChild()));
      if (current->HasRightChild()) queue.Enqueue(&(current->RightChild()));
    }

  }

  return *this;
}

/* ************************************************************************ */

// Specific member functions (inherited from ResettableIterator)

// (should not throw exceptions)
template<typename Data>
void BTBreadthIterator<Data>::Reset() noexcept {

  if (startpoint!=nullptr){
      queue.Clear();
      current = startpoint;
      if (current->HasLeftChild()) queue.Enqueue(&(current->LeftChild()));
      if (current->HasRightChild()) queue.Enqueue(&(current->RightChild()));
  }
}


}

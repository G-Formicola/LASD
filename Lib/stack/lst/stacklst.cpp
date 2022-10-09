
namespace lasd {

  /* ************************************************************************** */

  // Specific constructor
  // A stack obtained from a LinearContainer
  template<typename Data>                                     // : List<Data>::List(cont)
  StackLst<Data>::StackLst(const LinearContainer<Data>& cont) : List<Data>::List(cont) {
    /*ulong size = cont.Size();
    for(ulong i = 0 ; i<size ; i++){
        List<Data>::InsertAtBack(cont[i]);
    }*/
  }
  /* ************************************************************************ */

  // Copy constructor
  template<typename Data>
  StackLst<Data>::StackLst(const StackLst<Data>& source) : List<Data>::List(source) {}

  // Move constructor
  template<typename Data>
  StackLst<Data>::StackLst(StackLst<Data>&& source) noexcept : List<Data>::List(std::move(source)) {}

  /* ************************************************************************ */

  // Copy assignment
  template<typename Data>
  StackLst<Data>& StackLst<Data>::operator=(const StackLst<Data>& stack2){
    /*StackLst<Data>* tmp = new StackLst<Data>(stack2) ;
    std::swap(*this, *tmp);
    delete tmp ;*/
    List<Data>::operator=(stack2);
    return (*this);

  }

  // Move assignment
  template<typename Data>
  StackLst<Data>& StackLst<Data>::operator=(StackLst<Data>&& stack2) noexcept {
    /*std::swap(size, stack2.size);
    std::swap(head, stack2.head);
    std::swap(tail, stack2.tail);*/
    List<Data>::operator=(std::move(stack2));
    return (*this);
  }

  /* ************************************************************************ */

  // Comparison operators
  template<typename Data>
  bool StackLst<Data>::operator==(const StackLst& stack2) const noexcept {
    return List<Data>::operator==(stack2);
    /*if (size != stack2.size)
    {
        return false ;
    }
    else
    {
        if ( size > 0 ){
          Node* tmp1 = head ;
          Node* tmp2 = stack2.head ;
          for (ulong i = 0 ; i<size ; i++){
            if ( *(tmp1->element) != *(tmp2->element) ){ return false ; }
            tmp1 = (*tmp1).next ;
            tmp2 = (*tmp2).next ;
          }
        }
    }
    return true ;*/
  }

  template<typename Data>
  bool StackLst<Data>::operator!=(const StackLst& stack2) const noexcept {
    return (!(*this == stack2));
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)

  // Override Stack member (constant version; must throw std::length_error when empty)
  template<typename Data>
  const Data& StackLst<Data>::Top() const {
    if ( size == 0 ){
        throw std::length_error("Access to an empty Stack !");
    }
    else
    {
        const Data& result = List<Data>::Front();
        return result ;
    }
  }

  // Override Stack member (must throw std::length_error when empty)
  template<typename Data>
  Data& StackLst<Data>::Top() {
    if ( size == 0 ){
        throw std::length_error("Access to an empty Stack !");
    }
    else
    {
        Data& result = List<Data>::Front();
        return result ;
    }

  }

  // Override Stack member (must throw std::length_error when empty)
  template<typename Data>
  void StackLst<Data>::Pop() {
    if ( size == 0 ){
        throw std::length_error("Access to an empty Stack !");
    }
    else
    {
      List<Data>::RemoveFromFront();
    }
  }

  // Override Stack member (must throw std::length_error when empty)
  template<typename Data>
  Data StackLst<Data>::TopNPop() {
    if ( size == 0 ){
        throw std::length_error("Access to an empty Stack !");
    }
    else
    {
      Data result = List<Data>::FrontNRemove();
      return result ;
    }
  }

  // Override Stack member (copy of the value)
  template<typename Data>
  void StackLst<Data>::Push(const Data& value) {
    List<Data>::InsertAtFront(value);
  }

   // Override Stack member (move of the value)
  template<typename Data>
  void StackLst<Data>::Push(Data&& value) noexcept {
    List<Data>::InsertAtFront(std::move(value));
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)
   // Override Container member
  template<typename Data>
  void StackLst<Data>::Clear() {
      /*for ( ulong i=0 ; i<size ; i++ ){
        Pop();
      }*/
      List<Data>::Clear();
  }

  /* ************************************************************************** */

}

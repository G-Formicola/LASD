
namespace lasd {

/* ************************************************************************** */
//Destructor
template<typename Data>
QueueLst<Data>::~QueueLst(){
  Clear();
}
  // Specific constructor

  // A queue obtained from a LinearContainer
  template<typename Data>
  QueueLst<Data>::QueueLst(const LinearContainer<Data>& con) : List<Data>::List(con) {}

  /* ************************************************************************ */

  // Copy constructor
  template<typename Data>
  QueueLst<Data>::QueueLst(const QueueLst<Data>& source) : List<Data>::List(source) {}

  // Move constructor
  template<typename Data>
  QueueLst<Data>::QueueLst(QueueLst&& source) noexcept : List<Data>::List(std::move(source)) {}

/* ************************************************************************** */

// Copy assignment
template<typename Data>
QueueLst<Data>& QueueLst<Data>::operator=(const QueueLst<Data>& source){
    List<Data>::operator=(source);
    return *this ;
}

// Move assignment
template<typename Data>
QueueLst<Data>& QueueLst<Data>::operator=(QueueLst<Data>&& source) noexcept {
    List<Data>::operator=(std::move(source));
    return (*this);
}

/* ************************************************************************ */

// Comparison operators
template<typename Data>
bool QueueLst<Data>::operator==(const QueueLst<Data>& queue2) const noexcept {
    /*if ( size != queue2.size )
    {
      return false ;
    }
    else
    {
      if ( size > 0 ){
        Node* tmp1 = head ;
        Node* tmp2 = queue2.head ;
        for (ulong i = 0 ; i<size ; i++){
          if ( *(tmp1->element) != *(tmp2->element) ){ return false ; }
          tmp1 = (*tmp1).next ;
          tmp2 = (*tmp2).next ;
        }
      }
    }
    return true ;*/
    return List<Data>::operator==(queue2);
}

template<typename Data>
bool QueueLst<Data>::operator!=(const QueueLst<Data>& queue2) const noexcept {
    return (!(*this == queue2));
}

/* ************************************************************************ */

// Specific member functions (inherited from Queue)

// Override Queue member (constant version; must throw std::length_error when empty)
template<typename Data>
const Data& QueueLst<Data>::Head() const {
  if ( size == 0 )
  {
    throw std::length_error("Access to an empty Queue !");
  }
  else
  {
    const Data& result = List<Data>::Front();
    return result;
  }
}

// Override Queue member (must throw std::length_error when empty)
template<typename Data>
Data& QueueLst<Data>::Head() {
  if ( size == 0 )
  {
    throw std::length_error("Access to an empty Queue !");
  }
  else
  {
    Data& result = List<Data>::Front();
    return result;
  }
}

// Override Queue member (must throw std::length_error when empty)
template<typename Data>
void QueueLst<Data>::Dequeue() {
  if ( size == 0 )
  {
    throw std::length_error("Access to an empty Queue !");
  }
  else
  {
    List<Data>::RemoveFromFront();
  }
}

// Override Queue member (must throw std::length_error when empty)
template<typename Data>
Data QueueLst<Data>::HeadNDequeue() {
  if ( size == 0 )
  {
    throw std::length_error("Access to an empty Queue !");
  }
  else
  {
    //Data result = List<Data>::FrontNRemove();
    Data result = Head();
    Dequeue();
    return result ;
  }
}

// Override Queue member (copy of the value)
template<typename Data>
void QueueLst<Data>::Enqueue(const Data& dat) {
  List<Data>::InsertAtBack(dat);
}

// Override Queue member (move of the value)
template<typename Data>
void QueueLst<Data>::Enqueue(Data&& dat) noexcept {
  List<Data>::InsertAtBack(std::move(dat));
}

/* ************************************************************************ */

// Specific member functions (inherited from Container)
  // Override Container member
  template<typename Data>
  void QueueLst<Data>::Clear() {
      /*for ( ulong i = 0 ; i < size ; i++)
      {
        Dequeue();
      }*/
      List<Data>::Clear();
  }

/* ************************************************************************** */

}

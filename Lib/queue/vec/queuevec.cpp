
namespace lasd {

/* ************************************************************************** */

// Default constructor
template<typename Data>
QueueVec<Data>::QueueVec() : Vector<Data>::Vector(4) {}

/* ************************************************************************ */

// Specific constructor
// A queue obtained from a LinearContainer
template<typename Data>
QueueVec<Data>::QueueVec(const LinearContainer<Data>& con) : Vector<Data>::Vector(con) {
  sizeofqueue = con.Size();
}

/* ************************************************************************ */

// Copy constructor
template<typename Data>
QueueVec<Data>::QueueVec(const QueueVec<Data>& source) : Vector<Data>::Vector(source) {
  head = source.head ;
  sizeofqueue = source.sizeofqueue ;
}

// Move constructor
template<typename Data>
QueueVec<Data>::QueueVec(QueueVec&& source) noexcept : Vector<Data>::Vector(std::move(source)) {
  std::swap(head, source.head);
  std::swap(sizeofqueue, source.sizeofqueue);
}

/* ************************************************************************ */

// Copy assignment
template<typename Data>
QueueVec<Data>& QueueVec<Data>::operator=(const QueueVec<Data>& queue2){
    QueueVec<Data>* tmp = new QueueVec<Data>(queue2);
    std::swap(*this, *tmp);
    delete tmp ;
    return (*this) ;
}

// Move assignment
template<typename Data>
QueueVec<Data>& QueueVec<Data>::operator=(QueueVec<Data>&& queue2) noexcept {
    std::swap(vec, queue2.vec);
    std::swap(size, queue2.size);
    std::swap(head, queue2.head);
    std::swap(sizeofqueue, queue2.sizeofqueue);
    return (*this) ;
}

/* ************************************************************************ */

// Comparison operators
template<typename Data>
bool QueueVec<Data>::operator==(const QueueVec<Data>& queue2) const noexcept {
  if ( sizeofqueue != queue2.Size() )
  {
    return false ;
  }
  else
  {
    if(sizeofqueue > 0){
      ulong index1 ;
      ulong index2 ;
      for ( ulong i = 0 ; i < sizeofqueue ; i++ )
      {
        index1 = head + i ;
        index2 = queue2.head + i ;
        if ( vec[index1] != queue2.vec[index2] ){ return false ; }
      }
    }
  }
  return true ;
}

template<typename Data>
bool QueueVec<Data>::operator!=(const QueueVec<Data>& queue2) const noexcept {
  return ( ! ( (*this) == queue2 ) );
}

/* ************************************************************************ */

// Specific member functions (inherited from Queue)

// Override Queue member (constant version; must throw std::length_error when empty)
template<typename Data>
const Data& QueueVec<Data>::Head() const {
  if ( sizeofqueue == 0 )
  {
    throw std::length_error("Access to an empty Queue !");
  }
  else
  {
    const Data& result = vec[head] ;
    return result ;
  }
}


// Override Queue member (must throw std::length_error when empty)
template<typename Data>
Data& QueueVec<Data>::Head() {
  if ( sizeofqueue == 0 )
  {
    throw std::length_error("Access to an empty Queue !");
  }
  else
  {
    Data& result = vec[head] ;
    return result ;
  }
}

// Override Queue member (must throw std::length_error when empty)
template<typename Data>
void QueueVec<Data>::Dequeue() {
  if ( sizeofqueue == 0 )
  {
    throw std::length_error("Access to an empty Queue !");
  }
  else
  {
    head = ( (head+1) % size ) ;
    sizeofqueue-- ;
  }
}

// Override Queue member (must throw std::length_error when empty)
template<typename Data>
Data QueueVec<Data>::HeadNDequeue() {
  if ( sizeofqueue == 0 )
  {
    throw std::length_error("Access to an empty Queue !");
  }
  else
  {
    Data value = Head();
    Dequeue();
    return value ;
  }
}

// Override Queue member (copy of the value)
template<typename Data>
void QueueVec<Data>::Enqueue(const Data& dat) {
    if ( sizeofqueue == size ){ Expand(); }
    ulong tail ;
    if(sizeofqueue == 0)
    {
      tail = head ;
    }
    else
    {
      tail = (head+sizeofqueue)%size ;
    }
    vec[tail] = dat ;
    sizeofqueue++ ;
}

// Override Queue member (move of the value)
template<typename Data>
void QueueVec<Data>::Enqueue(Data&& dat) noexcept {
    if ( sizeofqueue == size ){ Expand(); }
    ulong tail ;
    if(sizeofqueue == 0)
    {
      tail = head ;
    }
    else
    {
      tail = (head+sizeofqueue)%size ;
    }
    vec[tail] = (std::move(dat));
    sizeofqueue++ ;
}

/* ************************************************************************** */

// Specific member functions (inherited from Container)
// Override Container member
template<typename Data>
void QueueVec<Data>::Clear(){
  sizeofqueue = 0 ;
}

/* ************************************************************************ */
// Auxiliary member functions

template<typename Data>
void QueueVec<Data>::Expand(){

  ulong newsize = size*2 ;

  Data* tmpVec = new Data[newsize] {};
  ulong auxIndex;

  for ( ulong i = 0 ; i < sizeofqueue ; i++ )
      {
        auxIndex = head + i ;
        std::swap(vec[auxIndex], tmpVec[i]);
      }

  std::swap(vec, tmpVec);
  size = newsize ;
  head = 0 ;

  delete[] tmpVec ;
}

}

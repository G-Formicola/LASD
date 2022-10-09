
namespace lasd {

/* ************************************************************************** */

// Specific constructors

// A vector with a given initial dimension
template<typename Data>
Vector<Data>::Vector(const ulong dim) {
  size = dim ;
  vec = new Data[dim] {};
}

// A vector obtained from a LinearContainer
template<typename Data>
Vector<Data>::Vector(const LinearContainer<Data>& container) {
  size = container.Size();
  vec = new Data[size] ;
  for (ulong i = 0; i < size; ++i) {
    vec[i] = container[i] ;
  }
}

// Copy constructor
template<typename Data>
Vector<Data>::Vector(const Vector<Data>& vect) {
  size = vect.size;
  vec = new Data[size];
  std::copy(vect.vec , vect.vec + vect.size , vec);
}

// Move constructor
template<typename Data>
Vector<Data>::Vector(Vector<Data>&& vect) noexcept {
  std::swap(size, vect.size);
  std::swap(vec, vect.vec);
}

// Destructor
template<typename Data>
Vector<Data>::~Vector() {
  delete[] vec;
}

/* ************************************************************************ */

// Copy assignment
template<typename Data>
Vector<Data>& Vector<Data>::operator=(const Vector<Data>& vect){
  Vector<Data>* tmp = new Vector<Data>(vect);
  std::swap(*tmp, *this);
  delete tmp ;
  return *this ;
}

// Move assignment
template<typename Data>
Vector<Data>& Vector<Data>::operator=(Vector<Data>&& vect) noexcept {
  std::swap(vect.vec, vec);
  std::swap(vect.size, size);
  return *this;
}

/* ************************************************************************ */

// Comparison operators

template <typename Data>
bool Vector<Data>::operator==(const Vector<Data>& vect) const noexcept {
  if (size != vect.size)
  {
    return false ;
  }
  else
  {
    for (ulong i = 0; i < size; i++)
    {
      if ( vec[i] != vect[i] ) { return false ; }
    }
    return true ;
  }
}

template <typename Data>
inline bool Vector<Data>::operator!=(const Vector<Data>& vect) const noexcept {
  return !(*this==vect);
}

/* ************************************************************************ */

// Specific member functions

// Resize the vector to a given size
template <typename Data>
void Vector<Data>::Resize(const ulong dimension) {
  if ( dimension == 0 ){
    Clear();
  }
  else if ( dimension != size )
  {
      Data* tmpVec = new Data[dimension] {};

      if ( dimension > size )
      {
          for ( ulong i = 0 ; i < size ; i++ )
          {
            std::swap(vec[i], tmpVec[i]);
          }
      }
      else if ( dimension < size )
      {
          for ( ulong i = 0 ; i < dimension ; i++ )
          {
            std::swap(vec[i], tmpVec[i]);
          }
      }

      std::swap(vec, tmpVec);
      size = dimension ;

      delete[] tmpVec ;

  }

}

/* ************************************************************************ */

// Specific member functions (inherited from Container)
// Override Container member

// Clear the vector
template<typename Data>
void Vector<Data>::Clear() {
  delete[] vec ;
  vec = nullptr ;
  size = 0 ;
}

/* ************************************************************************ */

// Specific member functions (inherited from LinearContainer)

// Override LinearContainer member (must throw std::length_error when empty)

template<typename Data>
Data& Vector<Data>::Front() const {
  if ( size == 0 )
  {
    throw std::length_error("Access to and empty vector !");
  }
  else
  {
    return vec[0];
  }
}

// Override LinearContainer member (must throw std::length_error when empty)
template<typename Data>
Data& Vector<Data>::Back() const {
  if ( size == 0 )
  {
    throw std::length_error("Access to and empty vector !");
  }
  else
  {
    return vec[size-1];
  }
}

// Override LinearContainer member (must throw std::out_of_range when out of range)

template<typename Data>
Data& Vector<Data>::operator[](const ulong index) const {
  if ( index >= size )
  {
    throw std::out_of_range("Requested index is out of range ! Vector size : " + std::to_string(size) +" !");
  }
  else
  {
    return vec[index];
  }
}

/* ************************************************************************** */


// Specific member functions (inherited from MappableContainer)

// Override MappableContainer member
template<typename Data>
void Vector<Data>::Map(const MapFunctor fun, void* par) {
  PreOrderMappableContainer<Data>::Map(fun, par);
}

/* ************************************************************************ */

// Specific member functions (inherited from PreOrderMappableContainer)

// Override PreOrderMappableContainer member
template<typename Data>
void Vector<Data>::MapPreOrder(const MapFunctor fun, void* par) {
    for ( ulong i=0 ; i<size ; i++){
        fun(vec[i], par);
    }
}

/* ************************************************************************ */

// Specific member functions (inherited from PostOrderMappableContainer)

// Override PostOrderMappableContainer member
template<typename Data>
void Vector<Data>::MapPostOrder(const MapFunctor fun, void* par) {
    ulong index = size ;
    while (index > 0)
    {
      fun(vec[--index], par);
    }

}

/* ************************************************************************ */

// Specific member functions (inherited from FoldableContainer)

// Override FoldableContainer member
template<typename Data>
void Vector<Data>::Fold(const FoldFunctor fun, const void* par1, void* par2) const {
  PreOrderFoldableContainer<Data>::Fold(fun, par1, par2);
}

/* ************************************************************************ */

// Specific member functions (inherited from PreOrderFoldableContainer)

// Override FoldableContainer member
template<typename Data>
void Vector<Data>::FoldPreOrder(const FoldFunctor fun, const void* par1, void* par2) const {
    for ( ulong i=0 ; i<size ; i++){
        fun(vec[i], par1, par2);
    }
}

/* ************************************************************************ */

// Specific member functions (inherited from PostOrderFoldableContainer)

// Override FoldableContainer member
template<typename Data>
void Vector<Data>::FoldPostOrder(const FoldFunctor fun, const void* par1, void* par2) const {
    ulong index = size ;
    while (index > 0)
    {
      fun(vec[--index], par1, par2);
    }

}

/* ************************************************************************ */

}

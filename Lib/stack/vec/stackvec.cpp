
namespace lasd {

  /* ************************************************************************** */

  // Default constructor
  template<typename Data>
  StackVec<Data>::StackVec() : Vector<Data>::Vector(3) {

  }

  /* ************************************************************************** */

  // Specific constructor
  // A stack obtained from a LinearContainer
  template<typename Data>
  StackVec<Data>::StackVec(const LinearContainer<Data>& con) : Vector<Data>::Vector(con) {
    sizeofstack = con.Size();
  }

  /* ************************************************************************ */

  // Copy constructor
  template<typename Data>
  StackVec<Data>::StackVec(const StackVec<Data>& source) : Vector<Data>::Vector(source) {
      sizeofstack = source.sizeofstack ;
  }

  // Move constructor
  template<typename Data>
  StackVec<Data>::StackVec(StackVec<Data>&& source) noexcept : Vector<Data>::Vector(source) {
    std::swap(sizeofstack, source.sizeofstack);
  }

  /* ************************************************************************ */

  // Copy assignment
  template<typename Data>
  StackVec<Data>& StackVec<Data>::operator=(const StackVec<Data>& source){
    StackVec<Data>* newStack = new StackVec<Data>(source);
    std::swap((*this),(*newStack));
    delete newStack;
    return (*this);
  }

  // Move assignment
  template<typename Data>
  StackVec<Data>& StackVec<Data>::operator=(StackVec<Data>&& source) noexcept{
    std::swap(size, source.size);
    std::swap(sizeofstack, source.sizeofstack);
    std::swap(vec, source.vec);
    return (*this) ;
  }

  /* ************************************************************************ */

  // Comparison operators
  template<typename Data>
  bool StackVec<Data>::operator==(const StackVec<Data>& stack2) const noexcept {
    if (sizeofstack != stack2.sizeofstack)
    {
      return false ;
    }
    else
    {
      if ( sizeofstack > 0 ){
        for (ulong i = 0; i < sizeofstack; i++) {
          if ( vec[i] != stack2.vec[i] ){return false ;}
        }
      }
    }
    return true ;
  }

  template<typename Data>
  bool StackVec<Data>::operator!=(const StackVec<Data>& stack2) const noexcept {
    return (!(*this == stack2));
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)

 // Override Stack member (constant version; must throw std::length_error when empty)
  template<typename Data>
  const Data& StackVec<Data>::Top() const {
    if ( sizeofstack > 0 )
    {
      ulong head = sizeofstack - 1 ;
      const Data& result = vec[head];
      return result;
    }
    else
    {
      throw std::length_error("Access to an empty stack !");
    }
  }

  // Override Stack member (must throw std::length_error when empty)
  template<typename Data>
  Data& StackVec<Data>::Top() {
    if ( sizeofstack > 0 )
    {
      ulong head = sizeofstack - 1 ;
      Data& result = vec[head];
      return result;
    }
    else
    {
      throw std::length_error("Access to an empty stack !");
    }

  }

  // Override Stack member (must throw std::length_error when empty)
  template<typename Data>
  void StackVec<Data>::Pop() {
    if ( sizeofstack > 0 )
    {
      Data tmp {} ;
      sizeofstack-- ;
      vec[sizeofstack] = tmp ;
      if ( (sizeofstack <= (size/2)) && sizeofstack > 3 ) { Reduce(); }
    }
    else
    {
      throw std::length_error("Access to an empty stack !");
    }
  }

  // Override Stack member (must throw std::length_error when empty)
  template<typename Data>
  Data StackVec<Data>::TopNPop() {
    if ( sizeofstack > 0 )
    {
        Data tmp = Top() ;
        Pop();
        return tmp ;
    }
    else
    {
      throw std::length_error("Access to an empty stack !");
    }
  }

  // Override Stack member (copy of the value)
  template<typename Data>
  void StackVec<Data>::Push(const Data& dat) {
    if ( sizeofstack == size ){
      Expand();
    }
    vec[sizeofstack] = dat ;
    sizeofstack++;
  }

  // Override Stack member (move of the value)
  template<typename Data>
  void StackVec<Data>::Push(Data&& dat) noexcept {
    if ( sizeofstack == size ){
      Expand();
    }
    vec[sizeofstack] = std::move(dat) ;
    sizeofstack++;
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  // Override Container member
  template<typename Data>
  void StackVec<Data>::Clear() {
      Vector<Data>::Clear();
      Vector<Data>::Resize(3);
      sizeofstack = 0 ;
  }
  /* ************************************************************************ */

  // Auxiliary member functions

  template<typename Data>
  void StackVec<Data>::Expand(){
    ulong newsize = size*2 ;
    Vector<Data>::Resize(newsize);
  }

  template<typename Data>
  void StackVec<Data>::Reduce(){
    ulong newsize = size - size/4 ;
    Vector<Data>::Resize(newsize);
  }

  /* ************************************************************************** */

}

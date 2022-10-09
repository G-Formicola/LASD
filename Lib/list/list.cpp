
namespace lasd {

/* ************************************************************************** */

// Default constructor
template<typename Data>
List<Data>::List(){
  head = nullptr ;
  tail = nullptr ;
  size = 0 ;
}

// Specific constructor

// A list obtained from a LinearContainer
template<typename Data>
List<Data>::List(const LinearContainer<Data>& container){

  size = container.Size();


  if (size > 0){

      struct Node* tmpnode ;
      for (ulong index = 0 ; index<size ; index++ )
      {
          tmpnode = new Node(container[index]);

          if ( index == 0 )
          {
            head = tmpnode ;
          }
          else
          {
            tail->next = tmpnode ;
          }

          tail = tmpnode ;
      }
  }

    /* Prova 2
    ulong saiz = container.Size();
    for (ulong i = 0 ; i<saiz ; i++)
      InsertAtBack(container[i]);
    */
}
/* ************************************************************************ */

// Copy constructor
template<typename Data>
List<Data>::List(const List<Data>& list){
    size = list.Size();

    if (size>0)
    {

      struct Node* auxnode = list.head ;
      struct Node* tmpnode ;

      for (ulong index = 0 ; index<size ; index++ )
      {
          tmpnode = new Node((*auxnode));

          if ( index == 0 )
          {
            head = tmpnode ;
          }
          else
          {
            tail->next = tmpnode ;
          }

          tail = tmpnode ;
          auxnode = auxnode->next ;
      }

    }
    /* Prova 2
    ulong saiz = list.Size();
    struct Node* iter = list.head ;
    for (ulong i=0 ; i<saiz ; i++){
      InsertAtBack(iter->element);
      iter = iter->next ;
    }*/
}

// Move constructor
template<typename Data>
List<Data>::List(List<Data>&& list) noexcept {
  std::swap(list.head, head);
  std::swap(list.tail, tail);
  std::swap(list.size, size);
}

/* ************************************************************************ */

// Destructor
template<typename Data>
List<Data>::~List(){
  Clear();
}
/* ************************************************************************ */

// Copy assignment
template<typename Data>
List<Data>& List<Data>::operator=(const List<Data>& list){

    List<Data>* tmplist = new List<Data>(list);
    std::swap(*this, *tmplist);
    delete tmplist;
    /* Prova 2
    Clear();
    ulong saiz = list.Size();
    struct Node* iter = list.head ;
    for (ulong i=0 ; i<saiz ; i++){
      InsertAtBack(iter->element);
      iter = iter->next;
    } */
    return (*this);
}

// Move assignment
template<typename Data>
List<Data>& List<Data>::operator=(List<Data>&& list) noexcept {
    std::swap(list.head, head);
    std::swap(list.tail, tail);
    std::swap(list.size, size);
    return *this ;
}

/* ************************************************************************ */

// Comparison operators
template<typename Data>
bool List<Data>::operator==(const List<Data>& list) const noexcept {

    if ( list.Size() != size )
    {
      return false ;
    }
    else
    {
        struct Node* aux1 = list.head ;
        struct Node* aux2 = head ;

        for (ulong index = 0 ; index<list.size ; index++)
        {
            if ( (aux1->element) != (aux2->element) )
            {
              return false ;
            }
            aux1 = aux1->next ;
            aux2 = aux2->next ;
        }

        return true ;
    }
}

template<typename Data>
inline bool List<Data>::operator!=(const List<Data>& list) const noexcept {
    return (!((*this)==list)) ;
}

/* ************************************************************************ */

// Specific member functions

// Copy of the value
template<typename Data>
void List<Data>::InsertAtFront(const Data& par) {
    struct Node* tmp = new Node(par);
    tmp->next = head ;
    head = tmp ;
    if(tail==nullptr){ tail = tmp ;}
    size = size + 1 ;
}

// 3° errore
// Move of the value
template<typename Data>
void List<Data>::InsertAtFront(Data&& par) noexcept {

    struct Node* tmp = new Node();
    tmp->element = std::move(par);
    tmp->next = head ;

    head = tmp ;
    if(tail==nullptr){ tail = tmp ;}
    size = size + 1 ;

}

  // 1° errore
 // (must throw std::length_error when empty)
template<typename Data>
void List<Data>::RemoveFromFront() {
  if ( size > 0 )
  {
    struct Node* tmp = head ;
    head = head->next ;
    size = size - 1 ;

    tmp->next = nullptr ;
    delete tmp;

    if(size == 0){
      head = nullptr;
      tail = nullptr;
    }


  }
  else
  {
    throw std::length_error("Access to an empty list !");
  }
}

// 2° errore
// (must throw std::length_error when empty)
template<typename Data>
Data List<Data>::FrontNRemove(){
  if ( size > 0 )
  {

    Data testa = Front();
    RemoveFromFront();

    return testa ;
  }
  else
  {
    throw std::length_error("Access to an empty list !");
  }
}

// Copy of the value
template<typename Data>
void List<Data>::InsertAtBack(const Data& value) {

    struct Node* tmp = new Node(value);

    if(tail!=nullptr)
    {
      tail->next = tmp ;
    }
    else
    {
      head = tmp ;
    }
    tail = tmp ;
    size = size + 1 ;

}

// Move of the value
template<typename Data>
void List<Data>::InsertAtBack(Data&& value) noexcept {

  // struct Node* tmp = new Node(std::move(value));
  struct Node* tmp = new Node();
  tmp->element = std::move(value);

  if(tail!=nullptr)
  {
    tail->next = tmp ;
  }
  else
  {
    head = tmp ;
  }
  tail = tmp ;
  size = size + 1 ;

}
/* ************************************************************************ */

// Specific member functions (inherited from Container)

// Override Container member - CHANGED
template<typename Data>
void List<Data>::Clear() {
    struct Node* tmp ;
    for (ulong i=0 ; i<size ; i++){
      tmp = head ;
      head = head->next ;
      delete tmp ;
    }
    head = nullptr ;
    tail = nullptr ;
    size = 0 ;
}

/* ************************************************************************ */

// Specific member functions (inherited from LinearContainer)

// Override LinearContainer member (must throw std::length_error when empty)
template<typename Data>
Data& List<Data>::Front() const {
  if ( size > 0 )
  {
    return (head->element) ;
  }
  else
  {
    throw std::length_error("Access to an empty list !");
  }
}

// Override LinearContainer member (must throw std::length_error when empty)
template<typename Data>
Data& List<Data>::Back() const {
  if ( size > 0 )
  {
    return (tail->element) ;
  }
  else
  {
    throw std::length_error("Access to an empty list !");
  }
}

// Override LinearContainer member (must throw std::out_of_range when out of range)
template<typename Data>
Data& List<Data>::operator[](const ulong dest) const {
  if ( dest >= size )
  {
    throw std::out_of_range("Requested index out of range. List' size : " + std::to_string(size) + " .");
  }
  else
  {
    Node* tmp = head ;

    for (ulong index = 0 ; index < dest ; index ++)
    {
      tmp = tmp->next ;
    }

    return (tmp->element) ;

  }

}
/* ************************************************************************ */

// Specific member functions (inherited from MappableContainer)

// Override MappableContainer member - CHANGED
template <typename Data>
void List<Data>::Map(const MapFunctor fun, void* par) {
  PreOrderMappableContainer<Data>::Map(fun, par);
}

/* ************************************************************************ */
// Specific member functions (inherited from PreOrderMappableContainer)

// Override PreOrderMappableContainer member - CHANGED
template<typename Data>
void List<Data>::MapPreOrder(const MapFunctor fun, void* par) {
    MapPreOrder(fun,par,head);

    /* Iterativo

    if(size>0){

      Node* tmp = head ;

      for (ulong i = 0; i < size; i++) {
        fun((tmp->element), par);
        tmp = tmp->next ;
      }

    }*/
}

/* ************************************************************************ */

// Specific member functions (inherited from PostOrderMappableContainer)

 // Override PostOrderMappableContainer member - CHANGED
template<typename Data>
void List<Data>::MapPostOrder(const MapFunctor fun, void* par) {

    MapPostOrder(fun,par,head);

    /* Iterativo

    ulong dim = Container::Size();

    if(dim>0){
      Node* rev_list[dim];
      Node* tmp = head ;
      for (ulong i = 0; i < dim; i++) {
        rev_list[i] = tmp ;
        tmp = tmp->next ;
      }

      ulong index = dim ;
      while (index > 0)
      {
        fun((rev_list[--index]->element), par);
      }
    }*/

  }

/* ************************************************************************ */


// Specific member functions (inherited from FoldableContainer)

// Override FoldableContainer member - CHANGED
template <typename Data>
void List<Data>::Fold(const FoldFunctor fun, const void* par1, void* par2) const {
  PreOrderFoldableContainer<Data>::Fold(fun, par1, par2);
}

/* ************************************************************************** */

// Specific member functions (inherited from PreOrderFoldableContainer)

 // Override FoldableContainer member - CHANGED
 template<typename Data>
 void List<Data>::FoldPreOrder(const FoldFunctor fun, const void* par1, void* par2) const {

   FoldPreOrder(fun,par1,par2,head);

   /* Iterativo

   if (size>0)
   {
     Node* tmp = head ;

     for (ulong i = 0; i < size; i++) {
       fun((tmp->element), par1, par2);
       tmp = tmp->next ;
     }

   }*/
 }

/* ************************************************************************ */

// Specific member functions (inherited from PostOrderFoldableContainer)

// Override FoldableContainer member - CHANGED
template<typename Data>
void List<Data>::FoldPostOrder(const FoldFunctor fun, const void* par1, void* par2) const {

  FoldPostOrder(fun,par1,par2,head);

  /* Iterativo

  ulong dim = Container::Size();

  if(dim>0){

    Node* rev_list[dim];
    Node* tmp = head ;

    for (ulong i = 0; i < dim; i++) {
      rev_list[i] = tmp ;
      tmp = tmp->next ;
    }

    ulong index = dim ;
    while (index > 0)
    {
      fun((rev_list[--index]->element), par1, par2);
    }

  }*/
}

/* ************************************************************************ */


// Accessory function executing from one point of the list onwards - NEW
template<typename Data>
void List<Data>::MapPreOrder(const MapFunctor fun, void* par1, Node* head) {
  if (head != nullptr){
    fun(head->element,par1);
    MapPreOrder(fun,par1,head->next);
  }
}


// Accessory function executing from one point of the list onwards - NEW
template<typename Data>
void List<Data>::MapPostOrder(const MapFunctor fun, void* par1, Node* head) {
  if (head != nullptr){
    MapPostOrder(fun,par1,head->next);
    fun(head->element,par1);
  }
}

/* ************************************************************************ */

// Auxiliary member functions (for PreOrderFoldableContainer & PostOrderFoldableContainer)

// Accessory function executing from one point of the list onwards - NEW
template<typename Data>
void List<Data>::FoldPreOrder(const FoldFunctor fun, const void* par1, void* par2, Node* head) const {
  if (head != nullptr){
    fun(head->element,par1,par2);
    FoldPreOrder(fun,par1,par2,head->next);
  }
}

// Accessory function executing from one point of the list onwards - NEW
template<typename Data>
void List<Data>::FoldPostOrder(const FoldFunctor fun, const void* par1, void* par2, Node* head) const {
  if (head != nullptr){
    FoldPostOrder(fun,par1,par2,head->next);
    fun(head->element,par1,par2);
  }
}

}

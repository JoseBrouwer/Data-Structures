//Name: Jose Brouwer
template<typename T>
List<T>::const_iterator::const_iterator()
{
  current = nullptr;
}
template<typename T>
const T& List<T>::const_iterator::operator*() const
{
  return retrieve();
}

template<typename T>
typename List<T>::const_iterator & List<T>::const_iterator::operator++()
{
  current = current->next;
  return *this;
}
template<typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++(int)
{
  const_iterator old = *this;
  ++(*this);
  return old;
}
template<typename T>
typename List<T>::const_iterator & List<T>::const_iterator::operator--()
{
  current = current->prev;
  return *this;
}
template<typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator--(int)
{
  const_iterator old = *this;
  --(*this);
  return old;
}

template<typename T>
bool List<T>::const_iterator::operator==(const const_iterator &rhs) const
{
  return current == rhs.current;
}
template<typename T>
bool List<T>::const_iterator::operator!=(const const_iterator &rhs) const
{
  return !(*this == rhs);
}

template<typename T>
T & List<T>::const_iterator::retrieve() const
{
  return current->data;
}
template<typename T>
List<T>::const_iterator::const_iterator(Node *p) : current{p}
{}

template<typename T>
List<T>::iterator::iterator()
{}
template<typename T>
T& List<T>::iterator::operator*()
{
  return const_iterator::retrieve();
}
template<typename T>
const T& List<T>::iterator::operator*() const
{
  return const_iterator::operator*();
}

template<typename T>
typename List<T>::iterator & List<T>::iterator::operator++()
{
  this->current = this->current->next;
  return *this;
}
template<typename T>
typename List<T>::iterator List<T>::iterator::operator++(int)
{
  iterator old = *this;
  ++(*this);
  return old;
}
template<typename T>
typename List<T>::iterator & List<T>::iterator::operator--()
{
  this->current = this->current->prev;
  return *this;
}
template<typename T>
typename List<T>::iterator List<T>::iterator::operator--(int)
{
  iterator old = *this;
  --(*this);
  return old;
}

template<typename T>
List<T>::iterator::iterator(Node *p): const_iterator{p}
{}

template<typename T>
List<T>::List()
{
  init();
}
template<typename T>
List<T>::List(const List &rhs)
{
  init();
  for(auto & x: rhs)
    push_back(x);
}
template<typename T>
List<T>::List(List && rhs)
  : theSize{rhs.theSize}, head{rhs.head}, tail{rhs.tail}
{
  rhs.theSize = 0;
  rhs.head = nullptr;
  rhs.tail = nullptr;
}
template<typename T>
List<T>::List(int num, const T& val)
{
  init();
  for(int i = 0; i < num; i++)
    push_front(val);
}
template<typename T>
List<T>::List(const_iterator start, const_iterator end)
{
  init();
  while(start != end)
  {
    push_back(*start);
    start++;
  }
}
template<typename T>
List<T>::List(std::initializer_list<T> iList)
{
  init();
  for(auto i : iList)
    push_back(i);
}
template<typename T>
List<T>::~List()
{
  clear();
  delete head;
  delete tail;
}
template<typename T>
const List<T>& List<T>::operator=(const List &rhs)
{
  List copy = rhs; //create List named copy that points to rhs
  std::swap(*this, copy); //swap the values of the calling obj and copy
  return *this; //the calling obj is now the same as copy
}
template<typename T>
List<T>& List<T>::operator=(List && rhs)
{
  //swap member data
  std::swap( theSize, rhs.theSize );
  std::swap( head, rhs.head );
  std::swap( tail, rhs.tail );
  return *this;
}
template<typename T>
List<T>& List<T>::operator=(std::initializer_list<T> iList)
{
  clear();
  for(auto i : iList)
    push_back(i);
  return *this;
}

template<typename T>
int List<T>::size() const
{
  return theSize;
}
template<typename T>
bool List<T>::empty() const
{
  return (size() == 0);
}
template<typename T>
void List<T>::clear()
{
  while(!empty())
    pop_front();
}
template<typename T>
void List<T>::reverse()
{
  List<T> temp = *this; //copy calling obj into temp list
  iterator itr1 = begin();
  iterator itr2 = --temp.end();
  for(int i = 0; i < theSize; i++) //do for the number of items
  {
    *itr1 = *itr2; //assign the values
    itr1++; //move forward in calling obj
    itr2--; //move backwards in temp
  }
  //temp cleared by destructor
}

template<typename T>
T& List<T>::front()
{
  return *begin();
}
template<typename T>
const T& List<T>::front() const
{
  return *begin();
}
template<typename T>
T& List<T>::back()
{
  return *--end();
}
template<typename T>
const T& List<T>::back() const
{
  return *--end();
}

template<typename T>
void List<T>::push_front(const T & val)
{
  insert(begin(), val);
}
template<typename T>
void List<T>::push_front(T && val)
{
  insert(begin(), std::move(val));
}
template<typename T>
void List<T>::push_back(const T & val)
{
  insert(end(), val);
}
template<typename T>
void List<T>::push_back(T && val)
{
  insert(end(), std::move(val));
}
template<typename T>
void List<T>::pop_front()
{
  erase(begin());
}
template<typename T>
void List<T>::pop_back()
{
  erase(--end());
}

template<typename T>
void List<T>::remove(const T& val)
{
  typename List<T>::iterator::iterator itr = begin();
  while(itr != end())
  {
    if(*itr == val) //if data at iterator = val
      itr = erase(itr); //call erase on the node
    else //since erase returns the item next to the removed we must check again
      itr++; //hence why the increase in iterator is within an else
  }
}

template<typename T>
template<typename PREDICATE>
void List<T>::remove_if(PREDICATE pred)
{
  List<T>::iterator itr = begin();
  for(itr; itr != end();)
  {
    if(pred(*itr)) //if true
      itr = erase(itr); //erase node
    else
      itr++; //same case as remove
  }
}
template<typename T>
void List<T>::print(std::ostream& os, char ofc) const
{
  List<T>::const_iterator itr = begin();
  while(itr != end())
  {
    if(itr != --end())
    {
      os << *itr << ofc;
    }
    else
      os << *itr;
    itr++;
  }
}
template<typename T>
typename List<T>::iterator List<T>::begin()
{
  return iterator(head->next);
}
template<typename T>
typename List<T>::const_iterator List<T>::begin() const
{
  return const_iterator(head->next);
}
template<typename T>
typename List<T>::iterator List<T>::end()
{
  return iterator(tail);
}
template<typename T>
typename List<T>::const_iterator List<T>::end() const
{
  return const_iterator(tail);
}
template<typename T>
typename List<T>::iterator List<T>::insert(iterator itr, const T& val)
{
  Node *p = itr.current; //store current into a temp Node ptr
  ++theSize; //increase the size since were inserting
  //the new itr's ptr has prev's next be a new node
  return iterator(p->prev = p->prev->next = new Node{val, p->prev, p});
}
template<typename T>
typename List<T>::iterator List<T>::insert(iterator itr,T && val)
{
  Node *p = itr.current;
  ++theSize;
  return iterator(p->prev = p->prev->next = new Node{std::move(val), p->prev, p});
}
template<typename T>
typename List<T>::iterator List<T>::erase(iterator itr)
{
  Node *p = itr.current; //store currentPtr in p
  iterator retVal(p->next); //retrieve the value ahead of current
  p->prev->next = p->next; //make previous' next = p->next
  p->next->prev = p->prev; //make next's previous = p->previous
  delete p; //delete the temp ptr
  --theSize; //reduce the size by 1
  return retVal; //return the value ahead of the removed item
}
template<typename T>
typename List<T>::iterator List<T>::erase(iterator start, iterator end)
{
  for(iterator itr = start; itr != end;)
    itr = erase(itr); //loop erase unitl we reach end
  return end;
}

template<typename T>
void List<T>::init()
{
  theSize = 0;
  head = new Node;
  tail = new Node;
  head->next = tail;
  tail->prev = head;
}

template<typename T>
bool operator==(const List<T> & lhs, const List<T> &rhs)
{
  //YOU CAN SCOPE RESOLUTE AND USE ITERATORS IF THIS VERSION DOESNT WORK
  typename List<T>::const_iterator::const_iterator itr1 = lhs.begin();
  typename List<T>::const_iterator::const_iterator itr2 = rhs.begin();
  if(lhs.size() != rhs.size())
    return false;
  for(int i = 0; i < lhs.size(); i++) //iterate amount of items
  {
    if(*itr1 != *itr2) //if values in the iterator position dont match
      return false;
    itr1++;
    itr2++;
  }
  return true; //if loop completes then the lists are the same
}
template<typename T>
bool operator!=(const List<T> & lhs, const List<T> &rhs)
{
  return !(lhs == rhs);
}
template<typename T>
std::ostream & operator<<(std::ostream &os, const List<T> &l)
{
  l.print(os);
  return os;
}

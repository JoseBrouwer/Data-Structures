//Name: Jose Brouwer
//Section: 5
#ifndef _TVECTOR_HPP
#define _TVECTOR_HPP

//Default and parameter constructor
template<typename T>
TVector<T>::TVector()
{
  capacity = SPARECAPACITY;
  size = 0; //is empty
  array = new T[capacity]; //create a dynamic array of type T
}
template<typename T>
TVector<T>::TVector(T val, int num)
{
  capacity = num + SPARECAPACITY;
  size = num;
  array = new T[capacity];
  for(int i = 0; i < size; i++)
    array[i] = val; //populate array with copies of val
}

//Destructor and Copy
template<typename T>
TVector<T>::~TVector()
{
  delete [] array;
}
template<typename T>
TVector<T>::TVector(const TVector<T>& v)
{
  capacity = v.capacity; //copy member data
  size = v.size;
  array = new T[capacity]; //create new array
  for(int i = 0; i < capacity; i++)
    array[i] = v.array[i]; //copy param array contents
}
template<typename T>
TVector<T>& TVector<T>::operator=(const TVector<T>& v)
{
  if(this != &v) //protect against self assignment
  {
    delete [] array; //clear current array pointer
    capacity = v.capacity; //copy member data
    size = v.size;
    array = new T[capacity]; //create new array
    for(int i = 0; i < capacity; i++)
      array[i] = v.array[i]; //copy param array contents

    return *this; //for cascading
  }
}

//Move
template<typename T>
TVector<T>::TVector(TVector<T> && v)
{
  capacity = v.capacity; //copy member data
  size = v.size;
  array = v.array; //copy address to param array

  v.array = nullptr; //null param pointer
  v.capacity = v.size = 0; //null param member data
}
template<typename T>
TVector<T>& TVector<T>::operator=(TVector<T> && v)
{
  std::swap(capacity, v.capacity);
  std::swap(size, v.size);
  std::swap(array, v.array);
  return *this;
}

template<typename T>
bool TVector<T>::IsEmpty() const
{
  if(size == 0) //if empty
    return true;
  return false;
}
template<typename T>
void TVector<T>::Clear()
{
  T* newArray = new T[capacity];
  delete [] array;
  array = newArray;
  size = 0; //represents empty container
}
template<typename T>
int TVector<T>::GetSize() const
{
  return size;
}

template<typename T>
void TVector<T>::InsertBack(const T& d)
{
  if(size < capacity)
  {
    array[size] = d; //insert item at back
    size++;
  }
  else //if full
  {
    SetCapacity(capacity*2);
    array[size] = d; //set final index to d
    size++;
  }
}
template<typename T>
void TVector<T>::RemoveBack()
{
  if(!IsEmpty()) //if not empty
  {
    size--; //reduce size by 1
    copyArray(0, size);
  }
  else
    return; //if empty do nothing
}

template<typename T>
T& TVector<T>::GetFirst() const
{
  if(size > 0)
    return array[0];
  else
    return dummy;
}
template<typename T>
T& TVector<T>::GetLast() const
{
  if(size > 0)
    return array[size - 1];
  else
    return dummy;
}

template<typename T>
TVectorIterator<T> TVector<T>::GetIterator() const
{
  TVectorIterator<T> itr;
  if(!IsEmpty())
  {
    itr.ptr = &array[0];
    itr.vsize = size;
    itr.index = 0;
  }
  return itr;
}
template<typename T>
TVectorIterator<T> TVector<T>::GetIteratorEnd() const
{
  TVectorIterator<int> itr;
  if(!IsEmpty())
  {
    itr.ptr = &array[size - 1];
    itr.vsize = size;
    itr.index = size - 1;
  }
  return itr;
}
template<typename T>
void TVector<T>::SetCapacity(unsigned int c)
{
  capacity = c; //update capacity
  if(capacity < size) //if capacity is less than size
  {
    copyArray(0, capacity);
    size = capacity; //set size to capacity
  }
  else
    copyArray(0, size);
}
template<typename T>
TVectorIterator<T> TVector<T>::Insert(TVectorIterator<T> pos, const T& d)
{
  if(IsEmpty())
  {
    size++; //inc size
    pos.vsize = size;
    pos.index = 0;
    pos.ptr = &array[0];
    array[0] = d; //place item in first slot
    return pos; //return iterator
  }
  else if(pos.index > size || pos.index < 0) //if pos is invalid
  {
    if(size == capacity)
      SetCapacity(capacity*2);
    array[size + 1] = d; //place the item at the end
    size++; //inc to new size
    pos.index = pos.vsize = size; //update iterator member data
    pos.ptr = &array[pos.index];
    return pos; //return iterator
  }
  else
  {
    if(size == capacity)
      SetCapacity(capacity*2); //double if full
    T* newArray = new T[capacity]; //new array to copy to
    for(int i = 0; i < pos.index; i++) //copy items up to pos
      newArray[i] = array[i];
    for(int i = pos.index; i < size; i++) //copy rest of array
      newArray[i + 1] = array[i]; //shifting items right
    newArray[pos.index] = d; //insert item at pos
    size++;
    delete [] array;
    array = newArray;
    pos.vsize = size; //set iterator size
    pos.ptr = &array[pos.index];
    return pos; //return iterator
  }
}
template<typename T>
TVectorIterator<T> TVector<T>::Remove(TVectorIterator<T> pos)
{
  if(IsEmpty())
  {
    pos.ptr = &array[0];
    pos.index = 0;
    pos.vsize = size;
    return pos; //return default iterator
  }
  T* newArray = new T[capacity]; //new array to copy to
  //copy around the item to remove
  for(int i = 0; i < pos.index; i++)
    newArray[i] = array[i];
  for(int i = pos.index + 1; i < size; i++)
    newArray[i - 1] = array[i];
  size--; //reduce size;
  delete [] array;
  array = newArray;
  pos.vsize = size; //set iterator size
  pos.ptr = &array[pos.index];
  return pos;
}
template<typename T>
TVectorIterator<T> TVector<T>::Remove
(TVectorIterator<T> pos1, TVectorIterator<T> pos2)
{
  if(IsEmpty())
  {
    TVectorIterator<T> itr; //default iterator
    return itr; //return default
  }
  else if(pos1.index > pos2.index) //if first is after second
    return pos1; //return first

  T* newArray = new T[capacity];
  int diff = pos2.index - pos1.index; //calc how many items are removed
  //copy items before and after the specified range
  int i = 0;
  for(i = 0; i < pos1.index; i++)
    newArray[i] = array[i];
  for(int j = pos2.index; j < size; j++)
  {
    newArray[i] = array[j];
    i++;
  }
  delete [] array;
  array = newArray;
  size -= diff; //subtract removed items;
  pos2.vsize = size;
  pos2.ptr = &array[pos1.index]; //items should be shifted to this position
  return pos2;
}
template<typename T>
void TVector<T>::Print(std::ostream& os, char delim) const
{
  for(int i = 0; i < size; i++)
  {
    os << array[i] << delim;
  }
}
template<typename T>
void TVector<T>::copyArray(int from, int to)
{
  T* newArray = new T[capacity];
  for(int i = from; i < to; i++)
    newArray[i] = array[i]; //copy array items
  delete [] array;
  array = newArray;
}

template <typename T>
TVector<T> operator+(const TVector<T>& t1, const TVector<T>& t2)
{
  TVector<T> t; //new vector
  TVectorIterator<T> newItr = t.GetIterator(); //new vector itr
  TVectorIterator<T> itr1 = t1.GetIterator(); //param1 itr
  TVectorIterator<T> itr2 = t2.GetIterator(); //param2 itr
  //itr1.Next();
  for(int i = 0; i < t1.GetSize(); i++)
  {
    newItr = t.Insert(newItr, itr1.GetData()); //copy t1
    itr1.Next();
    newItr.Next();
  }
  for(int i = 0; i < t2.GetSize(); i++)
  {
    newItr = t.Insert(newItr, itr2.GetData()); //copy t2
    itr2.Next();
    newItr.Next();
  }
  return t;
}

template <typename T>
TVectorIterator<T>::TVectorIterator()
{
  ptr = nullptr;
  index = 0;
  vsize = 0;
}
template <typename T>
bool TVectorIterator<T>::HasNext() const
{
  if((index + 1) <= vsize)
    return true;
  else
    return false;
}
template <typename T>
bool TVectorIterator<T>::HasPrevious() const
{
  if((index - 1) >= 0)
    return true;
  else
    return false;
}
template <typename T>
TVectorIterator<T> TVectorIterator<T>::Next()
{
  if(ptr != nullptr && index < vsize) //not null and not at end
  {
    index++;
    ptr++;
  }
  return *this; //is this how we return an iterator?
}
template <typename T>
TVectorIterator<T> TVectorIterator<T>::Previous()
{
  if(ptr != nullptr && index > 0)
  {
    index--;
    ptr--;
  }
  return *this;
}
template <typename T>
T& TVectorIterator<T>::GetData() const
{
  if(ptr == nullptr)
    return TVector<T>::dummy;
  else
    return *ptr;
}
template <typename T>
int TVectorIterator<T>::GetIndex() const
{
  return index;
}

#endif

//Name: Jose Brouwer
template <typename T>
std::ostream& operator<< (std::ostream& os, const Stack<T>& a)
{
  a.print(os);
  return os;
}
template <typename T>
bool operator== (const Stack<T>& s1, const Stack <T>& s2)
{
  auto itr1 = s1.cbegin();
  auto itr2 = s2.cbegin();
  while(itr1 != s1.cend() || itr2 != s2.cend())
  {
    if(*itr1 != *itr2)
      return false;
    else
    {
      itr1++;
      itr2++;
    }
  }
  return true;
}
template <typename T>
bool operator!= (const Stack<T>& s1, const Stack <T>& s2)
{
  return !(s1 == s2);
}
template <typename T>
bool operator<= (const Stack<T>& a, const Stack <T>& b)
{
  auto itr1 = a.cbegin();
  auto itr2 = b.cbegin();
  if(a.size() == b.size()) //if same sizes
  {
    while(itr1 != a.cend()) //until end is not reached
    {
      if(*itr1 > *itr2) //if ai > bi
        return false;
      else //keep going
      {
        itr1++;
        itr2++;
      }
    }
  }
  return true;
}

template <typename T>
Stack<T>::Stack()
{}
template <typename T>
Stack<T>::~Stack()
{
  clear();
}
template <typename T>
Stack<T>::Stack(const Stack<T>& s)
{
  aStack = s.aStack; //calling assignment operator in List?
}
template <typename T>
Stack<T>::Stack(Stack<T> && s)
{
  aStack = s.aStack; //copy
  s.aStack = nullptr; //null out
}

template <typename T>
Stack<T> & Stack<T>::operator= (const Stack <T>& s)
{
  aStack = s.aStack;
  return *this;
}
template <typename T>
Stack<T> & Stack<T>::operator=(Stack<T> && s)
{
  std::swap(aStack, s.aStack);
  return *this;
}

template <typename T>
bool Stack<T>::empty() const
{
  if(aStack.empty()) //call list empty fucntion, scope resolute?
    return true;
  return false;
}

template <typename T>
void Stack<T>::clear()
{
  aStack.clear(); //call List clear function
}
template <typename T>
void Stack<T>::push(const T& x)
{
  aStack.push_back(x);
}
template <typename T>
void Stack<T>::push(T && x)
{
  aStack.push_back(std::move(x));
}
template <typename T>
void Stack<T>::pop()
{
  aStack.pop_back();
}

template <typename T>
T& Stack<T>::top()
{
  return aStack.back();
}
template <typename T>
const T& Stack<T>::top() const
{
  return aStack.back();
}

template <typename T>
int Stack<T>::size() const
{
  return aStack.size();
}

template <typename T>
void Stack<T>::print(std::ostream& os, char ofc) const
{
  auto itr = aStack.cend();
  while(itr != aStack.cbegin())
  {
    os << *itr << ofc;
    itr--;
  }
}

template <typename T>
typename std::list<T>::const_iterator Stack<T>::cbegin() const
{
  return aStack.cbegin();
}
template <typename T>
typename std::list<T>::const_iterator Stack<T>::cend() const
{
  return aStack.cend();
}

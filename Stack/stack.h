//Name: Jose Brouwer
#ifndef DL_STACK_H
#define DL_STACK_H
#include <iostream>
#include <list>

namespace cop4530
{
  template <typename T>
  class Stack {
  public:
    Stack(); //zero-argument constructor.
    ~Stack(); //destructor.
    Stack(const Stack<T>&); //copy constructor.
    Stack(Stack<T> &&); //move constructor.

    Stack<T>& operator= (const Stack <T>&); //copy assignment operator=.
    Stack<T> & operator=(Stack<T> &&); //move assignment operator=

    bool empty() const; //returns true if the Stack contains no elements, and false otherwise.

    void clear(); //delete all elements from the stack.
    void push(const T& x); //adds  x  to the Stack.   copy version.
    void push(T && x); //adds x to the Stack. move version.
    void pop(); //removes and discards the most recently added element of the Stack.

    T& top(); //returns a reference to the most recently added element of the Stack (as a modifiable L-value).
    const T& top() const; //accessor that returns the most recently added element of the Stack (as a const reference)

    int size() const; //returns the number of elements stored in the Stack.

    /*print elements of Stack to ostream os. ofc is the separator between elements
    in the stack when they are printed out. Note that print() prints elements in
    the opposite order of the Stack (that is, the oldest element should be printed first).*/
    void print(std::ostream& os, char ofc = ' ') const;

    typename std::list<T>::const_iterator cbegin() const;
    typename std::list<T>::const_iterator cend() const;

  private:
    std::list<T> aStack;
  };

  //invokes the print() method to print the Stack<T> a in the specified iostream
  template <typename T>
  std::ostream& operator<< (std::ostream& os, const Stack<T>& a);

  //returns true if the two compared Stacks have the same elements, in the same order, and false otherwise
  template <typename T>
  bool operator== (const Stack<T>&, const Stack <T>&);

  template <typename T>
  bool operator!= (const Stack<T>&, const Stack <T>&); //opposite of operator==().

  /*returns true if every element in Stack a is smaller than or equal to the
  corresponding element of Stack b, i.e., if repeatedly invoking top() and pop()
  on both a and b,  we will generate a sequence of elements ai from a and bi from b,
  and for every i,  ai ≤ bi, until a is empty. (Note that this also means that a
  cannot have more elements than b for this condition to be true). Return false otherwise.*/
  template <typename T>
  bool operator<= (const Stack<T>& a, const Stack <T>& b);

  #include "stack.hpp"
  #endif
}

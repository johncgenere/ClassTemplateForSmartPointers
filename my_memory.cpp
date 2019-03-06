/*
  Name: John Genere
*/

#ifndef MY_MEMORY_CPP
#define MY_MEMORY_CPP

#include <iostream>
#include <algorithm>
#include "my_memory.h"
using namespace std;

// default constuctor
template <class Type>
my_unique_ptr<Type>::my_unique_ptr(){
  pointer = nullptr;      // when object declared, pointer points to null
}

// constructor that takes pointer and sets object to point to the same place
template <class Type>
my_unique_ptr<Type>::my_unique_ptr(Type *ptr){
  pointer = new Type(*ptr);   // sets object to point to the same place Type * points to
}

// move constructor
template <class Type>
my_unique_ptr<Type>::my_unique_ptr(my_unique_ptr && obj){
  pointer = nullptr;
  swap(pointer, obj.pointer);
  // the object being passed in is now set to nullptr
  // object being created now points to where the passed in obj pointed to
}

// destructor
template <class Type>
my_unique_ptr<Type>::~my_unique_ptr(){
  if (pointer != nullptr)     // pointer points somewhere
    delete pointer;
    pointer = nullptr;
}

// Dereference operator
template <class Type>
Type& my_unique_ptr<Type>::operator*(){
  return *pointer;
}

// -> operator
template <class Type>
Type* my_unique_ptr<Type>::operator->(){
  return pointer;
}

// Move assignment
template <class Type>
my_unique_ptr<Type>& my_unique_ptr<Type>::operator=(my_unique_ptr <Type> && rhs){
  // if the rhs is itself, just return itself
  if (&rhs == this)
    return *this;
  if (pointer != nullptr){     // pointer points somewhere
    delete pointer;            // free up space
    pointer = nullptr;
  }

  swap(pointer, rhs.pointer);

  return *this;
}

//Default constructor that sets all inner pointers to nullptr
template <class Type>
my_shared_ptr<Type>::my_shared_ptr(){
  pointer = nullptr;     // when object declared, pointer points to null
  counter = nullptr;     // when object declared, pointer points to null
}

// Constructor that takes Type * as a parameter and sets the object to point there
template <class Type>
my_shared_ptr<Type>::my_shared_ptr(Type *ptr){
  pointer = new Type(*ptr);     // pointer points to same place Type * points to
  counter = new int(1);         // counter now at one
}

// Copy constructor  -> does deep copy
template <class Type>
my_shared_ptr<Type>::my_shared_ptr(const my_shared_ptr &ptr){
  if (ptr.pointer == nullptr){  // in case rhs doesn't point somewhere
    pointer = nullptr;
    counter = nullptr;
  }
  else {
    pointer = new Type(*ptr.pointer);   // pointer gets mem address of ptr pointer
    ++(*(ptr.counter));        // copy made so counter of object being passed by ++
    counter = new int(*ptr.counter);    // objects get the same counter value
  }
}

// Move constructor
template <class Type>
my_shared_ptr<Type>::my_shared_ptr(my_shared_ptr && ptr){
  pointer = nullptr;
  counter = nullptr;
  swap(pointer, ptr.pointer);     // pointer swaps value with ptr.pointer
  swap(counter, ptr.counter);     // counter swaps value with ptr.counter
}

// Destructor
template <class Type>
my_shared_ptr<Type>::~my_shared_ptr(){

  if (pointer != nullptr){    // pointer points somewhere
    delete pointer;           // free up space
    delete counter;
    pointer = nullptr;
    counter = nullptr;
  }
}

// Dereference operator * that returns a reference to the item pointed by the object
template <class Type>
Type& my_shared_ptr<Type>::operator*(){
  return *pointer;
}

// Operator -> that returns the pointer to the object.
template <class Type>
Type* my_shared_ptr<Type>::operator->(){
  return pointer;
}

// Copy Assignment
template <class Type>
my_shared_ptr<Type>& my_shared_ptr<Type>::operator=(const my_shared_ptr &rhs){
  // if the rhs is itself, just return itself
  if(&rhs == this)
    return *this;

  if (pointer != nullptr){       // pointer points somewhere
    this -> counter -= 1;        // decrease counter since new value will be given
    if (this -> counter == 0){
      delete pointer;  // releases block of memory iff no other pointer is pointing there
    }
  }

  if (rhs.pointer == nullptr){   // in case rhs doesn't point somewhere
    pointer = nullptr;
    counter = nullptr;
  }

  else{
    pointer = new Type(*rhs.pointer);  // pointer gets mem address of ptr pointer
    (*(rhs.counter))++;        // copy made so counter of object being passed by ++
    counter = new int(*rhs.counter);   // objects get the same counter value
  }

  return *this;
}

// Move Assignment
template <class Type>
my_shared_ptr<Type>& my_shared_ptr<Type>::operator=(my_shared_ptr && rhs){
  // if the rhs is itself, just return itself
  if(&rhs == this)
    return *this;
  if (pointer != nullptr){     // pointer points somewhere
    this -> counter -= 1;      // decrease counter since new value will be given
    if (this -> counter == 0){
      delete pointer;  // releases block of memory iff no other pointer is pointing there
      pointer = nullptr;
    }
  }

  swap(pointer, rhs.pointer);
  swap(counter, rhs.counter);

  return *this;
}

#endif

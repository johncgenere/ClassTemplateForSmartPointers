/*
  Name: John Genere
*/

#ifndef MY_MEMORY_H
#define MY_MEMORY_H

template <class Type>
class my_unique_ptr{
public:
  // default constructor that initializes object to point to nullptr
  my_unique_ptr();
  // Constructor that takes a pointer Type * as a parameter and sets the object to point there
  explicit my_unique_ptr(Type *ptr);
  // Move constructor that takes my_unique_ptr object and constructs a new object from it
  explicit my_unique_ptr(my_unique_ptr && obj);
  // Destructor that releases/deletes the block of memory pointed by the object
  ~my_unique_ptr();
  // Dereference operator * that returns a reference to the item pointed by the object
  Type& operator*();
  // Operator -> that returns the pointer to the object. It allows to use the my_unique_ptr object for class member access
  Type* operator->();
  // Move assignment operator
  my_unique_ptr& operator=(my_unique_ptr && rhs);
  // Raw pointer is true if pointing somewhere
  operator bool() const { return pointer; }
  // Raw pointer false when pointing nowhere
  bool operator!() const { return !pointer; }
  // Copy constructor should be explicitly disabled/deleted
  my_unique_ptr(const my_unique_ptr&) = delete;
  // Copy assignment operator must be explicitly disabled/deleted
  my_unique_ptr& operator=(const my_unique_ptr&) = delete;

private:
  Type *pointer;  // only var needed
};

template <class Type>
class my_shared_ptr{
public:
  // Default constructor that sets all inner pointers to nullptr
  my_shared_ptr();
  // Constructor that takes Type * as a parameter and sets the object to point there
  explicit my_shared_ptr(Type *ptr);
  // Copy constructor
  explicit my_shared_ptr(const my_shared_ptr &ptr);
  // Move constructor
  explicit my_shared_ptr(my_shared_ptr && ptr);
  // Destructor
  ~my_shared_ptr();
  // Dereference operator * that returns a reference to the item pointed by the object
  Type& operator*();
  // Operator -> that returns the pointer to the object. It allows to use the my_shared_ptr object for class member access
  Type* operator->();
  // Copy Assignment
  my_shared_ptr& operator=(const my_shared_ptr &rhs);
  // Move Assignment
  my_shared_ptr& operator=(my_shared_ptr && rhs);
  // Raw pointer is true if pointing somewhere
  operator bool() const { return pointer; }
  // Raw pointer false when pointing nowhere
  bool operator!() const { return !pointer; }
private:
  Type *pointer;    // regular pointer
  int *counter;    // tracks how many pointers point to the same memory address
};

#include "my_memory.cpp"
#endif

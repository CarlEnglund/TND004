/**********************************************
* File: BiIterator.cpp                        *
* Author: Aida Nordman                        *
* Course: TND004, Lab 2                       *
* Date: VT2, 2014                             *
* Description: class biIterator               *
* Represents bidirectional iterators          *
***********************************************/


#include "BiIterator.h"


#ifndef DOXYGEN_SHOULD_SKIP_THIS


// Constructor
BiIterator::BiIterator(Node *ptr)
 : current(ptr)
 {

 }


//Dereferencing operator
ELEMENT& BiIterator::operator*() const
{
  //Return the value for the current node.
  return this->current->value;
}


//Member access operator
ELEMENT* BiIterator::operator->() const
{
  ELEMENT* e = &this->current->value;
  return e;
}


//Equality comparison operator
bool BiIterator::operator==(const BiIterator &it) const
{
  
  return (it.current->value == this->current->value);
}


//Inequality comparison operator
bool BiIterator::operator!=(const BiIterator &it) const
{
  return !(it.current->value == this->current->value);
}


//Pre increment operator
BiIterator& BiIterator::operator++()
{
  //See slide 11 och labnotes.
  //Check if there is a right subtree.
  if(this->current->r_thread)
    this->current = this->current->right;

  //Otherwise find the minium value in the subtree.
  else
    this->current = this->current->right->findMin();

  return *this;
}



//Pos increment operator: see page 277 and 278 of C++ direkt
BiIterator BiIterator::operator++(int)
{
  BiIterator tempIterator(*this);

  ++(*this);

  return tempIterator;
}

//Pre decrement operator
BiIterator& BiIterator::operator--()
{
  //Same as above
  //Check if there is a left subtree.
  if(this->current->r_thread)
    this->current = this->current->left;

  //Otherwise find the minium value in the subtree.
  else
    this->current = this->current->left->findMax();

  return *this;
}

//Pos decrement operator
BiIterator BiIterator::operator--(int)
{
  //Same as above
  BiIterator tempIterator(*this);

  --(*this);

  return tempIterator;
}

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

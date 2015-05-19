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
  if(!(current->r_thread))
    current = current->right->findMin();

  //Check if there is a right subtree.
  else
    current = current->right;

  return *this;
}



//Pos increment operator: see page 277 and 278 of C++ direkt
BiIterator BiIterator::operator++(int)
{
    BiIterator *it = this;
    
    if (!current->r_thread)
        current = current->right->findMin();
    else
        current = current->right;
    
    return *it;
}

//Pre decrement operator
BiIterator& BiIterator::operator--()
{
  if(!(this->current->l_thread))
    this->current = this->current->left;

  //Otherwise find the minium value in the subtree.
  else
    this->current = this->current->left->findMax();

  return *this;
}

//Pos decrement operator
BiIterator BiIterator::operator--(int)
{
    BiIterator *it = this;

    if (!current->l_thread)
        current = current->left->findMax();
    else
        current = current->left;
    return *it;
}

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

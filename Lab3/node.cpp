/**********************************************
* File: node.cpp                              *
* Author: Aida Nordman                        *
* Course: TND004, Lab 3                       *
* Date: VT2, 2014                             *
* Description: class Node                     *
***********************************************/

#include "node.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS


Node::Node(ELEMENT v, Node *l, Node *r)
 : value(v), left(l), right(r)
{
    l_thread = r_thread = false;
}


//Destructor
//recursively deletes the nodes in the left_subtree and right-subtree
Node::~Node()
{
    //ADD CODE
}


//Insert v in the tree having as root this node
//Return true, if v was inserted
//Otherwise, return false --v already exists in the tree
bool Node::insert(ELEMENT v)
{
    //does this have to be non-recursive?
    //order from left... 1 2 3 4 5 6 ------> pays no regard to height
    //insert in left subtree if less than root
    if (v.first < value.first)
    {
        //might be children on the same level
        if (l_thread) //if left thread is empty
        {
            //if left subtree is empty, point the left back to parent if understood correct from lab3_notes
            Node* child = new Node(v, this, this->right);
            child->l_thread = true; //both right and left thread of child are empty
            child->r_thread = true; 
            this->left = child;
            this->l_thread = false; //not empty anymore
            return true;
        }
        else //go left
            return this->left->insert(v);
    }


    //insert in right subtree if larger than root
    else if (v.first > value.first)
    {
        if (r_thread) //if right thread is empty
        {
            Node* child = new Node(v, this->left, this);
            child->l_thread = true;
            child-> r_thread = true;
            this->right = child;
            this->r_thread = false;
            return true;
        }
        else // go right
            return this->right->insert(v);

    }

    else // v.first == value.first
    {
        value.second++;
        return false;
    }
    return true;
}



//Remove the key from the tree having as root this node
//Return true, if a node storing key was found and deleted
//Otherwise, return false -- there is no node storing key
//isRight==false: this node is left child of parent
//isRight==true: this node is right child of parent
bool Node::remove(string key, Node* parent, bool isRight)
{
    //ADD CODE
    return false;
}



//Remove this node -- this node has at most one child
//isRight==false: this node is left child of parent
//isRight==true: this node is right child of parent
//Remove has 6 cases
//1a: a left child with only a right child
//1b: a left child with only a left child
//1c: a left child with no children
//2a: a right child with only a right child
//2b: a right child with only a left child
//2c: a right child with no children
void Node::removeMe(Node* parent, bool isRight)
{
   //ADD CODE
}



//Return a pointer to the Node storing key
//key is possibly stored in one of the sub-trees of this node
//If there is no node storing key then return nullptr
Node* Node::find(string key)
{
    //ADD CODE
    if (key < this->value.first)
    {
        if (l_thread) // empty!
        {
            return nullptr;
        }

        else
        {
           return this->left->find(key);
        }
    }
    
    else if (key > this->value.first)
    {
        if (r_thread) //empty!
        {
            return nullptr;
        }
        else
        {
            return this->right->find(key);
        }
    }
    else //found!
    {
        return this;
    }
    return nullptr;
}


//Return a pointer to the node storing the smalest value
//of the tree whose root is this node
Node* Node::findMin()
{ 
   if(!l_thread)
        return this->left->findMin();

   return this;
}


//Return a pointer to the node storing the largest value
//of the tree whose root is this node
Node* Node::findMax()
{
    if(!r_thread)
        return this->right->findMax();

    return this;
}



//Display in inorder all keys
//stored in the tree whose root is this node
//recursive function
//Used for debugging -- ONLY
void Node::display() const
{
    if ( !l_thread ) //display left sub-tree
        left->display();

    cout << value.first << " "; //display key stored in the node

    if ( !r_thread ) //display right sub-tree
        right->display();
}


#endif /* DOXYGEN_SHOULD_SKIP_THIS */

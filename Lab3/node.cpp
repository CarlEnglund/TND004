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
    if (!l_thread)
        delete left;
    if (!r_thread)
        delete right;
}


//Insert v in the tree having as root this node
//Return true, if v was inserted
//Otherwise, return false --v already exists in the tree
bool Node::insert(ELEMENT v)
{
    // Value bigger then value of node, check in the right subtree
    if(v.first > value.first){
        
        // If no more nodes in right thread, insert
        if(r_thread){
            
            Node* newChild = new Node(v, this, this->right);
            this->right = newChild;
            this->r_thread = false;
            newChild->r_thread = newChild->l_thread = true;
            
        }
        
        // Keep going right
        else
            return this->right->insert(v);
    }
    
    // Value smaller then value of node, check in the left subtree
    else if (v < value){
        
        // If no more nodes to the left, insert
        if(l_thread){
            
            Node* newChild = new Node(v, this->left, this);
            this->left = newChild;
            this->l_thread = false;
            newChild->r_thread = newChild->l_thread = true;
            
        }
        
        // Keep going left
        else
            return this->left->insert(v);
    }
    
    // Same value, updating..
    else {
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
    //Look for value if not correct, call yourself and keep searching.
    if(key < value.first)
    {
        
        if(!l_thread)
        {
            left->remove(key, this, false);
        }
    }
    
    //Look for value if not correct, call yourself and keep searching.
    else if(key > value.first)
    {
        if(!r_thread)
        {
            right->remove(key, this, false);
        }
    }
    
    //Correct value
    else if(key == value.first)
    {
        if(!r_thread && !l_thread)
        {
            value = right->findMin()->value;
            return right->remove(key, this, true);
        }
    }
    
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
    else if(key == this->value.first)//found!
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

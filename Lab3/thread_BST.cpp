/********************************************************
* File: threaded_BST.cpp                                *
* Author: Aida Nordman                                  *
* Course: TND004, Lab 3                                 *
* Date: VT2, 2014                                       *
* Description: class BST_threaded representing          *
*              a threaded binary search tree            *
*********************************************************/

#include "threaded_BST.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS

using namespace std;


//Default Constructor: create an empty tree
//Empty tree has a dummy node as root
//The real tree is stored as left child of the dummy root
BST_threaded::BST_threaded()
 : counter(0)
{
    pair <string, int> p;
    p = std::make_pair("", 0); // ELEMENT with a string (key) and counter for occurences. NOT same as counter in class
    root = new Node(p, nullptr, nullptr);
    
}


//destructor
BST_threaded::~BST_threaded()
{
  delete root;
  counter = 0; // perhaps?
}


//Test if the tree is empty
bool BST_threaded::empty() const
{
    //not sure if root->right is needed, cause real tree is stored as left child of dummy?
    if (root->left == nullptr && root->right == nullptr)
        return true;

    return false;
}

//Return mumber of keys (elements) stored in the tree
int BST_threaded::size() const
{
    return counter;
}

//Insert v in the tree
void BST_threaded::insert(ELEMENT v)
{
    if (empty())
    {
        //Insert first node of the BST has a left child of the BST
        root->left = new Node(v, root, root);
        root->left->l_thread = root->left->r_thread = true;

        root->l_thread = false;
        counter = 1;
    }
    else
        counter += root->left->insert(v); //call NODE::insert()
}


//Remove node with key from the tree
void BST_threaded::remove(string key)
{
   //ADD CODE
}



//If key matches the key of an element in the container,
//then return a reference to the ELEMENT with the key
//If key does not match the key of any element in the container,
//then an ELEMENT (key,0) is inserted and a reference to it is returned
ELEMENT& BST_threaded::operator[](string key)
{
    //ADD CODE
    Node* node = root->left->find(key);
    if (!node) // not found
    {
        pair <string, int> newElement;
        newElement = std::make_pair(key, 0);
        root->left->insert(newElement);
        counter++;
        return newElement;
    }
    return node->value; //found
}


//Find the node in the BST storing key
//Return a BiIterator referring to the node storing the key, if the key is found.
//Otherwise, return this->end().
BiIterator BST_threaded::find(string key) const
{
    if (!empty())
    {
        Node* node = root->left->find(key);

        if (node) // if node not null (found)
        {
            return BiIterator(node);
        }
        else
            return end();

    }
    return end();
}


//Return an iterator referring to the first node in the inorder traversal of the BST
BiIterator BST_threaded::begin() const
{
    //ADD CODE
    return end();
}


 //Return a BiIterator referring to the past-the-end element in the BST
BiIterator BST_threaded::end() const
{
    BiIterator it(root);

    return it;
}


//Display all keys increasingly
//To be used for debugging -- ONLY
void BST_threaded::display() const
{
    if (!empty())
        root->left->display();
     else
        cout << "The container is empty!!" << endl;

}


#endif /* DOXYGEN_SHOULD_SKIP_THIS */

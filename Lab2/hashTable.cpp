#include <assert.h>
#include <iomanip>

#include "hashTable.h"
#include <fstream>
const double MAX_LOAD_FACTOR = 0.5;

//Linear probing: Search sequentially in the table until an empty position is found, starting at h(x)
//The next position after the last (𝑀 − 1) is the first (0)
//Used in find, remove, insert


//Test if a number is prime
bool isPrime( int n )
{
    if( n == 2 || n == 3 )
        return true;

    if( n == 1 || n % 2 == 0 )
        return false;

    for( int i = 3; i * i <= n; i += 2 )
        if( n % i == 0 )
            return false;

    return true;
}


//Return a prime number at least as large as n
int nextPrime( int n )
{
    if( n % 2 == 0 )
        n++;

    for(; !isPrime( n ); n += 2 );

    return n;
}


// Constructor
// IMPLEMENT
HashTable::HashTable(int table_size, HASH f)
    : size(nextPrime(table_size)), h(f), nItems(0), counter(0)
{

    hTable = new Item*[size];

    for(int i = 0; i < size; i++)
    {
        hTable[i] = nullptr;
    }
}


//destructor
// IMPLEMENT
HashTable::~HashTable()
{
        for (int i = 0; i < size; i++)
        {
            if (!(Deleted_Item::get_Item()))
            delete hTable[i];
        }

        delete[] hTable;
        size = 0;
        nItems = 0;

}


//Return the load factor of the table
double HashTable::loadFactor() const
{
    return (double) nItems / size;
}


//Return the value associated with key
//If key does not exist in the table then NOT_FOUND is returned
// IMPLEMENT
int HashTable::find(string key) const
{

  int index = h(key, size);

  //If it's a nullptr it has been deleted(?).
  while(hTable[index] != nullptr)
  {

    if (hTable[index]->key == key)
      return hTable[index]->value;

    //next position after last is the first
    if(index == (size - 1))
      index = 0;

    index++;
  }

  return NOT_FOUND; //to be deleted
}


//Insert the Item (key, v) in the table
//If key already exists in the table then change the associated value to v
//Re-hash if the table becomes 50% full
// IMPLEMENT
void HashTable::insert(string key, int v)
{

  int index = h(key, size); // uses hash function my_hash to find index

  if (find(key) != NOT_FOUND) // if found, replace with v
  {
    while(hTable[index]->key != key)
    {

        if(index == (size - 1))
            index = 0;

        index++;
    }
    hTable[index]->value = v;
  }

  else
  {

    Item* newItem = new Item(key, v);

    while (hTable[index] != nullptr)
    {
      //primarily try to insert at a deleted position
      if (hTable[index] == Deleted_Item::get_Item())
      {
        break;
      }

      //next position after last is the first
      if(index == (size - 1))
        index = 0;


        index++;

    }

    hTable[index] = newItem;
    nItems++;


    if (loadFactor() >= MAX_LOAD_FACTOR)
    {
      reHash();
    }
  }
}


//Remove Item with key
//If an Item with key belongs to the table then return true,
//otherwise, return false
// IMPLEMENT
bool HashTable::remove(string key)
{
    int index = h(key, size);
    if(find(key) == NOT_FOUND)
      return false;

    while(hTable[index]->key != key)
    {
      //next position after last is the first
      if(index == (size-1))
        index = 0;

      index++;
    }

    delete hTable[index];
    hTable[index] = Deleted_Item::get_Item();
    nItems--;

    return true;
}

void HashTable::display(ostream& os)
{
    if (!hTable) return;

    os << "-------------------------------\n";

    for (int i = 0; i < size; ++i)
    {
        os << setw(6) << i << ": ";

        if (!hTable[i])
        {
            os << "null" << endl;
        }
        else
        {
            string key = hTable[i]->key;

            os << "key = " << "\"" << key << "\""
               << setw(12) << "value = " << hTable[i]->value
               << "  (" << h(key,size) << ")" << endl;
        }
    }

    os << endl;
}
void HashTable::displayFreq(ostream& os, int numbWords)
{
    os << "Number of words in the file: " << numbWords << endl;
    os << "Number of unique words: " << nItems << endl;

    for (int i = 0; i < size; ++i)
    {
        if (hTable[i] == nullptr || hTable[i] == Deleted_Item::get_Item())
        {
            continue;
        }
        else
        {
            os << "Key: " << setw(13) << left << hTable[i]->key << " Value: " << hTable[i]->value << endl;
        }
    }
}


//Display the table to stream os
// IMPLEMENT
ostream& operator<<(ostream& os, const HashTable& T)
{
  int index = 0;

  while(index < T.size)
  {
    if(T.hTable[index] != nullptr)
    {
      os << "value: " << T.hTable[index]->value;
      os << endl;
      os << "key " << T.hTable[index]->key;
    }
    index++;
  }

  return os;
}

//Private member functions

//Rehashing function
// IMPLEMENT
void HashTable::reHash()
{
   HashTable newHash(nextPrime(2*size), h);

    std::cout << "Rehashing... new size is " << nextPrime(2*size) << std::endl;

    for(int i = 0; i < size; i++){

        if(hTable[i] != nullptr && hTable[i]->value != NOT_FOUND){

            newHash.insert(hTable[i]->key, hTable[i]->value);
        }

    }

    std::swap(size, newHash.size);
    std::swap(hTable, newHash.hTable);

    std::swap(nItems, newHash.nItems);
}
//If k matches a key in the table, return reference to its value
//if k does not match, insert new element
int& HashTable::operator[](const string key)
{
  if (find(key) == NOT_FOUND)
  {
      insert(key, 0); // 0 i think?
  }
  int index = h(key, size);
  while (hTable[index] != nullptr)
  {
    if (hTable[index]->key == key)
    {
       return hTable[index]->value;
    }

    if (index == (size - 1))
        index = 0;

    index++;
  }
  return hTable[index]->value;
}

int HashTable::getCounter()
 {
     return counter;
 }


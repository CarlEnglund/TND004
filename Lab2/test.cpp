/*
  Name: hashTable.h
  Author: Aida Nordman
  Course: TND004, Lab 2
  Description: test program for class HashTable
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "hashTable.h"

using namespace std;

//A simple hash function
/*
unsigned my_hash(string s, int tableSize)
{
    unsigned hashVal = 0;

    for(unsigned i = 0; i < s.length(); i++)
        hashVal += s[i];

    hashVal %= tableSize;

    return hashVal;
}
*/
unsigned my_hash(const string key, int tableSize)
{
    unsigned int hashVal = 0;
    for (char ch : key)
        hashVal = 37 * hashVal + ch;

    return hashVal % tableSize;
}

void fixWords(string &s)
{
    string forbidden =".,!?:\"();";
    string newWord = "";
    bool test;
    for (int i = 0; i < s.length(); i++)
    {
        test = false;
        s[i] = tolower(s[i]);
        for (int k = 0; k < forbidden.length(); k++)
        {
            if (s[i] == forbidden[k])
            {
                test = true;
            }
        }
        if (!test) //if test is false, then assign char to the new word
        {
            newWord +=s[i];
        }
    }
    s = newWord;

}
vector <string> readFile(string fileName)
{
    ifstream in;
    in.open(fileName);
    vector <string> wordVec;
    string word;
    while (in >> word)
    {
        fixWords(word);
        wordVec.push_back(word);
      //  cout << word;

    }
    return wordVec;
}



//Test the code
int menu()
{
    int choice = 0;

    cout << "\n-------------------------" << endl;
    cout << "Operations on Hash Table" << endl;
    cout << "\n-------------------------" << endl;

    cout << "1. Insert " << endl;
    cout << "2. Search" << endl;
    cout << "3. Delete" << endl;
    cout << "4. Dump table" << endl;
    cout << "5. Operator []" << endl;
    cout << "6. Read from file" << endl;
    cout << "7. Write frequency table to file"  << endl;
    cout << "8. Exit" << endl;

    cout << "Enter your choice: ";

    cin >> choice;

    return choice;
}


int main()
{
    const int TABLE_SIZE = 7;

    HashTable table(TABLE_SIZE, my_hash);

    string key;
    int value = 0;
    int choice;
    bool go = true;
    string fileName;
    vector<string> myVec;
    int counter;
    ofstream out;
    out.open("outfile.txt");

    while( go )

    {
        choice = menu();

        switch(choice)
        {
        case 1:

            cout << "Enter value to be inserted: ";
            cin >> value;

            cout << "Enter key for the value to be inserted: ";
            cin >> key;

            table.insert(key, value);
            break;

        case 2:

            cout << "Enter key of the value to be searched: ";
            cin >> key;

            value = table.find(key);

            if (value == NOT_FOUND)
            {
                cout << "No element found at key " << key << endl;
            }
            else
            {
                cout << "value at key " << key << ": ";
                cout << value << endl;
            }
            break;

        case 3:
            cout << "Enter key of the value to be deleted: ";
            cin >> key;

            table.remove(key);
            break;

        case 4:
            table.display(cout);
            break;
        case 5:
            cout << "Enter a word: ";
            cin >> key;
            cout << "Value at key is: " << table[key] << endl;
            break;

        case 6:

            cout << "Enter a file name: ";
            cin >> fileName;

            myVec = readFile(fileName);

            for (int i = 0; i < myVec.size(); i++)
            {
                table[(myVec.at(i))]++;
                //std::cout << myVec.at(i);
            }
            break;

        case 7:
            table.displayFreq(out, myVec.size());
            break;
         case 8:
            go = false;
            break;


        default:
            cout << "\nEnter correct option\n";
        }
    }

    return 0;
}


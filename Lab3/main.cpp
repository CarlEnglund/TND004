/**********************************************
* File: main.cpp                              *
* Author: Aida Nordman                        *
* Course: TND004, Lab 3                       *
* Date: VT2, 2015                             *
* Description: frequency table                *
* DO NOT MODIFY                               *
***********************************************/

#include "threaded_BST.h"
#include "BiIterator.h"

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

/*void fixWords(string &s)
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

}*/
bool isNotAlnum (char ch)
{
    string forbidden =".,!?:\"();";
    for (int i = 0; i < forbidden.size(); i++)
    {
        if (ch == forbidden[i])
            return true;
    }
    return false;
}

void displayTable(MAP& table)
{
    //basically same as lab 2


    cout << "Frequency table sorted alpabetically: " << endl << endl
        << setw(17) << "KEY" << setw(10) << "COUNTER" << endl;
    cout << "=========================================" << endl;

    BiIterator it = table.begin();
    while (it != table.end())
    {
        cout << setw(17) << right << it->first << setw(17) << it->second << endl;
        it++;

    }

}

/*******************************
* 2. Main function             *
********************************/


int main()
{
    MAP table;

    string name;
    string s;
    int count = 0;
    /******************************************************
    * PHASE 0: Load the words in the text file            *
    *          into a the table                           *
    *******************************************************/

    cout << "File name? ";
    getline(cin, name);

    ifstream textFile(name);

    if (!textFile)
    {
        cerr << "Text file could not be opened!!" << endl;
        exit(1);
    }

    cout << "Loading the words from " << name << " ...\n";

    
    //Read words and load them in the table
    while (textFile >> s)
    {
        //remove non-alphanumeric chars
        s.erase(remove_if(s.begin(), s.end(), isNotAlnum), s.end());

        //convert to lower-case letters
        transform(s.begin(), s.end(), s.begin(), ::tolower);

        if (!s.size()) continue; //skip numbers and punctuation signs

        table[s].second++;  //if s is not in the table then it is inserted

        count++;
    }


    /******************************************************
    * PHASE 1: Display                                    *
    * - number of words in the text                       *
    * - number of unique words (occurring only once)      *
    * - frequency table                                   *
    *******************************************************/

    //ADD CODE
    cout << "Number of words in the file: " << count << endl;
    cout << "Number of unique words: " << table.size() << endl;
    displayTable(table);
    /******************************************************
    * PHASE 3: remove all words with counter 1            *
    *          and display table again                    *
    *******************************************************/

    string wait;
    getline(cin, wait);
    vector <string> removeVec;
    BiIterator it = table.begin();

    while (it != table.end())
    {
        //put all words we want to remove in vector
        if (it->second == 1)
        {
            removeVec.push_back(it->first);
        }
        it++;
    }

    for (int i = 0; i < removeVec.size(); i++)
    {
        table.remove(removeVec.at(i));
    }
    //display again
    cout << "Number of words in the file after removing: " << table.size() << endl;
    displayTable(table);
    //ADD CODE



    /***********************************************************
    * PHASE 4: request two words to the user w1 and w2         *
    *          then display all words in the interval [w1,w2]  *
    ************************************************************/
    string w1, w2;
    cout << "Enter words: ";
    cin >> w1 >> w2;
        cout << "Frequency table in [" << w1 << "," << w2 << "]" << endl;
       cout << setw(17) << "KEY" << setw(10) << "COUNTER" << endl;
    cout << "=========================================" << endl;
    
    //decreasing alphabetic order
    BiIterator it2 = table.end();
    bool test = false;
    while (it2 != table.begin())
    {
        
        if (it2->first == w2)
        {
            test = true;
        }
        if (test)
        {
            cout << setw(17) << right << it2->first << setw(17) << it2->second << endl;
        }
        if (it2->first == w1)
        {
            test = false;
        }
        it2--;
    }



    return 0;
}

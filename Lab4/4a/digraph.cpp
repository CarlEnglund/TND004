/*********************************************
* file:	~\tnd004\lab\lab4a\digraph.cpp       *
* remark: mplementation of directed graphs   *
* file for students                          *
**********************************************/


#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;

#include "digraph.h"
#include "queue.h"

const int INFINITY = 9999;

// -- CONSTRUCTORS
//digraph = directed graph
Digraph::Digraph(int n)
{
    assert(n >= 1);
    array = new List[n + 1];
    dist  = new int [n + 1];
    path  = new int [n + 1];
    done  = new bool[n + 1];
    size  = n;
}

// -- DESTRUCTOR

Digraph::~Digraph()
{
    delete[] array;
    delete[] dist;
    delete[] path;
    delete[] done;
}

// -- MEMBER FUNCTIONS

// insert directed edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Digraph::insertEdge(int u, int v, int w)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].insert(v, w);
}

// remove directed edge (u, v)
void Digraph::removeEdge(int u, int v)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].remove(v);
}

// unweighted single source shortest paths
void Digraph::uwsssp(int s)
{
    // s = start vertex
    //queue: first in, first out. jämför med stack: last in, first out.
    //enqueue: insertion/push, dequeue: deletion/pop
    //dvs: insertion i slutet, removal i början.
    if (s < 1 || s > size)
    {
         cout << "\nERROR: expected source s in range 1.." << size << " !" << endl;
         return;
    }
    // s.410 i boken eller föreläsning

    Queue<int> Q;

    //no nodes yet visited
    for(int i=1; i<size+1; i++)
    {
        dist[i] = INFINITY;
        path[i] = 0;
    }
    // first node -> set dist to 0
    dist[s]=0;
    Q.enqueue(s); // put start in queue
    while(!Q.isEmpty())
    {
        int v = Q.getFront(); //get first vertex in queue

       // cout << v << " ";
        //pop the front element
        Q.dequeue();
        //get first adjacent node
        Node *temp = array[v].getFirst();
        //while node has next
        while (temp != nullptr)
        {
            if (dist[temp->vertex] == INFINITY)
            {
                dist[temp->vertex] = dist[v]+1; // + 1 distance from start if infinity
                path[temp->vertex] = v;
                Q.enqueue(temp->vertex);
            }
            temp = temp->next;
        }
    }



}

// positive weighted single source shortest pats
// dijktras algorithm
void Digraph::pwsssp(int s)
{
    if (s < 1 || s > size)
    {
         cout << "\nERROR: expected source s in range 1.." << size << " !" << endl;
         return;
    }

    for (int i = 1; i < size + 1; i++)
    {
        dist[i] = INFINITY;
        path[i] = 0;
        done[i] = false;
    }

    dist[s] = 0;
    
    int currVer = s;
    done[currVer] = true;

    int d;
    while (true) // while d != INFINITY (while there is an unknown distance vertex)
    {
        Node* adjNode = array[currVer].getFirst(); //adjacent

        while (adjNode != nullptr)
        {
            //p.417 in book.
            //at each stage, select a vertex which has smallest dist from start among all unknown vertices.
            //update the dist of each vertex v adjacent vertex w , if better path through v.
          //  cout << "Vertex number: " << currVer << " Adjacent vertex: " << adjNode->vertex << endl;
            if (!done[adjNode->vertex])
            {
                //if shorter path
                if (dist[currVer] + adjNode->weight < dist[adjNode->vertex])
                {
                    dist[adjNode->vertex] = dist[currVer] +  adjNode->weight;
                    path[adjNode->vertex] = currVer;
                }
            }
            adjNode = array[currVer].getNext();
        }
        done[currVer] =  true; // all neighbours have been checked

        d = INFINITY;
        //find smallest undone distance vertex
        for (int i = 1; i < size + 1; i++)
        {
            if (!done[i] && dist[i] < d)
            {
                d = dist[i]; // will become smallest possible
                currVer = i;
            }
        }
        if (d == INFINITY)
            break;

    }

    // *** TODO ***
}

// print graph
void Digraph::printGraph() const
{
    cout << "------------------------------------------------------------------" << endl;
    cout << "vertex  adjacency list                  " << endl;
    cout << "------------------------------------------------------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " : ";
        array[v].print();
    }

    cout << "------------------------------------------------------------------" << endl;
}

// print shortest path tree for s
void Digraph::printTree() const
{
    cout << "----------------------" << endl;
    cout << "vertex    dist    path" << endl;
    cout << "----------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " :" << setw(8) << dist[v] << setw(8) << path[v] << endl;
    }

    cout << "----------------------" << endl;
}

// print shortest path from s to t
void Digraph::printPath(int t) const
{
    if (t < 1 || t > size)
    {
         cout << "\nERROR: expected target t in range 1.." << size << " !" << endl;
         return;
    }

    // RECURSION <3
    printPath(path[t]);
    std::cout << " " << t;

}


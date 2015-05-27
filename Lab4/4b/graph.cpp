/*********************************************
* file:	~\tnd004\lab\lab4b\graph.h           *
* remark:implementation of undirected graphs *
* file for students                          *
**********************************************/

#include <vector>
#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;

#include "graph.h"
#include "edge.h"
#include "heap.h"
#include "dsets.h"

const int INFINITY = 9999;

// -- CONSTRUCTORS

Graph::Graph(int n)
{
    assert(n >= 1);
    array = new List[n + 1];
    size  = n;
}

// -- DESTRUCTOR

Graph::~Graph()
{
    delete[] array;
}

// -- MEMBER FUNCTIONS

// insert undirected edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Graph::insertEdge(int u, int v, int w)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].insert(v, w);
    array[v].insert(u, w);
}

// remove undirected edge (u, v)
void Graph::removeEdge(int u, int v)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].remove(v);
    array[v].remove(u);
}


void Graph::mstPrim() const
{
    bool done[size + 1];
    int dist[size + 1];
    int path[size + 1];

    //Init all to false
    for(int i = 0; i <= size; i++)
    {
      done[i] = false;
      dist[i] = INFINITY;
      path[i] = 0;
    }

    int s = 1;
    dist[s] = 0;
    done[s] = true; 

    int totWeight = 0;
    
    int currVer = s;
    done[currVer] = true;
    int d;
    while(true) // while d != INFINITY (while there is an unknown distance vertex)
    {

        Node *adjNode = array[currVer].getFirst();
        while(adjNode)
        {
            if (!done[adjNode->vertex] && dist[adjNode->vertex] > adjNode->weight)
            {
                dist[adjNode->vertex] = adjNode->weight;
                path[adjNode->vertex] = currVer;

            }            
            adjNode = array[currVer].getNext();
        }
        done[currVer] = true; //all neighbours have been checked

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

        Edge myEdge(path[currVer],currVer, dist[currVer]);
        cout << myEdge << endl;

        totWeight += dist[currVer];
    }

    cout << "Total weight is: " << totWeight << endl;


}


// Kruskal's minimum spanning tree algorithm
void Graph::mstKruskal() const
{

    //kruskals maintains a collection of single-node trees
    //adding edge = merge two trees into one

    int totWeight = 0;
    //Init heap and Dsets
    Heap <Edge>H;
    DSets D(size);
    int totWeight = 0;



    //Occupy the heap.
    for (int i = 0; i < size; i++)
    {
        Node *n = array[i].getFirst();
        while(n) //while has neighbour
        {
            if(i < n->vertex)
            {
                Edge e(i, n->vertex, n->weight);
                H.insert(e);
            }
            n = array[i].getNext();
        } 
     
    }

    //Counter for the edges we want to add.
    int edgesAccepted = 0;
    while(edgesAccepted < size-1)
    {
        //Finds edge with lowest cost, see slides on lecture 14
        Edge b = H.deleteMin();
        //Does head and tail belong to the same tree? to avoid cycles!
        if(D.find(b.head) != D.find(b.tail)) 
        {
            //Merge two different trees
            D.join(D.find(b.head), D.find(b.tail));
            edgesAccepted++;
            totWeight += b.weight;
            cout << b << endl;
        } 

    }
    cout << endl << "Total weight = " << totWeight << endl;
    
    
  
}

// print graph
void Graph::printGraph() const
{
    cout << "------------------------------------------------------------------" << endl;
    cout << "vertex  adjacency list                                            " << endl;
    cout << "------------------------------------------------------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " : ";
        array[v].print();
    }

    cout << "------------------------------------------------------------------" << endl;
}

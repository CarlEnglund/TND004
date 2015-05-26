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

// Prim's minimum spanning tree algorithm
void Graph::mstPrim() const
{
    //Declare edges and bool array for what we have visited
    vector<Edge> edges;
    bool done[size+1];

    //Init all to false
    for(int i = 0; i <= size; i++)
    {
      done[i] = false;
    }

    //Starting vertex, set it to true. Get the first edge
    int s = 1;
    done[s] = true; 
    Node *edgeNodes = array[s].getFirst();
    while(true)
    {
      Edge smallest = Edge(0, 0, INFINITY);
      Node *res = nullptr;
      for (int j = 0; j <= size; j++)
      {
        if(!done[j])
          continue;

        edgeNodes = array[j].getFirst();

        while(edgeNodes)
        {
          Edge w = Edge(j, edgeNodes->vertex, edgeNodes->weight);

          if(!done[edgeNodes->vertex] && w < smallest)
          {
            smallest = w;
            s = w.tail;
            res = edgeNodes;
          }
          edgeNodes = edgeNodes->next;
        }

      }

      //Exit if we found next vertex?
      if(!res)
        break;

      cout << smallest<< endl;
      done[s] = true;
    }

    

}

// Kruskal's minimum spanning tree algorithm
void Graph::mstKruskal() const
{
    //Init heap and Dsets
    Heap <Edge>H;
    DSets D(size);


    //Occupy the heap.
    for (int i = 0; i < size; i++)
    {
     Node *n = array[i].getFirst();
     while(n)
     {
      if(i < n->vertex)
      {
        Edge e(i, n->vertex, n->weight);
        H.insert(e);
      }
      n = n->next;
     } 
     
    }

    int edgesAccepted = 0;

    while(edgesAccepted < size-1)
    {
       Edge b = H.deleteMin();
      if(D.find(b.head) != D.find(b.tail))
      {
        D.join(D.find(b.head), D.find(b.tail));
        edgesAccepted++;

        cout << b << endl;
      } 


    }

  
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

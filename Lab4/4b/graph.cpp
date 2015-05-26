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
    vector<Edge> edges;
    bool done[size+1];

    for(int i = 0; i <= size; i++)
    {
      done[i] = false;
    }

    //Starting vertex
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

      edges.push_back(smallest);
      cout << " " << s;
      done[s] = true;
    }

    for(Edge e : edges)
    {
      if(e.head > 0)
        cout << e << endl;
    }

}

// Kruskal's minimum spanning tree algorithm
void Graph::mstKruskal() const
{
    // *** TODO ***
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

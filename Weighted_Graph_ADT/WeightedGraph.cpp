//--------------------------------------------------------------------
//
//                                                 WeightedGraph.cpp
//
//  SOLUTION: Adjacency matrix implementation of the Weighted
//            Graph ADT
//
//--------------------------------------------------------------------

#ifndef WEIGHTEDGRAPH_CPP
#define WEIGHTEDGRAPH_CPP

using namespace std;

#include "WeightedGraph.h"
#include "config.h"

//--------------------------------------------------------------------

WeightedGraph:: WeightedGraph ( int maxNumber )

// Creates an empty graph. Allocates enough memory for maxNumber
// vertices (defaults to defMaxGraphSize).
{
    maxSize = (maxNumber > 0 && maxNumber <= MAX_GRAPH_SIZE) ? maxNumber : MAX_GRAPH_SIZE;
    size = 0;
    vertexList = new Vertex[maxSize];
    adjMatrix = new int[maxSize * maxSize];
    for (int i = 0; i < maxSize * maxSize; ++i) {
        adjMatrix[i] = INFINITE_EDGE_WT;
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

WeightedGraph:: WeightedGraph ( const WeightedGraph& other )

// Creates an empty graph. Allocates enough memory for maxNumber
// vertices (defaults to defMaxGraphSize).

{
    maxSize = other.size;
    size = other.size;
    vertexList = new Vertex[maxSize];
    adjMatrix = new int[maxSize * maxSize];
    for (int i = 0; i < maxSize * maxSize; ++i) {
        adjMatrix[i] = other.adjMatrix[i];
    }
    for (int i = 0; i < size; ++i) {
        vertexList[i] = other.vertexList[i];
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

WeightedGraph& WeightedGraph:: operator= ( const WeightedGraph& other )

// Copies from another WeightedGraph. 

{
    if (this != &other) {
        delete[] vertexList;
        delete[] adjMatrix;
        maxSize = other.size;
        size = other.size;
        vertexList = new Vertex[maxSize];
        adjMatrix = new int[maxSize * maxSize];
        for (int i = 0; i < maxSize * maxSize; ++i) {
            adjMatrix[i] = other.adjMatrix[i];
        }
        for (int i = 0; i < size; ++i) {
            vertexList[i] = other.vertexList[i];
        }
    }
    return *this;
}

//--------------------------------------------------------------------

WeightedGraph:: ~WeightedGraph ()

// Frees the memory used by a graph.

{
    delete[] vertexList;
    delete[] adjMatrix;
}

//--------------------------------------------------------------------

void WeightedGraph:: insertVertex ( const Vertex& newVertex ) throw ( logic_error )

// Inserts newVertex into a graph. If a vertex with the same label
// as newVertex already exists in the graph, then updates that
// vertex's data with newVertex's data.

{
    if (size == maxSize) {
        throw logic_error("Graph is full");
    }
    int idx = getIndex(newVertex.getLabel());
    if (idx != -1) {
        vertexList[idx] = newVertex;
    } else {
        vertexList[size] = newVertex;
        for (int i = 0; i < size; ++i) {
            adjMatrix[i * maxSize + size] = INFINITE_EDGE_WT;
            adjMatrix[size * maxSize + i] = INFINITE_EDGE_WT;
        }
        ++size;
    }
}

//--------------------------------------------------------------------

void WeightedGraph:: insertEdge ( const string& v1, const string& v2, int wt )
    throw ( logic_error )

// Insert an edge with the specified weight between vertices
// v1 and v2.

{
    int row = getIndex(v1);
    int col = getIndex(v2);

    if (row == -1 || col == -1) {
        throw logic_error("Error: one or both vertices not found");
    }

    setEdge(row, col, wt);
}

//--------------------------------------------------------------------

bool WeightedGraph:: retrieveVertex ( const string& v, Vertex &vData ) const

// Searches a graph for vertex v. If the vertex is found, then copies
// the vertex data to vData and returns 1. Otherwise, returns 0 with
// vData undefined.

{
    for (int i = 0; i < size; i++){
        if (vertexList[i].getLabel() == v){
            vData = vertexList[i];
            return true;
        }
    }
    return false;
}

//--------------------------------------------------------------------

bool WeightedGraph:: getEdgeWeight ( const string& v1, const string& v2, int &wt ) const throw ( logic_error )

// If there is an edge connecting vertices v1 and v2, then returns 1
// with wt returning the weight of the edge. Otherwise, returns 0
// with wt undefined.

{
    int row = getIndex(v1);
    int col = getIndex(v2);
    if (row == -1 || col == -1) {
        throw logic_error("Vertex not found.");
    }
    wt = getEdge(row, col);
    if (wt == INFINITE_EDGE_WT) {
        return false;
    } else {
        return true;
    }
}

//--------------------------------------------------------------------

void WeightedGraph:: removeVertex ( const string& v ) throw ( logic_error )

// Removes vertex v from a graph.

{
    int index = getIndex(v);
    if (index == -1) {
        throw logic_error("Invalid vertex label");
    }
    // Shift rows up
    for (int i = index + 1; i < size; i++) {
        for (int j = 0; j < size; j++) {
            setEdge(i - 1, j, getEdge(i, j));
        }
        vertexList[i - 1] = vertexList[i];
    }
    // Shift columns left
    for (int i = index + 1; i < size; i++) {
        for (int j = 0; j < size; j++) {
            setEdge(j, i - 1, getEdge(j, i));
        }
    }
    size--;
}

//--------------------------------------------------------------------

void WeightedGraph:: removeEdge ( const string& v1, const string& v2 ) throw ( logic_error )

// Removes the edge between vertices v1 and v2 from a graph.

{
    int index1 = getIndex(v1);
    int index2 = getIndex(v2);
    if (index1 == -1 || index2 == -1) {
        throw logic_error("Invalid vertex label");
    }
    setEdge(index1, index2, INFINITE_EDGE_WT);
}

//--------------------------------------------------------------------

void WeightedGraph:: clear ()

// Removes all the vertices and edges from a graph.

{
    size = 0;
    for (int i = 0; i < maxSize * maxSize; ++i) {
        adjMatrix[i] = INFINITE_EDGE_WT;
    }
}

//--------------------------------------------------------------------

bool WeightedGraph:: isEmpty () const

// Returns 1 if a graph is empty. Otherwise, returns 0.

{
    return size == 0;
}

//--------------------------------------------------------------------

bool WeightedGraph:: isFull () const

// Returns 1 if a graph is full. Otherwise, returns 0.

{
    return size == maxSize;
}

//--------------------------------------------------------------------

void WeightedGraph:: showStructure () const

// Outputs a graph's vertex list and adjacency matrix. This operation
// is intended for testing/debugging purposes only.

{
    if ( size == 0 ) {
       cout << "Empty graph" << endl;
    } else {
       cout << endl << "Vertex list : " << endl;
       for ( int row = 0 ; row < size ; row++ ) {
           cout << row << '\t' << vertexList[row].getLabel();
#if LAB12_TEST2
	   cout << '\t' << vertexList[row].getColor();
#endif
	   cout << endl;
       }

       cout << endl << "Edge matrix : " << endl << '\t';
       for ( int col = 0 ; col < size ; col++ )
           cout << col << '\t';
       cout << endl;
       for ( int row = 0 ; row < size ; row++ )
       {
           cout << row << '\t';
           for ( int col = 0 ; col < size ; col++ )
           {
               int wt = getEdge(row,col);
               if ( wt == INFINITE_EDGE_WT )
                  cout << "- \t";
               else
                  cout << wt << '\t';
           }
           cout << endl;
       }
    }
}

#if LAB12_TEST1		// computePaths
// should really be used for adjMatrix, too
class pathMatrix {
  public:
    pathMatrix(int initSize) : size(initSize) {
	matrix = new int[initSize * initSize];
    }

    ~pathMatrix() {
	delete matrix;
    }

    int getPath(int row, int col) const {
	return matrix[size * row + col];
    }

    void setPath(int row, int col, int wt) {
	matrix[size * row + col] = wt;
    }

  private:
    int *matrix;
    int size;
};

void WeightedGraph::showShortestPaths() const {
    pathMatrix pm(size);

    for ( int j = 0 ; j < size ; j++ )           // Copy edge matrix
        for ( int k = 0 ; k < size ; k++ )
            pm.setPath(j,k, getEdge(j,k));

    for ( int j = 0 ; j < size ; j++ )           // Set diagonal to 0
        pm.setPath(j,j, 0);

    for ( int m = 0 ; m < size ; m++ )           // Compute paths
        for ( int j = 0 ; j < size ; j++ )
            for ( int k = 0 ; k < size ; k++ )
	        // assumes sizeof(long) > sizeof(int)
                if ( long(pm.getPath(j,m)) + pm.getPath(m,k) < pm.getPath(j,k) )
                   pm.setPath(j,k, (pm.getPath(j,m) + pm.getPath(m,k)));

    cout << endl << "Path matrix : " << endl << '\t';
    for ( int col = 0 ; col < size ; col++ )
       cout << col << '\t';
    cout << endl;
    for ( int row = 0 ; row < size ; row++ )
    {
       cout << row << '\t';
       for ( int col = 0 ; col < size ; col++ )
       {
	   int wt = pm.getPath(row,col);
	   if ( wt == INFINITE_EDGE_WT )
	      cout << "- \t";
	   else
	      cout << wt << '\t';
       }
       cout << endl;
    }
}
#endif

#if LAB12_TEST2
bool WeightedGraph::hasProperColoring() const {
    bool fail = false;

    for (int j = 0; j < size && !fail; ++j) {
	for (int k = 0; k < size && !fail; ++k) {
	    fail = (   getEdge(j, k) != INFINITE_EDGE_WT
		    && vertexList[j].getColor() == vertexList[k].getColor() );

    return !fail;
}
#endif

//--------------------------------------------------------------------
//
//  Facilitator functions
//

int WeightedGraph:: getIndex ( const string& v ) const

// Returns the adjacency matrix index for vertex v. Returns size if
// the vertex does not exist.

{
    for (int i = 0; i < size; ++i) {
        if (vertexList[i].getLabel() == v) {
            return i;
        }
    }
    return -1; // vertex not found
}
       
//--------------------------------------------------------------------

int WeightedGraph:: getEdge ( int row, int col ) const

// Gets adjMatrix[row][col].

{
    return adjMatrix[row * size + col];
}

void WeightedGraph:: setEdge ( int row, int col, int wt )

// Gets adjMatrix[row][col].

{
    adjMatrix[row * size + col] = wt;
}

//--------------------------------------------------------------------
//
//                         In-lab operation
//
//--------------------------------------------------------------------

#if LAB12_TEST3
bool WeightedGraph:: areAllEven () const

// Returns true if all the vertices in a graph have even degree.
// Otherwise, returns false.

{
    bool fail;    // Vertex with odd degree found
    int degree,   // Vertex degree
        j, k;     // Loop counters

    fail = 0;
    for ( j = 0 ; j < size  &&  !fail ; j++ )
    {
        degree = 0;
        for ( k = 0 ; k < size ; k++ )
            if ( getEdge(j,k) != INFINITE_EDGE_WT )
               if ( j != k )
                  degree++;
               else
                  degree += 2;
        fail = ( degree % 2 != 0 );
    }

    return !fail;
}
#endif	// LAB12_TEST3

#endif	// #ifndef WEIGHTEDGRAPH_CPP


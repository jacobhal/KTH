#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include <unordered_map>

using std::cin;
using std::cout;
using std::cerr;


struct Edge {
  // Default constructor
  Edge(){}
  // Initialize with 3 values
  
  Edge(int x, int y, int a): v1(x), v2(y), edgeCapacity(a) {
    this->edgeFlow = 0;
    this->edgeRestCapacity = a;
  }
  
  // Constructor to initialize i value for edge
  Edge(int x, int y, int a, int i): v1(x), v2(y), edgeCapacity(a), i(i) {
    this->edgeFlow = 0;
    this->edgeRestCapacity = a;
  }

  // Assignment operator
  Edge& operator=(const Edge & source) {
    v1 = source.v1;
    v2 = source.v2;
    edgeCapacity = source.edgeCapacity;
    edgeRestCapacity = source.edgeRestCapacity;
    edgeFlow = source.edgeFlow;
    i = source.i;
    inverse = source.inverse;
  
    // Return the existing object
    return *this;
  }
  bool operator==(const Edge & source) {
    return (this->v1 == source.v1) && (this->v2 == source.v2);
  }

  int v1;
  int v2;
  // Variables for Ford-Fulkersons
  int edgeFlow; // = f[u,v]
  int edgeCapacity; // = c[u,v]
  int edgeRestCapacity; // = cf[u,v]
  int i;
  Edge* inverse;

  //  Find neighbours of an Edge
  std::vector<Edge*> neighbours(std::vector<Edge> edges) {
    std::vector<Edge*> e;
    Edge* tmp;
    for(unsigned int i = 0; i < edges.size(); ++i) {
      if(edges[i].v1 == this->v2) {
        //cout << "Printing neighbour..." << "\n";
        //cout << edges[i].v1 << " " << edges[i].v2 << " " << edges[i].edgeCapacity << "\n";
        tmp = &edges[i];
        e.push_back(tmp);
      }
    }
    return e;
  }
};

// Flow graph variables
int fVertices, fEdges, fSource, fTarget, max_flow;

// Bipartite graph variables
int gX, gY, nrOfEdges;

// Main vector for storing all edges
std::vector<Edge> edges;
// Store edges in bipartite graph
std::vector<Edge> bipgraph;
// Path vector used in bfs algorithm, filled if a path from source to target is found
std::vector<Edge> path;
// Neighbour list
std::unordered_map<int, std::vector<Edge*>> neighbours;



/**
 * -------------------------------------Helper functions----------------------------------------
 */


/*
  Used to create new edges for bipartite graphs.
 */
void newEdge(int v1, int v2) {
  bipgraph.push_back(Edge(v1, v2, 1));
}
/*
  Used to create new edges for flowgraphs.  
 */
void newFlowEdge(int i, int j) {

  Edge e = bipgraph[j];
  edges.push_back(Edge(e.v1, e.v2, e.edgeCapacity, i));
  edges.push_back(Edge(e.v2, e.v1, 0, i+1));
}
void print(Edge e) {
  cout << e.v1 << " " << e.v2 << " "  << e.edgeFlow << "/" << e.edgeCapacity << " " << e.edgeRestCapacity << " i-värde: " << e.i <<  "\n";
}
/*
  Run bfs to see if path from fSource to fTarget exists and store that path in vector path.
  TODO: path vector does not seem correct.
 */
bool bfs() {

  // Visited array of same size as edges, fill with 0:s
  bool visited[edges.size()];
  for(int i = 0; i < edges.size(); ++i) {
    visited[i] = 0;
  }

  // Create queue and add source vertex
  std::queue <Edge> q;
  // Made up starting node/edge
  Edge tmp = Edge(0, fSource, 0);
  q.push(tmp);

  Edge current;
  Edge next;

  // LÅNGSAMT
  //path.clear();
  path = std::vector<Edge>();
  


  while(!q.empty()) {
  
  current = q.front();
  q.pop();
    
    // Debugutskrift
    //minorPrint(current);


  // Retrieve neighbours of current edge from neighbourlist
  std::vector<Edge*> n = neighbours[current.v2];
  // Loop through the neighbours
  for (unsigned int i = 0; i < n.size(); ++i) {

    next = *n[i];
      //cout << "next.i: " << next.i << "\n";
      if (visited[next.v2] == false && next.edgeRestCapacity > 0) {
            // Return true if fTarget has been reached
            if(next.v2 == fTarget) {
              path.push_back(next); // Add node to path
              visited[next.v2] = true;
              return true;
            }
            path.push_back(next); // Add node to path
            q.push(next);
            visited[next.v2] = true;
          }
      }

  }

  return 0;
}


/* ---------------------------------------------------------------------------------------------*/

/*
  Solve the maxflow problem.
 */
void solveFlowGraph() {


max_flow = 0;
while(bfs()) {

  std::vector<Edge*> tmpPath;

  // Keep track of the previous edge when iterating over path vector
  Edge prevEdge = path[path.size()-1];
  // Initialize minimal flow
  int path_flow = prevEdge.edgeRestCapacity;
  // Iterate over path backwards to find the actual path (without all the neighbours found in bfs)
  for(int i = path.size()-1; i >= 0 ; --i) {
  //  cout << path[i].v1 << " " << path[i].v2 << " " << path[i].edgeCapacity << "\n";
    // Keep adding the matching previous edge until we reach the source
    if(path[i].v2 == prevEdge.v1 || path[i].v2 == fTarget) {
      path_flow = std::min(path_flow, path[i].edgeRestCapacity);
      tmpPath.push_back(&edges[path[i].i]);
      // We're done if the edge added is the source
      if(path[i].v1 == fSource) {
        break;
      }
      prevEdge = path[i];
    }
  }
  // Update flow
  max_flow += path_flow;
  
  // Update edges
  for(unsigned int i = 0; i < tmpPath.size(); ++i) {
    tmpPath[i]->edgeFlow += path_flow;
    tmpPath[i]->edgeRestCapacity = tmpPath[i]->edgeCapacity - tmpPath[i]->edgeFlow;
    // Inverses
    tmpPath[i]->inverse->edgeFlow = -tmpPath[i]->edgeFlow;
    tmpPath[i]->inverse->edgeRestCapacity = tmpPath[i]->inverse->edgeCapacity - tmpPath[i]->inverse->edgeFlow;
  } 
}

}
/*
  Read initial bipartite graph problem.
 */
void readBipGraph() {
  int x, y, e; // x och y är antalet hörn i grafen x respektive y och e är antalet kanter.
    // Om x = 3 och y = 2 kommer de se ut som följer: x = {1,2,3}, y = {4,5}
    // Läs antal hörn och kanter

    cin >> x >> y >> e;
    gX = x;
    gY = y;
    nrOfEdges = e;


    // Läs in kanterna, dessa läses in som 2 heltal, t.ex. 1 5 innebär att det finns en kant från 1 till 5.
    for (int i = 0; i < e; ++i) {
      int a, b;
      cin >> a >> b;
      newEdge(a, b);
    }
}
/*
  Turn bipartite graph into flowgraph.
 */
void makeFlowGraph() {
  // Number of vertices is the sum of vertices from both graphs
  fVertices = gX + gY;
  
  // Source and sink is set to number of vertices + 1 and vertices + 2 respectively
  fSource = fVertices+1;
  fTarget = fVertices+2;
  fVertices += 2;
  
  // Create edges between source and vertices in graph X and between vertices in graph Y and sink
  for(int i = 1; i <= fVertices-2; ++i) {
    if(i <= gX) {
      newEdge(fSource, i);
    } else {
      newEdge(i, fTarget);
    }
  }

  fEdges = bipgraph.size();

  // Reserve space for all edges and all the inverses
  edges.reserve(fEdges*2);
  int j = 0;
  for (int i = 0; i < fEdges*2; i = i + 2) {

    newFlowEdge(i, j);
    neighbours[edges[i].v1].push_back(&edges[i]);
    neighbours[edges[i+1].v1].push_back(&edges[i+1]);

    edges[i].inverse = &edges[i+1];
    edges[i+1].inverse = &edges[i];
    ++j;
  }

  bipgraph.clear();
}

/*
  Write the bipartite matching solution to stdout.
 */
void writeBipMatchSolution() {
  fEdges = 0;
  
  std::ostringstream stream;
  for(unsigned int i = 0; i < edges.size(); ++i) {
    if(edges[i].edgeFlow > 0 && i%2 == 0 && edges[i].v1 != fSource && edges[i].v2 != fTarget) {
      ++fEdges;
      stream << edges[i].v1 << " " << edges[i].v2 << "\n"; 
    }
  }
  
  
  //cout << fVertices << "\n" << fSource << " " << fTarget << " " << max_flow << "\n" << fEdges << "\n";
  cout << gX << " " << gY << "\n" << fEdges << "\n";

  std::string s = stream.str();
  cout << s;
  cout.flush();

}



int main(void) {
  // Två trick för att göra cin/cout lite snabbare.
  // Se http://kattis.csc.kth.se/doc/iostreamio
  std::ios::sync_with_stdio(false);
  cin.tie(0);

  //clock_t begin = clock();

  readBipGraph();

  makeFlowGraph();

  solveFlowGraph();

  writeBipMatchSolution();
  
/*
  clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

  cout << "Time elapsed: " << elapsed_secs << "s" << "\n";
*/
  return 0;
}




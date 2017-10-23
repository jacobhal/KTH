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
  /*
  bool exists(std::vector<Edge> e) {
  	for(int i = 0; i < e.size(); ++i) {
  		if(this->v1 == e[i].v1 && this->v2 == e[i].v2)
  			return true;
  	}
  	return false;
  }
  */
  /*
  void setInverse(std::vector<Edge> inverse, Edge newVal) {

  	auto pred = [this](const Edge & edge) {
    return (edge.v1 == this->v2) && (edge.v2 == this->v1);
	};
	std::replace_if(std::begin(inverse), std::end(inverse), pred, newVal);

  }
  */

  int v1;
  int v2;
  // Variables for Ford-Fulkersons
  int edgeFlow; // = f[u,v]
  int edgeCapacity; // = c[u,v]
  int edgeRestCapacity; // = cf[u,v]
  int i;
  Edge* inverse;

  //
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

// Main vector for storing all edges
std::vector<Edge> edges;
//std::vector<Edge> inverseEdges;
// Path vector used in bfs algorithm, filled if a path from source to target is found
std::vector<Edge> path;

// Neighbours
std::unordered_map<int, std::vector<Edge*>> neighbours;



/**
 * -------------------------------------Helper functions----------------------------------------
 */

/*
  Add new edge to Vector edges with values v1, v2, capacity/flow c and i value i.
 */
void newEdge(int v1, int v2, int c, int i) {
  edges.push_back(Edge(v1, v2, c, i));
  edges.push_back(Edge(v2, v1, 0, i+1));
}
/*
	Run bfs to see if path from fSource to fTarget exists and store that path in vector path.
	TODO: path vector does not seem correct.
 */
bool bfs() {

	// Visited array of same size as edges, fill with 0:s
	bool visited[fEdges];
	for(int i = 0; i < fEdges; ++i) {
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
	Read flowgraph from stdin.
 */
void readFlowGraph() {

  int vertices, e, source, target;

  // Läs in antal hörn, källa, sänka och antal kanter.
  // (Antal hörn, källa och sänka borde vara samma som vi i grafen vi
  // skickade iväg)
  cin >> vertices >> source >> target >> e;

  fVertices = vertices;
  fSource = source;
  fTarget = target;
  fEdges = e;

  // Reserve space for all edges and all the inverses
  edges.reserve(fEdges*2);

  for (int i = 0; i < fEdges*2; i = i + 2) {
    int u, v, c;
    // Capacity c from u to v
    cin >> u >> v >> c;
    newEdge(u, v, c, i);
    neighbours[edges[i].v1].push_back(&edges[i]);
    neighbours[edges[i+1].v1].push_back(&edges[i+1]);

    edges[i].inverse = &edges[i+1];
    edges[i+1].inverse = &edges[i];
  }
}

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
	//	cout << path[i].v1 << " " << path[i].v2 << " " << path[i].edgeCapacity << "\n";
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
	Print maxflow solution to standard output.
 */
void writeMaxFlowSolution() {
	fEdges = 0;
	
	std::ostringstream stream;
	for(unsigned int i = 0; i < edges.size(); ++i) {
		if(edges[i].edgeFlow > 0 && i%2 == 0) {
			++fEdges;
			stream << edges[i].v1 << " " << edges[i].v2 << " " << edges[i].edgeFlow << "\n";
		}
	}
	
	
	cout << fVertices << "\n" << fSource << " " << fTarget << " " << max_flow << "\n" << fEdges << "\n";
	
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

  readFlowGraph();

  solveFlowGraph();

  writeMaxFlowSolution();
/*
  clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

  cout << "Time elapsed: " << elapsed_secs << "s" << "\n";
*/
  return 0;
}




#include <iostream>
#include <vector>
#include <queue>

using std::cin;
using std::cout;
using std::cerr;


struct Edge {
  // Default constructor
  Edge(){}
  // Initialize with 3 values
  Edge(int x, int y, int a): v1(x), v2(y), edgeCapacity(a){
  	this->edgeFlow = 0;
  	this->edgeRestCapacity = edgeCapacity;
  }
  // Assignment operator
  Edge& operator=(const Edge & source) {
    v1 = source.v1;
    v2 = source.v2;
    edgeCapacity = source.edgeCapacity;
    edgeRestCapacity = source.edgeRestCapacity;
    edgeFlow = source.edgeFlow;
 	
    // Return the existing object
    return *this;
  }
  bool operator==(const Edge & source) {
  	return (this->v1 == source.v1) && (this->v2 == source.v2);
  }
  bool exists(std::vector<Edge> e) {
  	for(int i = 0; i < e.size(); ++i) {
  		if(this->v1 == e[i].v1 && this->v2 == e[i].v2)
  			return true;
  	}
  	return false;
  }
  int v1;
  int v2;
  // Variables for Ford-Fulkersons
  int edgeFlow; // = f[u,v]
  int edgeCapacity; // = c[u,v]
  int edgeRestCapacity; // = cf[u,v]

  //  Find neighbours of an Edge
  std::vector<Edge> neighbours(std::vector<Edge> edges) {
    std::vector<Edge> e;
    for(int i = 0; i < edges.size(); ++i) {
      if(edges[i].v1 == this->v2) {
      	//cout << "Printing neighbour..." << "\n";
      	//cout << edges[i].v1 << " " << edges[i].v2 << " " << edges[i].edgeCapacity << "\n";
        e.push_back(edges[i]);
      }
    }
    return e;
  }
};

// Flow graph variables
int fVertices, fEdges, fSource, fTarget, max_flow;
//std::multimap<int, int> edges;

// Main vector for storing all edges
std::vector<Edge> edges;
std::vector<Edge> inverseEdges;
// Path vector used in bfs algorithm, filled if a path from source to target is found
std::vector<Edge> path;


/**
 * -------------------------------------Helper functions----------------------------------------
 */

/*
  Add new edge to Vector edges with values v1, v2 and capacity/flow c.
 */
void newEdge(int v1, int v2, int c = 1) {
  edges.push_back(Edge(v1, v2, c));
  inverseEdges.push_back(Edge(v2, v1, 0));
}



/*
  Print values in edges and global variables.
  @param isFlowGraph: True if graph to be printed is a flow graph, otherwise false (then it is a bipartite graph).
  @param withCapacity: True if output for a bipartite graph should contain capacity.
  @param withFlow: True if the flow should be printed for a flow graph (which you would probably want when it is solved).
 */
/*
void print(bool isFlowGraph = false, bool withFlow = false) {

  if(!isFlowGraph) {
    cout << gX << " " << gY << std::endl << nrOfEdges << "\n";
    for(int i = 0; i < edges.size(); ++i) {
      cout << edges[i].v1 << " " << edges[i].v2;

      //(withCapacity) ? cout << " " << edges[i].c : false;
      cout << std::endl;
    }
   } else {
    cout << fVertices << "\n" << fSource << " " << fTarget;

    (withFlow) ? cout << " " << flow << "\n" : cout << "\n";
    cout  << fEdges << "\n";
    for(int i = 0; i < edges.size(); ++i) {
      cout << edges[i].v1 << " " << edges[i].v2 << " " << edges[i].c << std::endl;
    }
  }
  
}
*/

void minorPrint(Edge print) {
	//cout << "Nytt varv i bfs!" << std::endl;
	cout << "Current: " << print.v1 << " " << print.v2 << " " << print.edgeCapacity << std::endl;
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

	// Mark source as visited
    //visited[fSource] = true;


    Edge current;
    Edge next;

    

    while(!q.empty()) {
 		
 		current = q.front();
        q.pop();
        
        // Debugutskrift
        //minorPrint(current);

        // Retrieve neighbours of current edge with method neighbours in struct Edge
 		std::vector<Edge> neighbours = current.neighbours(edges);

 		// Loop through the neighbours
    	for (int i = 0; i < neighbours.size(); ++i) {
    		next = neighbours[i];
    		//cout << "Next: " << next.v1 << " " << next.v2 << " " << next.edgeCapacity << std::endl;
    		//cout << "Next.edgeRestCapacity: " << next.edgeRestCapacity << std::endl;
            if (visited[next.v2] == false && next.edgeRestCapacity > 0) {
    		//cout << "Next: " << next.v1 << " " << next.v2 << " " << next.edgeCapacity << std::endl;

            	// Return true if fTarget has been reached
            	if(next.v2 == fTarget) {
            		path.push_back(next); // Add node to path
	                visited[next.v2] = true;
	                //cout << "TADAAAAAA" << "\n";
	                cout << "\n" << "\n" << "\n";
					cout << "Skriver ut tmpPath... " << "\n";
					for(int i = 0; i < path.size(); ++i) {
						//cout << tmpPath[i].v1 << " " << tmpPath[i].v2 << " " << tmpPath[i].edgeCapacity<< "\n"; 
						cout << path[i].v1 << " " << path[i].v2 << " " << path[i].edgeFlow << "\n"; 

					}
					cout << "\n" << "\n" << "\n";
	                return true;
            	}
            	path.push_back(next); // Add node to path
                q.push(next);
                visited[next.v2] = true;
                // Debugutskrift
                //cout << "\"" << next.v1 << " " << next.v2 << " " << next.c << "\" " << "tillagd i kön!" << std::endl;
            }
        }

    }

    // Return true if target (or sink) is visited
    return 0;//(visited[fTarget] == true);
}


/* ---------------------------------------------------------------------------------------------*/

void readFlowGraph() {
  // debugutskrift
  //cerr << "Börjar läsa Maxflödeslösning." << std::endl;

  int vertices, e, source, target;

  // Läs in antal hörn, källa, sänka, flöde och antal kanter.
  // (Antal hörn, källa och sänka borde vara samma som vi i grafen vi
  // skickade iväg)
  cin >> vertices >> source >> target >> e;

  fVertices = vertices;
  fSource = source;
  fTarget = target;
  fEdges = e;
  // Clear edges vector.
  edges.clear();

  for (int i = 0; i < e; ++i) {
    int u, v, c;
    // Flöde f från u till v
    cin >> u >> v >> c;
    newEdge(u, v, c);
  }
}

/*
	Solve the maxflow problem.
 */
void solveFlowGraph() {




for(int i = 0; i < edges.size(); ++i) {
	 	//path[i].edgeFlow = 0;
	 	edges[i].edgeFlow = 0;
	 	//inverseEdges[i].edgeFlow = 0;
	 	//path[i].edgeRestCapacity = path[i].edgeCapacity;
	 	edges[i].edgeRestCapacity = edges[i].edgeCapacity;
	 	//inverseEdges[i].edgeRestCapacity = inverseEdges[i].edgeCapacity;
 	}

/*
while(bfs()) {
	// Vi måste införa inverser för att kunna ha flöde åt båda hållen.
	
	std::vector<Edge> tmpPath;

	Edge tmpEdge = path[fTarget];

	int path_flow = tmpEdge.edgeRestCapacity;

	while(tmpEdge.v1 != fSource) {
		path_flow = std::min(path_flow, tmpEdge.edgeRestCapacity);
		tmpPath.push_back(tmpEdge);
		tmpEdge = path[tmpEdge.v1];
	}
	// The first edge
	path_flow = std::min(path_flow, tmpEdge.edgeRestCapacity);
	tmpPath.push_back(tmpEdge);
	*/

while(bfs()) {
/*
	std::vector<Edge> tmpPath;

	Edge tmpEdge = path[fTarget];

	int path_flow = tmpEdge.edgeRestCapacity;

	while(tmpEdge.v1 != fSource) {
		path_flow = std::min(path_flow, tmpEdge.edgeRestCapacity);
		tmpPath.push_back(tmpEdge);
		tmpEdge = path[tmpEdge.v1];
	}
	// The first edge
	path_flow = std::min(path_flow, tmpEdge.edgeRestCapacity);
	tmpPath.push_back(tmpEdge);
*/
	std::vector<Edge> tmpPath;

	int path_flow = INT_MAX;
	Edge prevEdge;
	for(int i = path.size()-1; i >= 0; --i) {
		if(path[i].v2 == prevEdge.v1 || path[i].v2 == fTarget) {
			//cout << path[i].v1 << " " << path[i].v2 << " " << path[i].edgeCapacity << "\n";
			path_flow = std::min(path_flow, path[i].edgeRestCapacity);
			tmpPath.insert(tmpPath.begin(), path[i]);
		}
		prevEdge = path[i];
	}
	

// Debugutskrift
/*
	cout << "\n" << "\n" << "\n";
	cout << "Skriver ut tmpPath... " << "\n";
	for(int i = 0; i < tmpPath.size(); ++i) {
		//cout << tmpPath[i].v1 << " " << tmpPath[i].v2 << " " << tmpPath[i].edgeCapacity<< "\n"; 
		cout << path[i].v1 << " " << path[i].v2 << " " << path[i].edgeFlow << "\n"; 

	}
	cout << "\n" << "\n" << "\n";
	*/
	

	

	max_flow += path_flow;
	for(int i = edges.size(); i >= 0; --i) {
		if(edges[i].exists(tmpPath)) {
			edges[i].edgeFlow += path_flow;
			edges[i].edgeRestCapacity = edges[i].edgeCapacity - edges[i].edgeFlow;
		}
	}
}
}

/*

	A = 1;
	B = 2;
	S = 3;
	G = 4;
	C = 5;
	F = 6;
	D = 7;
	E = 8;
	H = 9;
   
  		_-------1-------_
  	_---3---_			2
  	|		|
  	4---_---5---_
  	|	6	|	7
  	9-------8		

   
  */


	
 
 /*
for(int i = 0; i < path.size() && path[i].edgeFlow > 0; ++i) {
	max_flow += path[i].edgeFlow;
}
*/
	

/*
	Print maxflow solution to standard output.
 */
void writeMaxFlowSolution() {
	cout << fVertices << "\n" << fSource << " " << fTarget << " " << max_flow << "\n" << fEdges << "\n";
	for(int i = 0; i < edges.size(); ++i) {
		cout << edges[i].v1 << " " << edges[i].v2 << " " << edges[i].edgeFlow << "\n";
	}

	cout.flush();

}



int main(void) {
  // Två trick för att göra cin/cout lite snabbare.
  // Se http://kattis.csc.kth.se/doc/iostreamio
  std::ios::sync_with_stdio(false);
  cin.tie(0);

  readFlowGraph();

  solveFlowGraph();

  writeMaxFlowSolution();

  // debugutskrift
  //cerr << "Bipred avslutar\n";
  return 0;
}






/*
	for(int i = edges.size(); i >= 0; --i) {

		std::find_if(path.begin(), path.end(), 
       	[&ce = edges[i]]
        (const Edge& e) -> bool { return (ce.v1 == e.v1) && (ce.v2 == e.v2);});
      
    
	if(i > path.size()-1 && edges[i].exists(path)) {
		edges[i].edgeFlow += path_flow;
		edges[i].edgeRestCapacity = edges[i].edgeCapacity - edges[i].edgeFlow;
	} else {
 		//path[i].edgeFlow += path_flow;
 		//inverseEdges[i].edgeFlow -= path[i].edgeFlow;
 		//cout << "inverseEdges[i].edgeFlow: " << inverseEdges[i].edgeFlow << "\n";
 		//path[i].edgeRestCapacity = path[i].edgeCapacity - path[i].edgeFlow;
 		//inverseEdges[i].edgeRestCapacity = inverseEdges[i].edgeCapacity - inverseEdges[i].edgeFlow;
		}

	}
	*/

/*
	edges.clear();
	newEdge(1,3);
	newEdge(3,6);
	newEdge(3,8);
	newEdge(3,10);
	newEdge(10,4);

	Edge e = Edge(2,3,1);
 	std::vector<Edge> n = e.neighbours(edges);

 	for(int i = 0; i < n.size(); ++i) {
 		cout << n[i].v1 << " " << n[i].v2 << " " << n[i].edgeCapacity << "\n";
 	}
*/
/*
	while(bfs()) {
		for(int i = 0; i < path.size(); ++i) {
			cout << path[i].v1 << " " << path[i].v2 << " " << path[i].edgeCapacity << "\n";
		}
		cout << "Nytt varv" << "\n";
	}
*/
/*
	for(int i = 0; i < edges.size(); ++i) {
	 	//path[i].edgeFlow = 0;
	 	edges[i].edgeFlow = 0;
	 	inverseEdges[i].edgeFlow = 0;
	 	//path[i].edgeRestCapacity = path[i].edgeCapacity;
	 	edges[i].edgeRestCapacity = edges[i].edgeCapacity;
	 	inverseEdges[i].edgeRestCapacity = inverseEdges[i].edgeCapacity;
 	}
 
max_flow = 0;

Edge tmp;
// As long as we find new paths, perform while loop
while(bfs()) {
	// Vi måste införa inverser för att kunna ha flöde åt båda hållen.
	
 	//max_flow += 1;
	
	std::vector<Edge> tmpPath;

	Edge tmpEdge = path[fTarget];

	int path_flow = tmpEdge.edgeRestCapacity;

	while(tmpEdge.v1 != fSource) {
		path_flow = std::min(path_flow, tmpEdge.edgeRestCapacity);
		tmpPath.push_back(tmpEdge);
		tmpEdge = path[tmpEdge.v1];
	}
	// The first edge
	path_flow = std::min(path_flow, tmpEdge.edgeRestCapacity);
	tmpPath.push_back(tmpEdge);


 

 	max_flow += path_flow;
 



	for(int i = 0; i < tmpPath.size(); ++i) {
		Edge & tmp = tmpPath[i];
		
		tmp.edgeFlow += path_flow;
		tmp.edgeRestCapacity = tmp.edgeCapacity - tmp.edgeFlow;
	}
	
 }
 
*/


	/*

	//readFlowGraph();
  fSource = 1;
  fTarget = 9;
  //solveFlowGraph();
  newEdge(1,2);
  newEdge(1,3);
  newEdge(3,4);
  newEdge(3,5);
  newEdge(4,6);
  newEdge(4,9);
  newEdge(5,6);
  newEdge(5,7);
  newEdge(5,8);
  newEdge(8,9);

 

  cout << bfs() << "\n";

  for(int i = 0; i < path.size(); ++i) {
  	cout << path[i].v1 << " " << path[i].v2 << " " << path[i].c << std::endl;
  }
  */

  /*

	A = 1;
	B = 2;
	S = 3;
	G = 4;
	C = 5;
	F = 6;
	D = 7;
	E = 8;
	H = 9;
   
  		_-------1-------_
  	_---3---_			2
  	|		|
  	4---_---5---_
  	|	6	|	7
  	9-------8		

   
  */
  /*

	int path_flow = INT_MAX;
	for(int i = path.size()-1; i >= 0; --i) {
		//tmp = path[i];
		//
		//minorPrint(path[i]);

		path_flow = std::min(path_flow, path[i].edgeRestCapacity);
		//cout << path_flow << "\n";
	}
	

	//for(int i = edges.size(); i >= 0; --i) {

		std::find_if(path.begin(), path.end(), 
       	[&ce = edges[i]]
        (const Edge& e) -> bool { return (ce.v1 == e.v1) && (ce.v2 == e.v2);});
      
    
	if(i > path.size() && edges[i].exists(path)) {
		edges[i].edgeFlow += path_flow;
		edges[i].edgeRestCapacity = edges[i].edgeCapacity - edges[i].edgeFlow;
	} else {
 		path[i].edgeFlow += path_flow;
 		inverseEdges[i].edgeFlow -= path[i].edgeFlow;
 		//cout << "inverseEdges[i].edgeFlow: " << inverseEdges[i].edgeFlow << "\n";
 		path[i].edgeRestCapacity = path[i].edgeCapacity - path[i].edgeFlow;
 		inverseEdges[i].edgeRestCapacity = inverseEdges[i].edgeCapacity - inverseEdges[i].edgeFlow;
		}

	}
	*/
 
 /*
for(int i = 0; i < path.size() && path[i].edgeFlow > 0; ++i) {
	max_flow += path[i].edgeFlow;
}
*/




//return max_flow;



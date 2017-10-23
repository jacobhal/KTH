/**
 * Exempel på in- och utdatahantering för maxflödeslabben i kursen
 * ADK.
 *
 * Använder iostreams i C++.
 * Anmärkning: scanf/printf-rutinerna från C-exemplet går att använda
 * även i C++ och är ofta märkbart snabbare än cin/cout som det här
 * programmet använder.
 *
 * Author: Per Austrin
 */

#include <iostream>
#include <map>
#include <vector>

using std::cin;
using std::cout;
using std::cerr;


struct Edge {
  // Default constructor
  Edge(){}
  // Initialize with 3 values
  Edge(int x, int y, int a): v1(x), v2(y), c(a){}
  // Assignment operator
  Edge& operator=(const Edge & source) {
    v1 = source.v1;
    v2 = source.v2;
    c = source.c;
  
    // Return the existing object
    return *this;
  }
  int v1;
  int v2;
  int c;

  //  Find neighbours of an Edge
  std::vector<Edge> neighbours(std::vector<Edge> edges) {
    std::vector<Edge> e;
    for(int i = 0; i < edges.size(); ++i) {
      if(edges[i].v1 == this->v2) {
        e.push_back(edges[i]);
      }
    }
    return e;
  }
};

// Normal graph variables
int gX, gY, nrOfEdges;
// Flow graph variables
int fVertices, fEdges, fSource, fTarget, edgeFlow;
//std::multimap<int, int> edges;

std::vector<Edge> edges;

/**
 * -------------------------------------Helper functions----------------------------------------
 */

/*
  Add new edge to Vector edges with values v1, v2 and capacity/flow c.
  TODO: Måste lägga till inverser för att hålla koll på flöde åt båda hållen sen.
 */
void newEdge(int v1, int v2, int c = 1) {
  edges.push_back(Edge(v1, v2, c));
}



/*
  Print values in edges and global variables.
  @param isFlowGraph: True if graph to be printed is a flow graph, otherwise false (then it is a bipartite graph).
  @param withFlow: True if the flow should be printed for a flow graph (which you would probably want when it is solved).
 */
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

    (withFlow) ? cout << " " << edgeFlow << "\n" : cout << "\n";
    cout  << fEdges << "\n";
    for(int i = 0; i < edges.size(); ++i) {
      cout << edges[i].v1 << " " << edges[i].v2 << " " << edges[i].c << std::endl;
    }
  }
  
}


/* ---------------------------------------------------------------------------------------------*/

void readBipartiteGraph() {
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
  Responsible for
 */
void writeFlowGraph() {
  fVertices = gX + gY;
  
  
  // fSource = 0
  // fTarget = fVertices+1


  // Källa och sänka ska tydligen vara värden som finns i grafen, inte 0 och antal hörn + 1?

  fSource = fVertices+1;
  fTarget = fVertices+2;
  fVertices += 2;

  

   // Skapa kanter mellan Källa och gX samt gY och Sänka.
   // TODO: Inverser eller ej?
  
  for(int i = 1; i <= fVertices-2; ++i) {
    if(i <= gX) {
      newEdge(fSource, i, 1);
    } else {
      newEdge(i, fTarget, 1);
    }
  }

  fEdges = edges.size();
  // Print flowgraph without flow value after source and target
  print(1,0);
  // Var noggrann med att flusha utdata när flödesgrafen skrivits ut!
  // Flush makes sure that the buffer is cleared and the characters are written to their destination
  cout.flush();

  // Debugutskrift
  //cerr << "Skickade iväg flödesgrafen\n";
}

/*
  Responsible for reading a maxflow solution from stdin and converting it to a solution 
  for the maximum matching problem.
 */

void readMaxFlowSolution() {
  // debugutskrift
  //cerr << "Börjar läsa Maxflödeslösning." << std::endl;

  int vertices, e, source, target, edgeFlow;

  // Läs in antal hörn, källa, sänka, flöde och antal kanter.
  // (Antal hörn, källa och sänka borde vara samma som vi i grafen vi
  // skickade iväg)
  cin >> vertices >> source >> target >> edgeFlow >> e;

  nrOfEdges = e;
  // Clear edges vector.
  edges.clear();

  for (int i = 0; i < e; ++i) {
    int u, v, f;
    // Flöde f från u till v
    cin >> u >> v >> f;
    if(u != fSource && v != fTarget) {
      newEdge(u, v, f);
    }
  }
  nrOfEdges = edges.size();

  // TODO: Översätt till matchningslösning
}

/*
  Responsible for writing the final maximum matching problem for a bipartite graph.
 */
void writeBipMatchSolution() {

  print();

}


int main(void) {
  // Två trick för att göra cin/cout lite snabbare.
  // Se http://kattis.csc.kth.se/doc/iostreamio
  std::ios::sync_with_stdio(false);
  cin.tie(0);

  

  // TODO: Väldigt osäker om multimap är bästa datastrukturen, en array skulle förmodligen funka lika bra eller bättre
  //std::multimap<int, int> edges; // Lagrar alla kanter i den bipartita grafen.
  readBipartiteGraph(); // Läser in bipartit graf

  writeFlowGraph(); 

  readMaxFlowSolution();

  writeBipMatchSolution();

  // debugutskrift
  //cerr << "Bipred avslutar\n";
  return 0;
}



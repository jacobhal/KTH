#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

int nrOfVertices, nrOfEdges, nrOfColours;

int nrOfRoles, nrOfScenes, nrOfActors;

typedef tuple<int,int> Edge;

vector<Edge> edges;



void print() {
  // tuple_element is a meta function to define type of tuple elements
  tuple_element <0, Edge>::type v1; //int
  tuple_element <1, Edge>::type v2; //int

  cout << nrOfVertices << "\n" << nrOfEdges << "\n" << nrOfColours;
  for(int i = 0; i < nrOfEdges; ++i) {
    cout << "\n";
    v1 = get<0> (edges[i]);
    v2 = get<1> (edges[i]);
    cout << v1 << " " << v2;
  }
  cout << "\n";
}

void readVerticeColoring() {

  int v, e, c;

  // Läs in antal roller, scener och skådespelare
  cin >> v >> e >> c;

  // Set variables
  nrOfVertices = v;
  nrOfEdges = e;
  nrOfColours = c;

  /*
    Hörn = Roller
    Kanter = Scener
    Färger = Skådespelare
   */
  nrOfRoles = nrOfVertices + 1;
  nrOfScenes = nrOfEdges + 2;
  nrOfActors = nrOfColours + 1;

  int v1, v2;

  // Lagra kanter (scener) i tuple vektor
  for(int i = 0; i < nrOfEdges; ++i) {
    cin >> v1 >> v2;
    // Add 2 to every value to avoid the divas
    edges.push_back(make_tuple(v1+1, v2+1));
  }
}

void writeRoleProblem() {
    cout << nrOfRoles << " " << nrOfScenes << " " << nrOfActors;

    // Add the divas separately
    cout << "\n";
    cout << "1 1" << endl;
    //cout << "1 2" << endl;

    // Start from third role
    for(int i = 2; i <= nrOfRoles; ++i) {
      cout << "\n";
      cout << nrOfActors - 1; // Number of actors with the added divas excluded
      // Start from actor nr 3 (since divas have their roles assigned already)
      for(int j = 2; j <= nrOfActors; ++j) {
        cout << " " << j;
      }
    }
	
    // Add scenes for divas (3 is also added since scenes cannot contain only one role)
    cout << "\n";
    for(int i = 0; i < nrOfRoles; ++i) {
      cout << "2 1" << i << "\n";
    } 

    // Write out all the scenes
    for(int i = 0; i < nrOfScenes - 2; ++i) {
      cout << "\n";
      cout << 2 << " " << get<0> (edges[i]) << " " << get<1> (edges[i]);
    }
    cout << "\n";
}


int main(void) {
  // Två trick för att göra cin/cout lite snabbare.
  // Se http://kattis.csc.kth.se/doc/iostreamio
  std::ios::sync_with_stdio(false);
  cin.tie(0);

  readVerticeColoring();

  writeRoleProblem();


  return 0;
}




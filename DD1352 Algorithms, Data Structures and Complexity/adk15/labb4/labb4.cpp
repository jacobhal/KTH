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
  nrOfRoles = nrOfVertices + 2;
  nrOfScenes = nrOfEdges + 2;
  nrOfActors = nrOfColours + 2;

  int v1, v2;

  // Lagra kanter (scener) i tuple vektor
  for(int i = 0; i < nrOfEdges; ++i) {
    cin >> v1 >> v2;
    // Add 2 to every value to avoid the divas
    edges.push_back(make_tuple(v1+2, v2+2));
  }
}

void writeRoleProblem() {
    cout << nrOfRoles << " " << nrOfScenes << " " << nrOfActors;

    // Add roles
    //  for the divas
    cout << "\n";
    cout << "1 1" << endl;
    cout << "1 2" << endl;

    // Start from third role
    for(int i = 3; i <= nrOfRoles; ++i) {
      cout << "\n";
      cout << nrOfActors - 2; // Number of actors with the added ones excluded
      // Start from actor nr 3 (since added ones have their roles assigned already)
      for(int j = 3; j <= nrOfActors; ++j) {
        cout << " " << j;
      }
    }
	
    // Add scenes
    cout << "\n";
    cout << "2 1 3" << endl;
    cout << "2 2 3";

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

/*
  General idea

  Add one colour (actor) to represent both divas so that the divas will always have the same colour and therefore
  they cannot participate in the same scene. We also need to add another role to represent our diva.
  For some cases this solution doesn't work (the most simple ones, for instance) so we have to add another
  actor, scene and role.
  Excluding the prints, this reduction is polynomial (constant) so it meets the requirements for a karp-reduction.
 */




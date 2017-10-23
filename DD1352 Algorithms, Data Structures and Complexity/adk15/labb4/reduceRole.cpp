#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

int nrOfVertices, nrOfEdges, nrOfColours;

int nrOfRoles, nrOfScenes, nrOfActors;

//vector< vector<int> > roles;
//vector< vector<int> > scenes;

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

  nrOfRoles = nrOfVertices + 3;
  nrOfScenes = nrOfEdges + 2;
  nrOfActors = nrOfColours + 2;

  int v1, v2;

  for(int i = 0; i < nrOfEdges; ++i) {
    cin >> v1 >> v2;
    edges.push_back(make_tuple(v1, v2));
  }

  //print();

/*
  // Read roles and add actors to roles array
  roles.reserve(nrOfRoles);
  for (int i = 0; i < nrOfRoles; ++i) {
    // Each line tells which actors can play role i
    int n;
    cin >> n;
    for(int j = 0; j < n; ++j) {
      int k;
      cin >> k;
      roles[i].push_back(k);
    }
  }


  // Read scenes and add roles to scenes array
  scenes.reserve(nrOfScenes);
  for(int i = 0; i < nrOfScenes; ++i) {
    // Each line tells which roles are used in scene i
    int n;
    cin >> n;
    for(int j = 0; j < n; ++j) {
      int k;
      cin >> k;
      scenes[i].push_back(k);
    }
  }
*/
  //print();

}

void writeRoleProblem() {
    cout << nrOfRoles << " " << nrOfScenes << " " << nrOfActors << "\n";

    // Print roles
    //cout << "-----------------ROLES---------------------" << "\n";
    cout << 1 << " " << 1 << "\n";
    cout << 1 << " " << 2 << "\n";
    cout << 1 << " " << 3;
    //cout << "\n" << "Nr of roles: " << nrOfRoles;
    // Start from role nr 4
    for(int i = 4; i <= nrOfRoles; ++i) {
      cout << "\n";
      cout << nrOfActors-2; // Number of actors with the added divas excluded
      // Start from actor nr 3
      for(int j = 3; j <= nrOfActors; ++j) {
        cout << " " << j;
      }
    }
    //cout << "\n" << "-----------------SCENES---------------------";

    // Print scenes
    cout << "\n" << 2 << " " << 1 << " " << 3 << "\n";
    cout << 2 << " " << 2 << " " << 3;
    //cout << "\n" << "Nr of scenes: " << nrOfScenes;
    // Start from scene nr 3
    for(int i = 0; i < nrOfScenes-2; ++i) {
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

  //reduce();

  writeRoleProblem();


  return 0;
}



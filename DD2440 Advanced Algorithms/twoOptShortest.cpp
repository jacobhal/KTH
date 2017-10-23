#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>
#include <limits>
#include <stack>
#include <algorithm>
#include <chrono>

struct Point {
    double a;
    double b;
    int   id;
};

struct Edge {
    int firstNode;
    int secondNode;
    int distance;

    void print() {
        std::cout << firstNode << " " << secondNode << " Distance: " << distance << std::endl; 
    }

    void print_ids() {
        std::cout << firstNode << "to " << secondNode << ", " << " Distance: " << distance << std::endl; 
    }
};

// Edge distance compare operator
bool operator< (const Edge& a, const Edge& b) {
    return a.distance < b.distance;
}

bool operator==(const Edge& a, const Edge& b) {
    return (a.firstNode == b.firstNode && a.secondNode == b.secondNode);
};

bool operator!=(const Edge& a, const Edge& b) {
    return (a.firstNode != b.firstNode || a.secondNode != b.secondNode);
};

// Function declarations
int distance(Point, Point);
std::vector<int> greedyAlgorithm();
std::vector<int> randomizeVector(std::vector<int> &);

int twoOpt();
void twoOptSwap(int&, int&);
int tourDistance(std::vector<int>);

bool isCyclic(Edge, std::vector<Edge>&);
bool findEdge(Edge, std::vector<Edge>&);
void shortestEdge(std::vector<Edge> &);


// Global variables
std::vector <Point> points;
std::vector <Edge> edges;

std::vector<std::vector<int>> distMat;
std::vector<int> tour;
std::vector<int> newTour;
std::vector<int> bestTour;

int nrOfPoints = 0;

using namespace std;
int main() {
    cin >> nrOfPoints;

    vector<int> path(nrOfPoints);

    for(int i = 0; i < nrOfPoints; ++i) {
        Point point;
        cin >> point.a;
        cin >> point.b;
        point.id = i;
        points.push_back(point);
        path[i] = i;
    }


    distMat.resize(nrOfPoints, vector<int>(nrOfPoints));

    for (int i = 0; i < distMat.size(); ++i) {
        for(int j = 0; j < distMat[i].size(); ++j) {
            distMat[i][j] = 0;
        }
    }

    for(int i = 0; i < nrOfPoints; ++i) {
        for(int j = i+1; j < nrOfPoints; ++j) {
            int dist = distance(points[i], points[j]);
            Edge edge;
            edge.firstNode = i;
            edge.secondNode = j;
            edge.distance = dist;
            distMat[i][j] = dist;
            distMat[j][i] = dist;
            edges.push_back(edge);
        }
    }


    sort(edges.begin(), edges.end());

    vector<Edge> e;
    shortestEdge(e);


    for(int i = 0; i < e.size(); ++i) {
        e[i].print();
    }


    

/*
    for (int i = 0; i < distMat.size(); ++i) {
        for(int j = 0; j < distMat[i].size(); ++j) {
            cout << distMat[i][j] << " ";
        }
        cout << endl;
    }
*/


    //tour = greedyAlgorithm();

    /*
    tour.resize(nrOfPoints);
    for(int i = 0; i < tour.size(); ++i) {
        tour[i] = i;
    }
    */

    //vector<Point>().swap(points);


    int bestDistance = numeric_limits<int>::max();
    int currentDistance = numeric_limits<int>::max();

    tour = randomizeVector(path);
    newTour.resize(tour.size());
    bestTour = tour;
    // Loop with random constructing
    for(int i = 0; i < 6; ++i) {
        tour = randomizeVector(path);
        currentDistance = twoOpt();
        if(bestDistance > currentDistance) {
            bestDistance = currentDistance;
            bestTour = tour;
        }
    }

    // Loop with greedy constructing
    for(int i = 0; i < 18; ++i) {
        tour = greedyAlgorithm();
        currentDistance = twoOpt();
        if(bestDistance > currentDistance) {
            bestDistance = currentDistance;
            bestTour = tour;
        }
    }
    

    for (int i = 0; i < tour.size(); ++i)
    {
        cout << bestTour[i] << endl;
    }
    

    return 0;
};


int adjacentNodes(Edge e, vector<Edge> &path) {
    int c1 = 1;
    int c2 = 1;
    for (int i = 0; i < path.size(); ++i) {
        if(path[i].firstNode == e.firstNode || path[i].secondNode == e.firstNode) {
            c1++;
        } else if (path[i].firstNode == e.secondNode || path[i].secondNode == e.secondNode) {
            c2++;
        }
    }
    int c = 0;
    if(c1 > c2) {
        c = c1;
    } else {
        c = c2;
    }
    cout << "Count: " << c << endl;
    return c;
}

void shortestEdge(vector<Edge> &path) {
    for(int i = 0; i < edges.size(); ++i) {
        cout << "Loop " << i << endl;
        if(!isCyclic(edges[i], path) && adjacentNodes(edges[i], path) < 3) {
            cout << "ADDING (" << edges[i].firstNode << ", " << edges[i].secondNode << ")" << endl;
            path.push_back(edges[i]);
        }
        if(path.size() == nrOfPoints-1) {
            break;
        }
    }
}
// FIX this
bool isCyclic(Edge edge, vector<Edge> &path) {

    int nextNode = 0;
    if(!findEdge(edge, path)) { // Edge not found in current path
        /*
        bool a = false;
        bool b = false;
        
        for(int i = 0; i < path.size(); ++i) {
            if(edge.firstNode == path[i].firstNode || edge.secondNode == path[i].firstNode) {
                nextNode = path[i].secondNode;
            }
            if(edge.secondNode == path[i].secondNode || edge.secondNode == path[i].secondNode) {
                nextNode = path[i].firstNode;
            }
        }
        if(a && b) {
            return true;
        }
        */
        
    }
    return false;
}

bool findEdge(Edge edge, vector<Edge> &e) {
    for(int i = 0; i < e.size(); ++i) {
        if(e[i] == edge) {
            return true;
        }
    }
    return false;
}



void twoOptSwap(int &i, int &j) {
    //cout << "Adding first routes\n";

    for (int k = 0;  k <= i-1; ++k)
    {
        newTour[k] = tour[k];
        //cout << "From: " << tour[k] << " To: " << tour[k+1] << endl;

    }

    //cout << "---SWAPPING---\n";

    int decrementer = 0;
    for (int k = i; k <= j; ++k)
    {
        //cout << "From: " << tour[k] << " To: " << tour[j-decrementer] << endl;
        newTour[k] = tour[j-decrementer];
        decrementer++;
    }

    //cout << "Adding last routes\n";

    for (int k = j+1;  k < tour.size(); ++k)
    {
        newTour[k] = tour[k];
    }

    
}


int twoOpt() {
    int tourSize = nrOfPoints;

    int improvement = 0;
    // Compute total tour distance
    int bestDist = tourDistance(tour);

    int diff = 0;
    vector<int> optimalSwap(2);
    

    while(improvement < 3) {
        for (int i = 0; i < tourSize - 1; ++i) {
           for (int j = i + 1; j < tourSize; ++j) {

                /*
                cout << "{";
                for (int i = 0; i < tour.size(); ++i) {
                    cout << tour[i];
                    if(i != tour.size()-1) {
                        cout << ", ";
                    }
                }
                cout << "}\n";
                */
                //double newDist = numeric_limits<int>::max();
                int indexI = i-1;
                int indexJ = j+1;
                if (i == 0) {
                    indexI = 0;
                }
                if (indexJ == tourSize) {
                    indexJ = j;
                }
                // kolla alla möjliga valueswaps sen gör den som är mest value.
                int oldPartTour = distMat[tour[indexI]][tour[indexI+1]] + distMat[tour[j]][tour[indexJ]];
                int newPartTour = distMat[tour[indexI]][tour[j]] + distMat[tour[indexI+1]][tour[indexJ]];
                if(oldPartTour > newPartTour){
                    optimalSwap[0] = i;
                    optimalSwap[1] = j;
                } else {
                    continue;
                }

                 // Update newTour with performed swap
                twoOptSwap(optimalSwap[0], optimalSwap[1]);

                int newDist = tourDistance(newTour);
                
                if (newDist < bestDist) {
                    improvement = 0;
                    tour = newTour;
                    bestDist = newDist;
                }   
                

            }
        }
        improvement++;
    }

    return tourDistance(tour);

        //cout << "Best distance: " << bestDist << endl;
    //}
}

int tourDistance(vector<int> seq) {

    int res = 0;
    for (int i = 0; i < tour.size()-1; ++i)
    {
        res += distMat[seq[i]][seq[i+1]];
    }
    res += distMat[seq[nrOfPoints-1]][seq[0]];
    //cout << "SUM: " << res << endl;
    return res;
    
}
 
/**
 * @brief      A greedy algoritm choosing the shortest path at every vertice.
 *
 * @return     Return chosen path.
 */
vector<int> greedyAlgorithm() {
    // Define path vector and initialize
    vector<int> path(nrOfPoints);
    vector<bool> isVisited(nrOfPoints);

    /* initialize random seed: */
    srand (time(NULL));

    int random = rand() % 10;

    path[random] = 0;
    isVisited[0] = true;

    //cout << "0: (" << points[path[0]].a << "," << points[path[0]].b << ")  \t" << endl;

    int best;
    int sum = 0;
    for(int i = 1; i < nrOfPoints; ++i) {
        best = -1;
        for(int j = 0; j < nrOfPoints; ++j) {
            
            if( (!isVisited[j] &&  best == -1) || (!isVisited[j]  && (distance(points[path[i-1]], points[j]) < distance(points[path[i-1]], points[best])) ) ) {
                best = j;
            }
        }
        path[i] = best;
        isVisited[best] = true;

    }

    return path;
}

vector<int> randomizeVector(vector<int> &path) {
    srand(time(NULL));
    random_shuffle(path.begin(), path.end());
    return path;
}

//Compute euclidian distance between two points (round to nearest integer)
int distance(Point firstPoint, Point secondPoint) {
    return sqrt(pow((secondPoint.a - firstPoint.a), 2) + pow((secondPoint.b - firstPoint.b), 2)) + 0.5;
}
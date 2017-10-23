/**
 * Authors: Jacob Hallman and Nedo Skobalj
 * (Greedy nearest neighbor)
 */
#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>
#include <limits>
#include <stack>
#include <algorithm>

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

// Structure for union by rank (rank associated with depth of tree which allows us to keep the resulting tree small)
struct Subset {
    int parent;
    int rank;
};


// Function declarations
int distance(Point, Point);
std::vector<int> greedyAlgorithm();
std::vector<int> randomizeVector();

int twoOpt();
void twoOptSwap(int&, int&);
int tourDistance(std::vector<int>);


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

    for(int i = 0; i < nrOfPoints; ++i) {
        Point point;
        cin >> point.a;
        cin >> point.b;
        point.id = i;
        points.push_back(point);
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

    int bestDistance = numeric_limits<int>::max();
    int currentDistance = numeric_limits<int>::max();
    for(int i = 0; i < 3; ++i) {
        tour = randomizeVector();
        bestTour = tour;
        newTour.resize(tour.size());
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

int tourDistance(vector<int> seq) {    

    int res = 0;
    for (int i = 0; i < tour.size()-1; ++i)
    {
        res += distMat[seq[i]][seq[i+1]];
    }
    res += distMat[seq[nrOfPoints-1]][seq[0]];

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

    path[0] = 0;
    isVisited[0] = true;

    int best;
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

vector<int> randomizeVector() {
    vector<int> path(nrOfPoints);
    for(int i = 0; i < nrOfPoints; ++i) {
        path[i] = i;
    }
    random_shuffle(path.begin(), path.end());
    return path;
}

//Compute euclidian distance between two points (round to nearest integer)
int distance(Point firstPoint, Point secondPoint) {
    return sqrt(pow((secondPoint.a - firstPoint.a), 2) + pow((secondPoint.b - firstPoint.b), 2)) + 0.5;
}
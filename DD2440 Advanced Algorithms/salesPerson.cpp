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
	Point a;
	Point b;
	int distance;

	void print() {
		std::cout << "(" << a.a << ", " << a.b << ") to (" << b.a << ", " << 
		b.b << ") Distance: " << distance << std::endl; 
	}

	void print_ids() {
		std::cout << a.id << "to " << b.id << ", " << " Distance: " << distance << std::endl; 
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

void twoOpt();
void twoOptSwap(int&, int&);
int tourDistance(std::vector<int>);


// Global variables
std::vector <Point> points;
std::vector <Edge> edges;
std::vector<std::vector<int>> distMat;
std::vector<int> tour;
std::vector<int> newTour;

using namespace std;
int main() {
	int nrOfPoints = 0;


	cin >> nrOfPoints;

	double a;
	double b;
	for(int i = 0; i < nrOfPoints; ++i) {
		cin >> a;
		cin >> b;
		Point point;
		point.a = a;
		point.b = b;
		point.id = i;
		points.push_back(point);
	}

/*
	distMat.resize(points.size(), vector<int>(points.size()));

	for (int i = 0; i < distMat.size(); ++i) {
		for(int j = 0; j < distMat[i].size(); ++j) {
			distMat[i][j] = 0;
		}
	}
*/
	for(int i = 0; i < nrOfPoints; ++i) {
		for(int j = i+1; j < nrOfPoints; ++j) {
			int dist = distance(points[i], points[j]);
			Edge edge;
			edge.a = points[i];
			edge.b = points[j];
			edge.distance = dist;
			edges.push_back(edge);
		}
	}


	tour = greedyAlgorithm();
	newTour.resize(tour.size());
	twoOpt();

	for (int i = 0; i < tour.size(); ++i)
	{
		cout << tour[i] << endl;
	}

	

/*
	for(int i = 0; i < tree.size(); ++i) {
		tree[i].print();
	}
*/
	

	return 0;
};

void twoOptSwap(int &i, int &j) {
	for (int k = 0;  k <= i-1; ++k)
	{
		newTour[k] = tour[k];
	}

	int decrementer = 0;
    for (int k = i; k <= j; ++k)
    {
    	newTour[k] = tour[j-decrementer];
        decrementer++;
    }


	for (int k = j+1;  k < tour.size(); ++k)
	{
		newTour[k] = tour[k];
	}

	
}


void twoOpt() {
	int tourSize = points.size();

	int improvement = 0;
	//while(improvement < 5) {
		
		// Compute total tour distance
		int bestDist = tourDistance(tour);

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
                twoOptSwap(i, j);
 
                double newDist = tourDistance(newTour);
 
                if (newDist < bestDist) {
                    improvement = 0;
                    tour = newTour;
                    bestDist = newDist;
                }
            }
        }
        improvement++;
	//}
}

int tourDistance(vector<int> seq) {
	/*
	int res = 0;
	int dist = 0;
	int firstNode = seq[0];
	for(int i = 0; i < tour.size()-1; ++i) {
		dist = distance(points[seq[i]], points[seq[i+1]]);
		res += dist;
	}
	res += distance(points[seq[points.size()-1]], points[firstNode]);
	return res;
	*/
	int res = 0;
	for (int i = 0; i < tour.size()-1; ++i)
	{
		res += distMat[seq[i]][seq[i+1]];
	}
	res += distMat[seq[points.size()-1]][seq[0]];
	return res;
}
 
/**
 * @brief      A greedy algoritm choosing the shortest path at every vertice.
 *
 * @return     Return chosen path.
 */
vector<int> greedyAlgorithm() {
	// Define path vector and initialize
	vector<int> path(points.size());
	vector<bool> isVisited(points.size());

	path[0] = 0;
	isVisited[0] = true;

	//cout << "0: (" << points[path[0]].a << "," << points[path[0]].b << ")  \t" << endl;

	int best;
	int sum = 0;
	for(int i = 1; i < points.size(); ++i) {
		best = -1;
		for(int j = 0; j < points.size(); ++j) {
			
			if( (!isVisited[j] &&  best == -1) || (!isVisited[j]  && (distance(points[path[i-1]], points[j]) < distance(points[path[i-1]], points[best])) ) ) {
				best = j;
			}
		}
		path[i] = best;
		isVisited[best] = true;

		//int min = distance(points[path[i-1]], points[path[i]]);
		//sum += min;
		//cout << path[i] << ": (" << points[path[i]].a << ",\t" << points[path[i]].b << ")  \t" << min << endl;

	}
	//cout << endl;
	//cout << distance(points[path[points.size() - 1]], points[path[0]]) << endl;
	//sum += distance(points[path[points.size() - 1]], points[path[0]]);
	//cout << "=" << endl;
	//cout << sum << endl;

	return path;
}



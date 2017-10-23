#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>
#include <limits>
#include <stack>

struct Point {
	double a;
	double b;
};

int distance(Point, Point);
std::vector<int> greedyAlgorithm();
int getShortestEdge(std::vector<bool>, std::vector<int>);
int getMinimumKeyIndex(std::vector<int>, std::vector<bool>);
std::vector<int> MST();
std::vector<int> DFS(int, std::vector<int>); 

// Global variables
std::vector <Point> points;

using namespace std;
int main() {
	int nrOfPoints = 0;


	cin >> nrOfPoints;

	double a,b;
	for(int i = 0; i < nrOfPoints; ++i) {
		cin >> a >> b;
		Point point;
		point.a = a;
		point.b = b;
		points.push_back(point);
	}

/*
	cout << "\n";
	cout << points[0].a << " " << points[0].b << endl;
	cout << points[8].a << " " << points[8].b << endl;
*/
/*
	cout << distance(points[0], points[8]) + distance(points[8], points[5]) + distance(points[5], points[4]) + distance(points[4], points[3]) 
	+ distance(points[3], points[9]) + distance(points[9], points[6]) + distance(points[6], points[2]) + distance(points[2], points[1])
	+ distance(points[1], points[7]) << endl;
*/	

	/*
	vector<int> result = greedyAlgorithm();

	for(int i = 0; i < result.size(); ++i) {
		cout << result[i] << endl;
	}

	*/






	//cout << "Testing MST" << endl;

	//vector<int> tree = MST();
	/*
	parent	index
	-1		0
	0		1
	0		2
	0		3
	2		4
	2		5
	4		7
	4		8
	3		6
	6		9
	6		10



	*/

	/*
		CONSTRUCT MST EXAMPLE TEST: https://www.cse.ust.hk/~dekai/271/notes/L07/L07.pdf

		GOTTA SEE IF MST IS CORRECT WHICH IT PROBABLY IS NOT...
	

	 
	 */

	vector<int> tree = {-1, 0, 0, 0, 2, 2, 3, 4, 4, 6, 6};
/*
	for(int i = 0; i < tree.size(); ++i) {
		cout << "Parent: " << tree[i] << ", Child: " << i << endl;
	}
*/
	DFS(0, tree);
	

	return 0;
};

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

	int best;
	for(int i = 1; i < points.size(); ++i) {
		best = -1;
		for(int j = 0; j < points.size(); ++j) {
			if( (!isVisited[j] &&  best == -1) || (!isVisited[j]  && (distance(points[path[i-1]], points[j]) < distance(points[path[i-1]], points[best])) ) ) {
				best = j;
			}
		}
		path[i] = best;
		isVisited[best] = true;

	}

	return path;
}

/**
 * @brief      Implementation of Prim's algorithm for creating a Minimal Spanning Tree (MST).
 *
 * @return     Return the MST.
 */
vector<int> MST() {
	// Define path vector and initialize
	vector<int> treeParent(points.size());		// MST Tree Index = child, Parent = value
	vector<int> minIndex(points.size());		// Distance
	vector<bool> visited(points.size());		// Keep track of visited nodes

	// Set visited nodes to false and all minIndex to infinite
	for(int i = 0; i < points.size(); ++i) {
		visited[i] = false;
		minIndex[i] = numeric_limits<int>::max();
	}

	treeParent[0] = -1; // Add first node as root
	minIndex[0] = 0;

	for(int i = 0; i < points.size()-1; ++i) {

		// Retrieve minimum key index
		int v = getMinimumKeyIndex(minIndex, visited);

		// Set selected index as visited
		visited[v] = true;

		// Update tree and minIndex adjacent to chosen node that have not yet been visited
		for(int j = 0; j < points.size(); ++j) {
			// Calculate distance from minimum key index to point
			int dist = distance(points[v], points[j]);

			// Check if calculated distance is less than the current calculated distance to node j
			if(dist < minIndex[j] && !visited[j]) {
				minIndex[j] = dist;
				treeParent[j] = v; // Store the minimum key index as parent for this node
			}

		}
	}

	return treeParent; 
}

/**
 * @brief      Gets the index of the minimal value in minKey vector. The index must be unvisited.
 *
 * @param[in]  weights  The weights
 * @param[in]  visited  The visited
 *
 * @return     The minimum key index.
 */
int getMinimumKeyIndex(vector<int> minIndex, vector<bool> visited) {
	int min = numeric_limits<int>::max();
	int index = -1;

	for(int i = 0; i < points.size(); ++i) {
		if(!visited[i] && minIndex[i] < min) {
			min = minIndex[i];
			index = i;
		}
	}

	return index;
}

vector<int> DFS(int v, vector<int> treeParent) {
	vector<bool> visited(points.size());
	vector<int> res(points.size());

	// Set visited nodes to false
	for(int i = 0; i < points.size(); ++i) {
		visited[i] = false;
	}

	stack<int> stack;

	visited[v] = true;
	stack.push(v);

	while(!stack.empty()) {
		v = stack.top();
		// Print chosen node
		cout << v << endl;
        stack.pop();

        // Add node to result vector
        res.push_back(v);

        // Very shitty
        for(int i = 0; i < treeParent.size(); ++i) {
        	// If v is parent of i and i has not been visited, push it so that we will visit it next
        	if(v == treeParent[i] && !visited[i]) {
        		visited[i] = true;
        		stack.push(i);
        	}
        }
	}

	return res;
}

// Compute euclidian distance between two points (round to nearest integer)
int distance(Point firstPoint, Point secondPoint) {
	return sqrt(pow((secondPoint.a - firstPoint.a), 2) + pow((secondPoint.b - firstPoint.b), 2)) + 0.5;
}
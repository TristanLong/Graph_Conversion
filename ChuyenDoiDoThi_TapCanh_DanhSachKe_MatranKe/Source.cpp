#include "iostream"
#include "fstream"
#include "vector"
using namespace std;
const int MAX = 20;

struct matrix {
	int adjMatrix[MAX][MAX];
	int vertices;
};

void readFile(matrix& adjacencyMatrix, ifstream& FileName) {
	FileName >> adjacencyMatrix.vertices;
	for (int i = 0; i < adjacencyMatrix.vertices; i++) {
		for (int j = 0; j < adjacencyMatrix.vertices; j++) {
			FileName >> adjacencyMatrix.adjMatrix[i][j];
		}
	}
	FileName.close();
}

void outputMatrix(matrix adjacencyMatrix) {
	cout << "\nADJACENCY MATRIX: " << endl;
	for (int i = 0; i < adjacencyMatrix.vertices; i++) {
		for (int j = 0; j < adjacencyMatrix.vertices; j++) {
			cout << adjacencyMatrix.adjMatrix[i][j] << " ";
		}
		cout << endl;
	}
}

// Ma trận kề sang tập cạnh
void matrixToEdge(matrix adjacencyMatrix, vector<pair<int,int>>& edge) {
	for (int i = 0; i < adjacencyMatrix.vertices; i++) {
		for (int j = 0; j < adjacencyMatrix.vertices; j++) {
			if (adjacencyMatrix.adjMatrix[i][j] == 1 && i < j)
				edge.push_back({ i,j });
		}
	}

	cout << "\nEDGE: ";
	for (auto it : edge) {
		cout << "(" << it.first << "," << it.second << ") ";
	}
}

// Ma trận kề sang danh sách kề 
void matrixToList(matrix adjacencyMatrix, vector<int> adjacencyList[]) {
	for (int i = 0; i < adjacencyMatrix.vertices; i++) {
		for (int j = 0; j < adjacencyMatrix.vertices; j++) {
			if (adjacencyMatrix.adjMatrix[i][j] == 1)
				adjacencyList[i].push_back(j);
		}
	}

	cout << "\nADJACENCY LIST: " << endl;
	for (int i = 0; i < adjacencyMatrix.vertices; i++) {
		cout << "Vertex " << i << ": ";
		for (int vertex : adjacencyList[i]) {
			cout << vertex << " ";
		}
		cout << endl;
	}
}

// Tập cạnh sang ma trận kề 
void edgeToMatrix(int vertices,vector < pair<int, int>> edge, matrix& adjacencyMatrix) {
	adjacencyMatrix.vertices = vertices;
	for (int i = 0; i < adjacencyMatrix.vertices; i++) {
		for (int j = 0; j < adjacencyMatrix.vertices; j++) {
			adjacencyMatrix.adjMatrix[i][j] = 0; // khởi tạo ma trận 0 
		}
	}

	// Gán giá trị cho cạnh tương ứng 
	for (auto it : edge) {
		adjacencyMatrix.adjMatrix[it.first][it.second] = adjacencyMatrix.adjMatrix[it.second][it.first]= 1;
	}

	outputMatrix(adjacencyMatrix);
}

// Tập cạnh sang danh sách kề 
void edgeToList(int vertices, vector<pair<int, int>> edge, vector<int> adjacencyList[]) {
	for (auto it : edge) {
		adjacencyList[it.first].push_back(it.second);
		adjacencyList[it.second].push_back(it.first);
	}
	
	cout << "ADJACENCY LIST: " << endl;
	for (int i = 0; i < vertices; i++) {
		cout << "Vertex " << i << ": ";
		for (auto it : adjacencyList[i]) {
			cout << it << " ";
		}
		cout << endl;
	}
}

// Danh sách kề sang ma trận kề 
void listToMatrix(vector<int> adjacencyList[], int vertices, matrix& adjacencyMatrix) {
	adjacencyMatrix.vertices = vertices;
	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			adjacencyMatrix.adjMatrix[i][j] = 0; // Khởi tạo ma trận kề ban đầu
		}
		for (int vertex : adjacencyList[i]) {
			adjacencyMatrix.adjMatrix[i][vertex] = 1; // Đánh dấu các cạnh trong ma trận
		}
	}

	outputMatrix(adjacencyMatrix); 
}

// Danh sách kề sang tập cạnh 
void listToEdge(vector<int> adjacencyList[], int vertices, vector<pair<int, int>>& edge) {
	for (int i = 0; i < vertices; ++i) {
		for (int j : adjacencyList[i]) {
			if (i < j) { // Chỉ thêm cạnh một lần duy nhất vì đồ thị vô hướng 
				edge.push_back({ i, j });
			}
		}
	}

	cout << "\nEDGE: ";
	for (auto it : edge) {
		cout << "(" << it.first << "," << it.second << ") ";
	}
}


int main() {
	// Thao tác trên đồ thị VÔ HƯỚNG 
	cout << "=====THIS IS UNDIRECTED GRAPH=====" << endl;

	matrix adjacencyMatrix;
	ifstream inFile("Text.txt");
	readFile(adjacencyMatrix, inFile);
	outputMatrix(adjacencyMatrix);

	int vertices = adjacencyMatrix.vertices;

	vector<pair<int, int>> edge;
	cout << "\nADJACENCY MATRIX TO EDGE: ";
	matrixToEdge(adjacencyMatrix, edge);

	vector<int> adjacencyList[MAX];
	cout << "\n\nADJACENCY MATRIX TO ADJACENCY LIST: ";
	matrixToList(adjacencyMatrix, adjacencyList);

	matrix newAdjacencyMatrix;
	cout << "\nEDGE TO ADJACENCY MATRIX: ";
	edgeToMatrix(vertices, edge, newAdjacencyMatrix);

	vector<int> newAdjacencyList[MAX];
	cout << "\nEDGE TO ADJACENCY LIST: " << endl;
	edgeToList(vertices, edge, newAdjacencyList);

	matrix newAdjacencyMatrix2;
	cout << "\nADJACENCY LIST TO ADJACENCY MATRIX: ";
	listToMatrix(adjacencyList, vertices, newAdjacencyMatrix2);

	vector<pair<int, int>> newEdge;
	cout << "\nADJACENCY LIST TO EDGE: ";
	listToEdge(adjacencyList, vertices, newEdge);
}

/*													
ADJACENCY MATRIX:
  A B C D E F G
A 0 1 0 1 0 0 0
B 1 0 1 1 1 0 0
C 0 1 0 0 1 0 0
D 1 1 0 0 1 1 0
E 0 1 1 1 0 1 1
F 0 0 0 1 1 0 1
G 0 0 0 0 1 1 0

ADJACENCY LIST:
Vertex 0: 1 3
Vertex 1: 0 2 3 4
Vertex 2: 1 4
Vertex 3: 0 1 4 5
Vertex 4: 1 2 3 5 6
Vertex 5: 3 4 6
Vertex 6: 4 5			

EDGE: (0,1) (0,3) (1,2) (1,3) (1,4) (2,4) (3,4) (3,5) (4,5) (4,6) (5,6)

														A			  B
														|\			 /|				  
														| \			/ |				  
														|  \	   /  |				  
														|   \	  /   |				 
														|    \	 /    |				 
														|     \ /     |				  
														|	   C      |				  
														|     / \     |
														|    /   \    |					
														|   /     \   |
														|  /       \  |
														| /         \ |
														|/           \|	
														D-------------E
														 \			 /|
														  \			/ |
														   \	   /  |
															\	  /   |
															 \	 /    |
															  \ /     |
															   F      |
																\     |			
																 \    |			
																  \   |
																   \  |
																	\ |
																	 \|
																	  G
*/
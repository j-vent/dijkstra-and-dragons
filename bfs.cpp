/**
* Implements BFS so the dragon can find shortest path to the knight.
**/

#include <queue>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <list>

using namespace std;

int row_size = 2;
int col_size = 2;
// stores current location on the grid
struct Coordinate {
	int x;
	int y;
	bool operator==(const Coordinate &other) const{
	  	return x==other.x && y==other.y; 
	}
	bool operator!=(const Coordinate &other) const{
	  	return x!=other.x || y!=other.y; 
	}
	

};

namespace std{
	template<>
	struct hash<Coordinate>{
			std::size_t operator()(const Coordinate &obj) const{
			
				using std:: size_t;
				using std::hash;

				// use the built-in hash function for int and bit shift left by 1 
				return ((hash<int>()(obj.x) << 1) ^(hash<int>()(obj.y) << 1))  ;
			}
	};
	
}

struct queueNode{
	Coordinate coordinates;
	int dist; // distance from dragon 
};

bool isValid(int row, int col){
	return(row>=0) && (row < 4) && (col>=0) && (col< 4);
}
// coords of cells surrounding dragon left, down, up, right
int adjrow[] = {-1,0,0,1}; 
int adjcol[] = {0,-1,1,0};

// map needs to be a shared var
// is map size static? if so, okay to hardcode
void BFS(int map[][4], Coordinate dragon, Coordinate knight, unordered_map<Coordinate,Coordinate>& searchTree){
	//unordered_map<, int> searchTree; // map each vertex to its predecessor and stores the path traversed
	bool visited[4][4];

	visited[dragon.x][dragon.y] = true;

	Coordinate path[4][4];
	int pathcounter = 0;

	queue<queueNode> q;
	queueNode startCell = {dragon, 0};
	q.push(startCell);

	
	while(!q.empty()){
		queueNode curr = q.front();
    	Coordinate currCoord = curr.coordinates;

    	// found 
    	cout << "curr x " << currCoord.x << " curr y " << currCoord.y << endl; 

    	if(currCoord.x == knight.x && currCoord.y == knight.y){
    		cout << "found " << endl;
    		return;
    	}
    	q.pop(); // dequeue
    	for(int i =0; i < 4; i++){
    		//cout << "checking adj cells " <<endl;
    		int row = currCoord.x + adjrow[i];
    		int col = currCoord.y + adjcol[i];
    		if(!visited[row][col] && isValid(row,col)) // !isBlock
    		{
    			// mark as visited
    			visited[row][col] = true;
    			// enqueue 
    			queueNode adjcell = {{row,col}, curr.dist+1};
    			q.push(adjcell);

    			// add to path
    			searchTree[{row,col}]=currCoord; // new points maps to point it came from 
    			


    		}
    	}
    	
	}


}

int main(){
	int map[4][4] = {{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}};
	Coordinate dragon = {0,0};
	Coordinate knight = {1,3};

	unordered_map<Coordinate,Coordinate> searchTree;
	BFS(map, dragon,knight, searchTree);
	
	list<Coordinate> path;
  if (searchTree.find(knight) == searchTree.end()) {
    cout << "Vertex " << (knight.x) << "," << (knight.y) << " not reachable from " << (dragon.x) << "," << (dragon.y) << endl;
  }
  else {
    Coordinate stepping = knight;
    while (stepping != dragon) {
      path.push_front(stepping);
      stepping = searchTree[stepping]; // crawl up the search tree one step
    }
    path.push_front(dragon);
    
    cout << "Path from dragon to knight" << ":";
    

    for(const Coordinate &coord: path){
    	cout << coord.x << " " << coord.y << endl;
    }
  }
	
	return 0;
}

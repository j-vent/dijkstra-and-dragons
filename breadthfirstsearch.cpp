/**
* Implements BFS so the dragon can find shortest path to the knight.
**/

#include "linked_list.h" // in place of queue

using namespace std;

// stores current location on the grid
struct Coordinate {
	int x;
	int y;
};


struct llNode{
	Coordinate coordinates;
	int dist; // distance from dragon 
};

bool isValid(int row, int col){
	return(row>=0) && (row < 5) && (col>=0) && (col< 7);
}
// coords of cells surrounding dragon left, down, up, right
int adjrow[] = {-1,0,0,1}; 
int adjcol[] = {0,-1,1,0};


Coordinate BFS(int map[][7], Coordinate dragon, Coordinate knight){ 
	bool visited[5][7];

	visited[dragon.x][dragon.y] = true;

	Coordinate path[5][7];
	int pathcounter = 0;

	LinkedList<llNode> ll;
	llNode startCell = {dragon, 0};
	ll.insertFront(startCell);

	int row, col;
	while(ll.size() > 0){
		llNode curr = ll.getFirst()->item; // get first cell
    	Coordinate currCoord = curr.coordinates;
    
    	if(currCoord.x == knight.x && currCoord.y == knight.y){
    		int r = currCoord.x;
    		int c = currCoord.y;

    		// back track to find the next step to take, like a searchtree
    		while(path[r][c].x !=dragon.x || path[r][c].y !=dragon.y){
    			r= path[r][c].x;
    			c = path[r][c].y;
    			if(!isValid(r,c)){
    				return {-1,-1}; // dragon cannot move
    			}
    		}
    		return {r, c}; // return coordinate for next move
    	}
    	ll.removeFront(); // dequeue
    	for(int i =0; i < 4; i++){
    		row = currCoord.x + adjrow[i];
    		col = currCoord.y + adjcol[i];

    		if(!visited[row][col] && isValid(row,col) && map[row][col]==1 || map[row][col]==2) 
    		{
    			// mark as visited
    			visited[row][col] = true;
    			// enqueue 
    			llNode adjcell = {{row,col}, curr.dist+1};
    			ll.insertBack(adjcell);

    			// add to path
    			path[row][col] = currCoord; // new points maps to point it came from 

    		}
    	}
    	
	}

	return {-1,-1}; // dragon cannot move
}

int main(){
	// hardcoded values, use map for proper level, change dragon and knight to objects
	int map[5][7] = {{1,1,0,0,1,1,1},{1,1,2,0,1,1,0},{1,1,1,1,0,0,0},{1,1,1,1,0,0,1},{1,1,0,1,1,1,3}}; 
	Coordinate dragon = {4,6};
	Coordinate knight = {1,2};

	Coordinate next_coord = BFS(map, dragon,knight);
	return 0;
}
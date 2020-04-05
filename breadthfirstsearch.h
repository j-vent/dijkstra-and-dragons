#ifndef __BREADTHFIRSTSEARCH_H
#define __BREADTHFIRSTSEARCH_H


// TODO: make Coordinate struct public type but where? 

struct Coordinate{ 
	int x;
	int y;
};

enum direction{up,down,left,right,center}; // move back to consts.h

Coordinate BFS(int map[][7], Coordinate dragon, Coordinate knight);


#endif
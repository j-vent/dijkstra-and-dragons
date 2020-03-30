#ifndef dragon_h
#define dragon_h

#include "consts_and_types.h"
class Dragon{
	public:
		//enum direction{up,down,left,right,center};
		Dragon(int x, int y, direction dir){// has location on grid, direction
			this->x = x;
			this->y = y;
			this->dir = dir;

		} 
		

		~Dragon(){}; // deconstructor

		//TODO: move to private, use getters and setters
		int x;
		int y;
		direction dir;

		void followKnight(); // use BFS to catch Knight

		bool isCaptured(); // if dragon as caught the knight (same cell on grid)
	private:
		 
		

};
#endif
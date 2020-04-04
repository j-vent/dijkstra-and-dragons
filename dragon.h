#ifndef DRAGON_H
#define DRAGON_H

#include "player.h"
#include "breadthfirstsearch.h"

class Dragon: public Player
{	//using Player::Player;
	public:
		Dragon(){};
		
		Dragon(int x, int y):Player(x,y){};
		
		~Dragon(){}; // deconstructor

		bool getHasKnight();

		void setHasKnight(bool v);
	
	private:
		 bool hasKnight; // if dragon as caught the knight (same cell on grid)
		

};
#endif
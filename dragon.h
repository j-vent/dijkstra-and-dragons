#ifndef dragon_h
#define dragon_h

#include "player.h"
#include "breadthfirstsearch.h"

class Dragon: public Player
{	//using Player::Player;
	public:
		Dragon(int x, int y):Player(x,y){};
		
		~Dragon(){}; // deconstructor

		bool getHasKnight();

		void setHasKnight(bool v);
	
	private:
		 bool hasKnight; // if dragon as caught the knight (same cell on grid)
		

};
#endif
#ifndef __PLAYER_H
#define __PLAYER_H
#include <Arduino.h>
#include "consts_and_types.h"
//extern Coordinate coord;
struct Coordinate{ 
	int x;
	int y;
};

class Player{
	public:
		Player(){};
		~Player(){}; 

		void move();

		void draw();

		/** // not sure if getters/setters needed 
		void getx();

		void setx();
		**/ 


	protected: // accessible by child classes
		Coordinate coord;
};

#endif
#include "dragon.h"
/**
Dragon::Dragon(int x, int y)
{
	this->x = x;
	this->y = y;
}
**/
void Dragon::setHasKnight(bool val){
	hasKnight = val;
}

bool Dragon::getHasKnight(){
	return hasKnight;
}

// add movement here
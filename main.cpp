#include "dragon.h"
#include "consts_and_types.h"

MCUFRIEND_kbv tft;


using namespace std;

//extern shared_vars shared;

// 0 is knight (player), 1 is dragon (computer)
int playerMode = 0; 


direction dir = center; 
Dragon dragon(0,0,dir); // initialize dragon 

void init_map(int level){
	
	tft.fillScreen(TFT_BLACK);
	
	// maps are represented as such: 0 for block, 1 for path, 2 for knight, 3 for dragon, 4 for gate, 5 for key
	int level1 [num_row][num_col] = {{2,1,1,0,0,1,1},{1,0,1,1,0,1,0},{1,0,0,1,1,3,0},{1,1,1,0,1,1,1},{1,1,1,1,1,4,0}};
	int xstep = display_width/num_col;
	int ystep = display_height/num_row;
	uint16_t xstart=0;
	uint16_t ystart = 0;
	uint16_t xnext = 0; 
	uint16_t ynext = display_height/num_row;
	uint16_t colour;
	int cell;
	for(int i=0; i <num_row; i++){
			for(int j=0; j <num_col; j++){
				//shared.level_map[i][j]= level1[i][j];
				//cell = shared.level_map[i][j];
				level_map[i][j]= level1[i][j];
				cell = level_map[i][j];
				switch(cell){
					case 0: // block
						colour = tft.color565(0x99, 0x4C, 0x00);
						break;
					case 1: // path
						colour = TFT_WHITE;
						break;
					case 2: // knight
						colour = tft.color565(0xA0, 0xA0, 0xA0);
						break;
					case 3: // dragon
						colour = tft.color565(0xFF, 0x00, 0x00);
						dragon.x = i;
						dragon.y = j;
						dragon.dir = center;
						//dragon((int)i,(int)j,center);
						//int dragonx = i;
						//int dragony = j;
						break;
					case 4: // gate
						colour = tft.color565(0x00, 0x66, 0x33);
						break;
					case 5: // key
						colour = tft.color565(0xE5, 0xD8, 0x22);
						break;
				}

				xnext = xstart+display_width/num_col;
				
				/**
				Serial.println("cell ");
				Serial.println(level_map[i][j]);
				Serial.print(" xstart ");
				Serial.println(xstart);
				Serial.print(" ystart ");
				Serial.println(ystart);
				/**
				Serial.print(" xnext ");
				Serial.println(xnext);
				Serial.print(" ynext ");
				Serial.println(ynext);
				**/

				//tft.fillRect(xstart,ystart,xnext,ynext,colour);
				tft.fillRect(xstart,ystart,xstep,ystep,colour);
				xstart=xnext;
				
				if(xstart + xstep > display_width){ // new row
					Serial.println("new row ");
					xstart = 0; 
					ystart = ynext;
					ynext = ystart+display_height/num_row;
					
				}
				
			}	
	}
	// message bar
	//tft.fillRect(0,display_height,tft_width,tft_height, TFT_BLACK);
	tft.fillRect(0,display_height,tft_width,24, TFT_BLACK);

}
/** converts coordinates on map into position on LCD display**/
/**
void moveDragon(){
	// top left corner of dragon cell 
} 
**/

// TODO: Make so that you don't have to hold the position for a long time
direction joystick() {
  delay(100);
  int xVal = analogRead(JOY_HORIZ);
  int yVal = analogRead(JOY_VERT);
  int buttonVal = digitalRead(JOY_SEL);

  bool stickPushed = false;
  //direction dir = 0;

  if (xVal > JOY_CENTRE + JOY_DEADZONE) {
  	Serial.println("L");
   	dir = left;
    stickPushed = true;
  }
  else if (xVal < JOY_CENTRE - JOY_DEADZONE) {
  	Serial.println("R");
    dir = right;
    stickPushed = true;
  }

  if (yVal < JOY_CENTRE - JOY_DEADZONE) {
  	Serial.println("U");
    dir = up;
    stickPushed = true;
  }
  else if (yVal > JOY_CENTRE + JOY_DEADZONE) {
  	Serial.println("D");
    dir = down;
    stickPushed = true;
  }

  /**  if (abs(xVal - JOY_CENTRE) <= JOY_DEADZONE &&
      abs(yVal - JOY_CENTRE) <= JOY_DEADZONE) {
    Serial.print("centre ");
    }*/
  if (!stickPushed) {
    //Serial.print("centre ");
  }

  if (buttonVal == LOW) {
    //Serial.print("pushed ");
  }
  Serial.println("dir");
  Serial.println(dir);
  return dir;

  //if(dir == up){}
}

void moveDragon(){
	Serial.println("Move dragon ");
	delay(100);
	direction dragonDir = joystick();
	Serial.println("dragon dir");
	Serial.println(dragonDir);
	// hardcoded
	int dragonx = 272;
	int dragony = 118;

	int dragonnextx = dragonx;
	int dragonnexty = dragony;
	// TO DO: make constraints
	int xstep = display_width/num_col;
	int ystep = display_height/num_row;
	switch(dragonDir){
		case up:
			Serial.println("up");	
			dragonnextx = dragonx;
			dragonnexty = dragony-ystep;
			//ystep = ystep *-1;
			break;
		case down:
			Serial.println("down");
			dragonnextx = dragonx;
			dragonnexty = dragony+ display_height/num_row;
			break;
		case right:
			Serial.println("right");
			dragonnexty = dragony;
			dragonnextx = dragonx+ display_width/num_col;
			break;
		case left:
			Serial.println("left");
			dragonnexty = dragony;
			dragonnextx = dragonx- display_width/num_col;
			//xstep = xstep*-1;
			break;
	}
	Serial.println("nextx ");
	Serial.println(dragonnextx);
	Serial.println("nexty");
	Serial.println(dragonnexty);

	Serial.println("xstep");
	Serial.println(xstep);
	Serial.println("ystep");
	Serial.println(ystep);
	// TODO: update dragon's position in grid and change its old position to path 

	// TODO: Fix fill (filling the wrong way (not top->bottom left-> right from the top left corner even if
	// starting coordinates are right 
	// TODO: Redraw over old spot
	tft.fillRect(dragonnextx,dragonnexty,
		xstep,ystep,TFT_MAGENTA); // draw new rect tft.color565(0xFF, 0x00, 0x00)
	//tft.fillRect(dragonx,dragony, 
		//xstep,ystep, TFT_WHITE); // redraw old block
}
void setup() {
    init();
    pinMode(JOY_SEL, INPUT_PULLUP);
    Serial.begin(9600);

    uint16_t ID = tft.readID();
    tft.begin(ID);
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);

    // clear to yellow
    tft.fillScreen(tft.color565(0xff, 0xff, 0x00));

    //shared.level_map;
}


int main(){
	setup();
	int level = 1;
	
	init_map(level);
	moveDragon();
	Serial.end();
	return 0;
}
#include "consts_and_types.h"

MCUFRIEND_kbv tft;

using namespace std;

int playerMode = 0; 

shared_vars shared;

// in level variables
// TODO: initialize these in a function
int keyx = 0;
int keyy = 0;
int gatex = 0;
int gatey = 0;
int numKeys = 0;
bool canOpenGate = false;

bool running = true;
direction dir = center; 
direction olddir = center;

void knight_turn_message(){
	tft.setCursor(0,display_height);
	tft.setTextColor(TFT_WHITE);
	tft.setTextSize(2);
	// TODO: Have random generated message from a list of messages 
	tft.print("Your turn, knight! Best of luck! ");

}

void dragon_turn_message(){
	tft.setCursor(0,display_height);
	tft.setTextColor(TFT_RED);
	tft.setTextSize(2);
	// TODO: Have random generated message from a list of messages 
	tft.print("Tis the great dragon's turn! ");

}
void lost_screen(){
	tft.setCursor(0,display_height/2);
	tft.setTextColor(TFT_RED);
	tft.setTextSize(4);
	tft.setTextWrap(true);
	tft.fillScreen(TFT_BLACK);
	tft.print("The knight has been captured!");
	// reload prev level

}


void init_map(int level){
	
	tft.fillScreen(TFT_BLACK);
	
	// maps are represented as such: 0 for block, 1 for path, 2 for knight, 3 for dragon, 4 for gate, 5 for key
	//dragon.setx(1);
	//char ans = dragon.getx();
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
				shared.level_map[i][j]= level1[i][j];
				cell = shared.level_map[i][j];
				switch(cell){
					case 0: // block
						//colour = tft.color565(0x99, 0x4C, 0x00);
						colour = TFT_BLACK;
						break;
					case 1: // path
						colour = TFT_WHITE;
						break;
					case 2: // knight
						colour = tft.color565(0xA0, 0xA0, 0xA0);
						shared.knight.setx(i);
						shared.knight.sety(j);
						break;
					case 3: // dragon
						colour = tft.color565(0xFF, 0x00, 0x00);
						shared.dragon.setx(i);
						shared.dragon.sety(j);
						
						break;
					case 4: // gate
						colour = tft.color565(0x00, 0x66, 0x33);
						gatex = i;
						gatey = j;
						break;
					case 5: // key
						colour = tft.color565(0xE5, 0xD8, 0x22);
						keyx = i;
						keyy = j;
						break;
				}

				xnext = xstart+display_width/num_col;
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
}
/**
* bool levelInit: true if a new level is being initialized
**/
void drawMap(bool levelInit) {
    int cursorx=0;
    int cursory=0;
    int cell;
    uint16_t colour;


    for (int i=0; i<5; i++) {
        cursory=0;
        for (int j=0; j<7; j++) {
        	if(levelInit){
        		shared.level_map[i][j]= level1[i][j]; // load level map into shared map 
        		// Serial.println(shared.level_map[i][j]);
        	}
        	
            cell = shared.level_map[i][j];
            //Serial.print(cell);
            
            switch(cell){
					case 0: // block
						//colour = tft.color565(0x99, 0x4C, 0x00);
						colour = TFT_BLACK;
						break;
					case 1: // path
						colour = TFT_WHITE;
						break;
					case 2: // knight
						//colour = tft.color565(0xA0, 0xA0, 0xA0);
						colour = TFT_BLUE;
						shared.knight.setx(i);
						shared.knight.sety(j);
						break;
					case 3: // dragon
						//colour = tft.color565(0xFF, 0x00, 0x00);
						colour = TFT_RED;
						shared.dragon.setx(i);
						shared.dragon.sety(j);
						
						break;
					case 4: // gate
						colour = tft.color565(0x00, 0x66, 0x33);
						gatex = i;
						gatey = j;
						break;
					case 5: // key
						colour = tft.color565(0xE5, 0xD8, 0x22);
						keyx = i;
						keyy = j;
						break;
			}
			tft.fillRect(cursory,cursorx,64,64,colour);
			/**
			Serial.print(" ");
            Serial.print(i);
            Serial.print(" ");
            Serial.println(j);
            **/

            cursory+=64;

        }
        cursorx+=64;
    }

    //tft.fillRect(knightx*64,knighty*64,64,64,TFT_BLUE);
    // tft.fillRect(dragonx*64,dragony*64,64,64,TFT_RED);
}

void fillPreview(int level[5][7], direction olddir, int knightx, int knighty) {



    if (olddir == left  && level[knighty][knightx-1]==0) {
        tft.fillRect((knightx-1)*64,knighty*64,64,64,TFT_BLACK);
    }
    else if (olddir == left  && level[knighty][knightx-1]==1) {
        tft.fillRect((knightx-1)*64,knighty*64,64,64,TFT_WHITE);
    }
    else if (olddir == right  && level[knighty][knightx+1]==1) {
        tft.fillRect((knightx+1)*64,knighty*64,64,64,TFT_WHITE);
    }
    else if (olddir == right  && level[knighty][knightx+1]==0) {
        tft.fillRect((knightx+1)*64,knighty*64,64,64,TFT_BLACK);
    }
    else if (olddir == up  && level[knighty-1][knightx]==1) {
        tft.fillRect(knightx*64,(knighty-1)*64,64,64,TFT_WHITE);
    }
    else if (olddir == up  && level[knighty-1][knightx]==0) {
        tft.fillRect(knightx*64,(knighty-1)*64,64,64,TFT_BLACK);
    }
    else if (olddir == down  && level[knighty+1][knightx]==1) {
        tft.fillRect(knightx*64,(knighty+1)*64,64,64,TFT_WHITE);
    }
    else if (olddir == down  && level[knighty+1][knightx]==0) {
        tft.fillRect(knightx*64,(knighty+1)*64,64,64,TFT_BLACK);
    }
}

void pushBlock(int level[5][7], direction dir, int playerx, int playery) {
    Serial.print("Pushblock ");
    Serial.print(playerx);
    Serial.println(playery);
    if (dir == left) {
        level[playerx][playery-1] = 0;
        level[playerx][playery] = 1;
    }
    else if (dir == right) {
        level[playerx][playery+1] = 0;
        level[playerx][playery] = 1;
    }
    else if (dir == up) {
        level[playerx-1][playery] = 0;
        level[playerx][playery] = 1;
    }
    else if (dir == down) {
        level[playerx+1][playery] = 0;
        level[playerx][playery] = 1;
    }
}

void knightTurn(int level[5][7], int& knightx, int& knighty, int dragonx, int dragony) {

    bool stickPushed = false;

    

    while(!stickPushed || dir == center) {
        int xVal = analogRead(JOY_HORIZ);
          int yVal = analogRead(JOY_VERT);
          int buttonVal = digitalRead(JOY_SEL);

          if (xVal > JOY_CENTRE + JOY_DEADZONE) {

              if(knightx > 0 && level[knighty][knightx-1]==1) {
                  tft.fillRect((knightx-1)*64,knighty*64,64,64,TFT_YELLOW);
                  olddir = dir;
                   dir = left;
              }
              else if (knightx > 1 && level[knighty][knightx-1]==0 && level[knighty][knightx-2]==1) {
                  tft.fillRect((knightx-1)*64,knighty*64,64,64,TFT_GREEN);
                  olddir = dir;
                   dir = left;
              }
          }
          else if (xVal < JOY_CENTRE - JOY_DEADZONE) {

              if(knightx < 6 && level[knighty][knightx+1]==1) {
                  tft.fillRect((knightx+1)*64,knighty*64,64,64,TFT_YELLOW);
                  olddir = dir;
                dir = right;
              }
              
              else if (knightx < 5 && level[knighty][knightx+1]==0 && level[knighty][knightx+2]==1) {
                  tft.fillRect((knightx+1)*64,knighty*64,64,64,TFT_GREEN);
                  olddir = dir;
                dir = right;
              }
          }
          else if (yVal < JOY_CENTRE - JOY_DEADZONE) {

              if(knighty > 0 && level[knighty-1][knightx]==1) {
                  tft.fillRect(knightx*64,(knighty-1)*64,64,64,TFT_YELLOW);
                  olddir = dir;
                dir = up;
              }
              else if (knighty > 1 && level[knighty-1][knightx]==0 && level[knighty-2][knightx]==1) {
              	 tft.fillRect(knightx*64,(knighty-1)*64,64,64,TFT_GREEN);
                  olddir = dir;
                dir = up;
              }    
          }
          else if (yVal > JOY_CENTRE + JOY_DEADZONE) {

              if(knighty < 4 && level[knighty+1][knightx]==1) {
                  tft.fillRect(knightx*64,(knighty+1)*64,64,64,TFT_YELLOW);
                  olddir = dir;
                dir = down;
              }
              else if (knighty < 3 && level[knighty+1][knightx]==0 && level[knighty+2][knightx]==1) {
                  tft.fillRect(knightx*64,(knighty+1)*64,64,64,TFT_GREEN);
                  olddir = dir;
                dir = down;
              }
          }

          
          if (olddir!=dir) {
               fillPreview(level, olddir, knightx, knighty);
           }

          if (buttonVal==0 && (yVal <= JOY_CENTRE + JOY_DEADZONE) && (yVal >= JOY_CENTRE - JOY_DEADZONE) && (xVal >= JOY_CENTRE - JOY_DEADZONE) && (xVal <= JOY_CENTRE + JOY_DEADZONE)){
              stickPushed = true;
          }
    }

    if (dir==left) {
        knightx=knightx-1;
    }
    else if (dir==right) {
        knightx=knightx+1;
    }
    else if (dir==up) {
        knighty=knighty-1;
    }
    else if (dir == down) {
        knighty= knighty+1;
    }

    if (level[knighty][knightx]==0) {
        pushBlock(level, dir, knightx, knighty);
    }

    olddir = center;
    dir = center;

}

bool gameLoop(){
	if(playerMode==0){
		tft.fillRect(0,display_height,tft_width,24, TFT_BLACK);
		// knight_turn_message();
		playerMode = 1;

	}
	else if(playerMode==1){
		Serial.println("dragon turn");

		Coordinate dragdir = {shared.dragon.getx(), shared.dragon.gety()};
		Coordinate knightdir = {shared.knight.getx(), shared.knight.gety()};
		
		if(shared.knight.getx() == shared.dragon.getx() && shared.knight.gety() == shared.dragon.gety()){
			Serial.println("caught");
			lost_screen();
			running = false;
			
		}
		Coordinate nextmove = BFS(shared.level_map,dragdir,knightdir);
		Serial.print("move x ");
		Serial.println(nextmove.x);
		Serial.print("move y ");
		Serial.println(nextmove.y);
		if(nextmove.x == -1 || nextmove.y ==-1){
			Serial.println("invalid move");
		}
		
		else{
			shared.level_map[dragdir.x][dragdir.y] = 1;
			shared.level_map[nextmove.x][nextmove.y] = 3; 
			drawMap(false);

		}
		delay(50);
	}
	return running;
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
   
	shared.dragon.setx(0);
	shared.dragon.sety(0);

	shared.knight.setx(0);
	shared.knight.sety(0);

	//shared.level_map[5][7]={{0}};
   	
}


int main(){
	setup();
	drawMap(true);
	playerMode = 1;
	while(running){
		gameLoop();
		Serial.println("looping");
	};
	Serial.println("done");
	Serial.end();
	return 0;
}
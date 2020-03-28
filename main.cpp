//#include <iostream>
//#include "fstream.h"


#include <Arduino.h>
#include <MCUFRIEND_kbv.h>
#include <SPI.h>
#include <SD.h>
#include <TouchScreen.h>
#include <Adafruit_GFX.h>

MCUFRIEND_kbv tft;

//include <iostream>
using namespace std;

/**dimension constants**/

// tft display dimensions
const int16_t tft_width = 480;
const int16_t tft_height = 320;


// message box dimensions
const int16_t msg_width = tft_width;
const int16_t msg_height = 24;

// display window size for the game map
const int16_t display_width = tft_width;
const int16_t display_height = tft_height - msg_height;

/**
* Read in the map layout for level
**/
const int num_row = 5;
const int num_col = 7; 
int level_map[num_row][num_col] = {0};

void init_map(int level){
	
	tft.fillScreen(TFT_BLACK);
	S

	// maps are represented as such: 0 for block, 1 for path, 2 for knight, 3 for dragon, 4 for gate, 5 for key
	int level1 [num_row][num_col] = {{2,1,1,0,0,1,1},{1,0,1,1,0,1,0},{1,0,0,1,1,3,0},{1,1,1,0,1,1,1},{1,1,1,1,1,4,0}};

	uint16_t xstart=0;
	uint16_t ystart = 0;
	uint16_t xnext = 0; 
	uint16_t ynext = display_height/num_row;
	uint16_t colour;

	for(int i=0; i <num_row; i++){
			for(int j=0; j <num_col; j++){
				level_map[i][j]= level1[i][j];
				
				if(level_map[i][j] == 0){
					colour = TFT_GREEN;
				}
				else if(level_map[i][j] == 1){
					colour = TFT_WHITE;
				}
				else if(level_map[i][j] == 2){
					colour = TFT_BLUE;
				}
				else if(level_map[i][j] == 3){
					colour = TFT_RED;
				}
				else if(level_map[i][j] == 4){
					colour = TFT_YELLOW;
				}
				
				xnext = xstart+display_width/num_col;
				
				/**
				Serial.println("cell ");
				Serial.println(level_map[i][j]);
				Serial.print(" xstart ");
				Serial.println(xstart);
				Serial.print(" ystart ");
				Serial.println(ystart);
				Serial.print(" xnext ");
				Serial.println(xnext);
				Serial.print(" ynext ");
				Serial.println(ynext);
				**/

				tft.fillRect(xstart,ystart,xnext,ynext,colour);
				xstart=xnext;
				
				if(xstart + display_width/num_col > display_width){ // new row
					Serial.println("new row ");
					xstart = 0; 
					ystart = ynext;
					ynext = ystart+display_height/num_row;
					
				}
				
			}	
	}

}
void setup() {
    init();

    Serial.begin(9600);

    uint16_t ID = tft.readID();
    tft.begin(ID);
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);

    // clear to yellow
    tft.fillScreen(tft.color565(0xff, 0xff, 0x00));
}


int main(){
	setup();
	int level = 1;
	
	init_map(level);
	Serial.end();
	return 0;
}
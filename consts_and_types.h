#ifndef __CONSTS_AND_TYPES_H
#define __CONSTS_AND_TYPES_H

#include <Arduino.h>
#include <MCUFRIEND_kbv.h>
#include <SPI.h>
#include <TouchScreen.h>
#include <Adafruit_GFX.h>

/** joystick constants **/
#define JOY_VERT  A9 // should connect A9 to pin VRx
#define JOY_HORIZ A8 // should connect A8 to pin VRy
#define JOY_SEL   53
// digital pin high or low (1 or 0)
// analog is 0-1024(res)
#define JOY_CENTRE   512
#define JOY_DEADZONE  64

// #include "player.h"
#include "dragon.h"
#include "knight.h"
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

// TODO: figure out other vars to add to struct
//struct shared_vars{

// const int level_map[num_row][num_col]={{0}};
struct shared_vars{
	int level_map[5][7];
	// extern Knight knight; 
	Dragon dragon;
	Knight knight;
	// constructor for struct?
	int keysFound;




};
/**
// TODO: make level struct
struct levels{
	const int level1 [num_row][num_col] = {{1,1,1,1,1,1,1},{1,1,1,1,0,0,1},{0,0,1,0,0,0,1},{1,1,0,1,1,1,3},{1,1,1,1,1,2,1}};

};


**/
const int level1 [num_row][num_col] = {{2,1,1,0,0,1,1},{1,0,1,1,0,1,0},{1,0,0,1,1,3,0},{1,1,1,0,1,1,1},{1,1,1,1,1,4,0}};
const int level2 [num_row][num_col] = {{1,1,1,1,1,1,1},{1,1,1,1,0,0,1},{0,0,1,0,0,0,1},{1,1,0,1,1,1,3},{1,1,1,1,1,2,1}};
// int level_map[5][7];
enum direction{up,down,left,right,center}; // move back to consts.h

// TODO: Use these for the player class and subclasses
// defined in player
// struct Coordinate;

// levels:
//const int level1 [num_row][num_col] = 
// const int level1 [num_row][num_col] = {{2,1,1,0,0,1,1},{1,0,1,1,0,1,0},{1,0,0,1,1,3,0},{1,1,1,0,1,1,1},{7,7,7,7,7,7,7}};
// const int level1 [num_row][num_col] = {{0,2,1,0,0,3,1},{1,0,1,1,0,0,0},{1,0,0,1,1,0,0},{1,1,1,0,1,1,1},{1,1,1,1,1,0,0}};
//const int level1 [7][5] = {{0,1,1,1,1},{1,0,0,1,1},{1,1,0,1,1},{0,1,1,0,1},{0,0,1,1,1},{1,1,0,1,0},{1,0,0,1,0}};
// const int level1[5][7] = {{1,1,0;
// TODO: move constants for Ard setup here


#endif
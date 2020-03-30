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
	int level_map[num_row][num_col]={{0}};


enum direction{up,down,left,right,center};

// TODO: move constants for Ard setup here



#endif
#pragma once

#define SCREEN_WIDTH	800 //glutGet(GLUT_WINDOW_WIDTH)
#define SCREEN_HEIGHT	600 // glutGet(GLUT_WINDOW_HEIGHT)
#define SECONDS		270

#define mWidth		64
#define mHeight		64
#define mDepth		64

#define TILE_SIZE_X	10
#define TILE_SIZE_Y	10

#define TILE_WORLD_SIZE_X	TILE_SIZE_X * TILE_NO_X
#define TILE_WORLD_SIZE_Y	TILE_SIZE_Y * TILE_NO_Y

#define HAZE_MIN	50
#define HAZE_MAX	400

#define StartDay	1
#define DayTime		9			//How long an in-gam daye is in in-game hours
#define HourTime	3000		//How long an in-game hour is in milliseconds
#define noiseWidth	DayTime * 7

#define WinMoneyCondition	90
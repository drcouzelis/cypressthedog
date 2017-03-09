#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include "allegro.h"

#define TILE_SIZE  40
#define SCRN_X  640 //320
#define SCRN_Y  480 //200
#define COLOR_DEPTH 8
#define SECONDS  1000
#define TIMER  2
#define NUM_OF_TILES  256
#define NUM_OF_LEVELS  50

#define GAME_TICKER  100
#define MAX_TICKER  1000000000


typedef enum  {
   F, T
}  FLAG;

typedef enum  {
   L=-1, R=1, U=3, D=4
}  DIRECTION;

/*
typedef struct  {
   int power;
   int timer;
}  MOMENTUM;
*/


/*
typedef struct  {
   int pos;
   int timer;
}  POS;
*/

typedef struct  {
   BITMAP *bmp;
   int pos;
   int size;
   int time;
   int speed;
}  ANIM_SET;


typedef struct  {
   int id_color;
   int passable;
   BITMAP *bmp;
}  TILE;


typedef struct  {
   BITMAP *bmp;
   int cc_x;
   int change_x;
   int pos;
}  SCROLL;


typedef struct  {
   int number;
   int w;
   int h;
   BITMAP *far;     //the far background picture
   BITMAP *walk;    //the parts you walk on
   BITMAP *oo;      //the oo placement
   SCROLL ground1;  //parallax scrolling
   SCROLL ground2;
}  LEVEL;


typedef struct  {

   FLAG f_dashing;

   int h_momentum;
   int v_momentum;

   int x,y;  //positions

   ANIM_SET stand_anim;
   ANIM_SET run_anim;
   ANIM_SET jump_anim;
   ANIM_SET fall_anim;
   ANIM_SET dash_anim;
   ANIM_SET *curr_anim;
   BITMAP *sprite;

   int health;
   DIRECTION facing;

}  CONTROLLABLE_CHAR;


typedef struct  {

   int id_color;
   int health;
   DIRECTION facing;

   int x, y;

   FLAG f_knocked_down;

   int v_momentum;
   int h_momentum;

   ANIM_SET walk_anim;
   ANIM_SET knocked_down_anim;
   ANIM_SET *curr_anim;
   BITMAP *sprite;

}  OO_CEDAR_TROOP;






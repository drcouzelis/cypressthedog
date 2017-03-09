#include "datas.h"
#define MOVE_CONST  1


int pos_check_passable (int pos_x, int pos_y, int size_x, int size_y, DIRECTION dir);
int pos_passable_tile_check (int y_loc, int i, DIRECTION dir);
int pos_change (int *orig_x, int *orig_y, int change_x, int change_y);



extern TILE *tile_set[NUM_OF_TILES];
extern LEVEL *level_set[NUM_OF_LEVELS];
extern int level;

int pos_change (int *use_x, int *use_y, int change_x, int change_y)
{

   DIRECTION dir;
   int x=0,y=0;
   int orig_x, orig_y;
   
   //change_x*=2;
   //change_y*=2;

   orig_x = *use_x;
   orig_y = *use_y;

   if (!change_y)
   {
      if (change_x>0)  { dir = R; x=1; }
      else  { dir = L; x=-1; }
   }
   else
   {
      if (change_y>0)  { dir = D; y=1; }
      else  { dir = U; y=-1; }
   }

   while (*use_x != orig_x+change_x || *use_y != orig_y+change_y)
   {
      if (pos_check_passable (*use_x, *use_y, TILE_SIZE, TILE_SIZE, dir))
      {
         *use_x += x*MOVE_CONST;
         *use_y += y*MOVE_CONST;
      }
      else
      {
         //if (*use_y < 0)
            //*use_y = 0;
         return (0);
      }
   }

   //if (*use_y < 0)
      //*use_y = 0;

   return (1);

}


int pos_passable_tile_check (int y_loc, int i, DIRECTION dir)
{

   if (i == 0)
      return (1);
   if (tile_set[i]->passable == 0)
      return (0);
   if (tile_set[i]->passable == 1)
      return (1);
   if (tile_set[i]->passable == 2 && dir == D && y_loc%TILE_SIZE==0)
      return (0);
   else  return (1);

}


int pos_check_passable (int pos_x, int pos_y, int size_x, int size_y, DIRECTION dir)
{

   int i;
   int offset_x=1, offset_y=1;

   if (dir == R)
   {
      while (offset_y < size_y)
      {
         i = getpixel (level_set[level]->walk, (pos_x+1)/TILE_SIZE, (pos_y+offset_y)/TILE_SIZE);
         if (!pos_passable_tile_check (pos_y,i,dir))
            return (0);
         offset_y += 1;
      }
   }
   else if (dir == L)
   {
      while (offset_y < size_y)
      {
         i = getpixel (level_set[level]->walk, (pos_x-size_x-1)/TILE_SIZE, (pos_y+offset_y)/TILE_SIZE);
         if (!pos_passable_tile_check (pos_y,i,dir))
            return (0);
         offset_y += 1;
      }
   }
   else if (dir == U)
   {
      while (offset_x < size_x)
      {
         i = getpixel (level_set[level]->walk, (pos_x-size_x+offset_x)/TILE_SIZE, (pos_y-1)/TILE_SIZE);
         if (!pos_passable_tile_check (pos_y,i,dir))
            return (0);
         offset_x += 1;
      }
   }
   else
   {
      while (offset_x < size_x)
      {
         i = getpixel (level_set[level]->walk, (pos_x-size_x+offset_x)/TILE_SIZE, (pos_y+size_y+1)/TILE_SIZE);
         if (!pos_passable_tile_check (pos_y,i,dir))
            return (0);
         offset_x += 1;
      }
   }

   return (1);

}





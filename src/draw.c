#include "datas.h"


void draw_screen (void);
void draw_bgrounds (LEVEL *ptr, int cc_x);
void draw_walkground (LEVEL *ptr, int cc_x);
void draw_scrollground (SCROLL *ptr, int cc_x);
void anim_frame (ANIM_SET *ptr);


extern BITMAP *screen_buffer;
extern CONTROLLABLE_CHAR cypress;
extern TILE *tile_set[256];
extern LEVEL *level_set[20];
extern int level;
extern int n;
extern volatile int timer;


void anim_frame (ANIM_SET *ptr)
{
   if (ptr->speed)   //set speed to 0 for no animation
   {
      ptr->time++;

      if (ptr->time >= ptr->speed)
      {
         if (ptr->pos >= ptr->size)
            ptr->pos = 1;
         else
            ptr->pos += 1;

         ptr->time = 0;
      }
   }
}


void draw_screen (void)
{

   /*
   textprintf (screen_buffer, font, 20,0, 1, "REFRESH  %d", n);
   n+=1;
   if (n > 999)
      n = 0;
   */
   //textprintf (screen_buffer, font, 20,10, 1, "CLOCK  %d", clock ());

   vsync ();
   blit (screen_buffer, screen, TILE_SIZE,0, 0,0, SCRN_X,SCRN_Y);

}


void draw_bgrounds (LEVEL *ptr, int cc_x)
{

   //farground
   blit (ptr->far, screen_buffer, 0,0, TILE_SIZE,0, SCRN_X,SCRN_Y);
   //scrollground
   draw_scrollground (&(ptr->ground1), cc_x);
   //draw_scrollground (&(ptr->ground2), cc_x);
   //walkground
   draw_walkground (ptr, cc_x);

}


void draw_scrollground (SCROLL *ptr, int cc_x)
{


   if (cc_x > ptr->cc_x)
      if (cc_x - ptr->cc_x >= ptr->change_x)
      {
         ptr->pos += (cc_x - ptr->cc_x) / ptr->change_x;
         ptr->cc_x = cc_x;
      }

   if (cc_x < ptr->cc_x)
      if (ptr->cc_x - cc_x >= ptr->change_x)
      {
         ptr->pos -= (ptr->cc_x - cc_x) / ptr->change_x;
         ptr->cc_x = cc_x;
      }

   if (ptr->pos >= ptr->bmp->w)
      ptr->pos = 0;
   else if (ptr->pos < 0)
      ptr->pos = ptr->bmp->w-1;


   masked_blit (ptr->bmp, screen_buffer, ptr->pos,0, 0,0, SCRN_X+(TILE_SIZE*2),SCRN_Y);
   if (ptr->pos > ptr->bmp->w-(SCRN_X+(TILE_SIZE*2)))
      masked_blit (ptr->bmp, screen_buffer, 0,0, ptr->bmp->w-ptr->pos,0, SCRN_X+(TILE_SIZE*2),SCRN_Y);


}


void draw_walkground (LEVEL *ptr, int cc_x)
{

   int id_color, x,y;

   for (y=0; y<(SCRN_Y/TILE_SIZE); y+=1)
      for (x=0; x<((SCRN_X/TILE_SIZE)+2); x+=1)
      {
         if ((id_color = getpixel (ptr->walk,cc_x/TILE_SIZE-(((SCRN_X/TILE_SIZE)+2)/2)+x,y)) != 0)
            masked_blit (tile_set[id_color]->bmp, screen_buffer, 0,0, x*TILE_SIZE-(cc_x%TILE_SIZE),y*TILE_SIZE, TILE_SIZE,TILE_SIZE);
      }

}







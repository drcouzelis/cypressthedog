#include "datas.h"


#define CC_MAX_H_MOMENTUM (TILE_SIZE/10)


//u=up, d=down, l=left, r=right
//v=vertical, h=horizontal
void cc_update (CONTROLLABLE_CHAR *ptr);
void cc_add_momentum_d (CONTROLLABLE_CHAR *ptr);
void cc_add_momentum_l (CONTROLLABLE_CHAR *ptr);
void cc_add_momentum_r (CONTROLLABLE_CHAR *ptr);
void cc_add_momentum_u (CONTROLLABLE_CHAR *ptr);
void cc_slow_momentum_h (CONTROLLABLE_CHAR *ptr);
void cc_draw (CONTROLLABLE_CHAR *ptr);

// External
void anim_frame (ANIM_SET *ptr);
int pos_check_passable (int pos_x, int pos_y, int size_x, int size_y, DIRECTION dir);
int pos_change (int *orig_x, int *orig_y, int change_x, int change_y);

//extern CONTROLLABLE_CHAR cypress;
extern BITMAP *screen_buffer;
//extern BITMAP *sprite;



void cc_draw (CONTROLLABLE_CHAR *ptr)
{

   if (ptr->v_momentum < 0)  ptr->curr_anim = &(ptr->jump_anim);
   else if (ptr->v_momentum > 0)  ptr->curr_anim = &(ptr->fall_anim);
   else if (ptr->h_momentum)  ptr->curr_anim = &(ptr->run_anim);
   else  ptr->curr_anim = &(ptr->stand_anim);

   //save to a single usable sprite
   blit (ptr->curr_anim->bmp, ptr->sprite, (TILE_SIZE*3)*(ptr->curr_anim->pos-1),0, 0,0, (TILE_SIZE*3),(TILE_SIZE*3));
   //blit (ptr->curr_anim->bmp, screen, 0,0, 0,0, 60,60);  readkey ();

   anim_frame (ptr->curr_anim);

   if (ptr->facing == R)
      draw_sprite (screen_buffer, ptr->sprite, (SCRN_X/2)-TILE_SIZE,ptr->y-TILE_SIZE);
   if (ptr->facing == L)
      draw_sprite_h_flip (screen_buffer, ptr->sprite, (SCRN_X/2)-TILE_SIZE,ptr->y-TILE_SIZE);

}



void cc_update (CONTROLLABLE_CHAR *ptr)
{

   if (key[KEY_RIGHT] && !key[KEY_LEFT])
      cc_add_momentum_r (ptr);
   else if (key[KEY_LEFT] && !key[KEY_RIGHT])
      cc_add_momentum_l (ptr);
   else
      cc_slow_momentum_h (ptr);

   cc_add_momentum_u (ptr);
   cc_add_momentum_d (ptr);

   cc_draw (ptr);

}


void cc_add_momentum_u (CONTROLLABLE_CHAR *ptr)
{

   if (key[KEY_Z] || key[KEY_COLON] || key[KEY_SPACE])
      if (!ptr->v_momentum)
         ptr->v_momentum = -(TILE_SIZE/2);

   if (ptr->v_momentum < 0)
   {
      //checks for hitting your head...
      if (pos_check_passable (ptr->x, ptr->y, TILE_SIZE, TILE_SIZE, U))
      {
         pos_change (&(ptr->x), &(ptr->y), 0, ptr->v_momentum/2);
         /*
         if (ptr->v_momentum <= -15)  pos_change (&(ptr->x), &(ptr->y), 0, -4);
         else if (ptr->v_momentum <= -13)  pos_change (&(ptr->x), &(ptr->y), 0, -3);
         else if (ptr->v_momentum <= -9)  pos_change (&(ptr->x), &(ptr->y), 0, -2);
         else  pos_change (&(ptr->x), &(ptr->y), 0, -1);
         */

         ptr->v_momentum += 1;
      }
      else
         ptr->v_momentum = 0;
   }

}



void cc_slow_momentum_h (CONTROLLABLE_CHAR *ptr)
{

   if (ptr->h_momentum < 0)
      ptr->h_momentum += 1;
   if (ptr->h_momentum > 0)
      ptr->h_momentum -= 1;

   pos_change (&(ptr->x), &(ptr->y), ptr->h_momentum, 0);

}


void cc_add_momentum_l (CONTROLLABLE_CHAR *ptr)
{

   ptr->facing = L;

   ptr->h_momentum -= 1;
   if (ptr->h_momentum < -CC_MAX_H_MOMENTUM)
      ptr->h_momentum = -CC_MAX_H_MOMENTUM;

   pos_change (&(ptr->x), &(ptr->y), ptr->h_momentum, 0);

}




void cc_add_momentum_r (CONTROLLABLE_CHAR *ptr)
{

   ptr->facing = R;

   ptr->h_momentum += 1;
   if (ptr->h_momentum > CC_MAX_H_MOMENTUM)
      ptr->h_momentum = CC_MAX_H_MOMENTUM;

   pos_change (&(ptr->x), &(ptr->y), ptr->h_momentum, 0);

}



void cc_add_momentum_d (CONTROLLABLE_CHAR *ptr)
{


   if (ptr->v_momentum >= 0)
   {
      //first find if you can fall down...
      if (pos_check_passable (ptr->x, ptr->y, TILE_SIZE, TILE_SIZE, D))
         ptr->v_momentum += 1;
      else
         ptr->v_momentum = 0;

      //now change the position according to momentum
      if (ptr->v_momentum > 0)
      {
         pos_change (&(ptr->x), &(ptr->y), 0, ptr->v_momentum/2);
         /*
         if (ptr->v_momentum <= 9)  pos_change (&(ptr->x), &(ptr->y), 0, 1);
         else if (ptr->v_momentum <= 13)  pos_change (&(ptr->x), &(ptr->y), 0, 2);
         else if (ptr->v_momentum <= 15)  pos_change (&(ptr->x), &(ptr->y), 0, 3);
         else pos_change (&(ptr->x), &(ptr->y), 0, 4);
         */

         //check if you've fallen off the bottom
         if (ptr->y >= SCRN_Y)
            ptr->health = 0;
      }
   }
}



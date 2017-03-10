#include "datas.h"


//as for now, this file will take care of all oo

void oo_draw_cedar_troop (OO_CEDAR_TROOP *ptr);
OO_CEDAR_TROOP * oo_new_cedar_troop (int x, int y);
void oo_destroy_cedar_troop (OO_CEDAR_TROOP *ptr);
void oo_update_cedar_troop (OO_CEDAR_TROOP *ptr);
void oo_add_momentum_d (OO_CEDAR_TROOP *ptr);
void oo_walk (OO_CEDAR_TROOP *ptr);

// External
void anim_frame (ANIM_SET *ptr);
int pos_check_passable (int pos_x, int pos_y, int size_x, int size_y, DIRECTION dir);
int pos_change (int *orig_x, int *orig_y, int change_x, int change_y, int size_x, int size_y);
int init_anim_set (ANIM_SET *anim_set, char file_name[100], int y_loc, int how_many_frames, int speed);


extern BITMAP *screen_buffer;
//extern BITMAP *sprite;
extern CONTROLLABLE_CHAR cypress;



OO_CEDAR_TROOP * oo_new_cedar_troop (int x, int y)
{
   OO_CEDAR_TROOP *ptr;

   ptr = (OO_CEDAR_TROOP *) malloc (sizeof (OO_CEDAR_TROOP));

   ptr->x = x*TILE_SIZE;
   ptr->y = y*TILE_SIZE;

   ptr->id_color = 18;
   ptr->health = 2;
   ptr->facing = R;

   ptr->f_knocked_down = F;

   ptr->v_momentum = 0;
   ptr->h_momentum = 0;

   init_anim_set (&(ptr->walk_anim), PKGDATADIR "/images/cedar.bmp", 1, 2, 20);
   init_anim_set (&(ptr->knocked_down_anim), PKGDATADIR "/images/cedar.bmp", 2, 1, 0);
   //printf (".2*seconds = %g \n", .2*SECONDS);  readkey ();
   //printf ("oo walk speed  %d \n", ptr->walk_anim.speed);  readkey ();

   ptr->sprite = create_bitmap (TILE_SIZE*3,TILE_SIZE*3);
   clear (ptr->sprite);

   return (ptr);

}


void oo_destroy_cedar_troop (OO_CEDAR_TROOP *ptr)
{

   destroy_bitmap (ptr->walk_anim.bmp);
   destroy_bitmap (ptr->knocked_down_anim.bmp);
   free (ptr);

}


void oo_update_cedar_troop (OO_CEDAR_TROOP *ptr)
{

   oo_walk (ptr);
   oo_add_momentum_d (ptr);
   oo_draw_cedar_troop (ptr);

}


void oo_walk (OO_CEDAR_TROOP *ptr)
{

   if (ptr->facing == R)
   {
      pos_change (&(ptr->x),&(ptr->y), 1,0, TILE_SIZE, TILE_SIZE);
      if (!pos_check_passable (ptr->x, ptr->y, TILE_SIZE,TILE_SIZE, R))
         ptr->facing = L;
   }
   else if (ptr->facing == L)
   {
      pos_change (&(ptr->x),&(ptr->y), -1,0, TILE_SIZE, TILE_SIZE);
      if (!pos_check_passable (ptr->x, ptr->y, TILE_SIZE,TILE_SIZE, L))
         ptr->facing = R;
   }

}


void oo_add_momentum_d (OO_CEDAR_TROOP *ptr)
{
   if (ptr->v_momentum >= 0)
   {
      if (pos_check_passable (ptr->x, ptr->y, TILE_SIZE, TILE_SIZE, D))
         ptr->v_momentum += 1;
      else
         ptr->v_momentum = 0;

      if (ptr->v_momentum > 0)
      {
         if (ptr->v_momentum <= 9)  pos_change (&(ptr->x), &(ptr->y), 0, 1, TILE_SIZE, TILE_SIZE);
         else if (ptr->v_momentum <= 13)  pos_change (&(ptr->x), &(ptr->y), 0, 2, TILE_SIZE, TILE_SIZE);
         else if (ptr->v_momentum <= 15)  pos_change (&(ptr->x), &(ptr->y), 0, 3, TILE_SIZE, TILE_SIZE);
         else pos_change (&(ptr->x), &(ptr->y), 0, 4, TILE_SIZE, TILE_SIZE);

         if (ptr->y >= SCRN_Y)
            ptr->health = 0;
      }
   }

}


void oo_draw_cedar_troop (OO_CEDAR_TROOP *ptr)
{
   int x;


   if (!ptr->f_knocked_down)  ptr->curr_anim = &(ptr->walk_anim);
   else  ptr->curr_anim = &(ptr->knocked_down_anim);

   blit (ptr->curr_anim->bmp, ptr->sprite, (TILE_SIZE*3)*(ptr->curr_anim->pos-1),0, 0,0, (TILE_SIZE*3),(TILE_SIZE*3));

   anim_frame (ptr->curr_anim);

   /*
   if (clock () - ptr->curr_anim->time >= 20)
   {
      if (ptr->curr_anim->pos >= ptr->curr_anim->size)
         ptr->curr_anim->pos = 1;
      else
         ptr->curr_anim->pos += 1;

      ptr->curr_anim->time = clock ();
   }
   */

   x = ((ptr->x - cypress.x) + (SCRN_X/2));
   //textprintf (screen_buffer, font, 20,20, 1, "OO X LOC  %d", ptr->x);
   //textprintf (screen_buffer, font, 20,30, 1, "CC X LOC  %d", cypress.x);
   //textprintf (screen_buffer, font, 20,40, 1, "OO DISP LOC  %d", x);

   if (x >= 0 && x <= SCRN_X+(TILE_SIZE*2))
   {
      if (ptr->facing == R)
         draw_sprite (screen_buffer, ptr->sprite, x-TILE_SIZE,ptr->y-TILE_SIZE);
      if (ptr->facing == L)
         draw_sprite_h_flip (screen_buffer, ptr->sprite, x-TILE_SIZE,ptr->y-TILE_SIZE);
   }

}





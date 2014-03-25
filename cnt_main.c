/**
 * Copyright 2009 David Couzelis
 * 
 * This file is part of "Cypress and Tally".
 * 
 * "Cypress and Tally" is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * "Cypress and Tally" is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with "Cypress and Tally".  If not, see <http://www.gnu.org/licenses/>.
 */

//  This is the next step of my first 2d sidescroller.
//  Good luck, Cypress!!
//  I implemented use of a project, and a general #include
//  file.  This code should be a lot easier to work with
//  now.  Plus, I neatened controllable characters

//  David Rawson Couzelis


#include "datas.h"


void game_update (OO_CEDAR_TROOP *oo);
void game_clean_up (void);
int time_check (int time1, int time2);

// External
int init_game (void);
void init_info (void);
OO_CEDAR_TROOP * oo_new_cedar_troop (int x, int y);
void draw_screen (void);
void draw_bgrounds (LEVEL *ptr, int cc_x);
void cc_update (CONTROLLABLE_CHAR *ptr);
void oo_update_cedar_troop (OO_CEDAR_TROOP *ptr);


CONTROLLABLE_CHAR cypress;
//CONTROLLABLE_CHAR tally;


TILE *tile_set[NUM_OF_TILES];     //tile's location is it's id color, for easy reference.
LEVEL *level_set[NUM_OF_LEVELS];  //level's location is it's number, for easy reference.
PALLETE game_pal;                 //all palletes in the game should be exactly the same.


BITMAP *screen_buffer;
//BITMAP *sprite;
int level = 1;
FLAG want_to_quit = F;
int fullscreen = 0;

int timer;
int n = 1;

int game_rest=0;


int main (void)
{

   OO_CEDAR_TROOP *bad_guy;


   init_game ();
   //printf ("game initialized \n");  //readkey ();

   init_info ();
   //printf ("info initialized \n");  //readkey ();


   bad_guy = (OO_CEDAR_TROOP *) oo_new_cedar_troop (33,5);


   do
   {

      //initial blits to the screen buffer.
      draw_bgrounds (level_set[level], cypress.x);
      //load new opp objects, animate cypress, animate opp objects....
      game_update (bad_guy);
      //individual characters are responsible for their own drawing to the screen buffer.
      draw_screen ();

      //textprintf (screen, font, 0,20, 1, "TIMER  %d", timer);

      if (key[KEY_ESC])
         want_to_quit = T;

      if (key[KEY_F]) {
         if (fullscreen == 1) {
            set_gfx_mode (GFX_AUTODETECT_WINDOWED, SCRN_X, SCRN_Y, 0, 0);
            set_pallete (game_pal);
            fullscreen = 0;
         } else {
            set_gfx_mode (GFX_AUTODETECT, SCRN_X, SCRN_Y, 0, 0);
            set_pallete (game_pal);
            fullscreen = 1;
         }
      }
      
      while (timer - game_rest < 2);
      game_rest = timer;

   }
   while (!want_to_quit && cypress.health > 0);

   game_clean_up ();

   return 0;
}
END_OF_MAIN()


void game_update (OO_CEDAR_TROOP *oo)
{

   cc_update (&cypress);
   oo_update_cedar_troop (oo);

}


int time_check (int time1, int time2)
{
   //returns time 1 (a later time) minus time 2 (the earlier time).
   if (time1 - time2 >= 0)
      return (time1 - time2);
   return (time1 - (time2 - MAX_TICKER));
}



void game_clean_up (void)
{
   int x;

   //printf ("cleaning up \n");  readkey ();

   //clean up tiles...
   for (x=0; x<NUM_OF_TILES; x+=1)
      if (tile_set[x] != NULL)
      {
         destroy_bitmap (tile_set[x]->bmp);
         free (tile_set[x]);
         //printf ("tile %d destroyed \n", x);  readkey ();
      }
   //printf ("tiles done \n");  readkey ();

   //clean up levels...
   /*
   for (x=0; x<NUM_OF_LEVELS; x+=1)
      if (level_set[x] != NULL)
      {
         printf ("ready to destroy level %x \n", x);
         destroy_bitmap (level_set[x]->far);
         destroy_bitmap (level_set[x]->walk);
         destroy_bitmap (level_set[x]->oo);
         free (level_set[x]);
         printf ("level %d destroyed \n", x);  readkey ();
      }
   */

   //clean up characters...
   destroy_bitmap (cypress.stand_anim.bmp);
   destroy_bitmap (cypress.run_anim.bmp);
   destroy_bitmap (cypress.jump_anim.bmp);
   destroy_bitmap (cypress.fall_anim.bmp);
   destroy_bitmap (cypress.dash_anim.bmp);
   //printf ("character destroyed \n");  readkey ();

}


















#include <assert.h>
#include "datas.h"


int init_game (void);
void init_info (void);
void init_cc (CONTROLLABLE_CHAR *ptr);
int init_anim_set (ANIM_SET *anim_set, char file_name[100], int y_loc, int how_many_frames, int speed);
int init_tile (void);
int init_level (void);


extern BITMAP *screen_buffer;
extern CONTROLLABLE_CHAR cypress;
extern PALLETE game_pal;
extern TILE *tile_set[NUM_OF_TILES];
extern LEVEL *level_set[NUM_OF_LEVELS];
extern volatile int timer;


void do_timer (void)
{
  timer++;
}
END_OF_FUNCTION (do_timer);


int init_game (void)
{
   int x;

   allegro_init ();
   install_keyboard ();
   set_gfx_mode (GFX_AUTODETECT_WINDOWED, SCRN_X, SCRN_Y, 0, 0);
   set_color_depth (COLOR_DEPTH);

   install_timer ();
   timer=0;
   LOCK_VARIABLE (timer);
   LOCK_FUNCTION (do_timer);
   install_int_ex(do_timer,BPS_TO_TIMER(GAME_TICKER));

   for (x=0; x<NUM_OF_TILES; x+=1)
      tile_set[x] = NULL;
   for (x=0; x<NUM_OF_LEVELS; x+=1)
      level_set[x] = NULL;

   return 1;

}



void init_info (void)
{

   //screen buffer holds one set tiles to the left, one to the right.
   screen_buffer = create_bitmap (SCRN_X + (TILE_SIZE * 2), SCRN_Y);
   clear (screen_buffer);
   //sprite = create_bitmap (60, 60);
   //clear (sprite);

   init_tile ();
   //printf("Initialized tiles. \n");
   init_level ();
   //printf("Initialized level. \n");
   init_cc (&cypress);
   //printf("Initialized cc. \n");

   set_pallete (game_pal);

}


void init_cc (CONTROLLABLE_CHAR *ptr)
{


   ptr->health = 5;
   ptr->facing = R;

   ptr->x = 600;
   ptr->y = 40;

   ptr->f_dashing = F;

   ptr->h_momentum = 0;
   ptr->v_momentum = 0;

   init_anim_set (&(ptr->stand_anim), PKGDATADIR "/images/cypress.bmp", 1, 1, 0);
   init_anim_set (&(ptr->run_anim), PKGDATADIR "/images/cypress.bmp", 4, 3, 8);
   init_anim_set (&(ptr->jump_anim), PKGDATADIR "/images/cypress.bmp", 2, 1, 0);
   init_anim_set (&(ptr->fall_anim), PKGDATADIR "/images/cypress.bmp", 3, 1, 0);
   init_anim_set (&(ptr->dash_anim), PKGDATADIR "/images/cypress.bmp", 1, 1, 0);

   ptr->sprite = create_bitmap (TILE_SIZE*3,TILE_SIZE*3);
   clear (ptr->sprite);

}


int init_anim_set (ANIM_SET *anim_set, char file_name[100], int y_loc, int how_many_frames, int speed)
{

   BITMAP *temp_bmp;

   temp_bmp = create_bitmap (how_many_frames*(3*TILE_SIZE), y_loc*(3*TILE_SIZE));
   clear (temp_bmp);
   anim_set->bmp = create_bitmap (how_many_frames*(3*TILE_SIZE), (3*TILE_SIZE));
   clear (anim_set->bmp);

   if (!(temp_bmp = load_bitmap (file_name, game_pal))) {
      assert (temp_bmp);
      return (0);
   }
   blit (temp_bmp, anim_set->bmp, 0,(y_loc-1)*(3*TILE_SIZE), 0,0, how_many_frames*(3*TILE_SIZE),(3*TILE_SIZE));

   anim_set->size = how_many_frames;
   anim_set->pos = 1;                //set initial frame position to 1
   anim_set->time = clock ();
   anim_set->speed = speed;
   //printf ("speed %g \n", speed);  //readkey ();

   return (1);
}


int init_level (void)
{

   LEVEL *temp_level = NULL;

   FILE *file;
   char temp_str[200];
   char full_path[200];
   int temp_int;
   int i;


   if ((file = fopen ( PKGDATADIR "/levels/levels.txt", "r")) == NULL)
      return (0);

   else
   {
      //printf ("starting the level load \n");  //readkey ();

      while ((fscanf (file, "%s", temp_str)) != EOF)
         if (strcmp (temp_str, "new_level") == 0)
         {
            do
            {
               fscanf (file, "%s", temp_str);
               if (strcmp (temp_str, "number") == 0)
               {
                  fscanf (file, "%d", &i);
                  temp_level = (LEVEL *) malloc (sizeof (LEVEL));
                  temp_level->number = i;

                  //printf ("created a new level \n");  //readkey ();
               }
               if (strcmp (temp_str, "width") == 0)
               {
                  fscanf (file, "%d", &(temp_level->w));
                  //printf ("width set \n");  //readkey ();
                  temp_level->h = 10;
               }
               if (strcmp (temp_str, "walkground") == 0)
               {
                  fscanf (file, "%s", temp_str);

                  temp_level->walk = create_bitmap (temp_level->w, temp_level->h);
                  clear (temp_level->walk);

                  full_path[0] = '\0';
                  strcpy (full_path, PKGDATADIR "/levels/");
                  strcat (full_path, temp_str);
                  temp_level->walk = load_bitmap (full_path, game_pal);
                  assert (temp_level->walk);
                  //printf ("walk bmp loaded \n");  //readkey ();

               }
               if (strcmp (temp_str, "farground") == 0)
               {
                  fscanf (file, "%s", temp_str);

                  temp_level->far = create_bitmap (SCRN_X, SCRN_Y);
                  clear (temp_level->far);

                  full_path[0] = '\0';
                  strcpy (full_path, PKGDATADIR "/images/");
                  strcat (full_path, temp_str);
                  temp_level->far = load_bitmap (full_path, game_pal);
                  assert (temp_level->far);
                  //printf ("farground loaded \n");  //readkey ();

               }
               if (strcmp (temp_str, "scrollground1") == 0)
               {

                  fscanf (file, "%s", temp_str);
                  fscanf (file, "%d", &temp_int);

                  temp_level->ground1.bmp = create_bitmap (temp_int, SCRN_Y);
                  clear (temp_level->ground1.bmp);

                  full_path[0] = '\0';
                  strcpy (full_path, PKGDATADIR "/images/");
                  strcat (full_path, temp_str);
                  assert (temp_level->ground1.bmp);
                  temp_level->ground1.bmp = load_bitmap (full_path, game_pal);
                  fscanf (file, "%d", &(temp_level->ground1.change_x));
                  temp_level->ground1.pos = 0;
                  temp_level->ground1.cc_x = cypress.x;
                  //printf ("cypress.x = %d \n", cypress.x);  //readkey ();
               }
               if (strcmp (temp_str, "scrollground2") == 0)
               {

                  fscanf (file, "%s", temp_str);
                  fscanf (file, "%d", &temp_int);

                  temp_level->ground2.bmp = create_bitmap (temp_int, SCRN_Y);
                  clear (temp_level->ground2.bmp);

                  full_path[0] = '\0';
                  strcpy (full_path, PKGDATADIR "/images/");
                  strcat (full_path, temp_str);
                  temp_level->ground2.bmp = load_bitmap (full_path, game_pal);
                  assert (temp_level->ground2.bmp);
                  fscanf (file, "%d", &(temp_level->ground2.change_x));
                  temp_level->ground2.pos = 0;
                  temp_level->ground2.cc_x = cypress.x;
               }

            }
            while (strcmp (temp_str, "end_level") != 0);

            level_set[temp_level->number] = temp_level;
            //printf ("one level set \n");  //readkey ();
         }

   }

   return (1);


}



int init_tile (void)
{

   TILE *temp_tile = NULL;

   FILE *file;
   char temp_str[200];
   char full_path[200];
   int i;

   BITMAP *temp_bmp;


   temp_bmp = create_bitmap (6400, TILE_SIZE);
   clear (temp_bmp);


   if ((file = fopen ( PKGDATADIR "/levels/tiles.txt", "r")) == NULL)
      return (0);

   else
   {
      //printf ("starting the load \n");  readkey ();

      while ((fscanf (file, "%s", temp_str)) != EOF)
         if (strcmp (temp_str, "new_tile") == 0)
         {
            do
            {
               fscanf (file, "%s", temp_str);
               if (strcmp (temp_str, "color_identity") == 0)
               {
                  fscanf (file, "%d", &i);
                  temp_tile = (TILE *) malloc (sizeof (TILE));
                  temp_tile->id_color = i;

                  //printf ("created a new tile \n");  readkey ();
               }
               if (strcmp (temp_str, "passable") == 0)
               {
                  fscanf (file, "%d", &(temp_tile->passable));
                  //printf ("passable checked \n");  readkey ();
               }
               if (strcmp (temp_str, "file_name") == 0)
               {
                  fscanf (file, "%s", temp_str);
                  full_path[0] = '\0';
                  strcpy (full_path, PKGDATADIR "/images/");
                  strcat (full_path, temp_str);
                  temp_bmp = load_bitmap (full_path, game_pal);
                  assert (temp_bmp);
                  //printf ("temp bmp loaded \n");  readkey ();

                  temp_tile->bmp = create_bitmap (TILE_SIZE, TILE_SIZE);
                  clear (temp_tile->bmp);
                  //printf ("bmp cleared \n");  readkey ();

                  fscanf (file, "%d", &i);
                  //printf ("i = %d \n", i);  readkey ();

                  //blit (temp_bmp, screen, 0,0, 0,0, 32,32);  readkey ();

                  blit (temp_bmp, temp_tile->bmp, (i-1)*TILE_SIZE,0, 0,0, TILE_SIZE,TILE_SIZE);
                  //printf ("transfered the bmp \n");  readkey ();

               }


            }
            while (strcmp (temp_str, "end_tile") != 0);

            tile_set[temp_tile->id_color] = temp_tile;
            //printf ("one tile set \n");  readkey ();
         }

   }

   return (1);

}



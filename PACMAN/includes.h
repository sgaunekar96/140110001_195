/* THIS HEADER FILE CONTAINS ALL THE GLOBAL VARIABLE USED IN THE
PROGRAM, ALONG WITH THE OTHER ESSENTIAL ALLEGRO 5 HEADER FILES */

# include <allegro5/allegro.h>
# include <allegro5/allegro_native_dialog.h>
# include <allegro5/allegro_primitives.h>
# include <allegro5/allegro_image.h>
# include <allegro5/allegro_audio.h>
# include <allegro5/allegro_acodec.h>
# include <allegro5/allegro_ttf.h>
# include <allegro5/allegro_font.h>

# include <stdlib.h>
# include <time.h>

ALLEGRO_DISPLAY *display;                       // ALLEGRO DISPLAY WINDOW

ALLEGRO_BITMAP *hero = NULL;                    // PACMAN BITMAP
ALLEGRO_BITMAP *ghost1 = NULL;                  // BLINKY BITMAP
ALLEGRO_BITMAP *ghost2 = NULL;                  // PINKY BITMAP
ALLEGRO_BITMAP *ghost3 = NULL;                  // INKY BITMAP
ALLEGRO_BITMAP *ghost4 = NULL;                  // CLYDE BITMAP
ALLEGRO_BITMAP *frightenedGhost = NULL;         // FRIGHTENED GHOST BITMAP
ALLEGRO_BITMAP *maze = NULL;                    // MAZE BITMAP

ALLEGRO_SAMPLE *startSound = NULL;              // STARTING SOUND SAMPLE
ALLEGRO_SAMPLE *munchSound = NULL;              // ENERGIZED SOUND SAMPLE
ALLEGRO_SAMPLE *endSound = NULL;                // ENDING SOUND SAMPLE

const int ScreenWidth = 560;
const int ScreenHeight = 720;

const int TileSize = 20;                        // TILE SIZE
const int FPS = 60;                             // FRAMES PER SECOND

enum Direction { NIL, LEFT, RIGHT, UP, DOWN };  // ENUM FOR DIRECTION
enum Identity { HERO, GHOST };                  // ENUM FOR SPRITE IDESNTITY

int score = 0;
int coins = 240;
int energizers = 4;

bool start = false;
bool gameOver = false;
bool redraw = true;
bool frightened = false;
bool backHome = false;

int flag;                                       // TO CHECK FOR JUNCTION
int tileCode;                                   // TO CHECK THE MATRIX VALUE

int refresh = 0;                                // WORKS WITH RESPECT TO THE TIMER FOR ANIMATING SPRITES
unsigned int iterations = 0;                    // TIMES THE FRIGHTENED MODE

int pacmap[36][28] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},        // EACH MATRIX ELEMENT REPRESENTS A
                      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},        // 20X20 PIXEL TILE ON CORRESPONDING
                      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},        // MAP. THE SPRITES MAY ONLY MOVE
                      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},        // ALONG THE NON ZERO TILES.
                      {0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0},
                      {0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0},        // 1S ARE USED TO REPRESENT TILES
                      {0,2,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,2,0},        // WHICH HAVE COINS IN THEM. 2S ARE
                      {0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0},        // DENOTE TILES HAVING ENERGIZERS,
                      {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},        // WHILE -1 IS USED TO DENOTE TILES
                      {0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0},        // WITHOUT ANY OR ENERGIZER IN THEM.
                      {0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0},
                      {0,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,0},        // WHEN PACMAN PASSES OVER A TILE
                     {0,0,0,0,0,0,1,0,0,0,0,0,-1,0,0,-1,0,0,0,0,0,1,0,0,0,0,0,0},       // IT CHANGES ITS CODE TO -1 SO THAT
                     {0,0,0,0,0,0,1,0,0,0,0,0,-1,0,0,-1,0,0,0,0,0,1,0,0,0,0,0,0},       // A COIN IS NOT PRINTED AT ITS
                   {0,0,0,0,0,0,1,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,1,0,0,0,0,0,0}, // CENTER FOR THE NEXT ITERATION.
                      {0,0,0,0,0,0,1,0,0,-1,0,0,0,0,0,0,0,0,-1,0,0,1,0,0,0,0,0,0},
                      {0,0,0,0,0,0,1,0,0,-1,0,0,0,0,0,0,0,0,-1,0,0,1,0,0,0,0,0,0},
              {0,-1,-1,-1,-1,-1,1,-1,-1,-1,0,0,0,0,0,0,0,0,-1,-1,-1,1,-1,-1,-1,-1,-1,0},
                      {0,0,0,0,0,0,1,0,0,-1,0,0,0,0,0,0,0,0,-1,0,0,1,0,0,0,0,0,0},
                      {0,0,0,0,0,0,1,0,0,-1,0,0,0,0,0,0,0,0,-1,0,0,1,0,0,0,0,0,0},
                {0,0,0,0,0,0,1,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,1,0,0,0,0,0,0},
                      {0,0,0,0,0,0,1,0,0,-1,0,0,0,0,0,0,0,0,-1,0,0,1,0,0,0,0,0,0},
                      {0,0,0,0,0,0,1,0,0,-1,0,0,0,0,0,0,0,0,-1,0,0,1,0,0,0,0,0,0},
                      {0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0},
                      {0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
                      {0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
                     {0,2,1,1,0,0,1,1,1,1,1,1,1,-1,-1,1,1,1,1,1,1,1,0,0,1,1,2,0},
                      {0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0},
                      {0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0},
                      {0,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,0},
                      {0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0},
                      {0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0},
                      {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
                      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};

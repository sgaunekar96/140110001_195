/*FUNCTION TO REDRAW THE MAZE, COINS, AND SPRITES WHEN REQUIRED*/


void redraw_coins(const sprite& pacman, ALLEGRO_BITMAP *maze)
{

    // LOADING REQUIRED LIBRARIES AND ADDONS
    al_init_primitives_addon();
    al_init_image_addon();

    // REDRAW THE MAZE
    al_draw_bitmap(maze, 0, 60, NULL);

    // DEFINING COLOUR TO BE USED
    ALLEGRO_COLOR gold = al_map_rgb(255, 215, 0);

    coins = 0;
    energizers = 0;

    // TO REDRAW COINS IN EACH TILE
    for(int i = 4; i < 33; i++)
    {
        for(int j = 0; j < 28; j++)
        {
            if(pacmap[i][j] == 1)
            {
                al_draw_filled_circle((j+0.5)*TileSize, (i+0.5)*TileSize, 2.5, gold);
                coins ++;
            }
            else if(pacmap[i][j] == 2)
            {
                if(pacman.bmpX < 18 && pacman.bmpX < 90)
                {
                    al_draw_filled_circle((j+0.5)*TileSize, (i+0.5)*TileSize, 8, gold);
                }
                energizers ++;
            }
        }
    }

    // CHECKING IF ALL COINS AND ENERGIZERS HAVE BEEN EATEN
    if(coins == 0 && energizers == 0)
    {
        gameOver = true;
    }

}

/*FUNCTION TO REDRAW PACMAN WHEN REQUIRED*/

void redraw_hero(const sprite& pacman, ALLEGRO_BITMAP *hero)
{

    // INSTALLING REQUIRED LIBRARIES AND ADDONS
    al_init_image_addon();

    // DRAW PACMAN AT THE START
    if (pacman.dir == NIL)
    {
        al_draw_bitmap_region(hero, 108, 0, 36, 36, pacman.X, pacman.Y, NULL);
    }

    // REDRAW PACMAN WHEN REQUIRED
    else
    {
        al_draw_bitmap_region(hero, pacman.bmpX, pacman.bmpY*al_get_bitmap_height(hero)/4,
            al_get_bitmap_width(hero)/4, al_get_bitmap_height(hero)/4, pacman.X, pacman.Y, NULL);
    }
}

/*FUNCTION TO REDRAW THE GHOSTS WHEN REQUIRED*/

void redraw_ghosts(const sprite& ghost, ALLEGRO_BITMAP *ghostBmp, ALLEGRO_BITMAP *frightenedGhost)
{

    // INSTALLING IMAGE ADDON
    al_init_image_addon();

    // REDRAW GHOST IMAGE WHEN NOT FRIGHTENED
    if(!frightened)
    {
        al_draw_bitmap_region(ghostBmp, ghost.bmpX, ghost.bmpY*al_get_bitmap_height(ghost1)/4,
            al_get_bitmap_width(ghostBmp)/2, al_get_bitmap_height(ghostBmp)/4, ghost.X, ghost.Y, NULL);
    }

    // REDRAW GHOST IMAGE WHEN FRIGHTENED
    else
    {
        // BLUE GHOSTS
        if(iterations / 60 <= 5)
        {
            al_draw_bitmap_region(frightenedGhost, 0, 0, al_get_bitmap_width(frightenedGhost)/4,
                            al_get_bitmap_height(frightenedGhost), ghost.X, ghost.Y, NULL);
        }

        // WHITE GHOSTS
        if(iterations / 60 > 5)
        {
            al_draw_bitmap_region(frightenedGhost, 72, 0, al_get_bitmap_width(frightenedGhost)/4,
                            al_get_bitmap_height(frightenedGhost), ghost.X, ghost.Y, NULL);
        }
    }
}

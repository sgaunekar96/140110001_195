/* FUNCTION TO CHECK WHETHER PACMAN AND ANY OF THE GHOSTS OCCUPY
THE SAME TILE ON THE  MAZE AND RESETS THE COORDINATES ACCORDINGLY*/

void checkStatus(const sprite &pacman, sprite& ghost)
{

    // CHECKING IF ROW AND COLUMN NUMBERS MATCH
    if(pacman.mapX == ghost.mapX && pacman.mapY == ghost.mapY)
    {
        if(!frightened)
        {
            gameOver = true;
        }

        else
        {
            ghost.X = 265;
            ghost.Y = 275;
            iterations%2 == 0 ? ghost.dir = LEFT : ghost.dir = RIGHT;
            score += 200;
        }
    }

}

/* CLASS SPRITE PROVIDES THE TEMPLATE FOR CREATION OF ALL THE SPRITES
TO BE USED IN THIS GAME AND DEFINES THEIR FUNCTIONS AND ATTRIBUTES*/

class sprite
{
    public:

        int X;          // STORES THE X COORDINATE OF THE SPRITE
        int Y;          // STORES THE Y COORDINATE OF THE SPRITE

        int mapX;       // STORES THE ROW IN THE MATRIX WHICH THE SPRITE OCCUPIES
        int mapY;       // STORES THE COLUMN IN THE MATRIX WHICH THE SPRITE OCCUPIES

        int bmpX;       // STORES THE X COORDINATE ON THE SPRITE BITMAP
        int bmpY;       // STORES THE Y COORDINATE ON THE SPRITE BITMAP

        int mX;         // STORES THE PREVIOUS ROW NUMBER WHERE A DECISION WAS TAKEN TO TURN
        int mY;         // STORES THE PREVIOUS COLUMN NUMBER WHERE A DECISION WAS TAKEN TO TURN

        int speed;      // STORES THE NUMBER OF PIXELS TO BE MOVED FOR EACH LOOP ITERATION
        int dir;        // STORES SPRITE DIRECTION (UP, DOWN, LEFT, RIGHT)

        int ID;         // STORES THE IDENTITY OF THE SPRITE (GHOST OR HERO)

        sprite(int x, int y, int s, int d, int id)  // CONSTRUCTOROF CLASS SPRITE
        {
            X = x;
            Y = y;

            mapX = mX = (X + 18) / TileSize;
            mapY = mY = (Y + 18) / TileSize;

            bmpX = 0;
            bmpY = 0;

            speed = s;
            dir = d;
            ID = id;
        }

    // move() FUNCTION CONTROLS THE SPRITE MOVEMENT- GHOSTS AS WELL AS PACMAN
    void Move()
    {
        mapX = (X + 18) / TileSize;
        mapY = (Y + 18) / TileSize;

        tileCode = pacmap[mapY][mapX];

        // GHOSTS TAKE DECISIONS TO TURN ONLY AT DETECTED JUNCTIONS
        if(ID == GHOST && junction())
        {
            // DECISION TO TURN IS ONLY TAKEN ONCE PER TILE
            if(mX != mapX || mY != mapY)
            {
                dir = turn();
                mX = mapX;
                mY = mapY;
            }

            // NEW MOVE IS GENERATED IF DIRECTION HAPPENS TO BE OBSTRUCTED
            else if(obstructed(dir))
            {
                dir = turn();
            }
        }

        switch(dir)
        {
        case LEFT:

            // SPRITES ONLY MOVE FORWARD IF THEIR CURRENT DIRECTION IS UNOBSTRUCTED
            if(!obstructed(dir))
            {
                X -= speed;

                // SETTING VALUES OF TILES TO -1 WHEN PACMAN HAS PASSED OVER THEM
                if(tileCode != 0 && ID == HERO)
                    pacmap[mapY][mapX] = -1;
            }

            // SPECIAL CASES FOR THE WORMHOLE
            else if(Y >= 315 && Y <= 355 && X <= 145)
                X -= speed;

            else if(Y >= 315 && Y <= 355 && X >= 415)
                X -= speed;

            if(X <= -30)
                X = 550;

                break;

        case RIGHT:

            if(!obstructed(dir))
            {
                X += speed;

                if(tileCode != 0 && ID == HERO)
                    pacmap[mapY][mapX] = -1;
            }

            else if(Y >= 315 && Y <= 355 && X >= 415)
                X += speed;

            else if(Y >= 315 && Y <= 355 && X <= 145)
                X += speed;

            if(X >= 550)
                X = -30;

            break;

        case UP:

            if(!obstructed(dir))
            {
                Y -= speed;

                if(tileCode != 0 && ID == HERO)
                    pacmap[mapY][mapX] = -1;
            }

            break;

        case DOWN:

            if(!obstructed(dir))
            {
                Y += speed;

                if(tileCode != 0 && ID == HERO)
                    pacmap[mapY][mapX] = -1;
            }

            break;
        }

        // UPDATING SPRITE POSITION ON THE MATRIX
        mapX = (X + 18) / TileSize;
        mapY = (Y + 18) / TileSize;

        tileCode = pacmap[mapY][mapX];

        if(tileCode == 2 && ID == HERO)
        {
            frightened = true;
            iterations = 0;
        }

        // UPDATING X COORDINATE ON THE BITMAPS FOR SPRITE ANIMATION
        if(refresh == 5)
        {
            bmpX += 36;
            refresh = 0;
        }

        if(ID == HERO && bmpX >= 144)
            bmpX = 0;

        else if(ID == GHOST && bmpX >=72)
            bmpX = 0;

        // SETTING Y COORDINATE ON BITMAP DEPENDENT ON DIRECTION
        bmpY = dir-1;

        return;
    }

    // FUNCTION RETURNS TRUE IF THE GIVEN DIRECTION IS OBSTRUCTED ELSE RETURNS FALSE
    bool obstructed(int d)
    {
        switch(d)
        {
        case LEFT:
            if(pacmap[(Y + 18) / TileSize][(X + 6) / TileSize] != 0)
                return false;
            else
                return true;
        case RIGHT:
            if(pacmap[(Y + 18) / TileSize][(X + 28) / TileSize] != 0)
                return false;
            else
                return true;
        case UP:
            if(pacmap[(Y + 6) / TileSize][(X + 18) / TileSize] != 0)
                return false;
            else
                return true;
        case DOWN:
            if(pacmap[(Y + 30) / TileSize][(X + 18) / TileSize] != 0)
                return false;
            else
                return true;
        }
    }

    // FUNCTION TO GENERATE AN UNOBSTRUCTED DIRECTION FOR THE GHOSTS
    int turn()
    {
        int d;
        do
        {
            d = 1 + rand()%4;
        }while(obstructed(d));

        return d;
    }

    // FUNSTION RETURNS TRUE WHEN GHOST HAS REACHED A JUNCTION, ELSE RETURNS FALSE
    bool junction()
    {
        flag = 0;

        if(pacmap[mapY+1][mapX] != 0 || pacmap[mapY-1][mapX] != 0)
            flag++;

        if(pacmap[mapY][mapX+1] != 0 || pacmap[mapY][mapX-1] != 0)
            flag++;

        if(flag == 2)
            return true;
        else
            return false;
    }

};

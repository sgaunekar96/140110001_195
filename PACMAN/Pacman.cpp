# include "includes.h"
# include "sprite.h"
# include "checkStatus.h"
# include "redraw.h"
# include "endGame.h"
# include "startGame.h"

int main()
{
    // SEEDING THE rand() FUNCTION FOR EVERY NEW GAME
    srand(time(NULL));

    // CREATING THE DIFFERENT SPRITES TO BE USED IN THE GAME
    sprite pacman(265,515,2,NIL,HERO);
    sprite blinky(12,72,2,RIGHT,GHOST);
    sprite pinky(512,72,2,LEFT,GHOST);
    sprite inky(12,632,2,RIGHT,GHOST);
    sprite clyde(512,632,2,LEFT,GHOST);

    // ERROR MESSAGE TO BE SHOWN IF UNABLE TO INITIALIZE ALLEGRO
    if(!al_init())
    {
        al_show_native_message_box(NULL, "Error", NULL, "Could not initialize Allegro 5", NULL, NULL);
        return -1;
    }

    // CREATES THE DISPLAY OF DEFINED WIDTH AND HEIGHT
    display = al_create_display(ScreenWidth,ScreenHeight);

    // ERROR MESSAGE TO BE SHOWN IF UNABLE TO CREATE THE DISPLAY
    if(!display)
    {
        al_show_native_message_box(NULL, "Error", NULL, "Could not create Allegro display", NULL, NULL);
        return -1;
    }

    // SETTING THE DISPLAY TITLE AND POSITION
    al_set_window_title(display,"PACMAN");
    al_set_window_position(display, 400, 0);

    // INSTALLING THE REQUIRED LIBRARIES
    al_init_primitives_addon();
    al_install_keyboard();
    al_install_mouse();
    al_install_audio();
    al_init_image_addon();
    al_init_acodec_addon();
    al_reserve_samples(3);

    // LOADING PACMAN IMAGE
    hero = al_load_bitmap("pacman.png");

    if(!hero)
    {
        al_show_native_message_box(NULL, "Error", NULL, "Could not create Pacman bitmap", NULL, NULL);
        return -1;
    }

    // LOADING 1ST GHOST IMAGE
    ghost1 = al_load_bitmap("blinky.png");

    if(!ghost1)
    {
        al_show_native_message_box(NULL, "Error", NULL, "Could not create BLinky bitmap", NULL, NULL);
        return -1;
    }

    // LOADING 2ND GHOST IMAGE
    ghost2 = al_load_bitmap("pinky.png");

    if(!ghost2)
    {
        al_show_native_message_box(NULL, "Error", NULL, "Could not create Pinky bitmap", NULL, NULL);
        return -1;
    }

    // LOADING 3RD GHOST IMAGE
    ghost3 = al_load_bitmap("inky.png");

    if(!ghost3)
    {
        al_show_native_message_box(NULL, "Error", NULL, "Could not create Inky bitmap", NULL, NULL);
        return -1;
    }

    // LOADING 4TH GHOST IMAGE
    ghost4 = al_load_bitmap("clyde.png");

    if(!ghost4)
    {
        al_show_native_message_box(NULL, "Error", NULL, "Could not create Clyde bitmap", NULL, NULL);
        return -1;
    }

    // LOADING THE MAZE
    maze = al_load_bitmap("maze.png");

    if(!maze)
    {
        al_show_native_message_box(NULL, "Error", NULL, "Could not create maze bitmap", NULL, NULL);
        return -1;
    }

    // LOADING FRIGHTENED GHOST IMAGE
    frightenedGhost = al_load_bitmap("frightened.png");

    if(!frightenedGhost)
    {
        al_show_native_message_box(NULL, "Error", NULL, "Could not create frightened ghost bitmap", NULL, NULL);
        return -1;
    }

    // LOADING STARTING AUDIO
    startSound = al_load_sample("pacman_beginning.wav");

    if(!startSound)
    {
        al_show_native_message_box(NULL, "Error", NULL, "Could not create startSound sample", NULL, NULL);
        return -1;
    }

    // LOADING ENERGIZER AUDIO
    munchSound = al_load_sample("pacman_chomp.wav");

    if(!munchSound)
    {
        al_show_native_message_box(NULL, "Error", NULL, "Could not create munchSound sample", NULL, NULL);
    }

    // LOADING ENDING AUDIO
    endSound = al_load_sample("pacman_death.wav");

    if(!startSound)
    {
        al_show_native_message_box(NULL, "Error", NULL, "Could not create endSound sample", NULL, NULL);
        return -1;
    }

    // CREATING THE ALLEGRO TIMER
    ALLEGRO_TIMER *timer = al_create_timer(1.0/FPS);
    // CREATING THE EVENT QUEUE
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    // REGISTERING EVENT SOURCES
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    // CALLING startG FUNCTION TO DISPLAY HOME SCREEN
    startG(display);

    if(start)
    {
    al_start_timer(timer);    // STARTS THE TIMER

    al_clear_to_color(al_map_rgb(0, 0, 0));    // CLEARS THE DISPLAY TO BLACK
    al_play_sample(startSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);    // PLAYS STARTING AUDIO

    // MAIN GAME LOOP
    while(!gameOver)
    {
        ALLEGRO_EVENT events;    // CREATES ALLEGRO EVENTS
        al_wait_for_event(event_queue, &events);    // WAITING FOR EVENTS IN QUEUE

        //SETTING PACMAN'S DIRECTION BASED ON USER INPUT
        if(events.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(events.keyboard.keycode)
            {

            case ALLEGRO_KEY_LEFT:
            case ALLEGRO_KEY_A:
                pacman.dir = LEFT;
                break;

            case ALLEGRO_KEY_RIGHT:
            case ALLEGRO_KEY_D:
                pacman.dir = RIGHT;
                break;

            case ALLEGRO_KEY_UP:
            case ALLEGRO_KEY_W:
                pacman.dir = UP;
                break;

            case ALLEGRO_KEY_DOWN:
            case ALLEGRO_KEY_S:
                pacman.dir = DOWN;
                break;

            case ALLEGRO_KEY_ESCAPE:
                gameOver=true;
                break;

            }
        }

        // CONTROLS GHOST MOVEMENT BASED ON TIMER OUTPUT
        if(events.type == ALLEGRO_EVENT_TIMER)
        {
            pacman.Move();
            blinky.Move();
            pinky.Move();
            inky.Move();
            clyde.Move();

            redraw = true;
            iterations ++;
        }

        // REDRAWS THE MAP, COINS AND SPRITES WHEN REQUIRED
        if (redraw == true)
        {

            redraw = false;

            // CHECKING WHETHER PACMAN OR THE GHOSTS HAVE BEEN ATTACKED
            checkStatus(pacman, blinky);
            checkStatus(pacman, pinky);
            checkStatus(pacman, inky);
            checkStatus(pacman, clyde);

            redraw_coins(pacman, maze);

            redraw_hero(pacman, hero);

            redraw_ghosts(blinky, ghost1, frightenedGhost);
            redraw_ghosts(pinky, ghost2, frightenedGhost);
            redraw_ghosts(inky, ghost3, frightenedGhost);
            redraw_ghosts(clyde, ghost4, frightenedGhost);

            // CONTROLS FRIGHTEN MODE SETTINGS
            if(frightened)
            {

                if(iterations / 60 >= 7)
                {
                    frightened = false;
                }
                else if(iterations % 60 == 1)
                {
                    // PLAYING ENERGIZER AUDIO WHEN FRIGHTENED
                    al_play_sample(munchSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                }

            }

            // UPDATES THE FRONT AND BACK BUFFERS SO THAT WHAT HAS BEEN DRAWN PREVIOUSLY BECOMES VISIBLE ON THE DISPLAY
            al_flip_display();
            // CLEARS SCREEN TO BLACK
            al_clear_to_color(al_map_rgb(0, 0, 0));

            refresh ++;
        }
    }

    if(coins != 0 || energizers !=0)
    {
        // PLAYS ENDING AUDIO IF PACMAN GETS EATEN BY A GHOST
        al_play_sample(endSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
        al_rest(1.7);
    }
    else
        al_rest(1);

    al_clear_to_color(al_map_rgb(0, 0, 0));
    endG(display);    // CALLS THE endG() FUNCTION TO DISPLAY THE CREDITS PAGE AND SCORE
    }

    // FREEING ALL RESOURCES USED TO PREVENT LEAKS
    al_destroy_display (display);
    al_destroy_timer (timer);
    al_destroy_sample (startSound);
    al_destroy_sample (munchSound);
    al_destroy_sample (endSound);
    al_destroy_bitmap (hero);
    al_destroy_bitmap (ghost1);
    al_destroy_bitmap (ghost2);
    al_destroy_bitmap (ghost3);
    al_destroy_bitmap (ghost4);
    al_destroy_bitmap (maze);
    al_destroy_event_queue (event_queue);

    return 0;
}

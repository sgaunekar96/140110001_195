/* THIS FUNCTION IS CALLED WHEN THE GAME GETS OVER AND IS USED TO
DISPLAY THE CREDITS AND SCORE. THERE IS ALSO AN OPTION TO QUIT GAME*/

#include<sstream>
#include<string>

void endG(ALLEGRO_DISPLAY *display)
{
    int mouseY, mouseX; // STORE MOUSE COORDINATES

    // INSTALLING THE REQUIRED LIBRARIES AND ADDONS
    al_install_mouse();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();

    // CALCULATING THE SCORE ACHIEVED BY THE PLAYER
    score += ((240-coins) * 10 + (4-energizers)*50);

    // CONVERTING SCORE TO STRING
    std::ostringstream convert;
    convert << score;

    // DEFINING COLOURS USED
    ALLEGRO_COLOR RoyalBlue = al_map_rgb(100, 149, 237);
    ALLEGRO_COLOR PacmanYellow = al_map_rgb(255, 238, 0);

    // LOADING FONT TO BE USED WITH REQUIRED SIZE
    ALLEGRO_FONT *font1 = al_load_ttf_font("PAC-FONT.ttf", 45, NULL);
    ALLEGRO_FONT *font2 = al_load_ttf_font("PAC-FONT.ttf", 25, NULL);
    ALLEGRO_FONT *font3 = al_load_ttf_font("Digital Sans.ttf", 40, NULL);

    // DRAWING THE HEADER
    al_draw_text(font1, RoyalBlue, ScreenWidth / 2, ScreenHeight/ 60 +20, ALLEGRO_ALIGN_CENTRE, "GAME OVER!");
    al_draw_line(95, 90, 465, 90, PacmanYellow, 4.0);

    // DRAWING THE BODY
    al_draw_text(font2, RoyalBlue, ScreenWidth / 2, 130, ALLEGRO_ALIGN_CENTRE, "Credits");
    al_draw_text(font2, PacmanYellow, ScreenWidth / 2, 210, ALLEGRO_ALIGN_CENTER, "Soham Gaunekar");
    al_draw_text(font2, PacmanYellow, ScreenWidth / 2, 300, ALLEGRO_ALIGN_CENTER, "Nisarg Gagrani");
    al_draw_text(font2, PacmanYellow, ScreenWidth / 2, 390, ALLEGRO_ALIGN_CENTER, "Soumya Nimodiya");
    al_draw_text(font2, PacmanYellow, ScreenWidth / 2, 480, ALLEGRO_ALIGN_CENTER, "Aditya Kumawat");
    al_draw_text(font2, RoyalBlue, 20, 640, ALLEGRO_ALIGN_LEFT, "Score: ");
    al_draw_text(font3, RoyalBlue, 140, 630, NULL, convert.str().c_str());
    al_draw_text(font2, RoyalBlue, 540, 640, ALLEGRO_ALIGN_RIGHT, "Quit");

    // UPDATES THE FRONT AND BACK BUFFERS SO THAT WHAT HAS BEEN DRAWN PREVIOUSLY BECOMES VISIBLE ON THE DISPLAY
    al_flip_display();

    bool done = false;

    // CREATES EVENT QUEUE FOR GOING BACK
    ALLEGRO_EVENT_QUEUE *eback = al_create_event_queue();
    // REGISTERING EVENT SOURCES
    al_register_event_source(eback, al_get_display_event_source(display));
    al_register_event_source(eback, al_get_mouse_event_source());

    // GET MOUSE CLICK TO QUIT GAME
    while(!done)
    {

        ALLEGRO_EVENT eventback;

        al_wait_for_event(eback, &eventback);

        if(eventback.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            mouseX = eventback.mouse.x;
            mouseY = eventback.mouse.y;

            if((460 < mouseX) && (mouseX < 550) && (mouseY < 680) && (mouseY > 600))
            {
                done = true;
            }
        }
    }

    // DESTROYING FONTS AND FREEING RESOURCES
    al_destroy_font(font1);
    al_destroy_font(font2);
    al_destroy_font(font3);
    al_destroy_event_queue(eback);
}


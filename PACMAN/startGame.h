# include "instructions.h"

void startG(ALLEGRO_DISPLAY *display)
{
    bool click = false;
    int mouseX, mouseY;    // STORE MOUSE COORDINATES

    // INSTALLING REQUIRED LIBRARIES AND ADDONS
    al_install_mouse();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();

    // DEFINING COLOURS TO BE USED
    ALLEGRO_COLOR RoyalBlue = al_map_rgb(100, 149, 237);
    ALLEGRO_COLOR PacmanYellow = al_map_rgb(255, 238, 0);

    // LOADING REQUIRED FONT
    ALLEGRO_FONT *font = al_load_ttf_font("PAC-FONT.ttf", 30, NULL);

    // LOADING LOGO IMAGE
    ALLEGRO_BITMAP *logo = al_load_bitmap("logo.png");

    // DRAWING HEADER
    al_draw_bitmap(logo, 35, 15, NULL);
    // DRAWING BODY
    al_draw_text(font, RoyalBlue, ScreenWidth / 2, 280, ALLEGRO_ALIGN_CENTER, "Start Game");
    al_draw_text(font, RoyalBlue, ScreenWidth / 2, 380, ALLEGRO_ALIGN_CENTER, "Instructions");
    al_draw_text(font, RoyalBlue, ScreenWidth / 2, 480, ALLEGRO_ALIGN_CENTER, "Quit");
    al_flip_display();

    bool done = false;

    // CREATING ALLEGRO EVENT QUEUE
    ALLEGRO_EVENT_QUEUE *ehome = al_create_event_queue();
    al_register_event_source(ehome, al_get_display_event_source(display));
    al_register_event_source(ehome, al_get_mouse_event_source());

    // MAIN LOOP
    while(!done)
    {
        click = false;
        ALLEGRO_EVENT event;
        al_wait_for_event(ehome, &event);
        al_draw_bitmap(logo, 35, 15, NULL);


        // TO GET MOUSE COORDINATES
        if(event.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            mouseX = event.mouse.x;
            mouseY = event.mouse.y;
        }

        // TO PERFORM RESPECTIVE TASK BASED ON POSITION OF CLICK
        else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            click =true;
            if(mouseX>180 && mouseX<380 && mouseY>270 && mouseY<320)
            {
                done = true;
                start = true;
            }
            else if(mouseX>180 && mouseX<380 && mouseY>370 && mouseY<420)
            {
                instructions(display);
            }
            else if(mouseX>180 && mouseX<380 && mouseY>470 && mouseY<520)
            {
                done = true;
            }
        }

        // TO CHANGE COLOUR OF TEXT WHEN  OUSE HOVERS OVER IT
        if(!click)
        {
            if(mouseX>180 && mouseX<380 && mouseY>270 && mouseY<320)
            {
                al_draw_text(font, PacmanYellow, ScreenWidth / 2, 280, ALLEGRO_ALIGN_CENTER, "Start Game");
                al_draw_text(font, RoyalBlue, ScreenWidth / 2, 380, ALLEGRO_ALIGN_CENTER, "Instructions");
                al_draw_text(font, RoyalBlue, ScreenWidth / 2, 480, ALLEGRO_ALIGN_CENTER, "Quit");
            }

            else if(mouseX>180 && mouseX<380 && mouseY>370 && mouseY<420)
            {
                al_draw_text(font, RoyalBlue, ScreenWidth / 2, 280, ALLEGRO_ALIGN_CENTER, "Start Game");
                al_draw_text(font, PacmanYellow, ScreenWidth / 2, 380, ALLEGRO_ALIGN_CENTER, "Instructions");
                al_draw_text(font, RoyalBlue, ScreenWidth / 2, 480, ALLEGRO_ALIGN_CENTER, "Quit");
            }

            else if(mouseX>230 && mouseX<330 && mouseY>470 && mouseY<520)
            {
                al_draw_text(font, RoyalBlue, ScreenWidth / 2, 280, ALLEGRO_ALIGN_CENTER, "Start Game");
                al_draw_text(font, RoyalBlue, ScreenWidth / 2, 380, ALLEGRO_ALIGN_CENTER, "Instructions");
                al_draw_text(font, PacmanYellow, ScreenWidth / 2, 480, ALLEGRO_ALIGN_CENTER, "Quit");
            }
            else
            {
                al_draw_text(font, RoyalBlue, ScreenWidth / 2, 280, ALLEGRO_ALIGN_CENTER, "Start Game");
                al_draw_text(font, RoyalBlue, ScreenWidth / 2, 380, ALLEGRO_ALIGN_CENTER, "Instructions");
                al_draw_text(font, RoyalBlue, ScreenWidth / 2, 480, ALLEGRO_ALIGN_CENTER, "Quit");
            }
        }

        al_flip_display();
        al_clear_to_color(al_map_rgb(0, 0, 0));
    }

    // DESTROYING CREATED BITMAPS, FONT, AND EVENT QUEUE TO FREE RESOURCES USED
    al_destroy_bitmap(logo);
    al_destroy_font(font);
    al_destroy_event_queue(ehome);
}

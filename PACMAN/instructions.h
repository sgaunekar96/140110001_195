/* FUNCTION IS CALLED TO DISPLAY THE INSTRUCTIONS OF THE PACMAN
GAME AND ALSO PROVIDES THE OPTION TO GO BACK TO THE HOME SCREEN */

void instructions(ALLEGRO_DISPLAY *display)
{
    // INSTALLING THE REQUIRED LIBRARIES AND ADDONS
    al_install_mouse();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();

    // CLEARING THE DISPLAY SCREEN TO BLACK
    al_clear_to_color(al_map_rgb(0, 0, 0));

    // DEFINING THE COLOURS TO BE USED
    ALLEGRO_COLOR RoyalBlue = al_map_rgb(100, 149, 237);
    ALLEGRO_COLOR PacmanYellow = al_map_rgb(255, 238, 0);

    // LOADING THE REQUIRED FONT WITH REQUIERED SIZE
    ALLEGRO_FONT *font1 = al_load_ttf_font("PAC-FONT.ttf", 45, NULL);
    ALLEGRO_FONT *font2 = al_load_ttf_font("Digital Sans.ttF", 25, NULL);
    ALLEGRO_FONT *font3 = al_load_ttf_font("PAC-FONT.ttF", 15, NULL);

    // DRAWING THE HEADER
    al_draw_text(font1, RoyalBlue, ScreenWidth / 2, ScreenHeight/60 + 30, ALLEGRO_ALIGN_CENTRE, "Instructions");
    al_draw_line(70, 115, 490, 115, PacmanYellow, 4.0);

    // DRAWING THE BODY
    al_draw_text(font2, PacmanYellow, 30, 200, ALLEGRO_ALIGN_LEFT," -> Use W/A/S/D or arrow keys to manoeuvre ");
    al_draw_text(font2, PacmanYellow, 30, 225, ALLEGRO_ALIGN_LEFT," pacman through the maze while avoiding ghosts.");
    al_draw_text(font2, PacmanYellow, 30, 280, ALLEGRO_ALIGN_LEFT," -> Eat all the dots to earn 10 points each,");
    al_draw_text(font2, PacmanYellow, 30, 305, ALLEGRO_ALIGN_LEFT," and flashing energizers for 50 points a piece.");
    al_draw_text(font2, PacmanYellow, 30, 370, ALLEGRO_ALIGN_LEFT," -> When energized, pacman can attack the ghosts");
    al_draw_text(font2, PacmanYellow, 30, 395, ALLEGRO_ALIGN_LEFT," to earn 200 additional points per ghost.");
    al_draw_text(font2, PacmanYellow, 30, 460, ALLEGRO_ALIGN_LEFT," -> Beware of white ghosts which are about");
    al_draw_text(font2, PacmanYellow, 30, 485, ALLEGRO_ALIGN_LEFT," to return  to their normal state.");
    al_draw_text(font2, PacmanYellow, 30, 550, ALLEGRO_ALIGN_LEFT," -> Click ESC to quit game while in play.");
    al_draw_text(font3, RoyalBlue, 540, 640, ALLEGRO_ALIGN_RIGHT, "Back to home screen");

    // UPDATES THE FRONT AND BACK BUFFERS SO THAT WHAT HAS BEEN DRAWN PREVIOUSLY BECOMES VISIBLE ON THE DISPLAY
    al_flip_display();

    bool done = false;

    // CREATING AN EVENT QUEUE TO GO BACK
    ALLEGRO_EVENT_QUEUE *eback = al_create_event_queue();
    // REGISTERING EVENT SOURCES
    al_register_event_source(eback, al_get_display_event_source(display));
    al_register_event_source(eback, al_get_mouse_event_source());

    while(!done)    // MAIN LOOP TO DETECT MOUSE CLICK
    {

        ALLEGRO_EVENT eventback;    // CREATING EVENT TO GO BACK

        al_wait_for_event(eback, &eventback);    // WAITS FOR EVENT

        if(eventback.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            // TO GET COORDINATES OF MOUSE CLICK
            int mouseX = eventback.mouse.x;
            int mouseY = eventback.mouse.y;

            // TO GO BACK TO HOME SCREEN
            if((300 < mouseX) && (mouseX < 530) && (mouseY < 680) && (mouseY > 600))
            {
                done = true;
            }
        }
    }

    // DESTROYS FONTS AND EVENT QUEUE AND FREE USED RESOURCES
    al_destroy_font(font1);
    al_destroy_font(font2);
    al_destroy_font(font3);
    al_destroy_event_queue(eback);
}

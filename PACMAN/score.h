#include<sstream>
#include<string>

void display_score()
{
    score += ((240-coins) * 10 + (4-energizers)*50);
    std::ostringstream convert;
    convert << score;
    if(coins == 0 && energizers == 0)
    {
        al_show_native_message_box(display, "GAME OVER!", "Score:", convert.str().c_str(), NULL, NULL);
    }
    else
    {
        al_show_native_message_box(display, "GAME OVER!", "Score:", convert.str().c_str(), NULL, ALLEGRO_MESSAGEBOX_ERROR);
    }
}

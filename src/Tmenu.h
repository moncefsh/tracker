#pragma once
#include <string>
#include <ncurses.h>

class Tmenu
{
public:
    Tmenu(int height,int width,std::string *opt,int num);
    void refresh(){wrefresh(_menu_win);}

    void clear(){wclear(_menu_win);}

    void draw();

    int handle_input();


private:
    WINDOW *_menu_win;
    std::string *_options;
    int _opt_num;
    int _height, _width;
    int _selected_opt;
};
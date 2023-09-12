#pragma once
#include "Ttime.h"
#include <ncurses.h>


class TchronoWin
{
public:
    //constructers
    TchronoWin(WINDOW *win);
    TchronoWin(int w, int h);
    //
    int win_width(){ return _width;}
    int win_height(){ return _height;}
    //chrono functions:
    bool handle_input();
    // drawning ....
    virtual void  draw();// initialize the screan before the chrono begin and wait for input to start
    void redraw();  // update the time on the screan
    //
    void refresh(){wrefresh(_chronoWin);}
    void clear() { wclear(_chronoWin);}
    

protected:
    Tchrono *_chrono;
    WINDOW *_chronoWin;
    int _width , _height;
};

class TtimerWin : Tchrono
{

};
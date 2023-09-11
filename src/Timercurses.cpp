#include "Timecurses.h"

#define SECOND 1000


TchronoWin::TchronoWin(WINDOW *win)
{
    this->_chronoWin = win;
    this->_chrono = new Tchrono();
    getmaxyx(win,_height,_width);
    wtimeout(this->_chronoWin,SECOND);
}
TchronoWin::TchronoWin(int w, int h)
{
    this->_height = h;
    this->_width = w;
    int xmax,ymax;
    getmaxyx(stdscr,ymax,xmax);
    this->_chronoWin=newwin(h,w,(ymax/2)-(h/2),(xmax/2)-(w/2));
    this->_chrono= new Tchrono();
    wtimeout(this->_chronoWin,SECOND);
}


    // drawning ....

void TchronoWin::draw()
{
    this->clear();
    mvwprintw(this->_chronoWin,2,2,"press X to start ");
    
}

void TchronoWin::redraw()
{

}
#include "Tmenu.h"

Tmenu::Tmenu(int height,int width,std::string *opt,int num)
{
    int xmax,ymax;
    getmaxyx(stdscr,ymax,xmax);
    _menu_win=newwin(height,width,(ymax/2)-(height/2),(xmax/2)-(width/2));
    this->_height=height;
    this->_width=width;
    _options =opt;
    _opt_num = num;
    _selected_opt=0;
    keypad(_menu_win,true);
}

void Tmenu::draw()
{ 
    box(_menu_win,0,0);
    mvwprintw(_menu_win,1,_width/2 -5,"Tmenu");
    int start_y=3;
    for(int i=0;i<_opt_num;i++)
    { 
        mvwprintw(_menu_win,i+start_y,_width/2 -5,"%s",_options[i].c_str());

        if (_selected_opt == i)
        	mvwchgat(_menu_win, i+start_y, 1, _width-2, A_NORMAL, 1, NULL);
    	else
        	mvwchgat(_menu_win, i+start_y, 1, _width-2, A_STANDOUT, 0, NULL);
    }
    mvwprintw(_menu_win,_opt_num+start_y+1,_width/2 -5," x to select option");
    refresh();
}

int Tmenu::handle_input()
{
    chtype input = wgetch(_menu_win);
    switch (input)
    {
    case KEY_ENTER: case 'x':
        return _selected_opt;
        break;
    case KEY_UP: 
        if(_selected_opt>0)
            _selected_opt--;
        break;
    case KEY_DOWN:
        if(_selected_opt<_opt_num-1)
            _selected_opt++;
        break;
    default:
        break;
    }
        return -1;// -1 mean the user still didnt press entre an any option on the screan
}

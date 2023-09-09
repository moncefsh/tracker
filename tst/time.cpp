#include "../src/Ttime.h"
#include "../src/Tmenu.h"
#include <thread>

#define BOARD_DIM 13
#define BOARD_ROWS BOARD_DIM
#define BOARD_COLS BOARD_DIM* 2.5


enum OPTIONS
{
    PASS=-1,
    TIMER=0,
    CHRONO=1,
    QUIT=2
};

int main()
{
    initscr();
    refresh();
    noecho();
    start_color();
    init_pair(1,COLOR_WHITE,COLOR_BLUE);
    curs_set(0);
    std::string ops[3]={"chrono" ,  "timer" ,"quit"};
    Tmenu  gmenu(BOARD_ROWS,BOARD_COLS,ops,3);

    bool in_menu=true;
    while(in_menu)
    {
        gmenu.draw();
        int key=gmenu.handle_input();
        switch (key)
        {
        case PASS:
            break;
        case TIMER:
        { 
            in_menu=false;
            gmenu.clear();
            gmenu.refresh();
            break;
        }
        case QUIT:
            endwin();
            return 0;
        case CHRONO:
        { 
            endwin();
            return 0;
        }
        default:
            break;
        }
    }

    



}





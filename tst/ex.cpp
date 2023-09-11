#include <iostream>
#include <thread>
#include <chrono>

typedef std::chrono::duration<double> duration;

/************************************************************************
 *      some implementation functios used to block cin in constant periods 
 *      of time , then check if there is a certain key ,which is an example 
 *      of flag() function tthe argument of  Ttimer::interept function 
 *************************************************************************/

// Set std::cin to non-blocking mode
/*
void setNonBlockingInput()
{
#ifdef _WIN32
    _setmode(_fileno(stdin), _O_TEXT);
#else
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
#endif
}

// Restore std::cin to blocking mode
void restoreBlockingInput()
{
#ifdef _WIN32
    _setmode(_fileno(stdin), _O_TEXT);
#else
    struct termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    oldt.c_lflag |= ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif
}

// Check if a key is pressed
bool isKeyPressed()
{//an intereption flag
#ifdef _WIN32
    return _kbhit();
#else
    fd_set rfds;
    struct timeval tv = { 0, 0 };
    int stdin_fileno = fileno(stdin);

    FD_ZERO(&rfds);
    FD_SET(stdin_fileno, &rfds);

    int retval = select(stdin_fileno + 1, &rfds, nullptr, nullptr, &tv);

    bool stopSection = false;
     if( (retval > 0) && (FD_ISSET(stdin_fileno, &rfds)))
    {
        
        std::string userInput;
        std::cin >> userInput;
            if (userInput == "stop") 
                stopSection = true;
    }
#endif
    return stopSection;

}*/


#include "Ttime.h"
#include <cstdlib>
#include <thread>
#include <string>
#ifdef _WIN32
#include <conio.h>
#else
#include <unistd.h>
#include <termios.h>
#endif

void Tchrono::start()
{
    //started the chrono
    if(!_isit_started)
    {
        _start_time = std::chrono::system_clock::now();//storing the current time
        _isit_started=true;// indecating that the chrono is in an active state
    }else
    {   //in case the client called start when the chrono  is already active
        throw std::invalid_argument("Tchrono::start:  the chrono is already started");
    }//should throw an exeption
    
}

void Tchrono::stop()
{
    //stop the chrono (kill it)

    if(_isit_started)
    {
        _end_time = std::chrono::system_clock::now();//storing the time whin the chrono stoped
        _isit_ended=true;   //indeciting that the chrono is stoped
        _dur=_end_time - _start_time; //calculing durration
        return ;
    }else
    {
        throw std::invalid_argument("Tchrono::end the chrono is not yet started ");
    }    
}



duration Tchrono::get_duration() 
{
    if(_isit_started && !_isit_ended){
        //this handle when the chrono is not stoped yet so it give the dur between the starting point
        //and the time when the function is called
        duration ddur = chrono::system_clock::now()- _start_time;
        return ddur;// time still didnt stop
    }
    
    // otherwise the _dur is already computed so we can return it 
    return _dur;
}

void Tchrono::reset() 
{
    //still dont know what for , but reset all data membres
    _start_time = time_point();
    _end_time = time_point();
    _isit_started=false;
    _isit_ended=false;
}

/************************************************************************
 *      some implementation functios used to block cin in constant periods 
 *      of time , then check if there is a certain key ,which is an example 
 *      of flag() function tthe argument of  Ttimer::interept function 
 *************************************************************************/

// Set std::cin to non-blocking mode
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

}


void Ttimer::start(int ddur,bool intereption_flag())
{
    _session_time=ddur;
    Tchrono::start();
    setNonBlockingInput();  // Set std::cin to non-blocking mode
    auto start = std::chrono::steady_clock::now();
    while ((std::chrono::duration<double>(std::chrono::steady_clock::now() - start).count() < ddur) ) {
        if(intereption_flag()) 
        {
            _isit_interept=true;
            break; 
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    restoreBlockingInput();  // Restore std::cin to blocking mode
    // Stop the timer
    stop();
}










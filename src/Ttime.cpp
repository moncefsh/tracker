#include "Ttime.h"

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
    //still dont know what for
    _start_time = time_point();
    _end_time = time_point();
    _isit_started=false;
    _isit_ended=false;
}






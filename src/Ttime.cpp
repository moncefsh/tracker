#include "Ttime.h"
#include <cstdlib>
#include <thread>
#include <string>
#include <iomanip>
#include <sstream>
#ifdef _WIN32
#include <conio.h>
#else
#include <unistd.h>
#include <termios.h>
#include <stdio.h> 
#endif


std::string dur_to_string(duration dur)
{
    if(dur < 0.0s)//in case duration is negative
        throw std::invalid_argument("dur_to_string: negative durration ");
    auto h = chrono::duration_cast<chrono::hours>(dur);
    dur -= h;
    auto m = chrono::duration_cast<chrono::minutes>(dur);
    dur -= m;
    auto s =chrono::duration_cast<chrono::seconds>(dur);
    std::string result;
    if (h < 10h)
        result.push_back('0');
    result += to_string(h/1h);
    result += ':';
    if (m < 10min)
        result.push_back('0');
    result += to_string(m/1min);
    result += ':';
    if (s < 10s)
        result.push_back('0');
    result += to_string(s/1s);
    return result;


}

duration string_to_dur(const std::string& str) {
    int h, m, s;

    if (sscanf( str.c_str() ,"%2d:%2d:%2d",&h,&m,&s)!=3) {
        throw std::invalid_argument("string_to_dur: invalid input format hh:mm:ss");
    }

    duration dur = std::chrono::hours(h) + std::chrono::minutes(m) + std::chrono::seconds(s);
    return dur;
}

//                                  Tchrono

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
        _dur =_end_time - _start_time; //calculing durration
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

//-------------------------------------------------------------------------------


//                     Ttimer

void Ttimer::start(duration ddur,bool interruption_flag(Ttimer *t))
{
    _session_time=ddur;
    Tchrono::start();
    auto start = std::chrono::steady_clock::now();
    int val=0;
    while (std::chrono::steady_clock::now()-start < ddur)
    {
        if(interruption_flag(this))
            break;
    }
    this->stop();
}

string Ttimer::get_time_remaining()
{
    duration remaining = this->_session_time - this->get_duration();
    if(remaining >=0s)
        return dur_to_string(remaining);
    return "";
}

bool interrupt_fromCin(Ttimer * t)
{
    //the function is an example of intereption_flag 
    //the function is called inside a while loop so for evry 400ms the function
    //will check if we got a the key from cin , in case is yes we return true , otherwise false
    static bool promp=true;
    std::string check;
    std::thread t1([&](){
        
        std::cin>>check;
    });
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    t1.detach();
    if(check == STOP)   //KEY is macro define in Ttime.h "stop"
        return true;
    else if(check == TIME)
        cout<< dur_to_string(t->get_duration())<<"\n";
    if(check!="")
        cout<<"1:: ";
    return false;
}




//                      operations && helpers functions



ostream& operator<<(ostream& os,Tchrono ch)
{
    if(!ch.isit_started())
        return os;
    time_t st= chrono::system_clock::to_time_t(ch.start_time());

    os<<"start "<<put_time(std::gmtime(&st), "%c")<<endl;
    if(ch.isit_ended())
    {
        time_t et= chrono::system_clock::to_time_t(ch.end_time());
        os<<"end "<<put_time(std::gmtime(&et),"%c")<<endl;   
    }
    os <<"duration "<<dur_to_string(ch.get_duration())<<endl;
    return os;
}



















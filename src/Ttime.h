// time facilites for the programme
// useing ctime library and other time related labriries

#pragma once

#include <ctime>
#include <chrono>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <exception>

using namespace std;
// represent a point in time , used to store a an exact time date
typedef chrono::system_clock::time_point time_point;
// duration stores a duration(as double) of time in second 
typedef std::chrono::duration<double> duration;




/*************************************************************************************************
 * Tchrono class:
 *              Tchrono work as stopwatch , when you call it's method strat() the object store 
 *              a time_point that indecit the time of calling the method,  after calling stop 
 *              the object store in other varaible the current time , and then by taking the
 *              deffrence between the two time_points we get the durration that watch was  working 
 *              
 * ***********************************************************************************************/


class Tchrono
{  
public:
    Tchrono(): _dur(),_isit_started(false) ,_isit_ended(false)
                ,_start_time(time_point()),_end_time(time_point()) {}
    virtual void  start() ;//start the chrono
    virtual void stop() ;//stop the chrono
    duration  get_duration();//it gives the duration that the chrono was working on it
    bool isit_started(){return _isit_started;}
    bool isit_ended(){return _isit_ended;}
    time_point start_time() const {return _start_time;}
    time_point end_time() const {return _end_time;}
    void resume(); // in case the user want to continue after stoping 
protected:
    time_point _start_time;
    time_point _end_time;
    duration _dur; //in second
    bool _isit_started;
    bool _isit_ended; 
};



/*************************************************************************************************
 * Ttimer class: subclass of Tchrono
 *              still work as Tchrono  but the defrence is that the client can set a duration 
 *              that represent the time between calling start and stop , and the client can i
 *              interept that duration by some signal(flag) that will cause the programme to call 
 *              the stop() method
 * ***********************************************************************************************/



class Ttimer: public Tchrono
{
public:
    Ttimer()
        :Tchrono(),session_time(0),isit_interept(false){}
    void start(int dur,bool interaption_flag()); 
    bool isit_finished(){return isit_interept;}
    bool interept(bool flag());
    int session() const {return session_time;}
private:
    int session_time;//in second;
    bool isit_interept;//is duration == session_time
};










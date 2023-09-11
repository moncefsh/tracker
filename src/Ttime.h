// time facilites for the programme
// useing ctime library and other time related labriries

#pragma once

#include <ctime>
#include <chrono>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <exception>
#include <string>


#define KEY "stop"


using namespace std;
// represent a point in time , used to store a an exact time date
typedef chrono::system_clock::time_point time_point;
// duration stores a duration(as double) of time in second 
typedef std::chrono::duration<double> duration;


//funion that transforme duration to HH:MM:ss forma
std::string dur_to_string(duration dur);
duration string_to_dur(const std::string& str);


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
    //methods
    Tchrono(): _dur(chrono::seconds(0)),_isit_started(false) ,_isit_ended(false)
                ,_start_time(time_point()),_end_time(time_point())  {}
    virtual void  start() ;//start the chrono
    void stop() ;//stop the chrono(kill it)
    duration  get_duration();//it gives the duration that the chrono was working on it
    bool isit_started(){return _isit_started;}
    bool isit_ended(){return _isit_ended;}
    time_point start_time() const {return _start_time;}
    time_point end_time() const {return _end_time;}
    void reset(); 
protected:
    time_point _start_time;
    time_point _end_time;
    duration _dur; //in second
    bool _isit_started;
    bool _isit_ended; 
};

ostream& operator<<(ostream& os,Tchrono ch);//output data of the chrono object in a human readebale way



/*************************************************************************************************
 * Ttimer class: subclass of Tchrono
 *              still work as Tchrono  but the defrence is that the client can set a duration 
 *              that represent the time between calling start and stop , and the client can i
 *              interept that duration by some signal(flag) that will cause the programme to call 
 *              the stop() method
 * ***********************************************************************************************/

bool interrupt_fromCin();
    //the function is an example of intereption_flag 
    //the function is called inside a while loop so for evry 400ms the function
    //will check if we got a the key from cin , in case is yes we return true , otherwise false



class Ttimer: public Tchrono
{
public:
    Ttimer()
        :Tchrono(),_session_time(chrono::seconds(0)),_isit_interept(false){}
    void start(duration dur,bool interruption_flag() = interrupt_fromCin ); 
    bool isit_finished(){return _isit_interept;}


    //bool interept(bool flag()); //flag is a boolen function that check from some conditions to interept the  timer
                                //for example it may check (in constant time intervales ) for some key_word in some input stream
    string get_time_remaining();
    duration session() const {return _session_time;}

private:
    duration _session_time;//in second;
    bool _isit_interept;//is duration == session_time
};


//ostream& operator<<(ostream& os,Ttimer tt);//output data of the timer object in a human readebale way













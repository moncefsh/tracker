#include "../Ttime.h"
#include <thread>


void run_chrono()
{
    Tchrono * t= new Tchrono();
    cout<<"the chrono start now! \n";
    cout<<"to stop write 'stop'\n";
    cout<<"to see time type 'time'\n\n";
    t->start();
    string str;
    cout<<"1:: ";
    while(cin>> str)
    {
        cout<<"1:: ";
        if(str=="stop")
        {
            t->stop();
            break;
        }
        if(str=="time")
        {
            cout<<dur_to_string(t->get_duration())<<endl;
            cout<<"1:: ";
        }
    }
    cout<<endl<<*t<<endl;
}

void run_timer()
{
    Ttimer *timer= new Ttimer();

    string stdur;
    cout<<"entre duration of session : ";
    cin>> stdur ;
    duration dur = string_to_dur(stdur);
    cout<<endl;
    timer->start(dur);

    
    cout<<endl<<*timer;
    delete timer; // Don't forget to clean up

}

void Ctimer()
{
    cout<<"to start timer entre 'timer' "<<endl;
    cout<<"to start timer entre 'chrono' "<<endl;
    cout<<"to exit entre 'exit'"<<endl<<">> : ";
    string str;
    while(cin>>str)
    {
        if(str=="timer")
        { 
            run_timer();
            break;
        }
        else if(str=="chrono")
        { 
            run_chrono();
            break;
        }
        else if(str == "exit")
        {
            cout<<"exiting the timer"<<endl;
            return ;
        }
    }
    

}


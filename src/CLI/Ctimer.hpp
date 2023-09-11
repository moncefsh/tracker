#include "../Ttime.h"
#include <thread>

void countdown(Ttimer* timer) {
    while (timer->isit_started() && !timer->isit_ended()) {
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Wait for 1 second
        std::cout << "Time left: " << timer->get_time_remaining() << "\r \n" << std::flush;
    }
    std::cout << std::endl;
}

void Ctimer()
{
    cout<<"to start timer entre 'start' "<<endl;
    cout<<"to exit entre 'exit'"<<endl<<">> : ";
    string str;
    while(cin>>str)
    {
        if(str=="start")
        { 
            break;
        }
        else if(str == "exit")
        {
            cout<<"exiting the timer"<<endl;
            return ;
        }
    }
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
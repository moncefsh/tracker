#include "../src/Ttime.h"
#include <thread>
int main()
{
    Tchrono ch;
    ch.start();
    std::this_thread::sleep_for(5s);
    ch.stop();
    cout<<ch;
    Ttimer tt;
    tt.start(std::chrono::seconds(10));
    cout<<tt;



}





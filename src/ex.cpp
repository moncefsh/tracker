#include <iostream>
#include <thread>
#include <chrono>

typedef std::chrono::duration<double> duration;



int getVal()
{
    int val=0;
    std::thread t1([&](){
        std::cin>>val;
    });
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    t1.detach();
    return val;
}

int main() {
    duration s= std::chrono::seconds(10);
    duration t= std::chrono::seconds(1);
    auto start = std::chrono::steady_clock::now();
    int val=0;
    while (std::chrono::steady_clock::now()-start < s)
    {
        if((val=getVal()))
            break;


    }
    std::cout<<val<<std::endl;

    
}
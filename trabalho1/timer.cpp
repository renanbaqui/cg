#include <iostream>
#include <chrono>
#include <thread>
 
int main()
{
    using namespace std::chrono_literals;

    for (int i = 0; i < 60; i++)
    {
        std::this_thread::sleep_for(1s);
        std::cout << i << std::endl;
    }
}

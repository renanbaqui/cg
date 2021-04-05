#include <iostream>
#include <random>

using namespace std;

int main()
{
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_real_distribution<> distr(-4, 4); // define the range

    float r1 = distr(gen);
    
    cout<<r1;
}

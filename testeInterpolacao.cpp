#include <iostream>
#include <random>

using namespace std;

int main()
{
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
 
    std::uniform_real_distribution<> distr(0, 3); // define the range
    float p1y = distr(gen);
    
    std::uniform_real_distribution<> distr2(-5, -2); // define the range // distr2
    float p2x = distr2(gen);
    
    std::uniform_real_distribution<> distr3(2, 5); // define the range // distr3
    float p3x = distr3(gen);
    
    std::uniform_real_distribution<> distr4(0, 2); // define the range // distr4
    float p3y = distr4(gen);
    
    std::uniform_real_distribution<> distr5(0, 2); // define the range // distr5
    float p4y = distr5(gen);    
    
/*    
    cout<<p1y;
    cout<<"\n";
    cout<<p2x;
    cout<<"\n";
    cout<<p3x;
    cout<<"\n";
    cout<<p3y;
    cout<<"\n";
*/    
    float p4x = (p2x + p3x)/2;
    float movepetrel = 1;

    float L0 = (((movepetrel - p4x)*(movepetrel - p3x))/((p2x - p4x)*(p2x - p3x)));
    float L1 = (((movepetrel - p2x)*(movepetrel - p3x))/((p4x - p2x)*(p4x - p3x)));
    float L2 = (((movepetrel - p2x)*(movepetrel - p4x))/((p3x - p2x)*(p3x - p4x)));
    
    cout<<p4x;
    cout<<"\n";
    cout<<L0;
    cout<<"\n";
    cout<<L1;
    cout<<"\n";
    cout<<L2;
    cout<<"\n";
}

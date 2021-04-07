#include <iostream>
#include <random>

using namespace std;

float p1, p2, p3;
std::random_device rd; // obtain a random number from hardware
std::mt19937 gen(rd()); // seed the generator
std::uniform_real_distribution<> distr(0, 3); // define the range
std::uniform_real_distribution<> distr2(-5, -2); // define the range // distr2
std::uniform_real_distribution<> distr3(2, 5); // define the range // distr3


void gera(){
    
    p1 = distr(gen);
        
    
    p2 = distr2(gen);
        
    
    p3 = distr3(gen);
}

int main()
{

    gera();
    
    cout<<p1;
    cout<<"\n";
    cout<<p2;
    cout<<"\n";
    cout<<p3;
    cout<<"\n\n";

    gera();

    cout<<p1;
    cout<<"\n";
    cout<<p2;
    cout<<"\n";
    cout<<p3;
    cout<<"\n";

}

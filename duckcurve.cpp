
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <cstdlib> 
#include <ctime> 
  
#include "bess.h"
#include "enode.h"

const double divfac=256.0*128;

// dt = 5 minutes, kWh = kW * dt * 12
const double every5min = 12;
const double dtphys= 8.0/86400.0;

/*
 add in time and splitting solar into the load and the grid with a time dependent ratio

t is in seconds

solar starts at 9*3600
solar ends at 20*3600
solar -> storage 100*(1 - abs(t - 15*3600)/ 6 hrs = 72 dt)
storage -> solar = solar -> storage

Stochastic driving:
The three variables are the time interval between spikes, the duration of the spike and the power reduction

*/

// bess.cpp
int main(int argc, char* argv[])
{
    ESS mybess(13.5, 5.5, 120, 5.6);
    Enode housenode;
    cout << " level " << mybess.get_level();
    double testv = housenode.run_test();
    cout << " power " << testv << endl;
    double driv[3];  double tintv, durat, powrd;
    fstream outf("pinkfloyd.csv", ios::out);

 //TESTING NODE, x1 + x2 + x3 + x4 = 0
    housenode.set_tag(3);
    housenode.set_val(0, 3.3);
    housenode.set_val(1, -1.8);
    housenode.set_val(2, 0.9);

    double myc = housenode.get_current();
    cout << " current " << myc << endl;

//start 11 hour daytime fill of battery, avoiding net metering at peak, 12 intervals of 5 minutes per hour
//empty battery after breakfast
    mybess.set_level(0.0);	
    double tval = every5min*9*dt;
    for (int ii = 0; ii < every5min*11; ii++)
{ 
  double temp=5.0*(1.0 - 1.1*fabs(tval - 180*dt)/72.0/dt);
  temp = max(temp, 0.0);
  double sol = sin(3.1416*ii/every5min/11); 
   if (temp < 0) cout << " negative solar power " << temp << endl;
       mybess.inc_level(sol*(5.0-temp)*dt);	
 tval += dt;
}
cout << " level " << mybess.get_level();

double t_elaps = 0.0;
double t_elect = 0.0; 
//random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr))); 
double sf=1.0; //stochastic function
while (t_elaps < 7500.0)
{
  
    for (int count=0; count <= 3; ++count)driv[count] = std::rand()/divfac/divfac/2.0 ;
    
    tintv = 2*5*300*dtphys*driv[0]; // 10 hours
    durat=300*dtphys*driv[1]; // T
    powrd= 1.0-driv[2];


    outf << setw(14) << setprecision(8) << t_elect << ',';
    outf << setw(14) << setprecision(8) << t_elaps << ',';
    outf << setw(14) << setprecision(8) << durat << ',';
    outf << setw(14) << setprecision(8) <<  powrd << ',';
    outf << setw(14) << setprecision(8) << sf << endl;
    
    if(t_elaps > tintv && t_elaps <= tintv + durat){
	    sf =powrd;
	} 
	    else if (t_elaps > tintv + durat) 
    {
       sf = 1.0;
       t_elaps = 0.0;
}
else   sf = 1.0;
    t_elect += dtphys;
    t_elaps += dtphys;

}
outf.close();
    return 0;
}

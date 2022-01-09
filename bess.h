#ifndef BESS_STOR_H
#define BESS_STOR_H

const double tunit=1.0/3600.0; // seconds in an  hour world.
const double dt = 300.0*tunit;

using namespace std;

/* bess.h, BESS class. Need to follow Kirchoff’s laws for current, use current instead of power to keep close to physics. Q is an integration of I but we are given an energy as an integral of I*V. Should be pretty close to the same. 
*/

class ESS {
private:
   double capacity;
   double level;
   double current;
   double maxpow;

   double voltage; // Power = I*V
   int charging; // 0 or 1
   int state; // empty, intermediate, full
public:
    ESS(); //capacity = 13.5 kWh
    ESS(double cap, double level_in, double volt, double mpow) {capacity = cap; level = level_in; voltage = volt; maxpow = mpow ;}
    ~ESS(){}; //capacity = 13.5 kWh
    void charge(double current, double voltage);
   double get_level() { return level; }
   void set_level(double in_level) { level = in_level; }
   void inc_level(double inclev) { level += inclev; }

};

#endif

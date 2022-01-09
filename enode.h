#ifndef ENODE_STOR_H
#define ENODE_STOR_H

#include <vector> 


/* enode.h, Power or current node class. Need to follow Kirchoff’s laws for current, use current instead of power to keep close to physics. Q is an integration of I but we are given an energy as an integral of I*V. Should be pretty close to the same. 
*/

/* procedure is to set value in node for 3 values, use node to calculate the rest. This may be too complicated, but can be fixed */
class Enode {
private:
	std::vector<double> current;
   int tag; // 0 is grid, 1 is load, 2 is solar, 3 is storage
public:
    Enode(); //capacity = 13.5 kWh
    ~Enode(){}; //capacity = 13.5 kWh
    double get_current();
    double run_test();
    double get_power() { return 120.0*current[tag]; }
    void set_val(int indx, double val);
    void set_tag(int tag_in) { tag = tag_in; }
};

#endif

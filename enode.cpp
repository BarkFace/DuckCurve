
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>

#include "enode.h"

Enode::Enode() 
{
   for (int ii =0;ii < 4;ii++)current.push_back(0);
}

double Enode::run_test()
{
    double powbess = 5.6;
    double pow_sol = 5.0;
    double xu = 2.0 - 0.93*pow_sol - 0.88*powbess ;
    return xu;
}

double Enode::get_current()
{
   double mask[4];
   for (int ii =0;ii < 4;ii++)mask[ii]=-1.0;
   mask[tag]=0.0;
   double curr=0;
	   for (int ii =0; ii < 4;ii++)
{
	std::cout << " line # " << ii << " current " << curr << std::endl;
curr += current[ii]*mask[ii];
}
   return curr;
}

void Enode::set_val(int indx, double val)
{
   current[indx] = val;
}


#include <cmath>
#include <fstream>
#include <iostream>
using namespace std;

double powerlaw(double x)
{
  return 5*pow(x,-1.1);
}

double bpl(double x)
{
  double x_b=5;
  double f_b=10;
  double gamma1=-0.8;
  double gamma2=-1.5;
  if(x<x_b)
    {
      return f_b*pow(x,gamma1)/pow(x_b,gamma1);
    }
  else
    {
      return f_b*pow(x,gamma2)/pow(x_b,gamma2);
    }
}



int main()
{
  double x,y,x1,x2,y1,y2;
  while(cin>>x>>x1>>x2>>y>>y1>>y2)
    {
      cout<<x<<"\t"<<y<<"\t"<<y-y1<<"\t"<<y+y2<<endl;
    }
}

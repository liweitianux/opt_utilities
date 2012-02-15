#include "opt.h"
#include <iostream>
using namespace std;

double foo(const double* p)
{
  return p[0]*p[0]+(p[1]-1)*(p[1]-1);
}

int main()
{
  double p[2]={1000,1000};
  optimize_powell(foo,2,p,1e-40);
  optimize_powell(foo,2,p,1e-40);
  cout<<p[0]<<"\t"<<p[1]<<endl;
}

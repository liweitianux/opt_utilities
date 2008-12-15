#include <math.h>

char p1name[2]="k";
char p2name[2]="b";

int main(int argc,char* argv[])
{}


int get_num_params()
{
  return 2;
}

const char* get_param_name(int n)
{
  if(n==0)
    {
      return p1name;
    }
  return p2name;
}

double get_default_value(int n)
{
  if(n==0)
    return 1;
  return 0;
}

double calc_model(double x,double p[])
{
  return p[0]*x+p[1];
}



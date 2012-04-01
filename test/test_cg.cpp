#include <methods/conjugate_gradient/conjugate_gradient.hpp>
#include <methods/powell/powell_method.hpp>
#include <vector>
using namespace std;

using namespace opt_utilities;

class foo
  :public diff_func_obj<double,vector<double> >
{
  foo* do_clone()const
  {
    return new foo(*this);
  }

  double do_eval(const vector<double>& p)
  {
    static int call_cnt=0;
    ++call_cnt;
    cerr<<call_cnt<<endl;
    double result=0;
    for(int i=0;i<p.size();++i)
      {
	result+=p[i]*p[i];
      }
    return result;
  }

  vector<double> do_gradient(const vector<double>& p)
  {
    static int call_cnt=0;
    ++call_cnt;
    cerr<<call_cnt<<endl;
    vector<double> result(p.size());
    for(int i=0;i<p.size();++i)
      {
	result[i]=2*p[i];
      }
    return p;
  }
};


int main()
{
  optimizer<double,vector<double> > opt;
  //opt.set_opt_method(conjugate_gradient<double,vector<double> >());
  opt.set_opt_method(powell_method<double,vector<double> >());
  opt.set_func_obj(foo());
  std::vector<double> p(2);
  p[0]=p[1]=4;
  opt.set_start_point(p);
  p=opt.optimize();
  cout<<p[0]<<"\t"<<p[1]<<endl;
}

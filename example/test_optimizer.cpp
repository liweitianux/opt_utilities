#include <core/optimizer.hpp>
#include <methods/powell/powell_method.hpp>
#include <methods/aga/aga.hpp>
#include <vector>
#include <iostream>


//declear a class derived from func_obj
class foo
  :public opt_utilities::func_obj<double,std::vector<double> >
//                              ^^^^^^^^double is the return type
//                                      vector is the parameter type
{
  double do_eval(const std::vector<double>& p)
  {
    double result=0;
    for(int i=0;i<p.size();++i)
      {
	result+=p[i]*p[i];
      }
    return result;
  }

  foo* do_clone()const
  {
    return new foo(*this);//default implement of the do_clone
  }
};


int main()
{
  //define an optimizer object
  opt_utilities::optimizer<double,std::vector<double> > op;
  //set the optimization method
  op.set_opt_method(opt_utilities::powell_method<double,std::vector<double> >());
  //attach the object function
  op.set_func_obj(foo());

  //define the starting point
  std::vector<double> p(3);
  p[0]=p[1]=p[2]=10;
  
  //set the starting point
  op.set_start_point(p);  
  std::cout<<"starting optimization from:"<<
    p[0]<<" "<<p[1]<<" "<<p[2]<<std::endl;

  //set the precision
  op.set_precision(1E-6);
  //perform the optimization
  p=op.optimize();

  //output the result
  std::cout<<"optimization result:"<<
    p[0]<<" "<<p[1]<<" "<<p[2]<<std::endl;


  /////////////////////////////////////////////

  //Let's change another method
  op.set_opt_method(opt_utilities::aga_method<double,std::vector<double> >());
  //define the lower and upper limit
  p[0]=p[1]=p[2]=-10;
  op.set_lower_limit(p);
  p[0]=p[1]=p[2]=10;
  op.set_upper_limit(p);
  //set the start point
  op.set_start_point(p);
  //set precision
  op.set_precision(1E-10);
  //start optimize
  p=op.optimize();
  std::cout<<"optimization result:"<<
    p[0]<<" "<<p[1]<<" "<<p[2]<<std::endl;
}

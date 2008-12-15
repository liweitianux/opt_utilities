#include <blitz/array.h>

using namespace blitz;

#include <core/opt_traits.hpp>

namespace opt_utilities
{
  template <typename TX>
  void set_element(blitz::Array<double,1>& x,size_t i,TX v)
  {
    x(i)=v;
  }

  
  inline const double& get_element(const blitz::Array<double,1>& x,size_t i)
  {
    return x(i);
  }
  
  inline size_t get_size(const Array<double,1>& x)
  {
    return x.extent(0);
  }

  inline void resize(Array<double,1>& x,size_t s)
  {
    x.resize(s);
  }

  inline Array<double,1>& opt_eq(Array<double,1>& lhs, const Array<double,1>& rhs)
  {
    lhs.resize(rhs.extent(0));
    lhs=rhs.copy();
    return lhs;
  }

  template <>
  class value_type_trait<Array<double,1> >
  {
  public:
    typedef double value_type;
  };

  template <>
  class value_type_trait<const Array<double,1> >
  {
  public:
    typedef double value_type;
  };
}

#include <statistics/chisq.hpp>
#include <core/optimizer.hpp>
#include <core/default_data_set.hpp>
#include <methods/powell/powell_method.hpp>
#include <methods/gsl_simplex/gsl_simplex.hpp>
#include <core/fitter.hpp>
using namespace std;
#include <fstream>
#include <vector>
#include <blitz/array.h>
//#include "gmpxx.h"
using namespace std;
//using namespace opt_utilities;
using namespace blitz;

class foo
  :public opt_utilities::func_obj<double,blitz::Array<double,1> >
{
  typedef blitz::Array<double,1> pT;
  double do_eval(const pT& x)
  {
    return x(0)*x(0)+x(1)*x(1);
  }
  
  foo* do_clone()const
  {
    return new foo(*this);
  }
};

class lin1d
  :public opt_utilities::model<double,double,blitz::Array<double,1> >
{
private:
  opt_utilities::model<double,double,Array<double,1> >* do_clone()const
  {
    return new lin1d(*this);
  }
public:
  lin1d()
  {
    this->push_param_info(opt_utilities::param_info<Array<double,1> >("k",1));
    this->push_param_info(opt_utilities::param_info<Array<double,1> >("b",0));
  }
  
public:
  double do_eval(const double& x,const Array<double,1>& param)
  {
    return x*opt_utilities::get_element(param,(size_t)0)+opt_utilities::get_element(param,(size_t)1);
  }
  
private:
  std::string do_to_string()const
  {
    return "linear model\n"
      "y=k*x+b\n";
  }
};



int main()
{
  opt_utilities::fitter<double,double,Array<double,1>,double> f;
  //opt_utilities::optimizer<double,Array<double,1> > opt;
  opt_utilities::powell_method<double,Array<double,1> > pm;
  f.set_method(pm);
  
  Array<double,1> a(2);
  a=2,4;

  opt_utilities::default_data_set<double,double> ds;

  for(double x=0;x<10;x+=.1)
    {
      opt_utilities::data<double,double> d;
      d.set_x(x);
      d.set_x_lower_err(0);
      d.set_x_upper_err(0);
      d.set_y(x*3+4);
      d.set_y_lower_err(.1);
      d.set_y_upper_err(.1);
      ds.push_back(d);
    }
  f.load_data(ds);
  f.set_model(lin1d());
  f.set_statistic(opt_utilities::chisq<double,double,blitz::Array<double,1>,double>());
  cout<<f.fit();
}


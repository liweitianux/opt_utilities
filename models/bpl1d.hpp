#ifndef BROKEN_POWER_LAW_MODEL_H_
#define BROKEN_POWER_LAW_MODEL_H_
#define OPT_HEADER
#include <core/fitter.hpp>
#include <cmath>

namespace opt_utilities
{
  template <typename T>
  class bpl1d
    :public model<T,T,std::vector<T>,std::string>
  {
  private:
    model<T,T,std::vector<T> >* do_clone()const
    {
      return new bpl1d<T>(*this);
    }

    const char* do_get_type_name()const
    {
      return "broken power law";
    }
  public:
    bpl1d()
    {
      this->push_param_info(param_info<std::vector<T> >("bpx",1));
      this->push_param_info(param_info<std::vector<T> >("bpy",1));
      this->push_param_info(param_info<std::vector<T> >("gamma1",1));
      this->push_param_info(param_info<std::vector<T> >("gamma2",1));
    }

    T do_eval(const T& x,const std::vector<T>& param)
    {
      T x_b=get_element(param,0);
      T f_b=get_element(param,1);
      T gamma1=get_element(param,2);
      T gamma2=get_element(param,3);
      if(x<x_b)
	{
	  return f_b*pow(x,gamma1)/pow(x_b,gamma1);
	}
      else
	{
	  return f_b*pow(x,gamma2)/pow(x_b,gamma2);
	}
    }


  private:
    std::string do_to_string()const
    {
      return "broken power law\n"
	"y=y_b*(x/x_b)^gamma1 for x<x_b\n"
	"y=y_b*(x/x_b)^gamma2 otherwise\n";
    }
  };
}



#endif
//EOF

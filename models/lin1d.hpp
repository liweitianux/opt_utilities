#ifndef LINEAR_MODEL_H_
#define LINEAR_MODEL_H_
#include <core/fitter.hpp>
#include <cmath>

namespace opt_utilities
{
  template <typename T>
  class lin1d
    :public model<T,T,std::vector<T>,std::string>
  {
  private:
    model<T,T,std::vector<T> >* do_clone()const
    {
      return new lin1d<T>(*this);
    }
  public:
    lin1d()
    {
      this->push_param_info(param_info<std::vector<T> >("k",1));
      this->push_param_info(param_info<std::vector<T> >("b",0));
    }

  public:
    T do_eval(const T& x,const std::vector<T>& param)
    {
      return x*get_element(param,0)+get_element(param,1);
    }

  private:
    std::string do_to_string()const
    {
      return "linear model\n"
	"y=k*x+b\n";
    }
  };
};



#endif
//EOF
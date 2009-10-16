#ifndef GAUSS_MODEL_H_
#define GAUSS_MODEL_H_
#define OPT_HEADER
#include <core/fitter.hpp>
#include <cmath>

namespace opt_utilities
{
  template <typename T>
  class gauss1d
    :public model<T,T,std::vector<T>,std::string>
  {
  private:
    model<T,T,std::vector<T> >* do_clone()const
    {
      return new gauss1d<T>(*this);
    }

    const char* do_get_type_name()const
    {
      return "1d gaussian";
    }
  public:
    gauss1d()
    {
      this->push_param_info(param_info<std::vector<T> >("N",1));
      this->push_param_info(param_info<std::vector<T> >("x0",0));
      this->push_param_info(param_info<std::vector<T> >("sigma",1));
    }

  public:
    T do_eval(const T& x,const std::vector<T>& param)
    {
      T N=get_element(param,0);
      T x0=get_element(param,1);
      T sigma=get_element(param,2);
      T y=(x-x0)/sigma;
      return N*exp(-y*y);
    }

  private:
    std::string do_to_string()const
    {
      return "Gaussian model\n"
	"y=N*exp(-(x-x0)^2/sigma^2\n";
    }
  };
}



#endif
//EOF

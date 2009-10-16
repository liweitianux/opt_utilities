#ifndef BETA_MODEL_H_
#define BETA_MODEL_H_
#define OPT_HEADER
#include <core/fitter.hpp>
#include <cmath>
#include <iostream>

namespace opt_utilities
{
  template <typename T>
  class beta1d
    :public model<T,T,std::vector<T>,std::string>
  {
  private:
    model<T,T,std::vector<T> >* do_clone()const
    {
      return new beta1d<T>(*this);
    }
    
    const char* do_get_type_name()const
    {
      return "1d beta model";
    }
  public:
    beta1d()
    {
      this->push_param_info(param_info<std::vector<T> >("S0",1));
      this->push_param_info(param_info<std::vector<T> >("rc",10));
      this->push_param_info(param_info<std::vector<T> >("beta",2./3.));
      this->push_param_info(param_info<std::vector<T> >("bkg",0));
    }


    T do_eval(const T& x,const std::vector<T>& param)
    {
      T S0=get_element(param,0);
      T r_c=get_element(param,1);
      T beta=get_element(param,2);
      T bkg=get_element(param,3);

      return bkg+S0*pow(1+(x*x)/(r_c*r_c),-3*beta+static_cast<T>(.5));
    }

    std::string do_to_string()const
    {
      return "Beta model\n"
	"S=S0*(1+(r/rc)^2)^(-3*beta+0.5)\n";
    }
  };
}



#endif
//EOF

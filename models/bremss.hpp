#ifndef BREMSS_MODEL_H_
#define BREMSS_MODEL_H_
#define OPT_HEADER
#include <core/fitter.hpp>
#include <cmath>

namespace opt_utilities
{
  template <typename T>
  class bremss
    :public model<T,T,std::vector<T>,std::string>
  {
  private:
    model<T,T,std::vector<T> >* do_clone()const
    {
      return new bremss<T>(*this);
    }
  public:
    bremss()
    {
      this->push_param_info(param_info<std::vector<T> >("norm",1));
      this->push_param_info(param_info<std::vector<T> >("kT",1));
    }

    T do_eval(const T& x,const std::vector<T>& param)
    {
      T norm=get_element(param,0);
      T kT=get_element(param,1);
      
      return norm*sqrt(kT)*exp(-x/kT);
    }

  private:
    std::string do_to_string()const
    {
      return "Simplified bremss model\n"
	"flux=norm*kT^0.5*e^{-E/kT}\n";
    }
  };
}



#endif
//EOF

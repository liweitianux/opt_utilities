/**
   \file quad_pl.hpp
   \brief power law model
   \author Junhua Gu
 */


#ifndef QUAD_PL_MODEL_H_
#define QUAD_PL_MODEL_H_
#define OPT_HEADER
#include <core/fitter.hpp>
#include <cmath>
#include <misc/optvec.hpp>

namespace opt_utilities
{
  template <typename T>
  class quad_pl
    :public model<optvec<T>,optvec<T>,optvec<T>,std::string>
  {
  private:
    quad_pl* do_clone()const
    {
      return new quad_pl<T>(*this);
    }

    const char* do_get_type_name()const
    {
      return "quad power law";
    }
  public:
    quad_pl()
    {
      this->push_param_info(param_info<optvec<T> >("a",1));
      this->push_param_info(param_info<optvec<T> >("b",1));
      this->push_param_info(param_info<optvec<T> >("c",1));
    }

    optvec<T> do_eval(const optvec<T>& x,const optvec<T>& param)
    {
      T a=get_element(param,0);
      T b=get_element(param,1);
      T c=get_element(param,2);
      return c*exp(a*log(x)*log(x)+b*log(x));
    }

  private:
    std::string do_get_information()const
    {
      return "Simple power law model\n"
	"y=A*x^gamma\n";
    }
  };
}



#endif
//EOF

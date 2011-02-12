#ifndef LIN1D_ESTIMATER
#define LIN1D_ESTIMATER
#include "pre_estimater.hpp"
#include <misc/optvec.hpp>
#include <vmodels/lin1d.hpp>


namespace opt_utilities
{
  template <typename T>
  class lin1d_estimater
    :public pre_estimater<optvec<T>,optvec<T>,optvec<T>,T,std::string>
  {
  private:
    const std::string model_id;
  private:
    lin1d_estimater()
      :model_id(lin1d<T>().get_type_name())
    {}

    lin1d_estimater<T> do_clone()const
    {
      return new lin1d_estimater<T>(*this);
    }

    void do_estimate(fitter<optvec<T>,optvec<T>,optvec<T>,T,std::string>& fit)const
    {
      if(model_id!=fit.get_model().get_type_name())
	{
	  return;
	}
    }
  };
}



#endif

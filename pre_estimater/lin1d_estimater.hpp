#ifndef LIN1D_ESTIMATER
#define LIN1D_ESTIMATER
#include "pre_estimater.hpp"
#include <misc/optvec.hpp>
#include <models/lin1d.hpp>
#include <vector>

namespace opt_utilities
{
  template <typename T>
  class lin1d_estimater
    :public pre_estimater<T,T,std::vector<T>,std::string>
  {
  private:
    lin1d_estimater()
    {
    }

    lin1d_estimater<T> do_clone()const
    {
      return new lin1d_estimater<T>(*this);
    }

    void do_estimate(const data<T,T>& d,model<T,T,std::vector<T>,std::string>& m)const
    {
    }
  };
}



#endif

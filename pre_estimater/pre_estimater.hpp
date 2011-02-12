#ifndef PRE_ESTIMATER_HPP
#define PRE_ESTIMATER_HPP

#include <core/fitter.hpp>


namespace opt_utilities
{
  template <typename  Ty,typename Tx,typename Tp,typename Ts=Ty,typename Tstr=std::string>
  class pre_estimater
  {
  private:
    virtual void do_estimate(fitter<Ty,Tx,Tp,Ts,Tstr>& fit)const=0;
    virtual pre_estimater* do_clone()const=0;
  public:
    void estimate(fitter<Ty,Tx,Tp,Ts,Tstr>& fit)const
    {
      do_estimate(fit);
    }

    pre_estimater* clone()const
    {
      return this->do_clone();
    }
  };
}


#endif

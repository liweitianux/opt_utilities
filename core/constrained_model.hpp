#ifndef CONSTRAINED_MODEL_HPP
#define CONSTRAINED_MODEL_HPP
#include "fitter.hpp"

namespace opt_utilities
{
  template <typename Ty,typename Tx,typename Tp,typename Tstr=std::string>
  class constrained_model
    :public model<Ty,Tx,Tp,Tstr>
  {
  public:
    bool meet_constraint(const Tp& p)const
    {
      return do_meet_constraint(p);
    }
  private:
    virtual bool do_meet_constraint(const Tp& p)const=0;
  };

}

#endif

#ifndef OPT_TYPES_HPP
#define OPT_TYPES_HPP
#include <core/optimizer.hpp>
#include <core/fitter.hpp>
#include <core/default_data_set.hpp>
#include <methods/powell/powell_method.hpp>
#include <statistics/chisq.hpp>
#include <statistics/leastsq.hpp>
#include <vector>

namespace opt_utilities
{
  template <typename Ty,typename Tx,typename Tp,typename Ts,typename Tstr>
  class opt_types
  {
  public:
    typedef fitter<Ty,Tx,Tp,Ts,Tstr> fitter;
    typedef chisq<Ty,Tx,Tp,Ts,Tstr> chisq;
    typedef leastsq<Ty,Tx,Tp,Ts,Tstr> leastsq;
    typedef powell_method<Ty,Tp> powell_method;
    typedef model<Ty,Tx,Tp,Tstr> model;
    typedef default_data_set<Ty,Ty> data_set;
    typedef optimizer<Ty,Tp> optimizer;
    typedef func_obj<Ty,Tp> func_obj;
    typedef opt_method<Ty,Tp> opt_method;
  };

  typedef opt_types<double,double,std::vector<double>,double,std::string> dopt;
}




#endif
//EOF

#ifndef PERFORM_FIT_HPP
#define PERFORM_FIT_HPP

/*
#include <statistics/chisq.hpp>
#include <statistics/cstat.hpp>
#include <data_sets/default_data_set.hpp>
#include <core/fitter.hpp>
#include <core/opt_traits.hpp>
#include <core/freeze_param.hpp>
#include <methods/powell/powell_method.hpp>
#include <models/gauss1d.hpp>
#include <models/bl1d.hpp>
#include <models/bpl1d.hpp>
#include <models/beta1d.hpp>
#include <models/dbeta1d.hpp>
#include <models/lin1d.hpp>
#include <models/poly1d.hpp>
#include <models/pl1d.hpp>
#include <models/models.hpp>
*/
#include <interface/type_depository.hpp>

namespace opt_utilities
{

  template <typename Ty,typename Tx,typename Tp,typename Ts,
	    typename Tstr>
  void perform_fit(const char* model_name,
		   const char* method_name,
		   const char* statistic_name,
		   const data_set<Ty,Tx>& ds,
		   const char* froze_parameters
		   )
  {
    fitter<Ty,Tx,Tp,Ts,Tstr> fit;
    fit.load_data(ds);
    const statistic<Ty,Tx,Tp,Ts,Tstr>* pstat=get_statistic<Ty,Tx,Tp,Ts,Tstr>(statistic_name);
    fit.set_statistic(*pstat);
    const opt_method<Ts,Tp>* popm=get_opt_method<Ty,Tp>(method_name);
    fit.set_opt_method(*popm);
    const model<Ty,Tx,Tp,Tstr>* pmo=get_model<Ty,Tx,Tp,Tstr>(model_name);
    fit.set_model(*pmo);
    fit.fit();
  }


}

#endif


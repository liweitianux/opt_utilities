/**
   \file error_estimator.hpp
   \brief define the function used to estimate the error boundaries of a fit
   \author Junhua Gu
 */

#ifndef ERROR_EST
#define ERROR_EST
#include <core/fitter.hpp>
#include <core/freeze_param.hpp>
#include <iostream>
#include <vector>
#include <string>

namespace opt_utilities
{
  /**
     \brief calculate the error boundary of a fit, according to the given delta statistic.
     \param fit the fitter that has a sucessful fit result
     \param pname the name of the parameter, the error of which will be estimated
     \param lower input as the initial value of the lower boundary, and output as the final result of the lower boundary
     \param upper input as the initial value of the upper boundary, and output as the final result of the upper boundary
     \param dchi the delta statistic corresponding to a certain confidence level
     \param precision determine how precise the error bounds should be determined
   */
  template <typename Ty,typename Tx,typename Tp,typename Ts,typename Tstr>
  void estimate_error(fitter<Ty,Tx,Tp,Ts>& fit,const Tstr& pname,typename element_type_trait<Tp>::element_type& lower,typename element_type_trait<Tp>::element_type& upper,const Ts& dchi,const Ts& precision)
  {
    typedef typename element_type_trait<Tp>::element_type Tpe;
    std::vector<Tstr> pnames;
    std::vector<Tpe> pvalues;
    //Make sure we start from an optimal parameter set
    fit.fit();
    //stores origin parameter values
    for(int i=0;i<fit.get_num_params();++i)
    {
      pnames.push_back(fit.get_param_info(i).get_name());
      pvalues.push_back(fit.get_param_info(i).get_value());
    }
    //ensure that the interesting parameter is free    
    if(fit.report_param_status(pname)=="frozen")
      {
	return;
      }
    try
      {
	freeze_param<Ty,Tx,Tp,Tstr>* pfp=dynamic_cast<freeze_param<Ty,Tx,Tp,Tstr>*>(&fit.get_param_modifier());
	if(pfp==0)
	  {
	    assert(0);
	  }
	*pfp+=freeze_param<Ty,Tx,Tp,Tstr>(pname);
      }
    catch(const param_modifier_undefined&)
      {
	fit.set_param_modifier(freeze_param<Ty,Tx,Tp,Tstr>(pname));
      }
    //get current statistic value
    Tpe current_value=
      fit.get_param_value(pname);
    //initial lower boundary should be a worse parameter,
    //so do the upper boundary
    if(lower>=current_value||upper<=current_value)
      {
	std::cerr<<"Error, initial lower and upper limits should be smaller and larger than the best fit value, respectively"<<std::endl;
	return;
      }
    
    Ts current_chi=fit.get_statistic_value();
    Tpe upper1=current_value;
    Tpe step=upper-current_value;
    //find a new upper bound, whose statistic is worse than the target statistic
    while(1)
      {
	fit.set_param_value(pname,upper);
	fit.fit();
	Ts chi=fit.get_statistic_value();
	std::cerr<<upper<<"\t"<<chi<<std::endl;
	if(chi>current_chi+dchi)
	  {
	    break;
	  }
	upper+=step;
      }
    //perform the bi-search
    Ts target_chi=current_chi+dchi;
    while(upper-upper1>std::abs(precision))
      {
	fit.set_param_value(pname,upper1);
	fit.fit();
	Ts s1=fit.get_statistic_value();
	fit.set_param_value(pname,upper);
	fit.fit();
	Ts s=fit.get_statistic_value();
	fit.set_param_value(pname,(upper+upper1)/2);
	fit.fit();
	Ts s01=fit.get_statistic_value();
	std::cerr<<s1-target_chi<<"\t"<<s01-target_chi<<"\t"<<s-target_chi<<std::endl;
	if((s1-target_chi)*(s01-target_chi)<0&&(s-target_chi)*(s01-target_chi)>=0)
	  {
	    upper=(upper+upper1)/2;
	  }
	else if((s1-target_chi)*(s01-target_chi)>0&&(s-target_chi)*(s01-target_chi)<=0)
	  {
	    upper1=(upper+upper1)/2;
	  }
	else
	  {
	    std::cerr<<"strange statistic structure"<<std::endl;
	    break;
	  }
      }
    
    for(int i=0;i<fit.get_num_params();++i)
    {
      fit.set_param_value(pnames[i],pvalues[i]);
    }

    fit.fit();
    
    

    ////
    Tpe lower1=current_value;
    step=current_value-lower;
    while(1)
      {
	fit.set_param_value(pname,lower);
	fit.fit();
	Ts chi=fit.get_statistic_value();
	std::cerr<<lower<<"\t"<<chi<<std::endl;
	if(chi>current_chi+dchi)
	  {
	    break;
	  }
	lower-=step;
      }
    
    fit.set_param_value(pname,current_value);
    fit.fit();
    
    while(lower1-lower>std::abs(precision))
      {
	fit.set_param_value(pname,lower1);
	fit.fit();
	Ts s1=fit.get_statistic_value();
	fit.set_param_value(pname,lower);
	fit.fit();
	Ts s=fit.get_statistic_value();
	fit.set_param_value(pname,(lower+lower1)/2);
	fit.fit();
	Ts s01=fit.get_statistic_value();
	std::cerr<<s1-target_chi<<"\t"<<s01-target_chi<<"\t"<<s-target_chi<<std::endl;
	if((s1-target_chi)*(s01-target_chi)<0&&(s-target_chi)*(s01-target_chi)>=0)
	  {
	    lower=(lower+lower1)/2;
	  }
	else if((s1-target_chi)*(s01-target_chi)>0&&(s-target_chi)*(s01-target_chi)<=0)
	  {
	    lower1=(lower+lower1)/2;
	  }
	else
	  {
	    std::cerr<<"strange statistic structure"<<std::endl;
	    break;
	  }
      }
    //restore the param_modifier
    dynamic_cast<freeze_param<Ty,Tx,Tp,Tstr>& >(fit.get_param_modifier())-=freeze_param<Ty,Tx,Tp,Tstr>(pname);
    //restore the origin param values
    for(int i=0;i<fit.get_num_params();++i)
      {
	fit.set_param_value(pnames[i],pvalues[i]);
      }
    
    fit.fit();
  }
}


#endif
//EOF

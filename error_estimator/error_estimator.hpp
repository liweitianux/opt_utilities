#ifndef ERROR_EST
#define ERROR_EST
#include <core/fitter.hpp>
#include <iostream>

namespace opt_utilities
{
  template <typename Ty,typename Tx,typename Tp,typename Ts,typename Tstr>
  void estimate_error(fitter<Ty,Tx,Tp,Ts>& fit,const Tstr& pname,typename element_type_trait<Tp>::element_type& lower,typename element_type_trait<Tp>::element_type& upper,const Ts& dchi)
  {
    
    typedef typename element_type_trait<Tp>::element_type Tpe;
    fit.fit();
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
    
    Tpe current_value=
      fit.get_param_value(pname);
    Tp current_params(fit.get_model().get_all_params());
    Ts current_chi=fit.get_statistic_value();
    Tpe upper1=current_value;
    Tpe step=upper-current_value;
    while(1)
      {
	fit.set_param_value(pname,upper);
	fit.fit();
	Ts chi=fit.get_statistic_value();
	cerr<<upper<<"\t"<<chi<<std::endl;
	if(chi>current_chi+dchi)
	  {
	    break;
	  }
	upper+=step;
      }
    
    Ts target_chi=current_chi+dchi;
    while(upper-upper1>1E-10)
      {
	std::cerr<<upper<<"\t"<<upper1<<std::endl;
	fit.set_param_value(pname,upper1);
	fit.fit();
	Ts s1=fit.get_statistic_value();
	fit.set_param_value(pname,upper);
	fit.fit();
	Ts s=fit.get_statistic_value();
	fit.set_param_value(pname,(upper+upper1)/2);
	fit.fit();
	Ts s01=fit.get_statistic_value();
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
    
    fit.set_param_value(pname,current_value);
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
    
    while(lower1-lower>1E-10)
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
	//std::cerr<<"l:"<<lower1<<"\t"<<(lower1+lower)/2<<"\t"<<lower<<std::endl;
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

    dynamic_cast<freeze_param<Ty,Tx,Tp,Tstr>& >(fit.get_param_modifier())-=freeze_param<Ty,Tx,Tp,Tstr>(pname);
    
  }
}


#endif
//EOF

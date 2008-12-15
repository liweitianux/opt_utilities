#ifndef BOOT_STRIP
#define BOOT_STRIP
#include <core/fitter.hpp>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <utility>
#include <algorithm>
#include <core/default_data_set.hpp>
using std::cout;
namespace opt_utilities
{
  template <typename Ty,typename Tx,typename Tp>
  class bootstrap
  {
  private:
    Ty rand_norm(Ty y0,Ty y_err)const
    {
      Ty y;
      do
	{
	  y=(rand()/(Ty)RAND_MAX-(Ty).5)*(10*y_err)+y0;
	}
      while(rand()/(Ty)RAND_MAX>exp(-(y-y0)*(y-y0)/(y_err*y_err)));
      return y;
      
    }
  public:
    std::vector<Tp> param_pool;
    default_data_set<Ty,Tx> current_data_set;
    default_data_set<Ty,Tx> origin_data_set;
    fitter<Ty,Tx,Tp>* p_fitter;
    Tp origin_param;
  public:
    bootstrap()
      :p_fitter(NULL)
    {}

    void set_fitter(fitter<Ty,Tx,Tp>& pf)
    {
      param_pool.clear();
      p_fitter=&pf;
      origin_data_set=dynamic_cast<const default_data_set<Ty,Tx>&>(pf.datas());
      origin_param=pf.get_all_params();
    }
    


    void sample(int n)
    {
      if(p_fitter!=NULL)
	{
	  for(int i=0;i<n;++i)
	    {
	      sample();
	    }
	  
	  p_fitter->load_data(origin_data_set);
	  p_fitter->set_param_value(origin_param);
	}
      else
	{
	  throw opt_exception("Fitter unset");
	}
    }

    const Tp& get_param(int i)const
    {
      return param_pool.at(i);
    }
    
  private:
    void sample()
    {
      current_data_set=default_data_set<Ty,Tx>();
      for(int i=0;i<origin_data_set.size();++i)
	{
	  data<Ty,Tx> d;
	  d=origin_data_set.get_data(i);
	  d.set_y(rand_norm(d.get_y(),(d.get_y_upper_err()+d.get_y_lower_err())/2));
	  current_data_set.push_back(d);
	}
      p_fitter->load_data(current_data_set);
      p_fitter->set_param_value(origin_param);
      param_pool.push_back(p_fitter->fit());
      for(size_t i=0;i<(param_pool.back()).size();++i)
	{
	  cout<<param_pool.back()[i]<<",";
	}
      std::cout<<std::endl;
    }
    
  public:
    std::pair<typename element_type_trait<Tp>::element_type,typename element_type_trait<Tp>::element_type>
    interval(std::string param_name,double level)
    {
      if(p_fitter==NULL)
	{
	  throw opt_exception("Fitter unset");
	}
      if(param_pool.empty())
	{
	  throw opt_exception("Bootstrap not done");
	}
      //sample();
      std::vector<typename element_type_trait<Tp>::element_type> _tmp;
      int order=p_fitter->get_param_order(param_name);
      for(typename std::vector<Tp>::iterator i=param_pool.begin();
	  i!=param_pool.end();++i)
	{
	  _tmp.push_back((*i)[order]);
	}
      sort(_tmp.begin(),_tmp.end());
      std::pair<typename std::vector<typename element_type_trait<Tp>::element_type>::iterator,
	typename std::vector<typename element_type_trait<Tp>::element_type>::iterator> 
	itv=equal_range(_tmp.begin(),_tmp.end(),origin_param[order]);
      int current_param_position=itv.second-_tmp.begin();
      std::cout<<_tmp.size()<<std::endl;
      return std::pair<typename element_type_trait<Tp>::element_type,
	typename element_type_trait<Tp>::element_type>(
				 _tmp.at((int)((1-level)*current_param_position)),
				 _tmp.at((int)(current_param_position+level*(_tmp.size()-current_param_position)))
				 );
      
    }

  };
  
};

#endif
//EOF

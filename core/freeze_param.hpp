#ifndef FREEZE_PARAM_HPP
#define FREEZE_PARAM_HPP
#include "fitter.hpp"
#include <vector>
#include <set>

namespace opt_utilities
{
  template <typename Ty,typename Tx,typename Tp,typename Tstr=std::string>
  class freeze_param
    :public param_modifier<Ty,Tx,Tp,Tstr>
  {
  private:
    std::set<Tstr> param_names;
    std::vector<int> param_num;
    int num_free;
    
  public:
    freeze_param()
    {
      
    }

    freeze_param(const Tstr& name)
    {
      param_names.insert(name);
    }
    
  private:
    freeze_param<Ty,Tx,Tp,Tstr>* do_clone()const
    {
      return new freeze_param<Ty,Tx,Tp,Tstr>(*this);
    }
    
    

    void update()
    {
      param_num.clear();
      for(typename std::set<Tstr>::const_iterator  i=param_names.begin();
	  i!=param_names.end();++i)
	{
	  try
	    {
	      param_num.push_back(this->get_model().get_param_order(*i));
	    }
	  catch(opt_exception& e)
	    {
	      param_names.erase(*i);
	      throw;
	    }
	  
	}
    }

    int do_get_num_free_params()const
    {
      return this->get_model().get_num_params()-param_num.size();
    }

    bool is_frozen(int i)const
    {
      if(find(param_num.begin(),param_num.end(),i)==param_num.end())
	{
	  return false;
	}
      return true;
    }


    Tp do_reform(const Tp& p)const
    {
      int nparams=(this->get_model().get_num_params());
      Tp reformed_p(nparams);
      int i=0,j=0;
      for(i=0;i<(int)nparams;++i)
	{
	  if(this->is_frozen(i))
	    {
	      const param_info<Tp,Tstr>& pinf=this->get_model().get_param_info(i);
	      //std::cout<<"frozen:"<<pinf.get_name()
	      //	       <<i<<"\t"<<j
	      //       <<std::endl;
	      //opt_eq(get_element(reformed_p,i),pinf.get_default_value());
	      set_element(reformed_p,i,pinf.get_default_value());
	    }
	  else
	    {
	      //opt_eq(get_element(reformed_p,i),get_element(p,j));
	      set_element(reformed_p,i,get_element(p,j));
	      j++;
	    }
	}
      /*
      for(int i=0;i<reformed_p.size();++i)
      {
      std::cout<<get_element(reformed_p,i)<<",";
      }
      */
      //std::cout<<"\n";
      return reformed_p;
      // return p;
    }

    Tp do_deform(const Tp& p)const
    {
      Tp deformed_p(do_get_num_free_params());
      int i(0),j(0);
      assert(get_size(p)==this->get_model().get_num_params());
      for(;i<(int)get_size(p);++i)
	{
	  //std::cout<<is_frozen(j)<<"\n";
	  if(!this->is_frozen(i))
	    {
	      //opt_eq(get_element(deformed_p,j),get_element(p,i));
	      set_element(deformed_p,j,get_element(p,i));
	      j++;
	    }
	}
      
      assert(j==do_get_num_free_params());
      return deformed_p;
    }


    Tstr do_report_param_status(const Tstr& name)const
    {
      if(param_names.find(name)==param_names.end())
	{
	  return "thawed";
	}
      return "frozen";
    }

  public:
    freeze_param operator+(const freeze_param& fp)const
    {
      freeze_param result(*this);
      for(typename std::set<Tstr>::const_iterator i=fp.param_names.begin();
	  i!=fp.param_names.end();
	  ++i)
	{
	  result.param_names.insert(*i);
	}
      return result;
    }

    freeze_param& operator+=(const freeze_param& fp)
    {
      //param_names.insert(param_names.end(),
      //fp.param_names.begin(),
      //fp.param_names.end());
      for(typename std::set<Tstr>::const_iterator i=fp.param_names.begin();
	  i!=fp.param_names.end();
	  ++i)
	{
	  param_names.insert(*i);
	}
      try
	{
	  update();
	}
      catch(opt_exception& e)
	{
	  throw;
	}
      return *this;
    }

    freeze_param& operator-=(const freeze_param& fp)
    {
      //param_names.insert(param_names.end(),
      //fp.param_names.begin(),
      //fp.param_names.end());
      for(typename std::set<Tstr>::const_iterator i=fp.param_names.begin();
	  i!=fp.param_names.end();
	  ++i)
	{
	  param_names.erase(*i);
	}
      try
	{
	  update();
	}
      catch(opt_exception& e)
	{
	  throw;
	}
      return *this;
    }

  };

  template <typename Ty,typename Tx,typename Tp,typename Tstr>
  freeze_param<Ty,Tx,Tp,Tstr> freeze(const Tstr& name)
  {
    return freeze_param<Ty,Tx,Tp,Tstr>(name);
  }

};


#endif
//EOF

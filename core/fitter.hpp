/**
   \file fitter.hpp
 */

#ifndef FITTER_HPP
#define FITTER_HPP
#include "opt_exception.hpp"
#include "optimizer.hpp"
#include <vector>
#include <string>
#include <cstdlib>
#include <cassert>
#include <iostream>
namespace opt_utilities
{

  ///////////////////////////////////
  //////class data///////////////////
  //////contain single data point////
  ///////////////////////////////////
  template<typename Ty,typename Tx,typename Tp,typename Ts,typename Tstr>
  class statistic;

  template<typename Ty,typename Tx,typename Tp,typename Tstr>
  class param_modifier;


  /**
     \brief representing a single data point
     \tparam Ty the type of y
     \tparam Tx the type of x
   */
  template<typename Ty,typename Tx>
  class data
  {
  private:
    Tx x,x_lower_err,x_upper_err;
    Ty y,y_lower_err,y_upper_err;
  public:
    /**
       construct function
       \param _x x
       \param _y y
       \param _y_lower_err lower y error
       \param _y_upper_err upper y error
       \param _x_lower_err lower x error
       \param _x_upper_err upper x error
     */
    data(const Tx& _x,const Ty& _y,
	 const Ty& _y_lower_err,
	 const Ty& _y_upper_err,const Tx& _x_lower_err,const Tx& _x_upper_err)
    {
      opt_eq(x,_x);
      opt_eq(x_lower_err,_x_lower_err);
      opt_eq(x_upper_err,_x_upper_err);
      opt_eq(y,_y);
      opt_eq(y_lower_err,_y_lower_err);
      opt_eq(y_upper_err,_y_upper_err);
 
    }

    
    /**
       default construct
     */
    data()
      :x(),
       x_lower_err(),
       x_upper_err(),
       y(),
       y_lower_err(),
       y_upper_err()
    {}

    
    /**
       copy construct
     */
    data(const data& rhs)
    {
      opt_eq(x,rhs.x);
      opt_eq(x_lower_err,rhs.x_lower_err);
      opt_eq(x_upper_err,rhs.x_upper_err);
      opt_eq(y,rhs.y);
      opt_eq(y_lower_err,rhs.y_lower_err);
      opt_eq(y_upper_err,rhs.y_upper_err);
    }


    /**
       Assignment operator
     */
    data& operator=(const data& rhs)
    {
      opt_eq(x,rhs.x);
      opt_eq(x_lower_err,rhs.x_lower_err);
      opt_eq(x_upper_err,rhs.x_upper_err);
      opt_eq(y,rhs.y);
      opt_eq(y_lower_err,rhs.y_lower_err);
      opt_eq(y_upper_err,rhs.y_upper_err);
      return *this;
    }

  public:

    /**
       set x
       \return x
     */
    const Tx& get_x()const
    {
      return x;
    }
    
    /**
       \return x lower error
     */
    const Tx& get_x_lower_err()const
    {
      return x_lower_err;
    }
    
    /**
       \return x upper error
     */
    const Tx& get_x_upper_err()const
    {
      return x_upper_err;
    }

    /**
       \return y
     */
    const Ty& get_y()const
    {
      return y;
    }
    

    /**
       \return y lower error
     */
    const Ty& get_y_lower_err()const
    {
      return y_lower_err;
    }

    /**
       \return y upper error
     */
    
    const Ty& get_y_upper_err()const
    {
      return y_upper_err;
    }


    /**
       set x
       \param _x x
     */

    void set_x(const Tx& _x)
    {
      opt_eq(x,_x);
    }
    
    /**
       set x lower error
       \param _x x lower error
     */
    void set_x_lower_err(const Tx& _x)
    {
      opt_eq(x_lower_err,_x);
    }
    

    /**
       set x upper error
       \param _x x upper error
     */
    void set_x_upper_err(const Tx& _x)
    {
      opt_eq(x_upper_err,_x);
    }


    /**
       set y 
       \param _y y
     */
    void set_y(const Ty& _y)
    {
      opt_eq(y,_y);
    }
    

    /**
       set y lower error
       \param _y y lower error
     */
    void set_y_lower_err(const Ty& _y)
    {
      opt_eq(y_lower_err,_y);
    }
    
    /**
       set y upper error
       \param _y y upper error
     */
    void set_y_upper_err(const Ty& _y)
    {
      opt_eq(y_upper_err,_y);
    }
    

  };

  /**
     \brief virtual class representing a set of data
     \tparam Ty type of y
     \tparam Tx type of x
   */  
  template <typename Ty,typename Tx>
  class data_set
  {
  private:
    
    virtual const data<Ty,Tx>& do_get_data(size_t i)const=0;
    virtual size_t do_size()const=0;
    virtual void do_add_data(const data<Ty,Tx>&)=0;
    virtual void do_clear()=0;
    virtual data_set<Ty,Tx>* do_clone()const=0;

    virtual void do_destroy()
    {
      delete this;
    }
  public:
    /**
       get data
       \param i the order of the data point
       \return the const reference of a class data point
     */
    const data<Ty,Tx>& get_data(size_t i)const
    {
      return this->do_get_data(i);
    }

    /**
       \return the size of the data set
     */
    size_t size()const
    {
      return do_size();
    }

    /**
       add data point
       \param d data point
     */
    void add_data(const data<Ty,Tx>& d)
    {
      return do_add_data(d);
    }

    /**
       clear the data set
     */
    void clear()
    {
      do_clear();
    }
    

    /**
       clone self
       \return a clone of self
     */
    data_set<Ty,Tx>* clone()const
    {
      return this->do_clone();
    }

    /**
       destroy the cloned object
     */

    void destroy()
    {
      do_destroy();
    }

    /**
       destruct function
     */

    virtual ~data_set(){}
      
  };

  

  /**
     \brief the information of a model parameter
     \tparam Tp type of model param type
     \tparam Tstr the type of string type used
   */
  template <typename Tp,typename Tstr=std::string>
  class param_info
  {
  private:
    Tstr name;
    //bool frozen;
    typename element_type_trait<Tp>::element_type value;
    typename element_type_trait<Tp>::element_type lower_limit;
    typename element_type_trait<Tp>::element_type upper_limit;
    
  public:

    /**
       construct function
       \param _name the name of the param
       \param _v the value of the param
       \param _l the lower boundary of the param
       \param _u the upper boundary of the param
     */
    param_info(const Tstr& _name,
	       const typename element_type_trait<Tp>::element_type& _v,
	       const typename element_type_trait<Tp>::element_type& _l=0,
	       const typename element_type_trait<Tp>::element_type& _u=0
	       )
      :name(_name),value(_v),lower_limit(_l),upper_limit(_u){}

    /**
       default construct
     */
    param_info()
      :name()
    {}


    /**
       copy construct function
     */
    param_info(const param_info& rhs)
      :name(rhs.name)
    {
      opt_eq(value,rhs.value);
      opt_eq(lower_limit,rhs.lower_limit);
      opt_eq(upper_limit,rhs.upper_limit);
    }

    
    /**
       assignment operator
     */
    param_info& operator=(const param_info& rhs)
    {
      name=rhs.name;
      opt_eq(value,rhs.value);
      opt_eq(lower_limit,rhs.lower_limit);
      opt_eq(upper_limit,rhs.upper_limit);
      return *this;
    }


    /**
       \return the name of the parameter
     */
    const Tstr& get_name()const
    {
      return this->name;
    }

    /**
       \return the current value of the parameter
     */
    const typename element_type_trait<Tp>::element_type& get_value()const
    {
      return value;
    }

    /**
       \return the lower boundary
     */
    const typename element_type_trait<Tp>::element_type& get_lower_limit()const
    {
      return lower_limit;
    }

    /**
       \return the upper boundary
     */
    const typename element_type_trait<Tp>::element_type& get_upper_limit()const
    {
      return upper_limit;
    }

    
    /**
       set the value
       \param x the value of the parameter
     */
    void set_value(const typename element_type_trait<Tp>::element_type& x)
    {
      opt_eq(value,x);
    }


    /**
       set the lower boundary
       \param x the lower boundary
     */
    void set_lower_limit(const typename element_type_trait<Tp>::element_type& x)
    {
      opt_eq(lower_limit,x);
    }

    /**
       set the upper limit
       \param x the upper boundary
     */
    void set_upper_limit(const typename element_type_trait<Tp>::element_type& x)
    {
      opt_eq(upper_limit,x);
    }

    /**
       set the name of the parameter
       \param _name the name of the parameter
     */

    void set_name(const Tstr& _name)
    {
      name=_name;
    }
  };




  /**
     \brief virtual class representing a model
     \tparam Ty the type of the returned value of the model
     \tparam Tx the type of the self-var
     \tparam Tp the type of the model param
     \tparam Tstr the type of the string used
   */
  template <typename Ty,typename Tx,typename Tp,typename Tstr=std::string>
  class model
  {
  private:
    std::vector<param_info<Tp> > param_info_list;
    param_info<Tp> null_param;
    //    int num_free_params;
    param_modifier<Ty,Tx,Tp,Tstr>* p_param_modifier;
  private:
    virtual model<Ty,Tx,Tp,Tstr>* do_clone()const=0;

    virtual void do_destroy()
    {
      delete this;
    }
  public:

    /**
       \return the cloned object
     */
    model<Ty,Tx,Tp,Tstr>* clone()const
    {
      return do_clone();
    }

    /**
       destroy the cloned object
     */
    void destroy()
    {
      do_destroy();
    }
  public:

    /**
       default construct function
     */
    model()
      :p_param_modifier(0)
    {}
    

    /**
       copy construct
     */
    model(const model& rhs)
      :p_param_modifier(0)
    {
      if(rhs.p_param_modifier!=0)
	{
	  set_param_modifier(*(rhs.p_param_modifier));
	}
      param_info_list=rhs.param_info_list;
      null_param=rhs.null_param;
      
    }
    

    /**
       assignment operator
     */
    model& operator=(const model& rhs)
    {
      if(this==&rhs)
	{
	  return *this;
	}
      if(rhs.p_param_modifier!=0)
	{
	  set_param_modifier(*(rhs.p_param_modifier));
	}
      param_info_list=rhs.param_info_list;
      null_param=rhs.null_param;
      return *this;
    }
    

    /**
       destructure function
     */
    virtual ~model()
    {
      if(p_param_modifier)
	{
	  //delete p_param_modifier;
	  p_param_modifier->destroy();
	}
    }
    

    /**
       set the param modifier
       \param pm param modifier
     */
    void set_param_modifier(const param_modifier<Ty,Tx,Tp,Tstr>& pm)
    {
      if(p_param_modifier!=0)
	{
	  //delete p_param_modifier;
	  p_param_modifier->destroy();
	}
      p_param_modifier=pm.clone();
      p_param_modifier->set_model(*this);
    }

    /**
       clear the param modifier
     */
    void set_param_modifier()
    {
      if(p_param_modifier!=0)
	{
	  //delete p_param_modifier;
	  p_param_modifier->destroy();
	}
      p_param_modifier=0;
    }
    

    /**
       \return the param_modifier
     */
    param_modifier<Ty,Tx,Tp,Tstr>& get_param_modifier()
    {
      if(p_param_modifier==0)
	{
	  throw param_modifier_undefined();
	}
      return *p_param_modifier;
    }


    /**
       report the param status
       \return the param status
     */
    Tstr report_param_status(const Tstr& s)const
    {
      if(p_param_modifier==0)
	{
	  return Tstr();
	}
      
      return p_param_modifier->report_param_status(s);
	
    }
    

    /**
       \param pname the name of the param
       \return the param info
    */
    const param_info<Tp,Tstr>& get_param_info(const Tstr& pname)
    {
      for(typename std::vector<param_info<Tp,Tstr> >::iterator i=param_info_list.begin();
	  i!=param_info_list.end();++i)
	{
	  if(i->get_name()==pname)
	    {
	      return *i;
	    }
	}
      std::cerr<<"Param unfound!"<<std::endl;
      assert(false);
      throw param_not_found();
      return null_param;
    }


    /**
       \param n the order of the parameter
       \return the param info
     */
    const param_info<Tp,Tstr>& get_param_info(size_t n)const
    {
      return param_info_list[n%get_num_params()];
    }

    
    /**
       \return the full parameter vector
     */
    Tp get_all_params()const
    {
      Tp result;
      resize(result,param_info_list.size());
      for(size_t i=0;i<param_info_list.size();++i)
	{
	  //opt_eq(get_element(result,i),param_info_list[i].get_value());
	  set_element(result,i,param_info_list[i].get_value());
	  //get_element((Tp)result,i);
	}
      return result;
    }


    /**
       \return the lower limit
     */
    Tp get_all_lower_limits()const
    {
      Tp result;
      resize(result,param_info_list.size());
      for(size_t i=0;i<param_info_list.size();++i)
	{
	  //opt_eq(get_element(result,i),param_info_list[i].get_value());
	  set_element(result,i,param_info_list[i].get_lower_limit());
	  //get_element((Tp)result,i);
	}
      return result;
    }

    /**
       \return the upper limit
     */
    Tp get_all_upper_limits()const
    {
      Tp result;
      resize(result,param_info_list.size());
      for(size_t i=0;i<param_info_list.size();++i)
	{
	  //opt_eq(get_element(result,i),param_info_list[i].get_value());
	  set_element(result,i,param_info_list[i].get_upper_limit());
	  //get_element((Tp)result,i);
	}
      return result;
    }

  
    /**
       \return the number of parameters
     */
    size_t get_num_params()const
    {
      return param_info_list.size();
    }


    /**
       \return the number of free parameters
     */
    size_t get_num_free_params()const
    {
      if(p_param_modifier)
	{
	  return p_param_modifier->get_num_free_params();
	}
      return get_num_params();
    }


    /**
       \param pname the name of the parameter
       \param v the value of the pearameter
    */
    void set_param_value(const Tstr& pname,
			 const typename element_type_trait<Tp>::element_type& v)
    {
      //int porder=0;
      for(typename std::vector<param_info<Tp,Tstr> >::iterator i=param_info_list.begin();
	  i!=param_info_list.end();++i)
	{
	  if(i->get_name()==pname)
	    {
	      i->set_value(v);
	      return;
	    }
	}
      std::cerr<<"param "<<pname<<" unfound"<<std::endl;
      throw param_not_found();
    }

    
    /**
       set the lower limit
       \param pname the parameter name
       \param v the value of the lower limit
     */
    void set_param_lower_limit(const Tstr& pname,
			       const typename element_type_trait<Tp>::element_type& v)
    {
      //int porder=0;
      for(typename std::vector<param_info<Tp,Tstr> >::iterator i=param_info_list.begin();
	  i!=param_info_list.end();++i)
	{
	  if(i->get_name()==pname)
	    {
	      i->set_lower_limit(v);
	      return;
	    }
	}
      std::cerr<<"param "<<pname<<" unfound"<<std::endl;
      throw param_not_found();
    }


    /**
       set the upper limit
       \param pname the parameter name
       \param v the value of the upper limit
    */
    void set_param_upper_limit(const Tstr& pname,
			       const typename element_type_trait<Tp>::element_type& v)
    {
      //int porder=0;
      for(typename std::vector<param_info<Tp,Tstr> >::iterator i=param_info_list.begin();
	  i!=param_info_list.end();++i)
	{
	  if(i->get_name()==pname)
	    {
	      i->set_upper_limit(v);
	      return;
	    }
	}
      std::cerr<<"param "<<pname<<" unfound"<<std::endl;
      throw param_not_found();
    }
    

    /**
       set param 
       \param param the values of the parameter
     */
    void set_param_value(const Tp& param)
    {
      for(size_t i=0;i<param_info_list.size();++i)
	{
	  param_info_list[i].set_value(get_element(param,i));
	}
    }


    /**
       set lower limit 
       \param param the lower limit of the parameter
    */
    void set_param_lower_limit(const Tp& param)
    {
      for(size_t i=0;i<param_info_list.size();++i)
	{
	  param_info_list[i].set_lower_limit(get_element(param,i));
	}
    }
    

    /**
       set upper limit 
       \param param the upper limit of the parameter
    */
    void set_param_upper_limit(const Tp& param)
    {
      for(size_t i=0;i<param_info_list.size();++i)
	{
	  param_info_list[i].set_upper_limit(get_element(param,i));
	}
    }


    /**
       get the order of a parameter
       \param pname the name of the parameter
       \return the order of the parameter
     */
    size_t get_param_order(const Tstr& pname)const
    {
      for(size_t i=0;i<param_info_list.size();++i)
	{
	  if(param_info_list[i].get_name()==pname)
	    {
	      return i;
	    }
	}
      //      std::cerr<<"param name invalid!"<<std::endl;
      // assert(false);
      throw param_not_found();
      return -1;
    }
    

		
  protected:

    /**
       add param info
       \param pinfo the param info to be added
     */
    void push_param_info(const param_info<Tp,Tstr>& pinfo)
    {
      param_info_list.push_back(pinfo);
      //      this->num_free_params++;
    }
    
    /**
       clear the param information list
     */
    void clear_param_info()
    {
      //      this->num_free_params=0;
      param_info_list.clear();
    }



  public:

    /**
       \return the description of the model
     */
    Tstr to_string()const
    {
      return do_to_string();
    }


    
    Tp reform_param(const Tp& p)const
    {
      if(p_param_modifier==0)
	{
	  return p;
	}
      return p_param_modifier->reform(p);
    }

    Tp deform_param(const Tp& p)const
    {
      if(p_param_modifier==0)
	{
	  return p;
	}
      return p_param_modifier->deform(p);
    }

    /**
       evaluate the model
       \param x the self var
       \param p the parameter
       \return the model value
     */
    Ty eval(const Tx& x,const Tp& p)
    {
      return do_eval(x,reform_param(p));
    }


    Ty eval_raw(const Tx& x,const Tp& p)
    {
      return do_eval(x,reform_param(p));
    }

  private:
    virtual Ty do_eval(const Tx& x,const Tp& p)=0;

  private:
    virtual Tstr do_to_string()const
    {
      return Tstr();
    }
    
  };


  /**
     \brief class to perform the model fitting
     \tparam Ty the type of the model return type
     \tparam Tx the type of the model self-var
     \tparam Tp the type of the model param
     \tparam Ts statistic type
     \tparam Tstr the type of string used
   */
  template<typename Ty,typename Tx,typename Tp,typename Ts=Ty,typename Tstr=std::string>
  class fitter
  {
  private:
    model<Ty,Tx,Tp,Tstr>* p_model;
    statistic<Ty,Tx,Tp,Ts,Tstr>* p_statistic;
    data_set<Ty,Tx>* p_data_set;
    optimizer<Ts,Tp> optengine;
  public:
    
    /**
       default construct function
    */
    fitter()
      :p_model(0),p_statistic(0),p_data_set(0),optengine()
    {}

    
    /**
       copy construct function
     */
    fitter(const fitter& rhs)
      :p_model(0),p_statistic(0),p_data_set(0),optengine()
    {
      if(rhs.p_model!=0)
	{
	  set_model(*(rhs.p_model));
	}
      if(rhs.p_statistic!=0)
	{
	  set_statistic(*(rhs.p_statistic));
	  assert(p_statistic->p_fitter!=0);
	}
      if(rhs.p_data_set!=0)
	{
	  load_data(*(rhs.p_data_set));
	}
      optengine=rhs.optengine;
    }
    

    /**
       assignment operator
     */
    fitter& operator=(const fitter& rhs)
    {
      if(this==&rhs)
	{
	  return *this;
	}
      if(rhs.p_model!=0)
	{
	  set_model(*(rhs.p_model));
	}
      if(rhs.p_statistic!=0)
	{
	  set_statistic(*(rhs.p_statistic));
	}
      if(rhs.p_data_set!=0)
	{
	  load_data(*(rhs.p_data_set));
	}
      optengine=rhs.optengine;
      return *this;
    }
    

    /**
       destruct function
     */
    virtual ~fitter()
    {
      if(p_model!=0)
	{
	  //delete p_model;
	  p_model->destroy();
	}
      if(p_statistic!=0)
	{
	  //delete p_statistic;
	  p_statistic->destroy();
	}
      if(p_data_set!=0)
	{
	  //delete p_data_set;
	  p_data_set->destroy();
	}
    }
    

    /**
       evaluate the model
     */
    Ty eval_model(const Tx& x,const Tp& p)
    {
      if(p_model==0)
	{
	  throw model_undefined();
	}
      return p_model->eval(x,p);
    }

    Ty eval_model_raw(const Tx& x,const Tp& p)
    {
      if(p_model==0)
	{
	  throw model_undefined();
	}
      return p_model->eval_raw(x,p);
    }
    

  public:

    /**
       set the model
       \param m model to be used
     */
    void set_model(const model<Ty,Tx,Tp,Tstr>& m)
    {
      if(p_model!=0)
	{
	  //delete p_model;
	  p_model->destroy();
	}
      p_model=m.clone();
      //p_model=&m;
      //  current_param.resize(m.get_num_params());
    }


    /**
       set the statistic (e.g., chi square, least square c-statistic etc.)
       \param s statistic to be used
     */
    void set_statistic(const statistic<Ty,Tx,Tp,Ts,Tstr>& s)
    {
      if(p_statistic!=0)
	{
	  //delete p_statistic;
	  p_statistic->destroy();
	}
      p_statistic=s.clone();
      //p_statistic=&s;
      p_statistic->set_fitter(*this);
    }

    /**
       set parameter modifier
       \param pm parameter modifier to be used
     */
    void set_param_modifier(const param_modifier<Ty,Tx,Tp,Tstr>& pm)
    {
      if(p_model==0)
	{
	  throw model_undefined();
	}
      p_model->set_param_modifier(pm);
    }

    /**
       clear the param modifier
    */
    void set_param_modifier()
    {
      if(p_model==0)
	{
	  throw model_undefined();
	}
      p_model->set_param_modifier();
    }


    /**
       Get the inner kept param modifier
       \return the reference of param_modifier
     */
    param_modifier<Ty,Tx,Tp,Tstr>& get_param_modifier()
    {
      if(p_model==0)
	{
	  throw model_undefined();
	}
      return p_model->get_param_modifier();
    }

    /**
       report the status of a parameter
       \param s the name of a parameter
       \return string used to describe the parameter
     */
    Tstr report_param_status(const Tstr& s)const
    {
      if(p_model==0)
	{
	  throw model_undefined();
	}
      return p_model->report_param_status(s);
    }
    
    /**
       load the data set
       \param da a data set
    */
    void load_data(const data_set<Ty,Tx>& da)
    {
      if(p_data_set!=0)
	{
	  //delete p_data_set;
	  p_data_set->destroy();
	}
      p_data_set=da.clone();
      if(p_statistic!=0)
	{
	  p_statistic->set_fitter(*this);
	}
    }
	

    /**
       get the data set that have been loaded
       \return the const reference of inner data_set
     */
    const data_set<Ty,Tx>& get_data_set()const
    {
      if(p_data_set==0)
	{
	  throw data_unloaded();
	}
      return *(this->p_data_set);
    }

    /**
       Get the model used
       \return the reference of model used
     */
    model<Ty,Tx,Tp,Tstr>& get_model()
    {
      if(p_model==0)
	{
	  throw model_undefined();
	}
      return *(this->p_model);
    }

    /**
       Get the statistic used
       \return the reference of the statistic used
     */
    statistic<Ty,Tx,Tp,Ts,Tstr>& get_statistic()
    {
      if(p_statistic==0)
	{
	  throw statistic_undefined();
	}
      return *(this->p_statistic);
    }
    
    /**
       Get the optimization method that used
       \return the reference of the opt_method
     */
    opt_method<Ts,Tp>& get_method()
    {
      return optengine.method();
    }
    

  public:
    /**
       set the value of a parameter
       \param pname the name of the parameter
       \param v the value of the parameter
    */
    void set_param_value(const Tstr& pname,
			 const typename element_type_trait<Tp>::element_type& v)
    {
      if(p_model==0)
	{
	  throw model_undefined();
	}
      p_model->set_param_value(pname,v);
    }

    /**
       set the lower limit of a parameter
       \param pname the name of the parameter
       \param v the lower limit of the parameter       
     */
    void set_param_lower_limit(const Tstr& pname,
			       const typename element_type_trait<Tp>::element_type& v)
    {
      if(p_model==0)
	{
	  throw model_undefined();
	}
      p_model->set_param_lower_limit(pname,v);
    }

    /**
       set the upper limit of a parameter
       \param pname the name of the parameter
       \param v the upper limit of the parameter       
     */
    void set_param_upper_limit(const Tstr& pname,
			       const typename element_type_trait<Tp>::element_type& v)
    {
      if(p_model==0)
	{
	  throw model_undefined();
	}
      p_model->set_param_upper_limit(pname,v);
    }
    

    /**
       set the values of all parameters
       \param param the vector containing the value of all parameters
     */

    void set_param_value(const Tp& param)
    {
      if(p_model==0)
	{
	  throw model_undefined();
	}
      p_model->set_param_value(param);
    }

    /**
       set the lower limits of all parameters
       \param param the vector containing the lower limits of all parameters
    */
    void set_param_lower_limit(const Tp& param)
    {
      if(p_model==0)
	{
	  throw model_undefined();
	}
      p_model->set_param_lower_limit(param);
    }

    /**
       set the upper limits of all parameters
       \param param the vector containing the upper limits of all parameters
    */
    void set_param_upper_limit(const Tp& param)
    {
      if(p_model==0)
	{
	  throw model_undefined();
	}
      p_model->set_param_upper_limit(param);
    }


    /**
       get the parameter value
       \param pname the name of the parameter
       \return the value of the parameter
     */
    typename element_type_trait<Tp>::element_type get_param_value(const Tstr& pname)const
    {
      if(p_model==0)
	{
	  throw model_undefined();
	}
      return p_model->get_param_info(pname).get_value();
    }

    /**
       get the lower limit of a parameter
       \param pname the name of a parameter
       \return the lower limit of a parameter
     */
    typename element_type_trait<Tp>::element_type get_param_lower_limit(const Tstr& pname)const
    {
      if(p_model==0)
	{
	  throw model_undefined();
	}
      return p_model->get_param_info(pname).get_lower_limit();
    }
    
    /**
       get the upper limit of a parameter
       \param pname the name of a parameter
       \return the upper limit of a parameter
     */
    typename element_type_trait<Tp>::element_type get_param_upper_limit(const Tstr& pname)const
    {
      if(p_model==0)
	{
	  throw model_undefined();
	}
      return p_model->get_param_info(pname).get_upper_limit();
    }

    
    /**
       get the param_info of a parameter
       \param pname the name of the parameter
       \return the const reference of a param_info object
     */
    const param_info<Tp,Tstr>& get_param_info(const Tstr& pname)const
    {
      if(p_model==0)
	{
	  throw model_undefined();
	}
      return p_model->get_param_info(pname);
    }
    
    /**
       get the param_info of a parameter by its order
       \param n the order of the parameter
       \return the const reference of a param_info object
     */
    const param_info<Tp,Tstr>& get_param_info(size_t n)const
    {
      if(p_model==0)
	{
	  throw model_undefined();
	}
      return p_model->get_param_info(n);
    }

    /**
       get the order of a parameter by its name
       \param pname the name of the parameter
       \return the order of the parameter
     */
    size_t get_param_order(const Tstr& pname)const
    {
      if(p_model==0)
	{
	  throw model_undefined();
	}
      return p_model->get_param_order(pname);
    }

    /**
       get the number of parameters
       \return the number of parameters
     */
    size_t get_num_params()const
    {
      if(p_model==0)
	{
	  throw model_undefined();
	}
      return p_model->get_num_params();
    }

    /**
       get all params
       \return the vector containing the values of all parameters
     */
    Tp get_all_params()const
    {
      if(p_model==0)
	{
	  throw model_undefined();
	}
      //return current_param;
      return p_model->get_all_params();
    }

    /**
       set the optimization method used to perform the model fitting
       \param pm the opt_method to be used
    */
    void set_method(const opt_method<Ts,Tp>& pm)
    {
      //assert(p_optimizer!=0);
      optengine.set_opt_method(pm);
    }

    /**
       set the precision
       \param y the precision
     */
    void set_precision(typename element_type_trait<Tp>::element_type y)
    {
      optengine.set_precision(y);
    }


    /**
       perform the fitting
     */
    Tp fit()
    {
      //      assert(p_model!=0);
      if(p_model==0)
	{
	  throw model_undefined();
	}
      if(p_data_set==0)
	{
	  throw data_unloaded();
	}
      //assert(p_optimizer!=0);
      //assert(p_data_set!=0);
      //assert(p_statistic!=0);
      if(p_statistic==0)
	{
	  throw statistic_undefined();
	}

      optengine.set_func_obj(*p_statistic);
      Tp current_param;
      Tp current_lower_limits;
      Tp current_upper_limits;
      opt_eq(current_param,p_model->get_all_params());
      opt_eq(current_lower_limits,p_model->get_all_lower_limits());
      opt_eq(current_upper_limits,p_model->get_all_upper_limits());
      Tp start_point;
      Tp upper_limits;
      Tp lower_limits;
      opt_eq(start_point,p_model->deform_param(current_param));
      opt_eq(upper_limits,p_model->deform_param(current_upper_limits));
      opt_eq(lower_limits,p_model->deform_param(current_lower_limits));

      //      std::cout<<start_point.size()<<std::endl;
      
      
      //for(int i=0;i<(int)start_point.size();++i)
      //	{
      //	  std::cout<<start_point[i]<<",";
      //	}
      //std::cout<<std::endl;
      //assert(start_point.size()!=0);
      if(get_size(start_point)==0)
	{
	  //return start_point;
	  return p_model->get_all_params();
	}
      optengine.set_lower_limit(lower_limits);
      optengine.set_upper_limit(upper_limits);
      optengine.set_start_point(start_point);
      
      Tp result;
      opt_eq(result,optengine.optimize());

      Tp decurrent_param;
      opt_eq(decurrent_param,p_model->reform_param(result));
      //current_param.resize(decurrent_param.size());
      resize(current_param,get_size(decurrent_param));
      opt_eq(current_param,decurrent_param);
      p_model->set_param_value(current_param);
      //   return current_param;
      return p_model->get_all_params();
    }

  };



  /**
     \brief virtual class representing a statistic
     \tparam Ty the type of the model return type
     \tparam Tx the type of the model self-var
     \tparam Tp the type of the model param
     \tparam Ts statistic type
     \tparam Tstr the type of string used
  */
  template<typename Ty,typename Tx,typename Tp,typename Ts,typename Tstr=std::string>
  class statistic
    :public func_obj<Ts,Tp>
  {
  private:
    fitter<Ty,Tx,Tp,Ts,Tstr>* p_fitter;
  
  private:
    virtual statistic<Ty,Tx,Tp,Ts,Tstr>* do_clone()const=0;

    virtual void do_destroy()
    {
      delete this;
    }

  public:
    /**
       clone the existing object
       \return the clone of self
     */
    statistic<Ty,Tx,Tp,Ts,Tstr>* clone()const
    {
      return this->do_clone();
    }
    
    /**
       destroy the cloned object
     */
    void destroy()
    {
      return do_destroy();
    }

    /**
       default construct
     */
    statistic()
      :p_fitter(0)
    {}
    
    /**
       copy construct
     */
    statistic(const statistic& rhs)
      :p_fitter(rhs.p_fitter)
    {}

    /**
       assignment operator
     */
    statistic& operator=(const statistic& rhs)
    {
      if(this==&rhs)
	{
	  return *this;
	}
      p_fitter=rhs.p_fitter;
      return *this;
    }
    

    /**
       destructure function
     */
    virtual ~statistic()
    {}

    /**
       set the fitter
       \param pfitter the fitter to be linked
    */
    virtual void set_fitter(fitter<Ty,Tx,Tp,Ts,Tstr>& pfitter)
    {
      p_fitter=&pfitter;
    }


    /**
       get the attached fitter
       \return the const reference of the fitter object
     */
    virtual const fitter<Ty,Tx,Tp,Ts,Tstr>& get_fitter()const
    {
      if(p_fitter==0)
	{
	  throw fitter_unset();
	}
      return *p_fitter;
    }
		
    /**
       evaluating the model
       \param x the self-var
       \param p the parameter
       \return the evaluated model value
     */
    Ty eval_model(const Tx& x,const Tp& p)
    {
      if(p_fitter==0)
	{
	  throw fitter_unset();
	}
      return p_fitter->eval_model(x,p);
    }

    /**
       get the data_set object managed by the fitter object
       \return the const reference of the data_set object
     */
    const data_set<Ty,Tx>& get_data_set()const
    {
      if(p_fitter==0)
	{
	  throw fitter_unset();
	}
      return p_fitter->get_data_set();
    }

  };


  /**
     \brief Used to modify the parameter, e.g., freezing, bind
     \tparam Ty the type of the model return type
     \tparam Tx the type of the model self-var
     \tparam Tp the type of the model param
     \tparam Tstr the type of string used
  */
  template <typename Ty,typename Tx,typename Tp,typename Tstr=std::string>
  class param_modifier
  {
  private:
    model<Ty,Tx,Tp,Tstr>* p_model;
  public:
    /**
       constructing full parameter list from the free parameters
     */
    Tp reform(const Tp& p)const
    {
      return do_reform(p);
    }

    /**
       constructing the free parameter from the full parameters
     */
    Tp deform(const Tp& p)const
    {
      return do_deform(p);
    }

    /**
       return the clone of self
       \return the clone of self
     */
    param_modifier<Ty,Tx,Tp,Tstr>* clone()const
    {
      return do_clone();
    }
    
    /**
       destroy the cloned object
     */
    void destroy()
    {
      do_destroy();
    }

  public:
    /**
       the default construct function
     */
    param_modifier()
      :p_model(0)
    {}
    
    /**
       copy construct function
     */
    param_modifier(const param_modifier& rhs)
      :p_model(rhs.p_model)
    {}

    /**
       assignment operator
     */
    param_modifier& operator=(const param_modifier& rhs)
    {
      if(this==&rhs)
	{
	  return *this;
	}
      p_model=rhs.p_model;
      return *this;
    }
    
  public:
    
    /**
       Attach the fitter object
       \param pf the fitter to be attached
     */
    void set_model(model<Ty,Tx,Tp,Tstr>& pf)
    {
      p_model=&pf;
      update();
    }

    /**
       get the model attached
       \return the const reference of the model
     */
    const model<Ty,Tx,Tp,Tstr>& get_model()const
    {
      if(p_model==0)
	{
	  std::cout<<"dajf;asdjfk;";
	  throw model_undefined();
	}
      return *(this->p_model);
    }

    /**
       calculate the number of free parameters
     */
    size_t get_num_free_params()const
    {
      return do_get_num_free_params();
    }

    /**
       report the status of parameters
       \param pname parameter name
       \return the string used to describe the parameter
     */
    Tstr report_param_status(const Tstr& name)const
    {
      return do_report_param_status(name);
    }

    /**
       destruct function
     */
    virtual ~param_modifier(){}
  private:
    virtual Tp do_reform(const Tp& p)const=0;
    virtual Tp do_deform(const Tp& p)const=0;
    virtual size_t do_get_num_free_params()const=0;
    virtual Tstr do_report_param_status(const Tstr&)const=0;
    virtual void update(){}

    virtual param_modifier<Ty,Tx,Tp,Tstr>* do_clone()const=0;
    
    virtual void do_destroy()
    {
      delete this;
    }

  };
}


#endif
//EOF

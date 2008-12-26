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


  template<typename Ty,typename Tx>
  class data
  {
  private:
    Tx x,x_lower_err,x_upper_err;
    Ty y,y_lower_err,y_upper_err;
  public:
    data(const Tx& _x,const Ty& _y,const Ty& _y_lower_err,const Ty& _y_upper_err,const Tx& _x_lower_err,const Tx& _x_upper_err)
    {
      opt_eq(x,_x);
      opt_eq(x_lower_err,_x_lower_err);
      opt_eq(x_upper_err,_x_upper_err);
      opt_eq(y,_y);
      opt_eq(y_lower_err,_y_lower_err);
      opt_eq(y_upper_err,_y_upper_err);
 
    }

    data()
      :x(),
       x_lower_err(),
       x_upper_err(),
       y(),
       y_lower_err(),
       y_upper_err()
    {}

    data(const data& rhs)
    {
      opt_eq(x,rhs.x);
      opt_eq(x_lower_err,rhs.x_lower_err);
      opt_eq(x_upper_err,rhs.x_upper_err);
      opt_eq(y,rhs.y);
      opt_eq(y_lower_err,rhs.y_lower_err);
      opt_eq(y_upper_err,rhs.y_upper_err);
    }

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
    const Tx& get_x()const
    {
      return x;
    }
    
    const Tx& get_x_lower_err()const
    {
      return x_lower_err;
    }
    
    const Tx& get_x_upper_err()const
    {
      return x_upper_err;
    }

    const Ty& get_y()const
    {
      return y;
    }
    
    const Ty& get_y_lower_err()const
    {
      return y_lower_err;
    }
    
    const Ty& get_y_upper_err()const
    {
      return y_upper_err;
    }


    void set_x(const Tx& _x)
    {
      opt_eq(x,_x);
    }
    
    void set_x_lower_err(const Tx& _x)
    {
      opt_eq(x_lower_err,_x);
    }
    
    void set_x_upper_err(const Tx& _x)
    {
      opt_eq(x_upper_err,_x);
    }

    void set_y(const Ty& _y)
    {
      opt_eq(y,_y);
    }
    
    void set_y_lower_err(const Ty& _y)
    {
      opt_eq(y_lower_err,_y);
    }
    
    void set_y_upper_err(const Ty& _y)
    {
      opt_eq(y_upper_err,_y);
    }
    

  };

  ////////////////////////////////////
  ///class data_set///////////////////
  ///contain a set of data////////////
  ////////////////////////////////////
  
  
  template <typename Ty,typename Tx>
  class data_set
  {
  private:
    
    virtual const data<Ty,Tx>& do_get_data(size_t i)const=0;
    virtual size_t do_size()const=0;
    virtual void do_push_back(const data<Ty,Tx>&)=0;
    virtual void do_clear()=0;
    virtual data_set<Ty,Tx>* do_clone()const=0;

    virtual void do_destroy()
    {
      delete this;
    }
  public:
    const data<Ty,Tx>& get_data(size_t i)const
    {
      return this->do_get_data(i);
    }
    size_t size()const
    {
      return do_size();
    }
    void push_back(const data<Ty,Tx>& d)
    {
      return do_push_back(d);
    }
    void clear()
    {
      do_clear();
    }
    
    data_set<Ty,Tx>* clone()const
    {
      return this->do_clone();
    }

    void destroy()
    {
      do_destroy();
    }

    virtual ~data_set(){}
      
  };

  ///////////////////////////////////////////////
  /////class param_info//////////////////////////
  /////record the information of one parameter///
  /////including the name, default value/////////
  ///////////////////////////////////////////////

  
  template <typename Tp,typename Tstr=std::string>
  class param_info
  {
  private:
    Tstr name;
    //bool frozen;
    typename element_type_trait<Tp>::element_type default_value;
    
  public:
    param_info(const Tstr& _name,
	       const typename element_type_trait<Tp>::element_type& _v)
      :name(_name),default_value(_v){}

    param_info()
      :name()
    {}

    param_info(const param_info& rhs)
      :name(rhs.name)
    {
      opt_eq(default_value,rhs.default_value);
    }
    
    param_info& operator=(const param_info& rhs)
    {
      name=rhs.name;
      opt_eq(default_value,rhs.default_value);
      return *this;
    }

    const Tstr& get_name()const
    {
      return this->name;
    }

    const typename element_type_trait<Tp>::element_type& get_default_value()const
    {
      return default_value;
    }

    void set_default_value(const typename element_type_trait<Tp>::element_type& x)
    {
      opt_eq(default_value,x);
    }

    void set_name(const Tstr& _name)
    {
      name=_name;
    }
  };





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
    model<Ty,Tx,Tp,Tstr>* clone()const
    {
      return do_clone();
    }

    void destroy()
    {
      do_destroy();
    }
  public:
    model()
      :p_param_modifier(0)
    {}
    
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
    
    virtual ~model()
    {
      if(p_param_modifier)
	{
	  //delete p_param_modifier;
	  p_param_modifier->destroy();
	}
    }
    
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

    void set_param_modifier()
    {
      if(p_param_modifier!=0)
	{
	  //delete p_param_modifier;
	  p_param_modifier->destroy();
	}
      p_param_modifier=0;
    }
    
    param_modifier<Ty,Tx,Tp,Tstr>& get_param_modifier()
    {
      if(p_param_modifier==0)
	{
	  throw param_modifier_undefined();
	}
      return *p_param_modifier;
    }

    Tstr report_param_status(const Tstr& s)const
    {
      if(p_param_modifier==0)
	{
	  return Tstr();
	}
      
      return p_param_modifier->report_param_status(s);
	
    }
    

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

    const param_info<Tp,Tstr>& get_param_info(size_t n)const
    {
      return param_info_list[n%get_num_params()];
    }

    
    Tp get_all_params()const
    {
      Tp result;
      resize(result,param_info_list.size());
      for(size_t i=0;i<param_info_list.size();++i)
	{
	  //opt_eq(get_element(result,i),param_info_list[i].get_default_value());
	  set_element(result,i,param_info_list[i].get_default_value());
	  //get_element((Tp)result,i);
	}
      return result;
    }

  
    size_t get_num_params()const
    {
      return param_info_list.size();
    }

    size_t get_num_free_params()const
    {
      if(p_param_modifier)
	{
	  return p_param_modifier->get_num_free_params();
	}
      return get_num_params();
    }

    void set_param_value(const Tstr& pname,
			 const typename element_type_trait<Tp>::element_type& v)
    {
      //int porder=0;
      for(typename std::vector<param_info<Tp,Tstr> >::iterator i=param_info_list.begin();
	  i!=param_info_list.end();++i)
	{
	  if(i->get_name()==pname)
	    {
	      i->set_default_value(v);
	      return;
	    }
	}
      std::cerr<<"param "<<pname<<" unfound"<<std::endl;
      throw param_not_found();
    }

    void set_param_value(const Tp& param)
    {
      for(size_t i=0;i<param_info_list.size();++i)
	{
	  param_info_list[i].set_default_value(get_element(param,i));
	}
    }

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
    void push_param_info(const param_info<Tp,Tstr>& pinfo)
    {
      param_info_list.push_back(pinfo);
      //      this->num_free_params++;
    }
    
    void clear_param_info()
    {
      //      this->num_free_params=0;
      param_info_list.clear();
    }



  public:
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

    
    Ty eval(const Tx& x,const Tp& p)
    {
      return do_eval(x,reform_param(p));
    }

    virtual Ty do_eval(const Tx& x,const Tp& p)=0;

  private:
    virtual Tstr do_to_string()const
    {
      return Tstr();
    }
    
  };



  template<typename Ty,typename Tx,typename Tp,typename Ts=Ty,typename Tstr=std::string>
  class fitter
  {
  public:
    model<Ty,Tx,Tp,Tstr>* p_model;
    statistic<Ty,Tx,Tp,Ts,Tstr>* p_statistic;
    data_set<Ty,Tx>* p_data_set;
    optimizer<Ts,Tp> optengine;
  public:
    fitter()
      :p_model(0),p_statistic(0),p_data_set(0),optengine()
    {}

    
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
    

    Ty eval_model(const Tx& x,const Tp& p)
    {
      if(p_model==0)
	{
	  throw model_undefined();
	}
      return p_model->eval(x,p);
    }
    

  public:
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
    /*
    void set(const model<Ty,Tx,Tp>& m)
    {
      set_model(m);
    }
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
    /*
    void set(const statistic<Ty,Tx,Tp>& s)
    {
      set_statistic(s);
    }
    */

    void set_param_modifier(const param_modifier<Ty,Tx,Tp,Tstr>& pm)
    {
      if(p_model==0)
	{
	  throw model_undefined();
	}
      p_model->set_param_modifier(pm);
    }

    void set_param_modifier()
    {
      if(p_model==0)
	{
	  throw model_undefined();
	}
      p_model->set_param_modifier();
    }

    param_modifier<Ty,Tx,Tp,Tstr>& get_param_modifier()
    {
      if(p_model==0)
	{
	  throw model_undefined();
	}
      return p_model->get_param_modifier();
    }

    Tstr report_param_status(const Tstr& s)const
    {
      if(p_model==0)
	{
	  throw model_undefined();
	}
      return p_model->report_param_status(s);
    }
    
    /*
    void set(const param_modifier<Ty,Tx,Tp>& pm)
    {
      set_param_modifier(pm);
    }
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
	
    const data_set<Ty,Tx>& datas()const
    {
      if(p_data_set==0)
	{
	  throw data_unloaded();
	}
      return *(this->p_data_set);
    }

    model<Ty,Tx,Tp,Tstr>& model()
    {
      if(p_model==0)
	{
	  throw model_undefined();
	}
      return *(this->p_model);
    }

    statistic<Ty,Tx,Tp,Ts,Tstr>& statistic()
    {
      if(p_statistic==0)
	{
	  throw statistic_undefined();
	}
      return *(this->p_statistic);
    }

    opt_method<Ts,Tp>& method()
    {
      return optengine.method();
    }
    

  public:
    void set_param_value(const Tstr& pname,
			 const typename element_type_trait<Tp>::element_type& v)
    {
      if(p_model==0)
	{
	  throw model_undefined();
	}
      p_model->set_param_value(pname,v);
    }

    void set_param_value(const Tp& param)
    {
      if(p_model==0)
	{
	  throw model_undefined();
	}
      p_model->set_param_value(param);
    }

    typename element_type_trait<Tp>::element_type get_param_value(const Tstr& pname)const
    {
      if(p_model==0)
	{
	  throw model_undefined();
	}
      return p_model->get_param_info(pname).get_default_value();
    }

    const param_info<Tp,Tstr>& get_param_info(const Tstr& pname)const
    {
      if(p_model==0)
	{
	  throw model_undefined();
	}
      return p_model->get_param_info(pname);
    }

    const param_info<Tp,Tstr>& get_param_info(size_t n)const
    {
      if(p_model==0)
	{
	  throw model_undefined();
	}
      return p_model->get_param_info(n);
    }

    size_t get_param_order(const Tstr& pname)const
    {
      if(p_model==0)
	{
	  throw model_undefined();
	}
      return p_model->get_param_order(pname);
    }

    size_t get_num_params()const
    {
      if(p_model==0)
	{
	  throw model_undefined();
	}
      return p_model->get_num_params();
    }

    Tp get_all_params()const
    {
      if(p_model==0)
	{
	  throw model_undefined();
	}
      //return current_param;
      return p_model->get_all_params();
    }

    void set_method(const opt_method<Ts,Tp>& pm)
    {
      //assert(p_optimizer!=0);
      optengine.set_opt_method(pm);
    }
    /*
    void set(const opt_method<Ty,Tp>& pm)
    {
      set_method(pm);
    }
    */
    void set_precision(typename element_type_trait<Tp>::element_type y)
    {
      optengine.set_precision(y);
    }

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
      opt_eq(current_param,p_model->get_all_params());
      Tp start_point;
      opt_eq(start_point,p_model->deform_param(current_param));
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


  template<typename Ty,typename Tx,typename Tp,typename Ts,typename Tstr=std::string>
  class statistic
    :public func_obj<Ts,Tp>
  {
  public:
    fitter<Ty,Tx,Tp,Ts,Tstr>* p_fitter;
  
  private:
    virtual statistic<Ty,Tx,Tp,Ts,Tstr>* do_clone()const=0;

    virtual void do_destroy()
    {
      delete this;
    }

  public:
    statistic<Ty,Tx,Tp,Ts,Tstr>* clone()const
    {
      return this->do_clone();
    }
    
    void destroy()
    {
      return do_destroy();
    }
    statistic()
      :p_fitter(0)
    {}
    
    statistic(const statistic& rhs)
      :p_fitter(rhs.p_fitter)
    {}

    statistic& operator=(const statistic& rhs)
    {
      if(this==&rhs)
	{
	  return *this;
	}
      p_fitter=rhs.p_fitter;
      return *this;
    }
    
    virtual ~statistic()
    {}

    virtual void set_fitter(fitter<Ty,Tx,Tp,Ts,Tstr>& pfitter)
    {
      p_fitter=&pfitter;
    }

    virtual const fitter<Ty,Tx,Tp,Ts,Tstr>& get_fitter()const
    {
      if(p_fitter==0)
	{
	  throw fitter_unset();
	}
      return *p_fitter;
    }
		
    Ty eval_model(const Tx& x,const Tp& p)
    {
      if(p_fitter==0)
	{
	  throw fitter_unset();
	}
      return p_fitter->eval_model(x,p);
    }

		
    const data_set<Ty,Tx>& datas()const
    {
      if(p_fitter==0)
	{
	  throw fitter_unset();
	}
      return p_fitter->datas();
    }

  };

  template <typename Ty,typename Tx,typename Tp,typename Tstr=std::string>
  class param_modifier
  {
  private:
    model<Ty,Tx,Tp,Tstr>* p_model;
  public:
    Tp reform(const Tp& p)const
    {
      return do_reform(p);
    }
    Tp deform(const Tp& p)const
    {
      return do_deform(p);
    }

    param_modifier<Ty,Tx,Tp,Tstr>* clone()const
    {
      return do_clone();
    }

    void destroy()
    {
      do_destroy();
    }

  public:

    param_modifier()
      :p_model(0)
    {}
    
    param_modifier(const param_modifier& rhs)
      :p_model(rhs.p_model)
    {}

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
    void set_model(model<Ty,Tx,Tp,Tstr>& pf)
    {
      p_model=&pf;
      update();
    }

    const model<Ty,Tx,Tp,Tstr>& get_model()const
    {
      if(p_model==0)
	{
	  std::cout<<"dajf;asdjfk;";
	  throw model_undefined();
	}
      return *(this->p_model);
    }

    size_t get_num_free_params()const
    {
      return do_get_num_free_params();
    }

    Tstr report_param_status(const Tstr& name)const
    {
      return do_report_param_status(name);
    }


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
  

  
};


#endif
//EOF

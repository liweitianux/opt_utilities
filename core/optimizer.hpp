#ifndef OPTIMZER_H_
#define OPTIMZER_H_
//#define DEBUG
#include <cstddef>
#include "opt_traits.hpp"
#include "opt_exception.hpp"
#include <cstdlib>
#include <functional>
#ifdef DEBUG
#include <iostream>
using namespace std;
#endif

namespace opt_utilities
{
  /////////Forward declare///////////////////////////////////
  template <typename rT,typename pT>
  class optimizer;
  
  template <typename rT,typename pT>
  class func_obj;
  
  template <typename rT,typename pT>
  class opt_method;


  //////////////Target Function/////////////////////
  ///An eval function should be implemented/////////
  ///The eval function return the function value////
  ///which is wrapped by the func_obj///////////////
  //////////////////////////////////////////////////
  template <typename rT,typename pT>
  class func_obj
    :public std::unary_function<pT,rT>
  {
  private:
    virtual rT do_eval(const pT&)=0;
    virtual func_obj<rT,pT>* do_clone()const=0;
    virtual void do_destroy()
    {
      delete this;
    }

  public:
  public:
    func_obj<rT,pT>* clone()const
    {
      return do_clone();
    }

    void destroy()
    {
      do_destroy();
    }

    rT operator()(const pT& p)
    {
      return do_eval(p);
    }
    

    rT eval(const pT& p)
    {
      return do_eval(p);
    };
    virtual ~func_obj(){};
    //    virtual XT walk(XT,YT)=0;
  };
  

  ///////////////Optimization method//////////////////////
  
  template <typename rT,typename pT>
  class opt_method
  {
  public:
    virtual void do_set_optimizer(optimizer<rT,pT>&)=0;
    virtual void do_set_precision(rT)=0;
    virtual pT do_optimize()=0;
    virtual void do_set_start_point(const pT& p)=0;
    virtual opt_method<rT,pT>* do_clone()const=0;

    virtual void do_destroy()
    {
      delete this;
    }
  public:
    void  set_optimizer(optimizer<rT,pT>& op)
      {
	do_set_optimizer(op);
      };

    void set_precision(rT x)
    {
      do_set_precision(x);
    }

    void set_start_point(const pT& p)
    {
      do_set_start_point(p);
    }
    
    pT optimize()
      {
	return do_optimize();
      };
    
    opt_method<rT,pT>* clone()const
    {
      return do_clone();
    }

    void destroy()
    {
      do_destroy();
    }

    virtual ~opt_method(){};
  };
  
  
  ///////////Optimizer////////////////////////////////////
  template <typename rT,typename pT>
  class optimizer
  {
  public:

  private:

    ////////////pointer to an optimization method objection////////////
    ////////////The optimization method implements a certain method ///
    ////////////Currently only Mont-carlo method is implemented////////
    opt_method<rT,pT>* p_opt_method;
    func_obj<rT,pT>* p_func_obj;
    
  public:
     optimizer()
      :p_opt_method(0),p_func_obj(0)
    {}

    optimizer(func_obj<rT,pT>& fc,const opt_method<rT,pT>& om)
      :p_func_obj(fc.clone()),p_opt_method(om.clone())
    {
      p_opt_method->set_optimizer(*this);
    }
    
    optimizer(const optimizer& rhs)
      :p_opt_method(0),p_func_obj(0)
    {
      if(rhs.p_func_obj!=0)
	{
	  set_func_obj(*(rhs.p_func_obj));
	}
      if(rhs.p_opt_method!=0)
	{
	  set_opt_method(*(rhs.p_opt_method));
	}
    }

    optimizer& operator=(const optimizer& rhs)
    {
      if(this==&rhs)
	{
	  return *this;
	}
      if(rhs.p_func_obj!=0)
	{
	  set_func_obj(*(rhs.p_func_obj));
	}
      if(rhs.p_opt_method!=0)
	{
	  set_opt_method(*(rhs.p_opt_method));
	}
      return *this;
    }
    

    virtual ~optimizer()
    {
      if(p_func_obj!=0)
	{
	  //delete p_func_obj;
	  p_func_obj->destroy();
	}
      if(p_opt_method!=0)
	{
	  //delete p_opt_method;
	  p_opt_method->destroy();
	}
    };

  public:
    ////////////Re-set target function object///////////////////////////
    void set_func_obj(const func_obj<rT,pT>& fc)
    {
      if(p_func_obj!=0)
	{
	  //delete p_func_obj;
	  p_func_obj->destroy();
	}
      p_func_obj=fc.clone();
      if(p_opt_method!=0)
	{
	  p_opt_method->set_optimizer(*this);
	}
    }

    ////////////Re-set optimization method//////////////////////////////
    void set_opt_method(const opt_method<rT,pT>& om)
    {
      if(p_opt_method!=0)
	{
	  //delete p_opt_method;
	  p_opt_method->destroy();
	}
      
      p_opt_method=om.clone();
      p_opt_method->set_optimizer(*this);
    }

    opt_method<rT,pT>& method()
    {
      if(p_opt_method==0)
	{
	  throw opt_method_undefined();
	}
      return *(this->p_opt_method);
    }

    void set_precision(rT x)
    {
      if(p_opt_method==0)
	{
	  throw opt_method_undefined();
	}
      p_opt_method->set_precision(x);
    }

    void set_start_point(const pT& x)
    {
      if(p_opt_method==0)
	{
	  throw opt_method_undefined();
	}
      p_opt_method->set_start_point(x);
    }
    
    ////////////Just call the eval function in the target function object///
    ////////////In case the pointer to a target function is uninitialed/////
    ////////////a zero-value is returned////////////////////////////////////
    rT eval(const pT& x)
    {
      if(p_func_obj==0)
	{
	  throw target_function_undefined();
	}
      return p_func_obj->eval(x);
    }

	

    ////////////Just call the optimize() function in the optimization method//
    ////////////If no optimization method is given, an zero-value is returned/
    pT optimize()
    {
      if(p_opt_method==0)
	{
	  throw opt_method_undefined();
	}
      if(p_func_obj==0)
	{
	  throw target_function_undefined();
	}
      return p_opt_method->optimize();
    }
    
    ////////////Function that offers the access to the target function object///
    func_obj<rT,pT>* ptr_func_obj()
    {
      return p_func_obj;
    }
    
  };
}
  
#endif
//EOF



/**
   \file conjugate_gradient.hpp
   \brief conjugate gradient optimization method
   \author Junhua Gu
 */

#ifndef CONJUGATE_GRADIENT
#define CONJUGATE_GRADIENT
#define OPT_HEADER
#include <core/optimizer.hpp>
//#include <blitz/array.h>
#include <limits>
#include <cassert>
#include <cmath>
#include "../linmin/linmin.hpp"
#include <algorithm>
#include <iostream>
#include <math/num_diff.hpp>
namespace opt_utilities
{
  /**
     \brief Impliment of an optimization method
     \tparam rT return type of the object function
     \tparam pT parameter type of the object function
   */
  template <typename rT,typename pT>
  class conjugate_gradient
    :public opt_method<rT,pT>
  {
  public:
    typedef pT array1d_type;
    typedef rT T;
  private:
    func_obj<rT,pT>* p_fo;
    optimizer<rT,pT>* p_optimizer;
    volatile bool bstop;
    
    const char* do_get_type_name()const
    {
      return "conjugate gradient";
    }
  private:
    array1d_type start_point;
    array1d_type end_point;
    
  private:
    rT threshold;
  private:
    rT func(const pT& x)
    {
      assert(p_fo!=0);
      return p_fo->eval(x);
    }

   
  private:


    
  public:
    
    conjugate_gradient()
      :threshold(1e-4)
    {}

    virtual ~conjugate_gradient()
    {
    };

    conjugate_gradient(const conjugate_gradient<rT,pT>& rhs)
      :opt_method<rT,pT>(rhs),p_fo(rhs.p_fo),p_optimizer(rhs.p_optimizer),
       start_point(rhs.start_point),
       end_point(rhs.end_point),
       threshold(rhs.threshold)
    {
    }

    conjugate_gradient<rT,pT>& operator=(const conjugate_gradient<rT,pT>& rhs)
    {
      threshold=rhs.threshold;
      p_fo=rhs.p_fo;
      p_optimizer=rhs.p_optimizer;
      start_point=rhs.start_point;
      end_point=rhs.end_point;
      threshold=rhs.threshold;
    }
    
    opt_method<rT,pT>* do_clone()const
    {
      return new conjugate_gradient<rT,pT>(*this);
    }
    
    void do_set_start_point(const array1d_type& p)
    {
      resize(start_point,get_size(p));
      opt_eq(start_point,p);
    }

    array1d_type do_get_start_point()const
    {
      return start_point;
    }

    void do_set_lower_limit(const array1d_type& p)
    {}

    void do_set_upper_limit(const array1d_type& p)
    {}

    void do_set_precision(rT t)
    {
      threshold=t;
    }

    rT do_get_precision()const
    {
      return threshold;
    }

    void do_set_optimizer(optimizer<rT,pT>& o)
    {
      p_optimizer=&o;
      p_fo=p_optimizer->ptr_func_obj();
    }
    
    
    
    pT do_optimize()
    {
      bstop=false;
      opt_eq(end_point,start_point);
      pT xn;
      opt_eq(xn,start_point);
      pT Delta_Xn1(gradient(*p_fo,start_point));
      for(size_t i=0;i<get_size(start_point);++i)Delta_Xn1[i]=-Delta_Xn1[i];
      rT alpha=0;
      linmin(start_point,Delta_Xn1,alpha,(*p_fo));
      for(size_t i=0;i<get_size(start_point);++i)xn[i]=start_point[i]+alpha*Delta_Xn1[i];
      pT LX;
      opt_eq(LX,Delta_Xn1);
      for(int n=1;;++n)
	{
	  pT Delta_Xn(gradient(*p_fo,xn));
	  for(size_t i=0;i<get_size(start_point);++i)Delta_Xn[i]=-Delta_Xn[i];
	  ////calc beta n
	  rT betan;
	  rT b1(0),b2(0);
	  for(size_t i=0;i<get_size(start_point);++i)
	    {
	      b1+=Delta_Xn[i]*(Delta_Xn[i]-Delta_Xn1[i]);
	      b2+=Delta_Xn1[i]*Delta_Xn1[i];
	    }
	  betan=max(rT(0),b1/b2);
	  ////
	  for(size_t i=0;i<get_size(start_point);++i)
	    LX[i]=Delta_Xn[i]+betan*LX[i];
	  linmin(xn,LX,alpha,(*p_fo));
	  for(size_t i=0;i<get_size(start_point);++i)
	    xn[i]+=alpha*LX[i];
	  rT delta=0;
	  rT xn_abs=0;
	  for(size_t i=0;i<get_size(start_point);++i)
	    {
	      delta+=LX[i]*LX[i];
	      xn_abs+=xn[i]*xn[i];
	    }
	  if(delta*alpha*alpha<threshold)
	    {
	      opt_eq(end_point,xn);
	      break;
	    }
	  opt_eq(Delta_Xn1,Delta_Xn);
	}
      return end_point;
    }
    
    void do_stop()
    {
      bstop=true;
    }

  };

}


#endif
//EOF

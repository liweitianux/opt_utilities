#ifndef BFGS_METHOD
#define BFGS_METHOD
#define OPT_HEADER
#include <core/optimizer.hpp>
//#include <blitz/array.h>
#include <limits>
#include <cstdlib>
#include <core/opt_traits.hpp>
#include <math/num_diff.hpp>
#include <cassert>
#include <cmath>
#include <ctime>
#include <vector>
#include <algorithm>
/*
 *
*/
#include <iostream>
using std::cout;
using std::endl;

namespace opt_utilities
{

  template <typename rT,typename pT>
  class bfgs_method
    :public opt_method<rT,pT>
  {
  private:
    pT start_point;
    rT threshold;
    func_obj<rT,pT>* p_fo;
    optimizer<rT,pT>* p_optimizer;
    typedef typename element_type_trait<pT>::element_type element_type;
    element_type* mem_pool;
    element_type** invBk;
    element_type** invBk1;
    bool bstop;
  private:
    const char* do_get_type_name()const
    {
      return "asexual genetic algorithm";
    }
    
    rT func(const pT& x)
    {
      assert(p_fo!=0);
      return p_fo->eval(x);
    }

  public:
    bfgs_method()
      :p_fo(0),p_optimizer(0),
       invBk(0),invBk1(0);
    {
      
    }
    
    virtual ~bfgs_method()
    {     
      destroy_workspace();
    };
    
    bfgs_method(const bfgs_method<rT,pT>& rhs)
      :p_fo(rhs.p_fo),p_optimizer(rhs.p_optimizer),
       threshold(rhs.threshold)
    {
    }

    bfgs_method<rT,pT>& operator=(const bfgs_method<rT,pT>& rhs)
    {
      p_fo=rhs.p_fo;
      p_optimizer=rhs.p_optimizer;
      threshold=rhs.threshold;
    }

    opt_method<rT,pT>* do_clone()const
    {
      return new bfgs_method<rT,pT>(*this);
    }
    
    void init_workspace(int n)
    {
      destroy_workspace();
      mem_pool=new element_type[n*n*2];
      invBk=new element_type*[n];
      invBk1=new element_type*[n];

      for(size_t i=0;i!=n;++i)
	{
	  invBk[i]=mem_pool+i*n;
	  invBk1[i]=invBk[i]+n*n;
	}
      for(size_t i=0;i!=n;++i)
	{
	  for(size_t j=0;j!=n;++j)
	    {
	      invBk[i][j]=(i==j?1:0);
	    }
	}
    }

    void destroy_workspace()
    {
      delete[] mem_pool;
      delete[] invBk;
      delete[] invBk1;
    }

  public:
    
    void do_set_start_point(const pT& p)
    {
      start_point=p;
      init_workspace(get_size(p));
    }

    pT do_get_start_point()const
    {
    }
    
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
      pT s;
      resize(s,get_size(start_point));
      pT old_grad;
      pT y;
      resize(old_grad,get_size(start_point));
      resize(y,get_size(start_point));
      for(size_t i=0;i!=get_size(p);++i)
	{
	  set_element(old_grad,i,gradient(*p_fo,start_point,i));
	  set_element(s,i,0);
	  for(size_t j=0;j!=get_size(p);++j)
	    {
	      s[i]+=invBk[i][j]*old_grad[j];
	    }
	}
      linmin(start_point,s,*p_fo);
      for(size_t i=0;i!=get_size(p);++i)
	{
	  set_element(y,gradient(*p_fo,start_point,i)-get_element(old_grad,i));
	}
      rT sy=0;
      pT invBy;
      pT yinvB;
      resize(invBy,get_size(p));
      resize(yinvB,get_size(p));
      for(size_t i=0;i!=get_size(p);++i)
	{
	  sy+=s[i]*y[i];
	  for(size_t j=0;j!=get_size(p);++j)
	    {
	      invBy[i]+=invBk[i][j]*y[j];
	      yinvB[i]+=y[j]*invBk[j][i];
	    }
	}
      rT yinvBy=0;
      for(size_t i=0;i!=get_size(p);++i)
	{
	  yinvBy+=invBy[i]*y[i];
	}
      for(size_t i=0;i<get_size(p);++i)
	{
	  for(size_t j=0;j<get_size(p);++j)
	    {
	      invBk[i][j]+=((sy+yinvBy)*s[i]*s[j]/(sy*sy)-(invBy[i]*s[j]+s[i]*yinvB[j])/(sy));
	    }
	}
      
    }
    
    void do_stop()
    {
      bstop=true;
    }

  };

}


#endif
//EOF

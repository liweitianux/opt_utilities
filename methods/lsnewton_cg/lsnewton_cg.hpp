#ifndef LSNEWTON_GG_HPP
#define LSNEWTON_GG_HPP
#include <core/optimizer.hpp>
#include <math/num_diff.hpp>
#include <math/vector_operation.hpp>
#include <methods/linmin/linmin.hpp>
#include <cmath>

#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

namespace opt_utilities
{
  
  template<typename rT,typename pT>
  void lsnewton_cg_f(func_obj<rT,pT>& foo,pT& x0,const rT& threshold)
  {
    for(int k=0;;++k)
      {
	cerr<<k<<endl;
	rT abs_gk=0;
	pT gk(gradient(foo,x0));
	abs_gk=inner_product(gk,gk);
	abs_gk=std::sqrt(abs_gk);
	rT epsilon=std::min(rT(.5),std::sqrt(abs_gk))*abs_gk;
	pT zj;
	pT dj;
	pT rj;
	opt_eq(rj,gk);
	resize(dj,get_size(x0));
	resize(rj,get_size(x0));
	resize(zj,get_size(x0));
	for(int i=0;i!=get_size(gk);++i)
	  {
	    set_element(dj,i,-get_element(gk,i));
	    set_element(zj,i,0);
	    //cerr<<"gk:"<<i<<"\t"<<gk[i]<<endl;
	  }
	pT p;
	
	for(int j=0;;++j)
	  {
	    cerr<<j<<endl;
	    rT ep=std::sqrt(std::numeric_limits<rT>::epsilon());
	    rT djBkdj=0;
	    pT Bkdj;
	    resize(Bkdj,get_size(x0));
	    pT x1,x2;
	    typename element_type_trait<pT>::element_type h=1;
	    for(int i=0;i<get_size(x0);++i)
	      {
		h=max(rT(1),std::abs(get_element(dj,i)));
		//cerr<<"dj:"<<j<<"\t"<<dj[i]<<endl;
	      }
	    h*=ep;

	    
	    resize(x1,get_size(x0));
	    resize(x2,get_size(x0));
	    
	    for(int i=0;i<get_size(x0);++i)
	      {
		set_element(x1,i,get_element(x0,i)-h*get_element(dj,i));
		set_element(x2,i,get_element(x0,i)+h*get_element(dj,i));
		//cerr<<i<<"\t"<<x1[i]<<"\t"<<x2[i]<<"\t"<<h<<"\t"<<dj[i]<<endl;
	      }

	    pT gk1(gradient(foo,x1));
	    pT gk2(gradient(foo,x2));

	    for(int i=0;i<get_size(x0);++i)
	      {
		set_element(Bkdj,i,(get_element(gk2,i)-get_element(gk1,i))/h/2.);
		djBkdj+=get_element(dj,i)*get_element(Bkdj,i);
		//std::cerr<<"aa="<<Bkdj[i]<<endl;
		
	      }
	    if(djBkdj<0)
	      {
		if(j==0)
		  {
		    opt_eq(p,gk);
		  }
		else
		  {
		    opt_eq(p,zj);
		  }
		break;
	      }
	    double rjrj=inner_product(rj,rj);
	    cerr<<"rjrj="<<j<<"\t"<<rjrj<<endl;
	    
	    if(rjrj<threshold)
	      {
		cerr<<"fdfa"<<endl;
		return;
	      }
	    double alpha=rjrj/djBkdj;
	    double beta=0;
	    //cerr<<"alpha="<<alpha<<endl;
	    for(int i=0;i<get_size(x0);++i)
	      {
		set_element(zj,i,get_element(zj,i)+alpha*get_element(dj,i));
		set_element(rj,i,get_element(rj,i)+alpha*get_element(Bkdj,i));
		
		//std::cerr<<"rj:"<<i<<"\t"<<Bkdj[i]<<endl;
	      }
	    double rj1rj1=inner_product(rj,rj);
	    //cerr<<"rj1rj1=\t"<<rj1rj1<<"\t"<<sqrt(rj1rj1)<<endl;
	    if(std::sqrt(rj1rj1)<epsilon)
	      {
		//cerr<<"afd"<<endl;
		opt_eq(p,zj);
		break;
	      }
	    beta=rj1rj1/rjrj;
	    //cerr<<"rj1:\t"<<beta<<endl;
	    for(int i=0;i<get_size(x0);++i)
	      {
		set_element(dj,i,-get_element(rj,i)+beta*get_element(dj,i));
	      }
	  }
	rT fret;
	//std::cerr<<p.size()<<std::endl;
	linmin(x0,p,fret,foo);
	for(int i=0;i<get_size(x0);++i)
	  {
	    set_element(x0,i,get_element(x0,i)+fret*get_element(p,i));
	  }
      }
  }
  
  
  template <typename rT,typename pT>
  class lsnewton_cg
    :public opt_method<rT,pT>
  {
  public:
    typedef pT array1d_type;
    typedef rT T;
  private:
    func_obj<rT,pT>* p_fo;
    optimizer<rT,pT>* p_optimizer;
    
    //typedef blitz::Array<rT,2> array2d_type;
    
    
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

   
  public:
    lsnewton_cg()
      :threshold(1e-4)
    {}

    virtual ~lsnewton_cg()
    {
    };

    lsnewton_cg(const lsnewton_cg<rT,pT>& rhs)
      :p_fo(rhs.p_fo),p_optimizer(rhs.p_optimizer),
       start_point(rhs.start_point),
       end_point(rhs.end_point),
       threshold(rhs.threshold)
    {
    }

    lsnewton_cg<rT,pT>& operator=(const lsnewton_cg<rT,pT>& rhs)
    {
      threshold=rhs.threshold;
      p_fo=rhs.p_fo;
      p_optimizer=rhs.p_optimizer;
      opt_eq(start_point,rhs.start_point);
      opt_eq(end_point,rhs.end_point);
    }
    
    opt_method<rT,pT>* do_clone()const
    {
      return new lsnewton_cg<rT,pT>(*this);
    }
    
    void do_set_start_point(const array1d_type& p)
    {
      start_point.resize(get_size(p));
      opt_eq(start_point,p);
      
    }

    array1d_type do_get_start_point()const
    {
      return start_point;
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
      lsnewton_cg_f(*p_fo,start_point,threshold);
      opt_eq(end_point,start_point);
      return end_point;
    } 
  };
  

}

#endif
//EOF

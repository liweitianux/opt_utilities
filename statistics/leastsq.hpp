/**
   \file leastsq.hpp
 */

#ifndef LEAST_SQ_HPP
#define LeAST_SQ_HPP
#include <core/fitter.hpp>
#include <iostream>
#include <vector>
#include <cmath>
using std::cerr;using std::endl;

namespace opt_utilities
{

   /**
      \brief least-square statistic
      \tparam Ty the return type of model
      \tparam Tx the type of the self-var
      \tparam Tp the type of model parameter
      \tparam Ts the type of the statistic
      \tparam Tstr the type of the string used
   */
  template<typename Ty,typename Tx,typename Tp,typename Ts,typename Tstr>
  class leastsq
    :public statistic<Ty,Tx,Tp,Ts,Tstr>
  {
  private:
    bool verb;
    int n;
    
    
    statistic<Ty,Tx,Tp,Ts,Tstr>* do_clone()const
    {
      // return const_cast<statistic<Ty,Tx,Tp>*>(this);
      return new leastsq<Ty,Tx,Tp,Ts,Tstr>(*this);
    }
  public:
    void verbose(bool v)
    {
      verb=v;
    }
  public:
    leastsq()
      :verb(false)
    {}
    
    

    Ts do_eval(const Tp& p)
    {
      Ts result(0);
      for(int i=(this->get_data_set()).size()-1;i>=0;--i)
	{
	  Ty chi=(this->get_data_set().get_data(i).get_y()-eval_model(this->get_data_set().get_data(i).get_x(),p));
	  result+=chi*chi;

	}
      if(verb)
	{
	  n++;
	  if(n%10==0)
	    {

	      cerr<<result<<"\t";
	      for(size_t i=0;i<get_size(p);++i)
		{
		  cerr<<get_element(p,i)<<",";
		}
	      cerr<<endl;
	    }

	}
      
      return result;
    }
  };
  
}

#endif
//EOF



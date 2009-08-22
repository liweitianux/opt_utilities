/**
   \file cstat.hpp
 */

#ifndef CSTAT_HPP
#define CSTAT_HPP
#include <core/fitter.hpp>
#include <iostream>

using std::cout;using std::endl;
namespace opt_utilities
{

  /**
     c-statistic, max-likelihood method
     \tparam Ty the return type of model
     \tparam Tx the type of the self-var
     \tparam Tp the type of model parameter
     \tparam Ts the type of the statistic
     \tparam Tstr the type of the string used
   */
  template<typename Ty,typename Tx,typename Tp,typename Ts,typename Tstr>
  class cstat
    :public statistic<Ty,Tx,Tp,Ts,Tstr>
  {
  private:
    bool verb;
    int n;
  public:
    cstat()
      :verb(true)
    {}

    void verbose(bool v)
    {
      verb=v;
    }
  public:

    statistic<Ty,Tx,Tp,Ts,Tstr>* do_clone()const
    {
      // return const_cast<statistic<Ty,Tx,Tp>*>(this);
      return new cstat<Ty,Tx,Tp,Ts,Tstr>(*this);
    }

    Ts do_eval(const Tp& p)
    {
      Ts result(0);
      for(int i=(this->get_data_set()).size()-1;i>=0;--i)
	{
	  Ty model_y=eval_model(this->get_data_set().get_data(i).get_x(),p);
	  result-=this->get_data_set().get_data(i).get_y()*std::log(model_y);
	}

      if(verb)
	{
	  n++;
	  if(n%10==0)
	    {
	      cout<<"a:"<<result<<"\t";
	      for(int i=0;i<get_size(p);++i)
		{
		  cout<<get_element(p,i)<<",";
		}
	      cout<<endl;
	    }
	  
	}
      return result;
    }
  };
}

#endif
//EOF



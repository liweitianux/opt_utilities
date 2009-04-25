#ifndef CSTAT_HPP
#define CSTAT_HPP
#include <core/fitter.hpp>
#include <iostream>

using std::cout;using std::endl;
namespace opt_utilities
{
  template<typename Ty,typename Tx,typename Tp,typename Ts,typename Tstr>
  class cstat_poisson
    :public statistic<Ty,Tx,Tp,Ts,Tstr>
  {
  private:
    bool verb;
    int n;

    Ty lnfrac(Ty y)const
    {
      return y*log(y)-y;
    }
    
  public:
    void verbose(bool v)
    {
      verb=v;
    }
  public:

    statistic<Ty,Tx,Tp,Ts,Tstr>* do_clone()const
    {
      // return const_cast<statistic<Ty,Tx,Tp>*>(this);
      return new cstat_poisson<Ty,Tx,Tp,Ts,Tstr>(*this);
    }

    Ts do_eval(const Tp& p)
    {
      Ts result(0);
      for(int i=(this->get_data_set()).size()-1;i>=0;--i)
	{
	  Ty model_y=eval_model(this->get_data_set().get_data(i).get_x(),p);
	  result+=model_y-this->get_data_set().get_data(i).get_y()*log(model_y)+lnfrac(this->get_data_set().get_data(i).get_y());
	}

      if(verb)
	{
	  n++;
	  if(n%10==0)
	    {
	      cout<<result/this->p_fitter->get_dof()<<"\t";
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



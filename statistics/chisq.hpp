#ifndef CHI_SQ_HPP
#define CHI_SQ_HPP
#include <core/fitter.hpp>
#include <iostream>
#include <vector>
#include <cmath>
using std::cerr;using std::endl;

namespace opt_utilities
{
  template<typename Ty,typename Tx,typename Tp,typename Ts,typename Tstr>
  class chisq
    :public statistic<Ty,Tx,Tp,Ts,Tstr>
  {
  private:
    bool verb;
    int n;
    
    
    statistic<Ty,Tx,Tp,Ts,Tstr>* do_clone()const
    {
      // return const_cast<statistic<Ty,Tx,Tp>*>(this);
      return new chisq<Ty,Tx,Tp,Ts,Tstr>(*this);
    }
  public:
    void verbose(bool v)
    {
      verb=v;
    }
  public:
    chisq()
      :verb(false)
    {}
    
    

    Ts do_eval(const Tp& p)
    {
      Ts result(0);
      for(int i=(this->datas()).size()-1;i>=0;--i)
	{
	  Ty chi=(this->datas().get_data(i).get_y()-eval_model(this->datas().get_data(i).get_x(),p))/this->datas().get_data(i).get_y_upper_err();
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

#if 1

  template<>
  class chisq<double,double,std::vector<double>,double,std::string>
    :public statistic<double,double,std::vector<double> ,double,std::string>
  {
  public:
    typedef double Ty;
    typedef double Tx;
    typedef std::vector<double> Tp;
    typedef double Ts;
    typedef std::string Tstr;
  private:
    bool verb;
    int n;
    
    statistic<Ty,Tx,Tp,Ts,Tstr>* do_clone()const
    {
      // return const_cast<statistic<Ty,Tx,Tp>*>(this);
      return new chisq<Ty,Tx,Tp,Ts,Tstr>(*this);
    }


  public:
    void verbose(bool v)
    {
      verb=v;
    }
  public:
    chisq()
      :verb(false)
    {}
    
    

    Ty do_eval(const Tp& p)
    {
      Ty result(0);
      for(int i=(this->datas()).size()-1;i>=0;--i)
	{

#ifdef HAVE_X_ERROR
	  Tx x1=this->datas().get_data(i).get_x()-this->datas().get_data(i).get_x_lower_err();
	  Tx x2=this->datas().get_data(i).get_x()+this->datas().get_data(i).get_x_upper_err();
	  Tx x=this->datas().get_data(i).get_x()+this->datas().get_data(i).get_x();
	  Ty errx1=(eval_model(x1,p)-eval_model(x,p));
	  Ty errx2=(eval_model(x2,p)-eval_model(x,p));
	  //Ty errx=0;
#else
	  Ty errx1=0;
	  Ty errx2=0;
#endif

	  Ty y_model=eval_model(this->datas().get_data(i).get_x(),p);
	  Ty y_obs=this->datas().get_data(i).get_y();
	  Ty y_err;
	  
	  Ty errx=0;
	  if(errx2>errx1)
	    {
	      errx=errx1>0?errx1:-errx1;
	    }
	  else
	    {
	      errx=errx2>0?errx2:-errx2;
	    }


	  if(y_model>y_obs)
	    {
	      y_err=this->datas().get_data(i).get_y_upper_err();
	    }
	  else
	    {
	      y_err=this->datas().get_data(i).get_y_lower_err();
	    }

	  Ty chi=(y_obs-y_model)/std::sqrt(y_err*y_err+errx*errx);

	  //	  Ty chi=(this->datas().get_data(i).get_y()-eval_model(this->datas().get_data(i).get_x(),p));
	  //	  cerr<<chi<<"\n";
	  result+=chi*chi;
	  //std::cerr<<chi<<std::endl;
	  //cerr<<eval_model(this->datas()[i].x,p)<<endl;
	  //cerr<<this->datas()[i].y_upper_err<<endl;
	  //	  cerr<<this->datas()[i].x<<"\t"<<this->datas()[i].y<<"\t"<<eval_model(this->datas()[i].x,p)<<endl;
	}
      if(verb)
	{
	  n++;
	  if(n%10==0)
	    {
	      cerr<<result<<"\t";
	      for(int i=0;i<(int)get_size(p);++i)
		{
		  cerr<<get_element(p,i)<<",";
		}
	      cerr<<endl;
	    }

	}
      
      return result;
    }
  };
#endif  
}

#endif
//EOF



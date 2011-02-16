#ifndef PRE_ESTIMATER_HPP
#define PRE_ESTIMATER_HPP

#include <core/fitter.hpp>


namespace opt_utilities
{
  

  template <typename  Ty,typename Tx,typename Tp,typename Tstr=std::string>
  class pre_estimater
  {
  private:
    std::string model_id;
  private:
    virtual void do_estimate(const data_set<Ty,Tx>& d,model<Ty,Tx,Tp,Tstr>& m)const=0;
    virtual pre_estimater* do_clone()const=0;
    virtual void do_destroy()
    {
      delete this;
    }
  public:
    void estimate(const data_set<Ty,Tx>& d,model<Ty,Tx,Tp,Tstr>& m)const
    {
      do_estimate(d,m);
    }

    pre_estimater* clone()const
    {
      return this->do_clone();
    }

    void destroy()
    {
      do_destroy();
    }
  public:
    std::string get_model_id()const
    {
      return model_id;
    }
    
    void set_model_id(const std::string& s)
    {
      model_id=s;
    }
  };

  template <typename  Ty,typename Tx,typename Tp,typename Tstr=std::string>
  class pre_estimatable
  {
  private:
    pre_estimater<Ty,Tx,Tp,Tstr>* ppe;
  public:
    pre_estimatable()
      :ppe(0)
    {}

    pre_estimatable(const pre_estimatable<Ty,Tx,Tp,Tstr>& rhs)
    {
      if(rhs.ppe)
	{
	  ppe=rhs.ppe->clone();
	}
    }

    pre_estimatable& operator=(const pre_estimatable<Ty,Tx,Tp,Tstr>& rhs)
    {
      if(this==&rhs)
	{
	  return *this;
	}
      if(ppe)
	{
	  ppe->destroy();
	}
      ppe=rhs.ppe->clone();
    }
    
    void set_pre_estimater(const pre_estimater<Ty,Tx,Tp,Tstr>& pe)
    {
      if(dynamic_cast<model<Ty,Tx,Tp,Tstr>&>(*this).get_type_name()!=pe.get_model_id())
	{
	  return;
	}
      if(ppe)
	{
	  ppe->destroy();
	}
      ppe=pe.clone();
    }

    virtual ~pre_estimatable()
    {
      if(ppe)
	{
	  ppe->destroy();
	}
    }

  public:
    void estimate(const data_set<Ty,Tx>& d)
    {
      if(ppe)
	{
	  ppe->estimate(d,dynamic_cast<model<Ty,Tx,Tp,Tstr>&>(*this));
	}
    }
  };
  
  template <typename Ty,typename Tx,typename Tp,typename Ts,typename Tstr>
  void pre_estimate(fitter<Ty,Tx,Tp,Ts,Tstr>& fit)
  {
    dynamic_cast<pre_estimatable<Ty,Tx,Tp,Tstr>&>(fit.get_model()).estimate(fit.get_data_set());
  }
}


#endif

#ifndef TYPE_DEPOSITORY_HPP
#define TYPE_DEPOSITORY_HPP
#include <string>
#include <utility>
#include "../core/optimizer.hpp"
#include "../core/fitter.hpp"
#include <map>
#include <iostream>
namespace opt_utilities
{

  enum fetch_direction
    {
      in,out
    };

  class type_unregistered
    :public opt_exception
  {
    const char* what()const throw()
    {
      return "type not registred";
    }
  };

  template <typename T>
  class holder
  {
  private:
    T* ptr;
  public:
    holder()
      :ptr(0)
    {}
    
    holder(T* p)
      :ptr(p)
    {}

    holder(const holder& rhs)
      :ptr(rhs.ptr)
    {
      const_cast<holder&>(rhs).ptr=0;
    }

    ~holder()
    {
      delete ptr;
    }

    holder& operator=(const holder& rhs)
    {
      if(this==&rhs)
	{
	  return *this;
	}
      delete ptr;
      ptr=rhs.ptr;
      const_cast<holder&>(rhs).ptr=0;
    }

  public:
    T* release()
    {
      T* p=ptr;
      ptr=0;
      return p;
    }

    void destroy()
    {
      delete ptr;
    }

    T* get()const
    {
      return ptr;
    }

    void reset(T* p)
    {
      destroy();
      ptr=p;
    }

    operator T*()
    {
      return ptr;
    }

    operator const T*()const
    {
      return ptr;
    }
    
  public:
    T& operator*()
    {
      return *ptr;
    }

  public:
    T* operator->()
    {
      return ptr;
    }
  };

  
  template <typename Ty,typename Tx>
  void delete_clone(const func_obj<Ty,Tx>* pfo)
  {
    const_cast<func_obj<Ty,Tx>* >(pfo)->destroy();
  }

  template <typename Ty,typename Tx>
  void fetch_func_obj(func_obj<Ty,Tx>* &fo,std::string cname,fetch_direction dir=in)
  {
    static std::map<std::string,holder<func_obj<Ty,Tx> > >pm;
    typename std::map<std::string,
      holder<func_obj<Ty,Tx> > >::iterator it=pm.find(cname);
    
    if(dir==out)
      {
	if(it==pm.end())
	  {
	    std::cerr<<cname<<std::endl;
	    throw type_unregistered();;
	  }
	else
	  {
	    func_obj<Ty,Tx>* result=it->second;
	    fo=result->clone();
	  }
      }
    else if(dir==in)
      {
	//pm.insert(make_pair(cname,holder<func_obj<Ty,Tx> >(fo->clone())));
	
	pm[cname]=holder<func_obj<Ty,Tx> >(fo->clone());
      }
  }

  template <typename Ty,typename Tx>
  void register_func_obj(const func_obj<Ty,Tx>& fo)
  {
    func_obj<Ty,Tx>* pfo=const_cast<func_obj<Ty,Tx>*>(&fo);
    fetch_func_obj(pfo,fo.get_type_name(),in);
  }

  template <typename Ty,typename Tx>
  func_obj<Ty,Tx>* get_func_obj(std::string cname)
  {
    func_obj<Ty,Tx>* pom;
    fetch_func_obj(pom,cname,out);
    return pom;
  }


  template <typename Ty,typename Tx>
  void delete_clone(const opt_method<Ty,Tx>* pfo)
  {
    const_cast<opt_method<Ty,Tx>* >(pfo)->destroy();
  }

  template <typename Ty,typename Tx>
  void fetch_opt_method(opt_method<Ty,Tx>* &fo,std::string cname,fetch_direction dir)
  {
    static std::map<std::string,holder<opt_method<Ty,Tx> > > pm;
    typename std::map<std::string,
      holder<opt_method<Ty,Tx> > >::iterator it=pm.find(cname);
    
    if(dir==out)
      {
	if(it==pm.end())
	  {
	    std::cerr<<cname<<std::endl;
	    throw type_unregistered();;
	  }
	else
	  {
	    opt_method<Ty,Tx>* result=it->second;
	    fo=result->clone();
	  }
      }
    else if(dir==in)
      {
	//pm.insert(cname,fo->clone());
	pm[cname]=holder<opt_method<Ty,Tx> >(fo->clone());
      }
  }

  template <typename Ty,typename Tx>
  void register_opt_method(const opt_method<Ty,Tx>& fo)
  {
    opt_method<Ty,Tx>* pfo=const_cast<opt_method<Ty,Tx>*>(&fo);
    fetch_opt_method(pfo,fo.get_type_name(),in);
  }

  template <typename Ty,typename Tx>
  opt_method<Ty,Tx>* get_opt_method(std::string cname)
  {
    opt_method<Ty,Tx>* pom;
    fetch_opt_method(pom,cname,out);
    return pom;
  }

  template<typename Ty,typename Tx,typename Tp,typename Ts,typename Tstr>
  void delete_clone(const statistic<Ty,Tx,Tp,Ts,Tstr>* pfo)
  {
    const_cast<statistic<Ty,Tx,Tp,Ts,Tstr>* >(pfo)->destroy();
  }


  template<typename Ty,typename Tx,typename Tp,typename Ts,typename Tstr>
  void fetch_statistic(statistic<Ty,Tx,Tp,Ts,Tstr>* &fo,std::string cname,fetch_direction dir)
  {
    static std::map<std::string,holder<statistic<Ty,Tx,Tp,Ts,Tstr> > > pm;
    typename std::map<std::string,
      holder<statistic<Ty,Tx,Tp,Ts,Tstr> > >::iterator it=pm.find(cname);
    
    if(dir==out)
      {
	if(it==pm.end())
	  {
	    std::cerr<<cname<<std::endl;
	    throw type_unregistered();;
	  }
	else
	  {
	    statistic<Ty,Tx,Tp,Ts,Tstr>* result=it->second;
	    fo=result->clone();
	  }
      }
    else if(dir==in)
      {
	//pm.insert(cname,fo->clone());
	pm[cname]=holder<statistic<Ty,Tx,Tp,Ts,Tstr> >(fo->clone());
  }
  }

  template<typename Ty,typename Tx,typename Tp,typename Ts,typename Tstr>
  void register_statistic(const statistic<Ty,Tx,Tp,Ts,Tstr>& fo)
  {
    statistic<Ty,Tx,Tp,Ts,Tstr>* pfo=const_cast<statistic<Ty,Tx,Tp,Ts,Tstr>*>(&fo);
    fetch_statistic(pfo,fo.get_type_name(),in);
  }

  template<typename Ty,typename Tx,typename Tp,typename Ts,typename Tstr>
  statistic<Ty,Tx,Tp,Ts,Tstr>* get_statistic(std::string cname)
  {
    statistic<Ty,Tx,Tp,Ts,Tstr>* pst;
    fetch_statistic(pst,cname,out);
    return pst;
  }

  template <typename Ty,typename Tx,typename Tp,typename Tstr>
  void delete_clone(const param_modifier<Ty,Tx,Tp,Tstr>* pfo)
  {
    const_cast<param_modifier<Ty,Tx,Tp,Tstr>* >(pfo)->destroy();
  }

  template <typename Ty,typename Tx,typename Tp,typename Tstr>
  void fetch_param_modifier(param_modifier<Ty,Tx,Tp,Tstr>* &fo,std::string cname,fetch_direction dir)
  {
    static std::map<std::string,holder<param_modifier<Ty,Tx,Tp,Tstr> > > pm;
    typename std::map<std::string,
      holder<param_modifier<Ty,Tx,Tp,Tstr> > >::iterator it=pm.find(cname);
    
    if(dir==out)
      {
	if(it==pm.end())
	  {
	    std::cerr<<cname<<std::endl;
	    throw type_unregistered();
	  }
	else
	  {
	    param_modifier<Ty,Tx,Tp,Tstr>* result=it->second;
	    fo=result->clone();
	  }
      }
    else if(dir==in)
      {
	//pm.insert(cname,fo->clone());
	pm[cname]=holder<param_modifier<Ty,Tx,Tp,Tstr> >(fo->clone());
      }
  }

  template<typename Ty,typename Tx,typename Tp,typename Tstr>
  void register_param_modifier(const param_modifier<Ty,Tx,Tp,Tstr>& fo)
  {
    param_modifier<Ty,Tx,Tp,Tstr>* pfo=const_cast<param_modifier<Ty,Tx,Tp,Tstr>*>(&fo);
    fetch_param_modifier(pfo,fo.get_type_name(),in);
  }

  template<typename Ty,typename Tx,typename Tp,typename Tstr>
  param_modifier<Ty,Tx,Tp,Tstr>* get_param_modifier(std::string cname)
  {
    param_modifier<Ty,Tx,Tp,Tstr>* ppm;
    fetch_param_modifier(ppm,cname,out);
    return ppm;
  }
  
  
  template <typename Ty,typename Tx>
  void delete_clone(const data_set<Ty,Tx>* pfo)
  {
    const_cast<data_set<Ty,Tx>* >(pfo)->destroy();
  }

  template <typename Ty,typename Tx>
  void fetch_data_set(data_set<Ty,Tx>* &fo,std::string cname,fetch_direction dir)
  {
    static std::map<std::string,holder<data_set<Ty,Tx> > > pm;
    typename std::map<std::string,
      holder<data_set<Ty,Tx> > >::iterator it=pm.find(cname);
    
    if(dir==out)
      {
	if(it==pm.end())
	  {
	    std::cerr<<cname<<std::endl;
	    throw type_unregistered();;
	  }
	else
	  {
	    data_set<Ty,Tx>* result=it->second;
	    fo=result->clone();
	  }
      }
    else if(dir==in)
      {
	//pm.insert(cname,fo->clone());
	pm[cname]=holder<data_set<Ty,Tx> >(fo->clone());
      }
  }

  template <typename Ty,typename Tx>
  void register_data_set(const data_set<Ty,Tx>& fo)
  {
    data_set<Ty,Tx>* pfo=const_cast<data_set<Ty,Tx>*>(&fo);
    fetch_data_set(pfo,fo.get_type_name(),in);
  }

  template<typename Ty,typename Tx>
  data_set<Ty,Tx>* get_data_set(std::string cname)
  {
    data_set<Ty,Tx>* pds;
    fetch_data_set(pds,cname,out);
    return pds;
  }
  
  

  ////////////////////
  template <typename Ty,typename Tx,typename Tp,typename Tstr>
  void delete_clone(const model<Ty,Tx,Tp,Tstr>* pfo)
  {
    const_cast<model<Ty,Tx,Tp,Tstr>* >(pfo)->destroy();
  }


  template <typename Ty,typename Tx,typename Tp,typename Tstr>
  void fetch_model(model<Ty,Tx,Tp,Tstr>* &fo,std::string cname,fetch_direction dir)
  {
    static std::map<std::string,holder<model<Ty,Tx,Tp,Tstr> > > pm;
    typename std::map<std::string,
      holder<model<Ty,Tx,Tp,Tstr> > >::iterator it=pm.find(cname);
    
    if(dir==out)
      {
	if(it==pm.end())
	  {
	    std::cerr<<cname<<std::endl;
	    throw type_unregistered();
	  }
	else
	  {
	    model<Ty,Tx,Tp,Tstr>* result=it->second;
	    fo=result->clone();
	  }
      }
    else if(dir==in)
      {
	pm[cname]= holder<model<Ty,Tx,Tp,Tstr> >(fo->clone());
      }
  }

  template <typename Ty,typename Tx,typename Tp,typename Tstr>
  void register_model(const model<Ty,Tx,Tp,Tstr>& fo)
  {
    model<Ty,Tx,Tp,Tstr>* pfo=const_cast<model<Ty,Tx,Tp,Tstr>*>(&fo);
    fetch_model(pfo,fo.get_type_name(),in);
  }

  template <typename Ty,typename Tx,typename Tp,typename Tstr>
  model<Ty,Tx,Tp,Tstr>* get_model(std::string cname)
  {
    model<Ty,Tx,Tp,Tstr>* pds;
    fetch_model(pds,cname,out);
    return pds;
  }
  
}


#endif

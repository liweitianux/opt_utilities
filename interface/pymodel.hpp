#ifndef PYMODEL
#define PYMODEL
#include <boost/python.hpp>
#include <core/fitter.hpp>
#include <core/opt_traits.hpp>


namespace opt_utilities
{

  template <typename Ty,typename Tx,typename Tp>
  class pymodel
    :public model<Ty,Tx,Tp,std::string>
  {
  private:
    boost::python::object pyfunc;
  public:
    pymodel()
    {
      if(!Py_IsInitialized())
	{
	  Py_Initialize();
	}
    }

    pymodel(const pymodel& rhs)
      :pyfunc(rhs.pyfunc)
    {
      for(int i=0;i<rhs.get_num_params();++i)
	{
	  this->push_param_info(rhs.get_param_info(i));
	}
    }

    pymodel& operator=(const pymodel& rhs)
    {
      if(this==&rhs)
	{
	  return *this;
	}
      pyfunc=rhs.pyfunc;
      for(int i=0;i<rhs.get_num_params();++i)
	{
	  this->push_param_info(rhs.get_param_info(i));
	}
      return *this;
    }

    ~pymodel()
    {}

  public:
    void attach(const std::string module_name,
		const std::string arg_name,
		const std::string arg_value,
		const std::string func_name)
    {
      this->clear_param_info();
      boost::python::object mod(boost::python::import(module_name.c_str()));
      pyfunc=mod.attr(func_name.c_str());
      boost::python::list args_names(mod.attr(arg_name.c_str()));
      boost::python::list args_values(mod.attr(arg_value.c_str()));
      
      int nparams=boost::python::len(args_names);
      for(size_t i=0;i!=nparams;++i)
	{
	  boost::python::object pname_obj=args_names[i];
	  std::string pname=boost::python::extract<std::string>(pname_obj);
	  typename element_type_trait<Tp>::element_type pvalue=
	    boost::python::extract<typename element_type_trait<Tp>::element_type>(args_values[i]);
	  
	  push_param_info(param_info<Tp,std::string>(pname,pvalue));
	}
    }
  private:
    model<Ty,Tx,Tp,std::string>* do_clone()const
    {
      return new pymodel(*this);
    }
    
    void do_destroy()
    {
      delete this;
    }
    
    Ty do_eval(const Tx& x,const Tp& p)
    {
      boost::python::list args;
      for(size_t i=0;i<get_size(p);++i)
	{
	  args.append(get_element(p,i));
	}
      return boost::python::extract<Ty>(pyfunc(x,args));
    }
  };
}


#endif
//EOF

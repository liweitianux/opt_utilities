#ifdef __linux__

#ifndef DL_MODEL_H_
#define DL_MODEL_H_
#include <core/fitter.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include <dlfcn.h>

namespace opt_utilities
{
  template <typename T>
  class dl_model
    :public model<T,T,std::vector<T>,std::string>
  {
  private:
    T (*calc_model)(T x,const T* p);
    int nparams;
    mutable void* handle;
  private:
    model<T,T,std::vector<T> >* do_clone()const
    {
      dl_model<T>* result=new dl_model<T>(*this);
      this->handle=NULL;
      return result;
    }

    //  public:
  public:
    dl_model()
      :handle(NULL)
    {}


  public:
    dl_model(const char* file_name)
      :handle(NULL)
    {
      
      handle=dlopen(file_name,RTLD_LAZY);
      
      if(!handle)
	{
	  throw opt_exception("faild loading object");
	}
      
      calc_model=(T (*)(T,const T*))dlsym(handle,"calc_model");
      
      if(!calc_model)
	{
	  throw opt_exception("symble undefined");
	}

      const char* (*get_param_name)(int)
	=(const char* (*)(int))dlsym(handle,"get_param_name");
      
      if(!get_param_name)
	{
	  throw opt_exception("symble undefined");
	}

      int (*get_num_params)()
	=(int (*)())dlsym(handle,"get_num_params");
      
      if(!get_num_params)
	{
	  throw opt_exception("symble undefined");
      if(!get_num_params)
	{
	  throw opt_exception("symble undefined");
	}	}

      T (*get_default_value)(int)
	=(T (*)(int))dlsym(handle,"get_default_value");
      
      if(!get_default_value)
	{
	  throw opt_exception("symble undefined");
	}

      nparams=get_num_params();
      
      for(int i=0;i!=nparams;++i)
	{
	  this->push_param_info(param_info<std::vector<T> >(get_param_name(i),
				get_default_value(i)));
	}
    }

    ~dl_model()
    {
      if(handle)
	{
	  dlclose(handle);
	}
    }

    void bind(const char* file_name)
    {
      if(handle)
	{
	  dlclose(handle);
	}
      this->clear_param_info();
      handle=dlopen(file_name,RTLD_LAZY);

      if(!handle)
	{
	  throw opt_exception("faild loading object");
	}

      calc_model=(T (*)(T,const T*))dlsym(handle,"calc_model");
      
      if(!calc_model)
	{
	  throw opt_exception("symble undefined");
	}

      const char* (*get_param_name)(int)
	=(const char* (*)(int))dlsym(handle,"get_param_name");
      
      if(!get_param_name)
	{
	  throw opt_exception("symble undefined");
	}


      int (*get_num_params)()
	=(int (*)())dlsym(handle,"get_num_params");
      
      if(!get_num_params)
	{
	  throw opt_exception("symble undefined");
	}      


      T (*get_default_value)(int)
	=(T (*)(int))dlsym(handle,"get_default_value");
     

      if(!get_default_value)
	{
	  throw opt_exception("symble undefined");
	}

      
      nparams=get_num_params();
      for(int i=0;i!=nparams;++i)
	{
	  this->push_param_info(param_info<std::vector<T> >(get_param_name(i),
				get_default_value(i)));
	}
    }

    T do_eval(const T& x,const std::vector<T>& param)
    {
      if(handle==NULL)
	{
	  throw opt_exception("dl object unloaded");
	}
      return calc_model(x,&get_element(param,0));
    }

    std::string do_to_string()const
    {
      return "Dynamical load model\n"
	"Should be loaded from an shared object file\n";
    }
  };
}



#endif
#endif
//EOF

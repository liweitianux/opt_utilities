#ifdef __linux__

#ifndef DL_MODEL_HPP
#define DL_MODEL_HPP
#define OPT_HEADER
#include <core/fitter.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include <dlfcn.h>

namespace opt_utilities
{

  template <typename Ty,
	    typename Tx,
	    typename Tp,
	    typename Tstr>
  model<Ty,Tx,Tp,Tstr>* load_model(const char* fname)
  {
    void* handle;
    
    handle=dlopen(fname,RTLD_LAZY);
    
    if(!handle)
      {
	throw opt_exception("faild loading object");
      }
    
    
    model<Ty,Tx,Tp,Tstr>* (*func_create)();
    
    func_create=(model<Ty,Tx,Tp,Tstr>* (*)())dlsym(handle,"create_model_object");
    
    if(!func_create)
      {
	throw opt_exception("symble undefined");
      }
    return func_create();
  }
  
  template <typename Ty,
	    typename Tp>
  opt_method<Ty,Tp>* load_opt_method(const char* fname)
  {
    void* handle;
    
    handle=dlopen(fname,RTLD_LAZY);
    
    if(!handle)
      {
	throw opt_exception("faild loading object");
      }
    
    
    opt_method<Ty,Tp>* (*func_create)();
    
    func_create=(opt_method<Ty,Tp>* (*)())dlsym(handle,"create_opt_method_object");
    
    if(!func_create)
      {
	throw opt_exception("symble undefined");
      }
    return func_create();
  }

  template <typename Ty,
	    typename Tp>
  func_obj<Ty,Tp>* load_func_obj(const char* fname)
  {
    void* handle;
    
    handle=dlopen(fname,RTLD_LAZY);
    
    if(!handle)
      {
	throw opt_exception("faild loading object");
      }
    
    
    func_obj<Ty,Tp>* (*func_create)();
    
    func_create=(func_obj<Ty,Tp>* (*)())dlsym(handle,"create_func_obj_object");
    
    if(!func_create)
      {
	throw opt_exception("symble undefined");
      }
    return func_create();
  }

  

}



#endif
#endif
//EOF

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

  template <typename T>
  model<T,T,std::vector<T>,std::string>* load_model(const char* fname)
  {
    void* handle;
    
    handle=dlopen(fname,RTLD_LAZY);
    
    if(!handle)
      {
	throw opt_exception("faild loading object");
      }
    
    
    model<T,T,std::vector<T>,std::string>* (*func_create)();
    
    func_create=(model<T,T,std::vector<T>,std::string>* (*)())dlsym(handle,"create_model_object");
    
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

#ifndef OPT_EXCEPTION
#define OPT_EXCEPTION
#include <string>
#include <exception>
namespace opt_utilities
{
  class opt_exception
    :public std::exception
  {
  private:
    std::string _what;
  public:
    opt_exception()
    {};
    
    ~opt_exception()throw()
    {}
    
    opt_exception(const std::string& str)
      :_what(str)
    {}

    const char* what()const throw()
    {
      return _what.c_str();
    }
  };
  
  class target_function_undefined
    :public opt_exception
  {
  public:
    target_function_undefined()
      :opt_exception("target function undefined")
    {}
  };

  class opt_method_undefined
    :public opt_exception
  {
  public:
    opt_method_undefined()
      :opt_exception("opt method undefined")
    {}
  };
  
  class fitter_unset
    :public opt_exception
  {
  public:
    fitter_unset()
      :opt_exception("fitter_unset")
    {}
  };

  class model_undefined
    :public opt_exception
  {
  public:
    model_undefined()
      :opt_exception("model_undefined")
    {}
  };

  class data_unloaded
    :public opt_exception
  {
  public:
    data_unloaded()
      :opt_exception("data not loaded")
    {}
  };


  class statistic_undefined
    :public opt_exception
  {
  public:
    statistic_undefined()
      :opt_exception("statistic undefined")
    {}
  };
  
  class param_not_found
    :public opt_exception
  {
  public:
    param_not_found()
      :opt_exception("param name invalid")
    {}
  };
  
  class param_modifier_undefined
    :public opt_exception
  {
  public:
    param_modifier_undefined()
      :opt_exception("param modifier undefined")
    {}
  };

};


#endif
//EOF

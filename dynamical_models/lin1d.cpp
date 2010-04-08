#include <core/fitter.hpp>
#include <cmath>
#include <vector>
using namespace std;
using namespace opt_utilities;
template <typename T>
class lin1d
  :public model<T,T,std::vector<T>,std::string>
{
private:
  model<T,T,std::vector<T> >* do_clone()const
  {
    return new lin1d<T>(*this);
  }
  
  const char* do_get_type_name()const
  {
    return "1d linear model";
  }
public:
  lin1d()
  {
    this->push_param_info(param_info<std::vector<T> >("k",1));
    this->push_param_info(param_info<std::vector<T> >("b",0));
  }
  
public:
  T do_eval(const T& x,const std::vector<T>& param)
  {
    return x*get_element(param,0)+get_element(param,1);
  }
  
private:
  std::string do_get_information()const
  {
    return "<math><mrow> <mtext>f(x;k,b)=k x+b</mtext>		\
    </mrow>							\
</math>";
  }
};

static lin1d<double> _model;


extern "C" model<double,double,vector<double>,std::string>*
create_model_object()
{
  return &_model;
}

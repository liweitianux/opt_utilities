#include <core/fitter.hpp>
#include <vector>
#include <string>
#include <cmath>

using namespace std;
using namespace opt_utilities;
class vk_temperature
  :public opt_utilities::model<double,double,std::vector<double>,std::string>
{
private:
  opt_utilities::model<double,double,std::vector<double>,std::string>* do_clone()const;
public:
  vk_temperature();
  double do_eval(const double& r,const std::vector<double>& param);
  
};


model<double,double,vector<double>,std::string>* vk_temperature::do_clone()const
{
  return new vk_temperature(*this);
}

vk_temperature::vk_temperature()
{
  this->push_param_info(param_info<std::vector<double> >("T0",2,0.1,10));
  this->push_param_info(param_info<std::vector<double> >("rcool",1e22,0.001,10));
  this->push_param_info(param_info<std::vector<double> >("acool",1));
  this->push_param_info(param_info<std::vector<double> >("Tmin",1,0.1,10));
  this->push_param_info(param_info<std::vector<double> >("rt",1e22,0.001,10));
  this->push_param_info(param_info<std::vector<double> >("a",1,-10,10));
  this->push_param_info(param_info<std::vector<double> >("c",1,-10,10));
  this->push_param_info(param_info<std::vector<double> >("b",1,-10,10));
}





double vk_temperature::do_eval(const double& r,const std::vector<double>& param)
{
  double T0=param[0];
  double rcool=param[1];
  double acool=param[2];
  double Tmin=param[3];
  double rt=param[4];
  double a=param[5];
  double c=param[6];
  double b=param[7];
  double x=pow(r/rcool,acool);
  double tcool=(x+Tmin/T0)/(x+1);
  double t=pow(r/rt,-a)/pow(1+pow(r/rt,b),c/b);
  return T0*t*tcool;
}


static vk_temperature _model;

extern "C" model<double,double,vector<double>,std::string>*
create_model_object()
{
  return &_model;
}

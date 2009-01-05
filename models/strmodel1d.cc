#include "strmodel1d.hpp"

using namespace mu;
using namespace std;
using namespace opt_utilities;

strmodel1d* strmodel1d::do_clone()const
{
  return new strmodel1d(*this);
}

strmodel1d::strmodel1d()
{
  set_buildin_fun();
}

strmodel1d::strmodel1d(const strmodel1d& rhs)
  :par_vec(rhs.par_vec),
   par_names(rhs.par_names),
   expr(rhs.expr),
   var_name(rhs.var_name)
   
{
  set_buildin_fun();
  set_expr(expr,par_names,var_name);
}

strmodel1d& strmodel1d::operator=(const strmodel1d& rhs)
{
  set_buildin_fun();
  expr=rhs.expr;
  par_names=rhs.par_names;
  var_name=rhs.var_name;
  par_vec=rhs.par_vec;
  set_expr(expr,par_names,var_name);
  return *this;
}

void strmodel1d::set_buildin_fun()
{
  mp.DefineFun("sin",sin);
  mp.DefineFun("cos",cos);
  mp.DefineFun("exp",exp);
  mp.DefineFun("tan",tan);
  mp.DefineFun("log",log);
}


void strmodel1d::set_expr(const string& _expr,
			  const std::vector<std::string>& _par_names,
			  const std::string& _var_name)
{
  expr=_expr;
  par_names=_par_names;
  var_name=_var_name;
  this->clear_param_info();
  par_vec.resize(par_names.size());
  mp.ClearVar();
  //  mp.ClearFun();
  for(unsigned int i=0;i<par_vec.size();++i)
    {
      mp.DefineVar(par_names[i].c_str(),&par_vec[i]);
      this->push_param_info(param_info<std::vector<double> >(par_names[i],0));
    }
  mp.DefineVar(var_name.c_str(),&x);
  mp.SetExpr(expr.c_str());
}


double strmodel1d::do_eval(const double& _x,const vector<double>& p)
{
  for(unsigned int i=0;i<par_vec.size();++i)
    {
      //get_element(par_vec,i)=get_element(p,i);
      set_element(par_vec,i,get_element(p,i));
      //      cout<<par_vec[i]<<" ";
    }
  x=_x;
  //  cout<<x<<" ";
  double result(mp.Eval());
  //  cout<<result<<endl;
  return result;
}

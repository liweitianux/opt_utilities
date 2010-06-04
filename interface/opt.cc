#include "opt.h"
#include <utilities/opt_types.hpp>
#include <math/num_diff.hpp>
#include <models/models.hpp>
#include <map>
#include <core/freeze_param.hpp>
#include <data_sets/default_data_set.hpp>
//#include <iostream>

using namespace std;
using namespace opt_utilities;
static const int max_fit_space_num=100;
struct fit_space;
static map<int,fit_space> fit_space_map;
struct fit_space
{
  dopt::fitter fit;
  ///  dopt::model model;
  fit_space()
  {
    fit.set_opt_method(dopt::powell_method());
    dopt::chisq cq;
    dopt::leastsq lsq;
    //  cq.verbose(true);
    fit.set_statistic(cq);
  }
  
};


extern "C"
{

void alloc_fit_(int& n)
{
  n=0;
  for(int i=1;i<max_fit_space_num;++i)
    {
      if(fit_space_map.find(i)==fit_space_map.end())
	{
	  fit_space_map.insert(make_pair(i,fit_space()));
	  //cout<<i<<endl;
	  //return i;
	  n=i;
	  break;
	}
    }
  
  return;
}


void free_fit_(const int& n)
{
  map<int,fit_space>::iterator iter=fit_space_map.find(n);
  if(iter==fit_space_map.end())
    {
      return;
    }
  fit_space_map.erase(iter);
}

void load_data_(const int& nfit,const int& ndatas,double* x,double* y,double* yl,double* yu,double* xl,double* xu)
{
  map<int,fit_space>::iterator iter=fit_space_map.find(nfit);
  if(iter==fit_space_map.end())
    {
      return;
    }
  //  cout<<x[0]<<endl;
  default_data_set<double,double> ds;
  for(int i=0;i<ndatas;++i)
    {
      data<double,double> d(x[i],y[i],yl[i],(yu==0?yl[i]:yu[i]),(xl==0?0:xl[i]),(xu==0?0:xu[i]));
      //  cout<<x[i]<<" "<<y[i]<<endl;
      ds.add_data(d);
    }
  iter->second.fit.load_data(ds);
}


void set_model_(const int& nfit,const char* model_name)
{
  map<int,fit_space>::iterator iter=fit_space_map.find(nfit);
  
  if(iter==fit_space_map.end())
    {
      cerr<<"fit not found"<<endl;
      return;
    }
  try
    {
      iter->second.fit.set_model(opt_utilities::get_1dmodel_by_name(model_name));
    }
  catch(opt_exception& e)
  {
    //cout<<model_name<<endl;
    cout<<e.what()<<endl;
    throw e;
  }
}

void set_param_(const int& nfit,const char* pname,const double& value)
{
  map<int,fit_space>::iterator iter=fit_space_map.find(nfit);
  cerr<<"pname="<<pname<<endl;
  cerr<<"value="<<value<<endl;
  if(iter==fit_space_map.end())
    {
      cerr<<"fit not found"<<endl;
      return;
    }
  iter->second.fit.set_param_value(pname,value);
}


void freeze_param_(const int& nfit,const char* pname)
{
  map<int,fit_space>::iterator iter=fit_space_map.find(nfit);
  if(iter==fit_space_map.end())
    {
      return;
    }
  opt_utilities::freeze_param<double,double,std::vector<double> > fp(pname);
  try
    {
      dynamic_cast<opt_utilities::freeze_param<double,double,vector<double> >& >(iter->second.fit.get_param_modifier())+=fp;
    }
  catch(opt_exception& e)
    {
      (void)e;
      iter->second.fit.set_param_modifier(fp);
    }
}


void thaw_param_(const int& nfit,const char* pname)
{
  map<int,fit_space>::iterator iter=fit_space_map.find(nfit);
  if(iter==fit_space_map.end())
    {
      return;
    }
  opt_utilities::freeze_param<double,double,std::vector<double> > fp(pname);
  try
    {
      dynamic_cast<opt_utilities::freeze_param<double,double,vector<double> >& >(iter->second.fit.get_param_modifier())-=fp;
    }
  catch(opt_exception& e)
    {
      (void)e;
      //iter->second.fit.set_param_modifier(fp);
    }
}

void perform_fit_(const int& nfit)
{
  map<int,fit_space>::iterator iter=fit_space_map.find(nfit);
  if(iter==fit_space_map.end())
    {
      return;
    }
  iter->second.fit.fit();
}


void get_param_(const int& nfit,double& r,const char* pname)
{
  map<int,fit_space>::iterator iter=fit_space_map.find(nfit);
  if(iter==fit_space_map.end())
    {
      //return 0;
      cerr<<"fit not found"<<endl;
      r=0;
      return;
    }
  //  cerr<<"fdsaf"<<r<<endl;
  r=iter->second.fit.get_param_value(pname);
  
}



}


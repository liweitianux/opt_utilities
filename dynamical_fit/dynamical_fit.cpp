#include <core/fitter.hpp>
#include <interface/optdl.hpp>
#include <misc/data_loaders.hpp>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <methods/powell/powell_method.hpp>
#include <statistics/chisq.hpp>
#include <cstdlib>

using namespace std;
using namespace opt_utilities;


int main(int argc,char* argv[])
{
  if(argc!=2)
    {
      cerr<<"Usage: "<<argv[0]<<" <config file>"<<endl;
      exit(-1);
    }
  ifstream cfg_file(argv[1]);
  fitter<double,double,std::vector<double>,double,std::string> fit;
  fit.set_opt_method(powell_method<double,vector<double> >());
  fit.set_statistic(chisq<double,double,vector<double>,double,string>());
  std::string model_so_name;
  cfg_file>>model_so_name;
  cerr<<"loading model shared object "<<model_so_name<<endl;
  fit.set_model(*load_model<double,double,vector<double>,string>(model_so_name.c_str()));
  
  string data_file_name;
  cfg_file>>data_file_name;
  cerr<<"setting initializational values:"<<endl;
  for(;;)
    {
      string p,v;
      cfg_file>>p>>v;
      if(!cfg_file.good())
	{
	  break;
	}
      istringstream oss(v);
      
      double dvp=0;
      oss>>dvp;
      cerr<<p<<"="<<dvp<<endl;
      fit.set_param_value(p,dvp);
    }
  cfg_file.close();

  ifstream data_file(data_file_name.c_str());
  
  dl_x_xu_xl_y_yu_yl<double,double> dl;
  dl.load_from(data_file);
  data_file.close();

  fit.load_data(dl.get_data_set());

  vector<double> p=fit.fit();
  cout<<p[0]<<"\t"<<p[1]<<endl;
  
}

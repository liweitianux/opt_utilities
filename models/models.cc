#include "models.hpp"
#include <core/opt_exception.hpp>
#include "gauss1d.hpp"
#include "bl1d.hpp"
#include "nfw1d.hpp"
#include "bpl1d.hpp"
#include "beta1d.hpp"
#include "nbeta1d.hpp"
#include "dbeta1d.hpp"
#include "lin1d.hpp"
#include "pl1d.hpp"
#include "poly1d.hpp"
#include "bremss.hpp"
#include "beta2d2.hpp"
#include "beta2d.hpp"
#include "dbeta2d2.hpp"
#include "dbeta2d3.hpp"
#include "dbeta2d.hpp"
#include "dl_model.hpp"
#include <iostream>
using namespace std;


namespace opt_utilities
{
  strmodel1d strm1d;
  std::map<std::string,model<double,double,std::vector<double>,std::string>* > model_map;
  std::map<std::string,model<double,vecn<double,2>,std::vector<double>,std::string>* > model2d_map;
  std::list<std::string> get_model_name_list()
  {
    std::list<std::string> result;
    for(std::map<std::string,model<double,double,std::vector<double>,std::string>* >::iterator i=model_map.begin();
	i!=model_map.end();++i)
      {
	result.push_back(i->first);
      }
	return result;
  }

  std::list<std::string> get_model2d_name_list()
  {
    std::list<std::string> result;
    for(map<std::string,model<double,vecn<double,2>,std::vector<double>,std::string>* > ::iterator i=model2d_map.begin();
	i!=model2d_map.end();++i)
      {
	result.push_back(i->first);
      }
    return result;
  }

model<double,double,std::vector<double>,std::string>& get_1dmodel_by_name(const char* name)
  {
    std::map<std::string,model<double,double,std::vector<double>,std::string >* >::iterator iter;
    iter=model_map.find(name);
    if(iter==model_map.end()||iter->second==0)
      {
	throw opt_exception("model does not exist");
      }
    return *(iter->second);
  }

  strmodel1d& get_strm1d()
  {
    return strm1d;
  }

model<double,vecn<double,2>,std::vector<double>,std::string>& get_2dmodel_by_name(const char* name)
  {
    std::map<std::string,model<double,vecn<double,2>,std::vector<double>,std::string>* >::iterator iter;
    iter=model2d_map.find(name);
    if(iter==model2d_map.end()||iter->second==0)
      {
	throw opt_exception("model does not exist");
      }
    return *(iter->second);
  }

  int get_n_1dmodels()
  {
    return model_map.size();
  }

  int get_n_2dmodels()
  {
    return model2d_map.size();
  }

  class model_map_keeper_class
  {
  private:
    void init_model_map()
    {

      //#define DECL_POLY(n) model_map["poly1d##n"]=new poly1d<double,n>;


      model_map["lin1d"]=new lin1d<double>;
      model_map["pl1d"]=new pl1d<double>;
      model_map["bl1d"]=new bl1d<double>;
      model_map["bpl1d"]=new bpl1d<double>;
      model_map["beta1d"]=new beta1d<double>;  
      model_map["bremss"]=new bremss<double>;
      model_map["nbeta1d"]=new nbeta1d<double>;  
      model_map["2beta1d"]=new dbeta1d<double>;
      model_map["nfw"]=new nfw1d<double>;
      model_map["gauss1d"]=new gauss1d<double>;  
      model_map["poly1d2"]=new poly1d<double,2>;
      model_map["poly1d3"]=new poly1d<double,3>;
      model_map["poly1d4"]=new poly1d<double,4>;
      model_map["poly1d5"]=new poly1d<double,5>;
#ifdef __linux__
      model_map["dlmodel"]=new dl_model<double>;
#endif
      //DECL_POLY(7)
    }
    
    void release_model_map()
    {
      for(std::map<std::string,model<double,double,std::vector<double>,std::string>* >::iterator i=model_map.begin();
	  i!=model_map.end();++i)
	{
	  delete i->second;
	}
    }
  public:
    model_map_keeper_class()
    {
      init_model_map();
	  std::cerr<<"1d models Initialized"<<std::endl;
    }
    
    ~model_map_keeper_class()
    {
      release_model_map();
	  std::cerr<<"1d models Released"<<std::endl;
    }

  }model_map_keeper;

  class model2d_map_keeper_class
  {
  private:
    void init_model_map()
    {
      model2d_map["beta2d"]=new beta2d<double>;
      model2d_map["beta2d2"]=new beta2d2<double>;
      model2d_map["dbeta2d"]=new dbeta2d<double>;
      model2d_map["dbeta2d2"]=new dbeta2d2<double>;
      model2d_map["dbeta2d3"]=new dbeta2d3<double>;  
    }
    
    void release_model_map()
    {
      for(std::map<std::string,model<double,vecn<double,2>,std::vector<double>,std::string>* >::iterator i=model2d_map.begin();
	  i!=model2d_map.end();++i)
	{
	  delete i->second;
	}
    }
  public:
    model2d_map_keeper_class()
    {
      init_model_map();
      std::cerr<<"2d models Initialized"<<std::endl;
    }
    
    ~model2d_map_keeper_class()
    {
      release_model_map();
      std::cerr<<"2d models Released"<<std::endl;
    }

  }model2d_map_keeper;


};

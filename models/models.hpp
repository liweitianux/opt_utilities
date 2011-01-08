/**
   \file models.hpp
   \brief implement of the prototype pattern to get models from string keywords
   \author Junhua Gu
 */


#ifndef MODELS_HPP
#define MODELS_HPP
#define OPT_HEADER
#include <core/fitter.hpp>
#include <map>
#include <string>
#include <list>
#include "vecn.hpp"
#include "strmodel1d.hpp"



namespace opt_utilities
{
  extern std::map<std::string,model<double,double,std::vector<double>,std::string>* > model_map;
  extern std::map<std::string,model<double,vecn<double,2>,std::vector<double>,std::string >* > model2d_map;

  extern strmodel1d strm1d;
  extern std::list<std::string> get_model_name_list();
  extern int get_n_1dmodels();
  //  extern void init_model_map();
  //  extern void release_model_map();
  
  extern std::list<std::string> get_model2d_name_list();
  //  extern void init_model2d_map();
  //  extern void release_model2d_map();
  extern int get_n_2dmodels();
  
  extern model<double,double,std::vector<double>,std::string >& get_1dmodel_by_name(const char*);
  extern  model<double,vecn<double,2>,std::vector<double>,std::string >& get_2dmodel_by_name(const char*);

  extern strmodel1d& get_strm1d();
}


#endif

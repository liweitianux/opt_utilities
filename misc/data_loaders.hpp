#ifndef DATA_LOADERS_H
#define DATA_LOADERS_H
#include <core/fitter.hpp>
#include <data_sets/default_data_set.hpp>
#include <iostream>
#include <fstream>
#include <cmath>

namespace opt_utilities
{
  template <typename Ty,typename Tx>
  class dl_x_y_ye;

  template <typename Ty,typename Tx>
  std::istream& operator>>(std::istream& ifs,dl_x_y_ye<Ty,Tx>& dl);

  template <typename Ty,typename Tx>
  class dl_x_xe_y_ye;

  template <typename Ty,typename Tx>
  std::istream& operator>>(std::istream& ifs,dl_x_xe_y_ye<Ty,Tx>& dl);

  template <typename Ty,typename Tx>
  class dl_x_xu_xl_y_yu_yl;
  
  template <typename Ty,typename Tx>
  std::istream& operator>> (std::istream& ifs,dl_x_xu_xl_y_yu_yl<Ty,Tx>& dl);

  template <typename Ty,typename Tx>
  class dl_x_y_ye
  {
  private:
    default_data_set<Ty,Tx> ds;
  public:
    data_set<Ty,Tx>& get_data_set()
    {
      return ds;
    }

    void load_from(std::istream& ifs)
    {
      for(;;)
	{
	  Tx x;
	  Tx x_err;
	  Ty y;
	  Ty y_err(1);
	  
	  ifs>>x>>y>>y_err;
	  
	  if(!ifs.good())
	    {
	      break;
	    }
	  data<Ty,Tx> d(x,y,y_err,y_err,x_err,x_err);
	  ds.push_back(d);
	}
      //return ifs;
    }

    void load_from(const char* name)
    {
      std::ifstream ifs(name);
      load_from(ifs);

    }
    //friend std::istream& operator>> <>(std::istream& ifs,dl_x_y_ye<Ty,Tx>& dl);
  };

  template <typename Ty,typename Tx>
  std::istream& operator>>(std::istream& ifs,dl_x_y_ye<Ty,Tx>& dl)
  {
    dl.load_from(ifs);
    return ifs;
  }


  template <typename Ty,typename Tx>
  class dl_x_xe_y_ye
  {
  private:
    default_data_set<Ty,Tx> ds;
  public:
    data_set<Ty,Tx>& get_data_set()
    {
      return ds;
    }

    void load_from(std::istream& ifs)
    {
      for(;;)
	{
	  Tx x;
	  Tx x_err;
	  Ty y;
	  Ty y_err(1);
	  
	  ifs>>x>>x_err>>y>>y_err;
	  
	  if(!ifs.good())
	    {
	      break;
	    }
	  data<Ty,Tx> d(x,y,y_err,y_err,x_err,x_err);
	  ds.push_back(d);
	}
    }

    void load_from(const char* name)
    {
      std::ifstream ifs(name);
      load_from(ifs); 
    }
  };

  template <typename Ty,typename Tx>
  std::istream& operator>>(std::istream& ifs,dl_x_xe_y_ye<Ty,Tx>& dl)
  {
    dl.load_from(ifs);
    return ifs;
  }

  template <typename Ty,typename Tx>
  class dl_x_xu_xl_y_yu_yl
  {
  private:
  
    default_data_set<Ty,Tx> ds;
  public:
    data_set<Ty,Tx>& get_data_set()
    {
      return ds;
    }
    
    void load_from(std::istream& ifs)
    {
      for(;;)
	{
	  Tx x;
	  Tx xl,xu;
	  Ty y;
	  Ty yl(1),yu(1);
	  
	  ifs>>x>>xu>>xl>>y>>yu>>yl;
	  
	  xu=std::abs(xu);
	  xl=std::abs(xl);
	  yu=std::abs(yu);
	  yl=std::abs(yl);
	  
	  if(!ifs.good())
	    {
	      break;
	    }
	  data<Ty,Tx> d(x,y,yl,yu,xl,xu);
	  ds.push_back(d);
	}
    }

    void load_from(const char* name)
    {
      std::ifstream ifs(name);
      load_from(ifs);
    }
  };

  template <typename Ty,typename Tx>
  std::istream& operator>> (std::istream& ifs,dl_x_xu_xl_y_yu_yl<Ty,Tx>& dl)
  {
    dl.load_from(ifs);
    return ifs;
  }

  

}


#endif
//EOF

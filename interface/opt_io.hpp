#ifndef OPT_IO
#define OPT_IO
#include <iostream>
#include <cmath>
#include "core/fitter.hpp"


namespace std
{
  template <typename Ty,typename Tx>
  std::ostream& operator<<(std::ostream& os,const opt_utilities::data<Ty,Tx>& d)
  {
    os<<d.get_x()<<"("<<-std::abs(d.get_x_lower_err())<<",+"<<std::abs(d.get_x_upper_err())<<") "<<d.get_y()<<"("<<-std::abs(d.get_y_lower_err())<<",+"<<std::abs(d.get_y_upper_err())<<") ";
    return os;
  }
  
  template <typename Ty,typename Tx>
  std::ostream& operator<<(std::ostream& os,const opt_utilities::data_set<Ty,Tx>& ds)
  {
    os<<"data set with size of "<<ds.size()<<"\n"
      <<"[\n";
    int s=5>ds.size()?ds.size():5;
    for(int i=0;i<s;++i)
      {
	os<<ds.get_data(i)<<"\n";
      }
    os<<"]";
    return os;
  }
}
#endif

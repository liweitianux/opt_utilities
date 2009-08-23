/**
   \file sorted_data_set.hpp
*/

#ifndef SORTED_DATA_SET
#define SORTED_DATA_SET
#include "core/fitter.hpp"
#include <vector>
#include <algorithm>

namespace opt_utilities
{
  
  template <typename Ty,typename Tx>
  bool comp_data(const data<Ty,Tx>& d1,const data<Ty,Tx>& d2)
  {
    return d1.get_x()<d2.get_x();
  }



  /**
     \brief automatically sorting data set
     \tparam Ty type of y
     \tparam Tx type of x
   */
  template <typename Ty,typename Tx>
  class sorted_data_set
    :public data_set<Ty,Tx>
  {
  private:
    std::vector<data<Ty,Tx> > data_vec;
    
    data_set<Ty,Tx>* do_clone()const
    {
      return new sorted_data_set<Ty,Tx>(*this);
    }
    
    
    const data<Ty,Tx>& do_get_data(size_t i)const
    {
      return data_vec.at(i);
    }
    
    size_t do_size()const
    {
      return data_vec.size();
    }
    
    void do_add_data(const data<Ty,Tx>& d)
    {
      typename std::vector<data<Ty,Tx> >::iterator p
	=std::lower_bound(data_vec.begin(),data_vec.end(),d,comp_data<Ty,Tx>);
      //data_vec.push_back(d);
      data_vec.insert(p,d);
    }
    
    void do_clear()
    {
      data_vec.clear();
    }
    
  };
}

#endif
//EOF

/**
   \file default_data_set.hpp
 */

#ifndef DEFAULT_DATA_SET
#define DEFAULT_DATA_SET
#define OPT_HEADER
#include "core/fitter.hpp"
#include <vector>


namespace opt_utilities
{

  /**
     \brief default implement of the data set
     \tparam Ty type of y
     \tparam Tx type of x
   */
  template <typename Ty,typename Tx>
  class default_data_set
    :public data_set<Ty,Tx>
  {
    //  private:
  public:
    std::vector<data<Ty,Tx> > data_vec;
    
    data_set<Ty,Tx>* do_clone()const
    {
      return new default_data_set<Ty,Tx>(*this);
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
      data_vec.push_back(d);
    }
  
    void do_clear()
    {
      data_vec.clear();
    }

  public:
    default_data_set()
    {}
    
    default_data_set(const default_data_set<Ty,Tx>& rhs)
      :data_vec(rhs.data_vec)
    {}

    default_data_set(const data_set<Ty,Tx>& rhs)
    {
      data_vec.resize(rhs.size());
      for(int i=0;i<data_vec.size();++i)
	{
	  data_vec[i](rhs.get_data(i));
	}
    }

    default_data_set& operator=(const default_data_set<Ty,Tx>& rhs)
    {
      data_vec=rhs.data_vec;
      return *this;
    }

    default_data_set& operator=(const data_set<Ty,Tx>& rhs)
    {
      data_vec.resize(rhs.size());
      for(int i=0;i<data_vec.size();++i)
	{
	  data_vec[i](rhs.get_data(i));
	}
      return *this;
    }

    
  };
}

#endif
//EOF

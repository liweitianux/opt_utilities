#ifndef DEFAULT_DATA_SET
#define DEFAULT_DATA_SET
#include "fitter.hpp"
#include <vector>


namespace opt_utilities
{

template <typename Ty,typename Tx>
class default_data_set
  :public data_set<Ty,Tx>
{
private:
  std::vector<data<Ty,Tx> > data_vec;

  data_set<Ty,Tx>* do_clone()const
  {
    return new default_data_set<Ty,Tx>(*this);
  }


  const data<Ty,Tx>& do_get_data(int i)const
  {
    return data_vec.at(i);
  }
  
  int do_size()const
  {
    return data_vec.size();
  }
  
  void do_push_back(const data<Ty,Tx>& d)
  {
    data_vec.push_back(d);
  }
  
  void do_clear()
  {
    data_vec.clear();
  }
  
};
}

#endif
//EOF

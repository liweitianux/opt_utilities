#ifndef VECTOR_OPERATION_HPP
#define VECTOR_OPERATION_HPP
#include <core/opt_traits.hpp>

template <typename pT>
typename element_type_trait<pT>::element_type
inner_product(const pT& v1,const pT& v2)
{
  typename element_type_trait<pT>::element_type result;
  for(int i=0;i<get_size(v1);++i)
    {
      result+=get_element(v1,i)*get_element(v2,i);
    }
  return result;
}


#endif

#ifndef ARRAY_OPERATION
#define ARRAY_OPERATION
#include <cstddef>
namespace opt_utilities
{
  /////////Useful function///////////////////////////////////
  template <typename T>
  inline size_t get_size(const T& x)
  {
    return x.size();
  }
  
  template <typename T>
  class element_type_trait
  {
  public:
    typedef typename T::value_type element_type;
  };

  template <typename T>
  class return_type_trait
  {
  public:
    typedef T value_type;
    typedef T& reference_type;
    typedef const T& const_reference_type;
  };
  
  template <typename T>
  inline typename return_type_trait<typename element_type_trait<T>::element_type>::const_reference_type get_element(const T& x,size_t i)
  {
    return x[i];
  }
  /*
  template <typename T>
  inline typename element_type_trait<T>::element_type& get_element(T& x,size_t i)
  {
    return x[i];
  }
  */

  template<typename T,typename TX>
  inline void set_element(T& x,size_t i,
			  const TX& v)
  {
    x[i]=v;
  }

  template <typename T>
  inline void resize(T& x,size_t s)
  {
    x.resize(s);
  }

  template <typename Tl,typename Tr>
  inline Tl& opt_eq(Tl& lhs,const Tr& rhs)
  {
    return (lhs=rhs);
  }
};



#endif

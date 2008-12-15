#ifndef BAS_UTIL
#define BAS_UTIL
#include <core/opt_traits.hpp>
namespace opt_utilities
{
  template <typename T>
  T tabs(T x)
  {
    return T(x)<T(0)?T(-x):T(x);
  }

  template <typename T>
  T sqr(T x)
  {
    return x*x;
  }
  
  
  template <typename T>
  void shft3(T&a,T& b,T& c,T d)
  {
    opt_eq(a,b);
    opt_eq(b,c);
    opt_eq(c,d);
  }

  template <typename T>
  void shft(T& a,T& b,T& c,T d)
  {
    opt_eq(a,b);
    opt_eq(b,c);
    opt_eq(c,d);
  }
  template <typename T>  
  void swap(T& ax,T& bx)
  {
    //  swap(ax,bx);
    T temp;
    opt_eq(temp,ax);
    opt_eq(ax,bx);
    opt_eq(bx=temp);
  }
  
  template <typename T>
  T sign(const T& a,const T& b)
  {
    return b>=0?T(a>=0?T(a):T(-a)):T(a>=0?T(-a):T(a));
  }
  
  template <typename T>
  T max(T a,T b)
  {
    return b>a?T(b):T(a);
  }

  template <typename T>
  void mov3(T& a,T& b,T& c, T& d,T& e,T& f)
  {
    opt_eq(a,d);opt_eq(b,e);opt_eq(c,f);
  }
}

#endif

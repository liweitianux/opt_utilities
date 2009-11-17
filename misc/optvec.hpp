#ifndef OPTVEC_HPP
#define OPTVEC_HPP

#include <vector>
#include <cassert>

namespace opt_utilities
{
  template <typename T>
  class optvec
    :public std::vector<T>
  {
  public:
    optvec()
    {}

    optvec(size_t s)
      :std::vector<T>(s)
    {}

    optvec(const std::vector<T>& rhs)
      :std::vector<T>(rhs)
    {}

    optvec& operator=(const optvec& rhs)
    {
      //dynamic_cast<std::vector<T>&>(*this).operator=(rhs);
      std::vector<T>::operator=(rhs);
      return *this;
    }
  public:
    operator std::vector<T>& ()
    {
      return dynamic_cast<std::vector<T>&>(*this);
    }
    
    operator const std::vector<T>& ()const
    {
      return dynamic_cast<const std::vector<T>&>(*this);
    }
  };

  template<typename T>
  optvec<T> operator+(const optvec<T>& x1,const optvec<T>& x2)
  {
    
    optvec<T> result(x1);
    for(size_t i=0;i!=x1.size();++i)
      {
	result[i]=result[i]+x2.at(i);
      }
    return result;
  }

  template<typename T>
  optvec<T> operator-(const optvec<T>& x1,const optvec<T>& x2)
  {
    
    optvec<T> result(x1);
    for(size_t i=0;i!=x1.size();++i)
      {
	result[i]=result[i]-x2.at(i);
      }
    return result;
  }
  
  template<typename T>
  optvec<T> operator*(const optvec<T>& x1,const optvec<T>& x2)
  {
    
    optvec<T> result(x1);
    for(size_t i=0;i!=x1.size();++i)
      {
	result[i]=result[i]*x2.at(i);
      }
    return result;
  }

  template<typename T>
  optvec<T> operator/(const optvec<T>& x1,const optvec<T>& x2)
  {
    
    optvec<T> result(x1);
    for(size_t i=0;i!=x1.size();++i)
      {
	result[i]=result[i]/x2.at(i);
      }
    return result;
  }

  template <typename T>
  T sum(const optvec<T>& x)
  {
    T result=0;
    for(size_t i=0;i!=x.size();++i)
      {
	result+=x[i];
      }
    return result;
  }
  
  template<typename T>
  bool operator<(const optvec<T>& x1,const optvec<T>& x2)
  {
    for(size_t i=0;i!=x1.size();++i)
      {
	if(x1[i]!=x2[i])
	  {
	    return x1[i]<x2[i];
	  }
      }
    return false;
  }
  
};
#endif

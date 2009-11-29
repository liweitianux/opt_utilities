#ifndef OPTVEC_HPP
#define OPTVEC_HPP

#include <vector>
#include <cassert>
#include <cmath>

namespace opt_utilities
{
  template <typename T>
  class optvec
    :public std::vector<T>
  {
  public:
    optvec()
    {}
    
    explicit optvec(size_t s)
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
    
    optvec<T> result(x1.size());
    for(size_t i=0;i!=x1.size();++i)
      {
	result[i]=x1[i]+x2.at(i);
      }
    return result;
  }

  template<typename T>
  optvec<T> operator+(const optvec<T>& x1,const T& x2)
  {
    
    optvec<T> result(x1.size());
    for(size_t i=0;i!=x1.size();++i)
      {
	result[i]=x1[i]+x2;
      }
    return result;
  }

  template<typename T>
  optvec<T>& operator+=(optvec<T>& x1,const optvec<T>& x2)
  {
    for(size_t i=0;i!=x1.size();++i)
      {
	x1[i]+=x2.at(i);
      }
    return x1;
  }

  template<typename T>
  optvec<T> operator-(const optvec<T>& x1,const optvec<T>& x2)
  {
    
    optvec<T> result(x1.size());
    for(size_t i=0;i!=x1.size();++i)
      {
	result[i]=x1[i]-x2.at(i);
      }
    return result;
  }

  template<typename T>
  optvec<T> operator-(const optvec<T>& x1,const T& x2)
  {
    
    optvec<T> result(x1.size());
    for(size_t i=0;i!=x1.size();++i)
      {
	result[i]=x1[i]-x2;
      }
    return result;
  }  
  
  template<typename T>
  optvec<T> operator-(const optvec<T>& x1)
  {
    
    optvec<T> result(x1.size());
    for(size_t i=0;i!=x1.size();++i)
      {
	result[i]=-x1[i];
      }
    return result;
  }
  
  
  template<typename T>
  optvec<T>& operator-=(optvec<T>& x1,const optvec<T>& x2)
  {
    for(size_t i=0;i!=x1.size();++i)
      {
	x1[i]-=x2.at(i);
      }
    return x1;
  }

  template<typename T>
  optvec<T> operator*(const optvec<T>& x1,const optvec<T>& x2)
  {
    
    optvec<T> result(x1.size());
    for(size_t i=0;i!=x1.size();++i)
      {
	result[i]=x1[i]*x2.at(i);
      }
    return result;
  }

  template<typename T>
  optvec<T> operator*(const optvec<T>& x1,const T& x2)
  {
    
    optvec<T> result(x1.size());
    for(size_t i=0;i!=x1.size();++i)
      {
	result[i]=x1[i]*x2;
      }
    return result;
  }

  template<typename T>
  optvec<T> operator*(const T& x1,const optvec<T>& x2)
  {
    
    optvec<T> result(x2.size());
    for(size_t i=0;i!=x2.size();++i)
      {
	result[i]=x2[i]*x1;
      }
    return result;
  }
  

  template<typename T>
  optvec<T>& operator*=(optvec<T>& x1,const optvec<T>& x2)
  {
    for(size_t i=0;i!=x1.size();++i)
      {
	x1[i]*=x2.at(i);
      }
    return x1;
  }

  template<typename T>
  optvec<T>& operator*=(optvec<T>& x1,const T& x2)
  {
    for(size_t i=0;i!=x1.size();++i)
      {
	x1[i]*=x2;
      }
    return x1;
  }
  

  template<typename T>
  optvec<T> operator/(const optvec<T>& x1,const optvec<T>& x2)
  {
    
    optvec<T> result(x1.size());
    for(size_t i=0;i!=x1.size();++i)
      {
	result[i]=x1[i]/x2.at(i);
      }
    return result;
  }
  
  template<typename T>
  optvec<T> operator/(const optvec<T>& x1,const T& x2)
  {
    
    optvec<T> result(x1.size());
    for(size_t i=0;i!=x1.size();++i)
      {
	result[i]=x1[i]/x2;
      }
    return result;
  }

  template<typename T>
  optvec<T> operator/(const T& x1,const optvec<T>& x2)
  {
    
    optvec<T> result(x1.size());
    for(size_t i=0;i!=x1.size();++i)
      {
	result[i]=x1/x2[i];
      }
    return result;
  }

  template<typename T>
  optvec<T>& operator/=(optvec<T>& x1,const optvec<T>& x2)
  {
    for(size_t i=0;i!=x1.size();++i)
      {
	x1[i]/=x2.at(i);
      }
    return x1;
  }

  template<typename T>
  optvec<T>& operator/=(optvec<T>& x1,const T& x2)
  {
    for(size_t i=0;i!=x1.size();++i)
      {
	x1[i]/=x2;
      }
    return x1;
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


#define DEF_VEC_FUNC(_func) template <typename T>		\
  opt_utilities::optvec<T> _func(const opt_utilities::optvec<T>& x)	\
  {								\
    opt_utilities::optvec<T> result(x.size());		\
    for(int i=0;i!=result.size();++i)				\
      {								\
	result[i]=_func(x[i]);					\
      }								\
    return result;						\
  }

namespace std
{
  DEF_VEC_FUNC(sin);
  DEF_VEC_FUNC(cos);
  DEF_VEC_FUNC(log);
  DEF_VEC_FUNC(sqrt);
  DEF_VEC_FUNC(exp);
  template<typename T>
  opt_utilities::optvec<T> pow(const opt_utilities::optvec<T>& x,const T& y)
  {
    opt_utilities::optvec<T> result(x.size()); 
    for(int i=0;i!=result.size();++i)	       
      {			
	result[i]=pow(x[i],y);
      }
    return result;	
  }

}


#endif

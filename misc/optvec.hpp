#include <vector>

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
};

#include "optimizer.hpp"
#include "powell_method.hpp"
#include "add_model.hpp"
#include "lin1d.hpp"
#include "poly1d.hpp"
#include "data_loaders.hpp"
#include "chisq.hpp"
#include "freeze_param.hpp"
#include "add_model.hpp"
#include "mul_model.hpp"
#include "pow_model.hpp"
#include "gsl_simplex.hpp"
#include "pl1d.hpp"
using namespace std;
#include "dl_model.hpp"
#include <fstream>
#include <vector>
//#include "gmpxx.h"
#include "strmodel1d.hpp"
using namespace std;
using namespace opt_utilities;

class foo
  :public func_obj<double,vector<double> >
{
public:
  double do_eval(const vector<double>& p)
  {
    //   cout<<"p0="<<p[0]<<endl;
    return p[0]*p[0]+p[1]*p[1];
  }

  foo* do_clone()const
  {
    return new foo(*this);
  }
};


double my_f (const gsl_vector *v, void *params)
{
  double x, y;
  double *p = (double *)params;
  //  cout<<p[1]<<endl;
  x = gsl_vector_get(v, 0);
  y = gsl_vector_get(v, 1);
  
  return x*x+y*y;
}





int main()
{
  
  optimizer<double,vector<double> > op;
  powell_method<double,vector<double> > pw;
  gsl_simplex<double,vector<double> > gs;

  op.set_func_obj(foo());
  op.set_opt_method(gs);
  vector<double> p1(2);
  p1[0]=1;
  p1[1]=1;
  op.set_start_point(p1);
  
  vector<double> p=op.optimize();
  cout<<p[0]<<"\t"<<p[1]<<endl;
  
  return 0;


  
  const gsl_multimin_fminimizer_type *T = 
    gsl_multimin_fminimizer_nmsimplex;
  gsl_multimin_fminimizer *s = NULL;
  gsl_vector *ss, *x;
  gsl_multimin_function minex_func;
  
  size_t iter = 0;
  int status;
  double size;
     
  /* Starting point */
  x = gsl_vector_alloc (2);
  gsl_vector_set (x, 0, 5.0);
  gsl_vector_set (x, 1, 7.0);
     
  /* Set initial step sizes to 1 */
  ss = gsl_vector_alloc (2);
  gsl_vector_set_all (ss, 1.0);
  foo f;
  /* Initialize method and iterate */
  minex_func.n = 2;
  minex_func.f = &gsl_func_adapter<double,vector<double> >;
  minex_func.params = (void *)&f;
     
  s = gsl_multimin_fminimizer_alloc (T, 2);
  gsl_multimin_fminimizer_set (s, &minex_func, x, ss);
  
  do
    {
      iter++;
      status = gsl_multimin_fminimizer_iterate(s);
           
      if (status) 
	break;
     
      size = gsl_multimin_fminimizer_size (s);
      status = gsl_multimin_test_size (size, 1e-2);
     
      if (status == GSL_SUCCESS)
	{
	  printf ("converged to minimum at\n");
	}
     
      printf ("%5d %10.3e %10.3ef f() = %7.3f size = %.3f\n", 
	      iter,
	      gsl_vector_get (s->x, 0), 
	      gsl_vector_get (s->x, 1), 
	      s->fval, size);
    }
  while (status == GSL_CONTINUE && iter < 100);
  
  /*
  foo f;
  gsl_vector_set (x, 0, 0.0);
  gsl_vector_set (x, 1, 0.0);
  cout<<"fdsa ";
  cout<<gsl_func_adapter<double,vector<double> >(x,(void*)&f)<<endl;;

  */

  gsl_vector_free(x);
  gsl_vector_free(ss);
  gsl_multimin_fminimizer_free (s);
     
  



  return status;


  
}


#ifndef OPT_H
#define OPT_H
//#define F77
#ifdef F77
#define alloc_fit_ alloc_fit__
#define free_fit_ free_fit__
#define load_data_ load_data__
#define set_model_ set_model__
#define set_param_ set_param__
#define freeze_param_ freeze_param__
#define thraw_param_ thraw_param__
#define perform_fit_ perform_fit__
#define get_param_ get_param__
#endif

extern "C"
{
  int alloc_fit_(int&);
  int free_fit_(const int& nxc);
  int load_data_(const int& nfit,const int& ndatas,double* x,double* y,double* yl,double* yu=0,double* xl=0,double* xu=0);
  int set_model_(const int& nfit,const char* model_name);
  int set_param_(const int& nfit,const char* param_name,const double& value);
  int freeze_param_(const int& nfit,const char* param_name);
  int thraw_param_(const int& nfit,const char* param_name);
  int perform_fit_(const int& nfit);
  int get_param_(const int& nfit,double& r,const char* param_name);
}

#endif

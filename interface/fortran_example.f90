function foo(p)
  double precision foo
  double precision p(2)
  foo=p(1)**2+p(2)**2;
  return
end function foo
  

program main
  double precision foo
  double precision p(2)
  integer np
  double precision precision
  np=2
  precision=1e-10
  p(1)=4000
  p(2)=5000
  write(*,*) p,foo(p)
  call optimize_powell(foo,np,p,precision)
  write(*,*) p,foo(p)
end program main

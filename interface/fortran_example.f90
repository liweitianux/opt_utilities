function foo(p)
  double precision foo
  double precision p(2)
  foo=p(1)**2+p(2)**2;
  return
end function foo
  

program main
  double precision foo
  double precision p(2)
  p(1)=4
  p(2)=5
  write(*,*) p,foo(p)
  call optimize_powell(foo,2,p,1E-10)
  write(*,*) p,foo(p)
end program main

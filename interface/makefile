INC=-I../


libopt.a:opt.o
	$(AR) $@ opt.o

opt.o:opt.cc opt.h
	$(CPP) $< -o $@ $(INC) $(CPPFLAGS)


clean:
	$(RM) *.o
	$(RM) *~

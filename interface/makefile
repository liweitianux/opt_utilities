target: libopt.a
INC=-I../


libopt.a:opt.o
	$(AR) rv $@ opt.o

opt.o:opt.cc opt.h
	$(CXX) $< -o $@ $(INC) $(CXXFLAGS) -c


clean:
	$(RM) *.o
	$(RM) *~

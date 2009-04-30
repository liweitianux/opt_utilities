INC=-I../


libopt.a:opt.o
	$(AR) $@ opt.o

opt.o:opt.cc opt.h
	$(CXX) $< -o $@ $(INC) $(CXXFLAGS)


clean:
	$(RM) *.o
	$(RM) *~

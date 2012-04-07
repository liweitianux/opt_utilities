targets=test_optimizer many_dims test_fitter test_cg

all:$(targets)

test_optimizer:test_optimizer.cpp
	$(CXX) $< -o $@ -I .. -O3 -g

many_dims:many_dims.cpp
	$(CXX) $< -o $@ -I .. -O3 -g -p

test_fitter:test_fitter.cpp
	$(CXX) $< -o $@ -I .. -O3 -g

test_cg:test_cg.cpp
	$(CXX) $< -o $@ -I .. -O3 -g

clean:
	rm -f $(targets) *.o *~

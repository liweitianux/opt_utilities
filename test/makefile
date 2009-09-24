targets=test_optimizer many_dims

all:$(targets)

test_optimizer:test_optimizer.cpp
	$(CXX) $< -o $@ -I .. -O3 -g

many_dims:many_dims.cpp
	$(CXX) $< -o $@ -I .. -O3 -g


clean:
	rm -f $(targets) *.o *~

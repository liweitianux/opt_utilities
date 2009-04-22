targets=test_optimizer

all:$(targets)

test_optimizer:test_optimizer.cpp
	g++ $< -o $@ -I .. -O3


clean:
	rm -f $(targets) *.o *~

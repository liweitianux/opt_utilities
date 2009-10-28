target=test_optimizer test_fitter

all:$(target)


test_optimizer:test_optimizer.cpp
	g++ -o $@ $< -I ../ -O3 -g

test_fitter:test_fitter.cpp
	g++ -o $@ $< -I ../ -O3 -g

clean:
	rm -f $(target)

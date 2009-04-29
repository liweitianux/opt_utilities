OPT_HEADS=models/beta1d.hpp  statistics/chisq.hpp    models/lin1d.hpp\
      models/pl1d.hpp models/bl1d.hpp\
	statistics/leastsq.hpp\
	core/fitter.hpp models/models.hpp\
	core/opt_traits.hpp\
	methods/powell/powell_method.hpp models/bpl1d.hpp\
	core/freeze_param.hpp\
	models/gauss1d.hpp core/optimizer.hpp\
	misc/bootstrap.hpp\
	models/dl_model.hpp\
	models/mul_model.hpp\
	models/add_model.hpp\

LDL=-ldl

export CPP=g++
export CC=gcc
export AR = ar rv
export RANLIB = ranlib
export RM=rm -f
export CFLAGS=-DNDEBUG -ansi -pedantic -g -O2 -Wall -c -I .
export CPPFLAGS=-DNDEBUG -ansi -pedantic -g -O2 -Wall -c -I . -DHAVE_X_ERROR


INC=-I. -I/usr/include/gsl/
LIB= -L./muparser  $(LDL) -lmuparser -g -lgsl -lgslcblas
OPT_OBJ=models/models.o version_ctrl.o models/strmodel1d.o

TARGET=liboptcall test_dl.so models/strmodel1d.o models/models.o

all: $(TARGET)

models/models.o:models/models.cc ${OPT_HEADS}
	$(CPP) -c $< -o $@ ${INC} ${CPPFLAGS}

version_ctrl.o:version_ctrl.cc
	$(CPP) -c $< ${CPPFLAGS}

bin/test.o:test.cc ${OPT_HEADS}
	$(CPP) -c $< -o $@ ${INC} ${CPPFLAGS} --ansi

test:${OPT_OBJ} bin/test.o
	$(CPP) bin/test.o models/strmodel1d.o models/models.o version_ctrl.o -o $@ ${LIB}

test_dl.so:models/dlmodel_template.c
	$(CC) $< --shared -o $@


models/strmodel1d.o:models/strmodel1d.cc models/strmodel1d.hpp
	$(CPP) -c $< -o $@ -I./muparser $(INC) $(CPPFLAGS)


libmuparser:
	make -C muparser

liboptcall:
	make -C interface

clean:
	rm -f `find .|grep \~`
	rm -f `find .|grep '\.o'`
	rm -f muparser/libmuparser.a
	make -C muparser clean
	make -C interface clean

distclean:clean
	rm -f `find . -iname *.a`
	rm -f $(TARGET)

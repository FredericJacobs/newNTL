SRCS=$(wildcard *.cpp)
EXE=$(patsubst %.cpp,%,${SRCS})

all: ${EXE}

lib:
	make -C ../src clean
	make -C ../src newntl.a


clean:
	rm ${EXE}

%: %.cpp
	g++ -O0 -g3 -Wall -fopenmp -o $@ $< -I../include/  ../src/newntl.a -lfplll -lmpfr -lgmp -lm
	
bak:
	g++ -O2 -Wall -o $@ $< -I../include/  ../src/newntl.a ../../libfplll-new/src/.libs/libfplll.a -lmpfr -lgmp -lm

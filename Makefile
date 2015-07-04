LIBS=-lcppcms -lbooster


all: fms

fms: main.cpp
	$(CXX) -O2 -Wall -g main.cpp Admin.cpp -o fms.out -std=c++0x ${LIBS} -fpermissive

clean:
	rm -fr fms.out fms.exe cppcms_rundir

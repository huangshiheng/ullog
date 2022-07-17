cc=g++
all:clean log.o
	mkdir output
	mkdir output/include
	mkdir output/lib
	mkdir output/demo
	ar crv liblog.a log.o
	mv liblog.a output/lib
	cp include/log.h output/include
	${cc} -o read_log demo/read_log.cpp -I output/include -L output/lib -llog -lpthread -std=c++11
	mv read_log output/demo/
	cp demo/log.conf output/demo/
	rm log.o
log.o:
	${cc} -c src/log.cpp -std=c++11
clean:
	rm -rf output read_log log.o

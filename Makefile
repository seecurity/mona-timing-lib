all:
	@echo "please start with 'make linux' or 'make osx' depending which os you're running"

linux:
	swig -python fau_timer.i
	gcc -fPIC -c fau_timer.c fau_timer_wrap.c -I/usr/include/python2.7
	ld -shared fau_timer.o fau_timer_wrap.o -o _fau_timer.so 

osx:
	swig -python fau_timer.i
	python setup.py build_ext --inplace

clean:
	rm -f fau_timer *.o *.so

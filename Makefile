all: clean
	mkdir ./build
	gcc -o ./build/off2lua -g -pg main.c

clean:
	rm -Rf ./build
	rm -f gmon.out
	rm -f *.lua
	rm -f a.txt

test:
	 ./build/off2lua ~/Documents/3d\ models/teapot.off teapot.lua teapot
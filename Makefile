all: clean
	mkdir ./build
	gcc -o ./build/off2lua -g main.c

clean:
	rm -Rf ./build

test:
	 ./build/off2lua ~/Documents/3d\ models/teapot.off teapot.lua teapot
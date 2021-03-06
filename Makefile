all: clean
	mkdir ./build
	gcc -o ./build/off2lua -g -pg main.c

clean:
	rm -Rf ./build
	rm -f gmon.out
	rm -f *.lua
	rm -f a.txt

install:
	install ./build/off2lua /usr/local/bin/off2lua

#cross compile for windows from linux
windows:
	x86_64-w64-mingw32-gcc  -o ./build/off2lua.exe -g -pg main.c

test:
	 ./build/off2lua ~/Documents/3d\ models/teapot.off teapot.lua teapot
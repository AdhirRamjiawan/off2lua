all: clean
	mkdir ./build
	gcc -o ./build/off2lua main.c

clean:
	rm -Rf ./build